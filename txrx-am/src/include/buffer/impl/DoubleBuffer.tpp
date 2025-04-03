#pragma once

#include <algorithm>
#include <stdexcept>
#include <fmt/format.h>
#include <cstring>

// Конструктор с проверкой нулевой емкости
template <BufferCompatible _DT>
DoubleBuffer<_DT>::DoubleBuffer(const size_t capacity, std::unique_ptr<_DT[]> buffer)
    : buffer_(std::move(buffer)),
      capacity_(capacity),
      buff_idx_center_(capacity / 2),
      idx_rd_(0),
      idx_wd_(buff_idx_center_) 
{
    /**
     * Проверка валидности емкости буфера
     * Если capacity == 0, буфер не может быть использован
     */
    if (capacity_ == 0) {
        throw std::invalid_argument("Capacity cannot be zero");
    }
}

// Фабричный метод с обработкой ошибок выделения памяти
template <BufferCompatible _DT>
std::optional<DoubleBuffer<_DT>> DoubleBuffer<_DT>::Create(size_t capacity) {
    try {
        /**
         * Попытка выделить память для буфера
         * В случае неудачи std::make_unique бросит std::bad_alloc
         */
        auto buffer = std::make_unique<_DT[]>(capacity);
        return std::optional<DoubleBuffer<_DT>>(std::in_place, capacity, std::move(buffer));
    } catch (...) {
        // Возвращаем пустой optional при любой ошибке
        return std::nullopt;
    }
}

// Переключение между буферами чтения/записи
template <BufferCompatible _DT>
void DoubleBuffer<_DT>::buff_switch() {
    /**
     * 1) [r,r,r,r,r|w,w,w,w,w] 
     * 2) [w,w,w,w,w|r,r,r,r,r]
     *                       _  --idx 
     * 3) [r,r,r,r,r|w,w,w,w,w]
     *             _ --idx
     */
    std::lock_guard<std::mutex> lock(switch_mutex_);
    idx_rd_.store(buff_idx_center_, std::memory_order_release);
    idx_wd_.store(0, std::memory_order_release);
    std::atomic_thread_fence(std::memory_order_seq_cst);
}

// Добавление элемента в буфер записи
template <BufferCompatible _DT>
[[nodiscard]] int8_t DoubleBuffer<_DT>::Push(const _DT& data) {
    /**
     * Условие заполненности [w]:
     *  (Указатель достиг конца)
     * Если [w] область заполнена, а [r] - пуста
     * То мы делаем buff_switch
     */
    std::lock_guard<std::mutex> lock(write_mutex_);
    
    if (AvailableSizeWD() == 0) {
        const size_t rd_idx = idx_rd_.load(std::memory_order_acquire);
        if (rd_idx == 0) {
            std::lock_guard<std::mutex> switch_lock(switch_mutex_);
            buff_switch();
            if (AvailableSizeWD() == 0) return BUFFER_WD_IS_FILLED;
        } else {
            return BUFFER_WD_IS_FILLED;
        }
    }
    
    const size_t wd_idx = idx_wd_.load(std::memory_order_relaxed);
    buffer_[wd_idx] = data;
    idx_wd_.store(wd_idx + 1, std::memory_order_release);
    return OP_SUCCESS;
}

// Извлечение элемента из буфера чтения с RVO
template <BufferCompatible _DT>
[[nodiscard]] _DT DoubleBuffer<_DT>::Pull() {
    /**
     * Условие пустоты [r]:
     *  Указатель находится в начале (пуст)
     *  Указатель находится в конце (всё прочитал и пуст)
     */
    std::lock_guard<std::mutex> lock(read_mutex_);
    
    if (AvailableSizeRD() == 0) {
        std::lock_guard<std::mutex> switch_lock(switch_mutex_);
        buff_switch();
        if (AvailableSizeRD() == 0) return _DT{};
    }

    const size_t rd_idx = idx_rd_.load(std::memory_order_relaxed);
    _DT result = std::move(buffer_[rd_idx]);
    idx_rd_.store(rd_idx + 1, std::memory_order_release);
    return result;
}

