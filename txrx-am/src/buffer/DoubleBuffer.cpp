#include "buffer/DoubleBuffer.hpp"

#include <stdexcept>
#include <fmt/core.h> 

template <typename _DT>
DoubleBuffer<_DT>::DoubleBuffer() {}

template <typename _DT> 
DoubleBuffer<_DT>::~DoubleBuffer() { 
    // pass 
    // thnx std::make_unique
}

template <typename _DT>
void DoubleBuffer<_DT>::Make(size_t capacity) { 
    if (capacity % 2 != 0) { 
        throw std::invalid_argument(
            fmt::format("Capacity must be a power of two, but got: {}", capacity)
        );
    }

    try {
        buffer_ = std::make_unique<_DT[]>(capacity);
    } catch (const std::bad_alloc& e) {
        throw std::runtime_error(
            fmt::format("Memory allocation failed for capacity {}: {}", capacity, e.what())
        );
    }
    
    capacity_       = capacity;
    buff_center_    = capacity / 2;

    /**
     * Set pointer <rd> [left side]
     */
    _ptr_rd = &buffer_[0];

    /**
     * Set pointer <wd> [right side]
     */
    _ptr_wd = &buffer[buff_center_]
}

/**
 * buff: [r,r,r,r,r|w,w,w,w,w]
 *                 ----------
 * Desc: Мы можем выполнять данную операцию
 * Пока [w] область не заполнена
 * Если [w] область заполнена, а [r] - пуста
 * То мы делаем buff_switch
 */
template <typename _DT> 
int8_t DoubleBuffer<_DT>::Push(_DT& data) { 
    if ( ( _ptr_wd == _ptr_rd - 1 ) || (_ptr_wd == &buffer_[capacity_ - 1] && _ptr_rd == &buffer_[0]) ) {
        return BUFFER_WD_IS_FILLED;
    }

    *_ptr_wd = data; 

    return OP_SUCCESS; 
}

/**
 * buff: [r,r,r,r,r|w,w,w,w,w]
 *       -----------
 * Desc: Мы можем выполнять данную операцию
 * Пока [r] не пуста
 * Если [r] пуста, то мы делаем buff_switch
 */
template <typename _DT> 
_DT DoubleBuffer<_DT>::Pull() { 
    if ( (_ptr_rd == ))
}

/**
 * 
 */
template <typename _DT>
void DoubleBuffer<_DT>::buff_switch() { 

}

/**
 * 
 */
template <typename _DT>
int8_t DoubleBuffer<_DT>::DirectPull(_DT& val, size_t size, bool copy) {

}

/**
 * 
 */
template <typename _DT>
int8_t DoubleBuffer<_DT>::DirectPush(_DT& val, size_t size) {

}