// generic decoding API, virtual class from which decoding algorithms can be derived

#ifndef MCCL_CORE_MATRIX_HPP
#define MCCL_CORE_MATRIX_HPP

#include <mccl/core/matrix.hpp>
#include <functional>
#include <stdlib.h>

MCCL_BEGIN_NAMESPACE

// virtual base class: interface for ISD for a given syndrome target
template<typename data_t>
class ISDAPI_target
{
public:
    // pass parameters to actual object
    //virtual void configure(const parameters_t& params) = 0;
    
    // deterministic initialization for given parity check matrix H0 and target syndrome s0
    virtual void initialize(const matrix_ref_t<data_t>& H0, const vector_ref_t<data_t>& s0) = 0;
    
    // probabilistic preparation of loop invariant
    virtual void prepare_loop() = 0;
    
    // perform one loop iteration, return true if successful and store result in e
    virtual bool loop_next() = 0;
    
    // run loop until a solution is found
    virtual void solve()
    {
        prepare_loop();
        while (!loop_next())
            ;
    }
    
    vector_t<data_t> e;
};

// virtual base class: interface for exhaustive ISD returning all solutions
template<typename data_t>
class ISDAPI_exhaustive
{
public:
    // pass parameters to actual object
    //virtual void configure(const parameters_t& params) = 0;
    
    // deterministic initialization for given parity check matrix H0 and target syndrome s0
    virtual void initialize(const matrix_ref_t<data_t>& H0, const vector_ref_t<data_t>& s0, std::function<void,vector_ref_t<data_t>&>& callback) = 0;
    
    // preparation of loop invariant
    virtual void prepare_loop() = 0;
    
    // perform one loop iteration, return true if not finished
    virtual bool loop_next() = 0;
    
    // run loop and pass all solutions through callback
    virtual void solve()
    {
        prepare_loop();
        while (loop_next())
            ;
    }
};


template<typename data_t>
class ISD_target_generic: public ISDAPI_target<data_t>
{
public:
    // pass parameters to actual object
    //virtual void configure(const parameters_t& params) = 0;
    
    // deterministic initialization for given parity check matrix H0 and target syndrome s0
    void initialize(const matrix_ref_t<data_t>& H0, const vector_ref_t<data_t>& s0) final
    {
        H = H0;
        s = s0;
    }
    
    // probabilistic preparation of loop invariant
    void prepare_loop() final
    {
    }
    
    // perform one loop iteration, return true if successful and store result in e
    bool loop_next() final
    {
    }
    
    // run loop until a solution is found
    /*void solve()
    {
        prepare_loop();
        while (!loop_next())
            ;
    }*/
    
    vector_t<data_t> e;
    matrix_t<data_t> H;
    vector_t<data_t> s;
};

MCCL_END_NAMESPACE
