#pragma once 

#include <memory>

template <typename _DT>
class DoubleBuffer { 
    enum { 
        OUT_OF_RANGE, 
        BUFFER_WD_IS_FILLED,
        BUFFER_RD_IS_FILLED,
        OP_SUCCESS
    };
public: 
    /**
     * 
     */
    explicit DoubleBuffer();
    
    /**
     * 
     */
    ~DoubleBuffer();

    /**
     * 
     */
    static void Make(size_t capacity);

    /**
     * 
     */
    int8_t Push(_DT& data);  

    /**
     *  Add RVO?
     */
    _DT Pull(); 
    
    
    /**
     * ZeroCopy
     */
    int8_t DirectPull(_DT& val, size_t size, bool copy);

    /**
     * 
     */
    int8_t DirectPush(_DT& val, size_t size);
     
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
    const size_t buff_center_;
    /**
     * 
     */
    size_t* _ptr_rd; 
    /**
     * 
     */
    size_t* _ptr_wd;
};

template class DoubleBuffer<double>; 
template class DoubleBuffer<float>; 
template class DoubleBuffer<short>;
template class DoubleBuffer<bool>;
template class DoubleBuffer<int>; 
template class DoubleBuffer<unsigned int>;
