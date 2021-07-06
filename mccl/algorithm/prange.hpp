#ifndef MCCL_ALGORITHM_PRANGE_HPP
#define MCCL_ALGORITHM_PRANGE_HPP

#include <mccl/algorithm/decoding.hpp>

MCCL_BEGIN_NAMESPACE

class subISD_prange
    : public ISD_API_exhaustive_sparse_t
{   
public:        
    using ISD_API_exhaustive_sparse_t::callback_t;

    void initialize(const mat_view& H_, const vec_view& S, unsigned int w_, callback_t _callback, void* _ptr)
    {
        callback = _callback;
        ptr = _ptr;
    }

    bool loop_next()
    {
        (*callback)(ptr,E1_sparse, 0);
        return false;
    }
private:
    callback_t callback;
    void* ptr;
    std::vector<uint32_t> E1_sparse;
};


class subISDT_prange
    : public ISD_API_exhaustive_transposed_sparserange_t
{
public:
    using ISD_API_exhaustive_transposed_sparserange_t::callback_t;
    
    void initialize(const cmat_view& HTpadded, size_t HTcolumns, const cvec_view& Spadded, unsigned int w, callback_t _callback, void* _ptr) final
    {
        // should only be used with l=0
        if (HTcolumns != 0)
            throw;
        callback = _callback;
        ptr = _ptr;
    }
    
    void prepare_loop() final
    {
    }
    
    bool loop_next() final
    {
        (*callback)(ptr, nullptr, nullptr, 0);
        return false;
    }
    
    void solve() final
    {
        loop_next();
    }
    
private:
    callback_t callback;
    void* ptr;
};

MCCL_END_NAMESPACE

#endif
