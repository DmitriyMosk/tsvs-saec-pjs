#include "buffer/DoubleBuffer.hpp"

// #include <stdexcept>
// #include <fmt/core.h> 
// #include <iostream>

// template <typename _DT>
// DoubleBuffer<_DT>::DoubleBuffer(const size_t capacity) 
//     : capacity_(capacity) 
//     {}

// template <typename _DT> 
// DoubleBuffer<_DT>::~DoubleBuffer() { 
//     // pass 
//     // thnx std::make_unique
// }

// /**            _ --idx
//  * 1) [r,r,r,r,r|w,w,w,w,w] 
//  * 2) [w,w,w,w,w|r,r,r,r,r]
//  *                       _  --idx 
//  * 3) [r,r,r,r,r|w,w,w,w,w]
//  *             _ --idx
//  */
// template <typename _DT>
// void DoubleBuffer<_DT>::buff_switch() {
//     idx_rd_ = buff_idx_center_;
//     idx_wd_ = 0;
// }

// template <typename _DT>
// void DoubleBuffer<_DT>::Alloc() { 
//     try {
//         buffer_ = std::make_unique<_DT[]>(capacity_);
//     } catch (const std::bad_alloc& e) {
//         throw std::runtime_error(
//             fmt::format("Memory allocation failed for capacity {}: {}", capacity_, e.what())
//         );
//     }
    
//     buff_idx_center_ = static_cast<size_t>(capacity_ / 2);

//     /**
//      * Set pointer <rd> [left side]
//      */
//     idx_rd_ = 0;

//     /**
//      * Set pointer <wd> [right side]
//      */
//     idx_wd_ = buff_idx_center_; 
// }

// /**
//  * [_,_,_,(_ptr_wd),e,e,|(buff_center_)]
//  * Заполнено 3 ячейки, следуща запись на 4ой (look position _ptr_wd)
//  * Всего size(WD) = 6 idxs:[0,...,5] buff_center_ = 6
//  */
// template <typename _DT>
// size_t DoubleBuffer<_DT>::AvailableSizeWD() {
//     // если idx_wd_ >= buff_idx_center => right side for write
//     return (idx_wd_ >= buff_idx_center_)
//         ? (capacity_ - idx_wd_) 
//         // иначе right-side
//         : (buff_idx_center_ - idx_wd_);
// }

// template <typename _DT>
// size_t DoubleBuffer<_DT>::AvailableSizeRD() {
//     // если idx_rd_ >= buff_idx_center => right side for write
//     return (idx_rd_ >= buff_idx_center_)
//         ? (capacity_ - idx_rd_) 
//         // иначе right-side
//         : (buff_idx_center_ - idx_rd_);
// }


// // rd/wd 
// template <typename _DT>
// float DoubleBuffer<_DT>::RatioBetween() { 
//     return AvailableSizeRD() / AvailableSizeWD(); 
// }

// /**
//  * buff: [r,r,r,r,r|w,w,w,w,w]
//  *                 ----------
//  * Desc: Мы можем выполнять данную операцию
//  * Пока [w] область не заполнена
//  * Если [w] область заполнена, а [r] - пуста
//  * То мы делаем buff_switch
//  */
// template <typename _DT> 
// int8_t DoubleBuffer<_DT>::Push(const _DT& data) { 
//     if (AvailableSizeWD() == 0) { 
//         if (idx_rd_ == 0) { 
//             buff_switch();
//         } else {
//             return BUFFER_WD_IS_FILLED;
//         }
//     } 

//     buffer_[idx_wd_] = data; 
//     idx_wd_++; 

//     return OP_SUCCESS; 
// }

// /**
//  * buff: [r,r,r,r,r|w,w,w,w,w]
//  *       -----------
//  * Desc: Мы можем выполнять данную операцию
//  * Пока [r] не пуста
//  * Если [r] пуста, то мы делаем buff_switch
//  * 
//  * RVO: implemented
//  */
// template <typename _DT> 
// _DT DoubleBuffer<_DT>::Pull() { 
//     if (AvailableSizeRD() == 0) { 
//         buff_switch(); 
//     }

//     return buffer_[idx_rd_++];
// }

// /**
//  * DMA Implementation
//  */
// template <typename _DT>
// int8_t DoubleBuffer<_DT>::DirectPull(_DT* dest, size_t size, bool copy) {
//     size_t read_available = AvailableSizeRD();

//     if (read_available == 0) { 
//         buff_switch(); 
//     } 

//     if (read_available < size) {
//         return INSUFFICIENT_ELEMENTS
//     }
    
//     memcpy(dest, &buffer_[idx_rd_], size * sizeof(_DT));

//     if (!copy) {
//         idx_rd_ += size;
//     }

//     return OP_SUCCESS; 
// }

// /**
//  * DMA Implementation
//  */
// template <typename _DT>
// int8_t DoubleBuffer<_DT>::DirectPush(_DT* src, size_t size) {
//     if (AvailableSizeWD() == 0) { 
//         if (idx_rd_ == 0) { 
//             buff_switch();
//         } else { 
//             return BUFFER_WD_IS_FILLED;
//         }
//     }

//     if (AvailableSizeWD() < size) {
//         return INSUFFICIENT_SPACE;
//     }

//     memcpy(&buffer_[idx_wd_], src, size * sizeof(_DT));
    
//     idx_wd_ += size; 

//     return 0;
// }