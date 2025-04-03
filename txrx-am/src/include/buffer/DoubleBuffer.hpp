#pragma once 

#include <atomic> 
#include <memory>
#include <mutex>
#include <optional>
#include <concepts>
#include <span>
#include <format>

/**
 *  <Что-зачем-почему>
 *  
 *  
 */
template <typename T> 
concept BufferCompatible = std::is_object_v<T> && 
                            (std::is_trivially_copyable_v<T> ||
                            std::is_copy_constructible_v<T>);

/**
 * IO буфер, где массив длинной N 
 * делится на 2 части: 
 *  1) Для записи
 *  2) Для чтения
 */
template <BufferCompatible _DT>
class DoubleBuffer { 
public: 
    enum { 
        OP_SUCCESS              =  1, 
        OUT_OF_RANGE            = -1,
        BUFFER_WD_IS_FILLED     = -2,
        BUFFER_RD_IS_EMPTY      = -3, 
        INSUFFICIENT_ELEMENTS   = -4, 
        INSUFFICIENT_SPACE      = -5, 
        INVALID_POINTER         = -6
    };
    /**
     * 
     */
    explicit DoubleBuffer(const size_t capacity, std::unique_ptr<_DT[]> buffer);
    
    /**
     * 
     */
    ~DoubleBuffer() = default;

    /**
     * 
     */
    static std::optional<DoubleBuffer<_DT>> Create(size_t capacity);

    /**
     * 
     */
    DoubleBuffer(const DoubleBuffer&) = delete;
    DoubleBuffer& operator=(const DoubleBuffer&) = delete;
    DoubleBuffer(DoubleBuffer&&) noexcept = default;
    DoubleBuffer& operator=(DoubleBuffer&&) noexcept = default;

    /**
     * 
     */
    [[nodiscard]] int8_t Push(const _DT& data);  

    /**
     *  Add RVO?
     */
    [[nodiscard]] _DT Pull();
    
    
    /**
     * ZeroCopy
     */
    [[nodiscard]] int8_t DirectPull(_DT* val, size_t size, bool copy);

    /**
     * ZeroCopy
     */
    [[nodiscard]] int8_t DirectPush(_DT* val, size_t size);

    /**
     * 
     */
    inline size_t AvailableSizeWD();

    /**
     * 
     */
    inline size_t AvailableSizeRD(); 

    /**
     * 
     */
    inline float RatioBetween();
     
private: 
    /**
     *
     */
    void buff_switch(); 
    /**
     * 
     */
    std::unique_ptr<_DT[]> buffer_;
    /**
     * 
     */
    const size_t capacity_;
    /**
     * 
     */
    size_t buff_idx_center_;
    /**
     * 
     */
    std::atomic<size_t> idx_rd_; 
    /**
     * 
     */
    std::atomic<size_t> idx_wd_;
    /**
     * 
     */
    mutable std::mutex read_mutex_;
    mutable std::mutex write_mutex_; 
    std::mutex switch_mutex_;
};

#include "buffer/impl/DoubleBuffer.tpp"