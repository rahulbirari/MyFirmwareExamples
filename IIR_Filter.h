/*
 * IIR_Filter.h
 *
 *  Created on: Jul 24, 2018
 *      Author: birarirx
 */

#ifndef IIR_FILTER_H_
#define IIR_FILTER_H_

#define GLOBAL_Q 14     // 2bits.14bits  = 16 bits

#include "IQmathLib.h"

// IIR CO-EFFICIENTS

#define FILTER_ORDER 4

#define NUM_OF_COEFF (FILTER_ORDER+1)
typedef struct
{
    const  _iq b_coeff[NUM_OF_COEFF];
    const  _iq a_coeff[NUM_OF_COEFF];
           _iq       w[NUM_OF_COEFF];
}IIR_FILTER;

typedef IIR_FILTER* FILTER_POINTER;

// struct type  IIR_Filter Declares a Nth Order IIR  Filter in
// Direct Form-2  also known as (Canonical Form).   Filter can
// be initialized  by defining variable of type  IIR_FILTER as
// shown in the example  below.   Type of filter can be distin-
// guished by  having  unique identifier eg. LPF,HPF,BPF,NOTCH.
//
// Coefficients  should be declared in IQ form since, it gives
// flexibility to switch between fixed and floating point form
// coefficients a and b are const type so it can't be changed.
//
// eg.  4th Order Low pass filter
//
// IIR_FILTER LPF ={
//      // b-coeff inputs
// {_IQ(0.1689),_IQ(0.6757),_IQ(1.014),_IQ(0.6757),_IQ(0.1689)},
//      // a_coefficients
// {_IQ(1) ,   _IQ(0.6692),_IQ(0.7732),_IQ(0.1967),_IQ(0.06386)},
//      // w filter memory
//  {0,0,0,0,0}};



_iq IIR_Filter(FILTER_POINTER FILTER, _iq x_in);
// Function performs IIR Filtering on the given one dimensional
// input x_in and outputs single dimensional output.    Type of
// Filtering performed on input x_in depends on the

void Reset_IIR_Filter(FILTER_POINTER FILTER);
// Resets the filter memory array w. IIR_Filter should be reset
// after each session, to get the correct Output result.

#endif /* IIR_FILTER_H_ */
