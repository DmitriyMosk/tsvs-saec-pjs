#pragma once

#include <memory>
#include <cstdint>

/**
 *  Buffer description:
 *  Потоко безопасность SPSC (Single Producer/Single Consumer) 
 *  Гарантирует потокобезопасность следующих операций:
 *  Pull, Push, PullMemory, PushMemory
 */

template <typename _DT>
class AtomicQueue { 
public:
    /**
     * 
     */
    explicit AtomicQueue() = default;

    /**
     *  For RAII
     */
    ~AtomicQueue(); 

    /**
     *  
     */
    int8_t Push(_DT& src);

    /**
     * 
     */
    int8_t Pull(_DT& dst);

    /**
     * Request DirectAccess
     */
    void RequestZeroCopy();

    /**
     *  ZeroCopy operation
     */
    int8_t PullMemory(size_t st_addr, size_t pull_c, _DT* src_begin);

    /**
     *  ZeroCopy operation
     */
    int8_t PushMemory(size_t st_addr, size_t push_c, _DT* dst_begin); 

    /**
     * Mark End ZC Operation
     */
    void FinishZeroCopy();

private: 
    const size_t capacity_;

    std::unique_ptr<_DT[]> buff_ptr_;
};