/*
 * IIR_Filter.c
 *
 *  Created on: Jul 24, 2018
 *      Author: birarirx
 */

#include "IIR_Filter.h"


// ###############################################################################
//
// 4th Order Sallen Key IIR Filters
//
//Low Pass Filter
//
//    Y(z)        0.1689 + 0.6757 z^-1 + 1.014 z^-2 + 0.6757 z^-3 + 0.1689 z^-4
//  -------  =  ----------------------------------------------------------------
//    X(z)         1 + 0.6692 z^-1 + 0.7732 z^-2 + 0.1967 z^-3 + 0.06386 z^-4
//
//High Pass Filter
//
//    Y(z)         0.26 z^4 - 1.04 z^3 + 1.56 z^2 - 1.04 z + 0.26
//  -------  =  ----------------------------------------------------
//    X(z)        z^4 - 1.491 z^3 + 1.174 z^2 - 0.4153 z + 0.08026
//
// LPF and HPF above are digitized using Tustin method to obtain digital domain
// transfer function  and  difference equation is realized using  the following
// form. Please note filter coefficients in the digital form dependent  on  the
// sampling frequency. Here, sampling frequency is 250kHz.
//
// Digital Implementation Direct Form - 2 (Canonical Form) Structure
//
//xn-->(+)----------Wn----->(x)--(+)-->yn
//      |           |        ^    |
//      |           V        |    |
//      |          (z)^-1    b(0) |
//      |           |             |
//      |           V             |
//     (+)<-(x)<----+------>(x)->(+)
//      |    ^      |        ^    |
//      |    |      V        |    |
//      |   -a(1)  (z)^-1    b(1) |
//      |           |             |
//      |           V             |
//     (+)<-(x)<----+------>(x)->(+)
//      |    ^      |        ^    |
//      |    |      V        |    |
//      |   -a(2)  (z)^-1    b(2) |
//      |           |             |
//      |           V             |
//     (+)<-(x)<----+------>(x)->(+)
//      |    ^      |        ^    |
//      |    |      V        |    |
//      |   -a(3)  (z)^-1    b(3) |
//      |           |             |
//      |           V             |
//      --->(x)--->(+)<-----(x)----
//           ^               ^
//           |               |
//          -a(4)            b(4)
//
//
//###############################################################################

#pragma DATA_SECTION(LPF,"Cla_Data")

 IIR_FILTER LPF ={
{_IQ(0.1689),_IQ(0.6757),_IQ(1.014),  _IQ(0.6757),_IQ(0.1689)},         // b-coeff input
{_IQ(1) ,    _IQ(0.6692),_IQ(0.7732), _IQ(0.1967),_IQ(0.06386)},        // a-coeff output
{0,0,0,0,0}
};

#pragma DATA_SECTION(HPF,"Cla_Data")
IIR_FILTER HPF ={
{_IQ(0.26), _IQ(-1.04), _IQ(0.56),   _IQ(1.04),     _IQ(0.26)},         // b-coeff input
{_IQ(1) ,   _IQ(-1.491),_IQ( 1.174), _IQ(- 0.4153), _IQ(0.08026)},      // a-coeff output
{0,0,0,0,0}
};

#pragma DATA_SECTION(BPF,"Cla_Data")
IIR_FILTER BPF ={
{_IQ(0),    _IQ(0),     _IQ(0),   _IQ(0),   _IQ(0)},                    // b-coeff input
{_IQ(0),    _IQ(0),     _IQ(0),   _IQ(0),   _IQ(0)},                    // a-coeff output
{0,0,0,0,0}
};

#pragma CODE_SECTION(Reset_IIR_Filter,"Cla_Prog");
void Reset_IIR_Filter(FILTER_POINTER FILTER)
{unsigned int i;
    for (i = 0; i< NUM_OF_COEFF; i++)   // Wipes filter memory
        FILTER->w[i] = 0;
}

#pragma CODE_SECTION(IIR_Filter,"Cla_Prog");
long IIR_Filter(FILTER_POINTER FILTER, _iq x_in)
{
// Direct -2 Canonical Form
static _iq w[NUM_OF_COEFF]={0}; _iq  y_op = 0;
unsigned int i;

    w[0] = x_in;
    for (i = 1; i< NUM_OF_COEFF; i++){  // IIR Filtering
        w[0] += _IQmpy(FILTER->a_coeff[i],FILTER->w[i]);
        y_op += _IQmpy(FILTER->b_coeff[i],FILTER->w[i]);
    }   y_op +=  w[0];

    // Shift w
    for(i = (NUM_OF_COEFF-1); i > 0 ; i--)
        FILTER->w[i] = FILTER->w[i-1];

    return y_op;
}