// Прямое чтение данных (ZeroCopy)
template <BufferCompatible _DT>
[[nodiscard]] int8_t DoubleBuffer<_DT>::DirectPull(_DT* dest, size_t size, bool copy) {
    /**
     * DMA Implementation
     * Используется для быстрого копирования блоков данных
     */
    if (!dest) return INVALID_POINTER;
    
    std::lock_guard<std::mutex> lock(read_mutex_);
    
    size_t available = AvailableSizeRD();
    if (available == 0) {
        std::lock_guard<std::mutex> switch_lock(switch_mutex_);
        buff_switch();
        available = AvailableSizeRD();
        if (available == 0) return BUFFER_RD_IS_EMPTY;
    }
    
    if (available < size) return INSUFFICIENT_ELEMENTS;
    
    const size_t rd_idx = idx_rd_.load(std::memory_order_relaxed);
    
    if constexpr (std::is_trivially_copyable_v<_DT>) {
        std::memcpy(dest, &buffer_[rd_idx], size * sizeof(_DT));
    } else {
        std::copy_n(&buffer_[rd_idx], size, dest);
    }
    
    if (!copy) {
        idx_rd_.store(rd_idx + size, std::memory_order_release);
    }
    
    return OP_SUCCESS;
}

// Прямая запись данных (ZeroCopy)
template <BufferCompatible _DT>
[[nodiscard]] int8_t DoubleBuffer<_DT>::DirectPush(_DT* src, size_t size) {
    /**
     * DMA Implementation
     * Оптимизированное копирование для больших блоков
     */
    if (!src) return INVALID_POINTER;
    
    std::lock_guard<std::mutex> lock(write_mutex_);
    
    if (AvailableSizeWD() == 0) {
        const size_t rd_idx = idx_rd_.load(std::memory_order_acquire);
        if (rd_idx == 0) {
            std::lock_guard<std::mutex> switch_lock(switch_mutex_);
            buff_switch();
            if (AvailableSizeWD() == 0) return BUFFER_WD_IS_FILLED;
        } else {
            return BUFFER_WD_IS_FILLED;
        }
    }
    
    if (AvailableSizeWD() < size) return INSUFFICIENT_SPACE;
    
    const size_t wd_idx = idx_wd_.load(std::memory_order_relaxed);
    
    if constexpr (std::is_trivially_copyable_v<_DT>) {
        std::memcpy(&buffer_[wd_idx], src, size * sizeof(_DT));
    } else {
        std::copy_n(src, size, &buffer_[wd_idx]);
    }
    
    idx_wd_.store(wd_idx + size, std::memory_order_release);
    return OP_SUCCESS;
}

// Расчет доступного места для записи
template <BufferCompatible _DT>
size_t DoubleBuffer<_DT>::AvailableSizeWD() {
    /**
     * [_,_,_,(_ptr_wd),e,e,|(buff_center_)]
     * Заполнено 3 ячейки, следующая запись на 4ой
     */
    const size_t wd_idx = idx_wd_.load(std::memory_order_acquire);
    return (wd_idx >= buff_idx_center_) 
        ? (capacity_ - wd_idx)
        : (buff_idx_center_ - wd_idx);
}

// Расчет доступных данных для чтения
template <BufferCompatible _DT>
size_t DoubleBuffer<_DT>::AvailableSizeRD() {
    /**
     * Условие пустоты [r]:
     *  Указатель находится в начале (пуст)
     *  Указатель находится в конце (всё прочитал и пуст)
     */
    const size_t rd_idx = idx_rd_.load(std::memory_order_acquire);
    return (rd_idx >= buff_idx_center_)
        ? (capacity_ - rd_idx)
        : (buff_idx_center_ - rd_idx);
}

// Соотношение свободного/занятого места
template <BufferCompatible _DT>
float DoubleBuffer<_DT>::RatioBetween() {
    /**
     * Соотношение RD/WD используется для балансировки
     * производительности чтения/записи
     */
    const size_t wd_size = AvailableSizeWD();
    return wd_size ? static_cast<float>(AvailableSizeRD()) / wd_size : 0.0f;
}
