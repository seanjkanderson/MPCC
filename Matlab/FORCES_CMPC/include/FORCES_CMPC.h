/*
FORCES_CMPC : A fast customized optimization solver.

Copyright (C) 2013-2021 EMBOTECH AG [info@embotech.com]. All rights reserved.


This software is intended for simulation and testing purposes only. 
Use of this software for any commercial purpose is prohibited.

This program is distributed in the hope that it will be useful.
EMBOTECH makes NO WARRANTIES with respect to the use of the software 
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A 
PARTICULAR PURPOSE. 

EMBOTECH shall not have any liability for any damage arising from the use
of the software.

This Agreement shall exclusively be governed by and interpreted in 
accordance with the laws of Switzerland, excluding its principles
of conflict of laws. The Courts of Zurich-City shall have exclusive 
jurisdiction in case of any dispute.

*/

/* Generated by FORCESPRO v4.2.0 on Sunday, February 21, 2021 at 1:48:08 AM */
#ifndef FORCES_CMPC_H
#define FORCES_CMPC_H

#ifndef SOLVER_STDIO_H
#define SOLVER_STDIO_H
#include <stdio.h>
#endif


#ifndef SOLVER_STANDARD_TYPES
#define SOLVER_STANDARD_TYPES

typedef signed char solver_int8_signed;
typedef unsigned char solver_int8_unsigned;
typedef char solver_int8_default;
typedef signed short int solver_int16_signed;
typedef unsigned short int solver_int16_unsigned;
typedef short int solver_int16_default;
typedef signed int solver_int32_signed;
typedef unsigned int solver_int32_unsigned;
typedef int solver_int32_default;
typedef signed long long int solver_int64_signed;
typedef unsigned long long int solver_int64_unsigned;
typedef long long int solver_int64_default;

#endif


/* DATA TYPE ------------------------------------------------------------*/
typedef double FORCES_CMPC_float;


typedef double FORCES_CMPCinterface_float;

/* SOLVER SETTINGS ------------------------------------------------------*/

/* MISRA-C compliance */
#ifndef MISRA_C_FORCES_CMPC
#define MISRA_C_FORCES_CMPC (0)
#endif

/* restrict code */
#ifndef RESTRICT_CODE_FORCES_CMPC
#define RESTRICT_CODE_FORCES_CMPC (0)
#endif

/* print level */
#ifndef SET_PRINTLEVEL_FORCES_CMPC
#define SET_PRINTLEVEL_FORCES_CMPC    (2)
#endif

/* timing */
#ifndef SET_TIMING_FORCES_CMPC
#define SET_TIMING_FORCES_CMPC    (1)
#endif

/* Numeric Warnings */
/* #define PRINTNUMERICALWARNINGS */

/* maximum number of iterations  */
#define SET_MAXIT_FORCES_CMPC         (200)	

/* scaling factor of line search (affine direction) */
#define SET_LS_SCALE_AFF_FORCES_CMPC  (FORCES_CMPC_float)(0.9)      

/* scaling factor of line search (combined direction) */
#define SET_LS_SCALE_FORCES_CMPC      (FORCES_CMPC_float)(0.95)  

/* minimum required step size in each iteration */
#define SET_LS_MINSTEP_FORCES_CMPC    (FORCES_CMPC_float)(1E-08)

/* maximum step size (combined direction) */
#define SET_LS_MAXSTEP_FORCES_CMPC    (FORCES_CMPC_float)(0.995)

/* desired relative duality gap */
#define SET_ACC_RDGAP_FORCES_CMPC     (FORCES_CMPC_float)(0.0001)

/* desired maximum residual on equality constraints */
#define SET_ACC_RESEQ_FORCES_CMPC     (FORCES_CMPC_float)(1E-06)

/* desired maximum residual on inequality constraints */
#define SET_ACC_RESINEQ_FORCES_CMPC   (FORCES_CMPC_float)(1E-06)

/* desired maximum violation of complementarity */
#define SET_ACC_KKTCOMPL_FORCES_CMPC  (FORCES_CMPC_float)(1E-06)

/* desired maximum violation of stationarity (only checked if value is > 0) */
#define SET_ACC_KKTSTAT_FORCES_CMPC  (FORCES_CMPC_float)(-1)

/* RETURN CODES----------------------------------------------------------*/
/* solver has converged within desired accuracy */
#define OPTIMAL_FORCES_CMPC      (1)

/* maximum number of iterations has been reached */
#define MAXITREACHED_FORCES_CMPC (0)

/* solver has stopped due to a timeout */
#define TIMEOUT_FORCES_CMPC   (2)

/* no progress in line search possible */
#define NOPROGRESS_FORCES_CMPC   (-7)

/* fatal internal error - nans occurring */
#define NAN_FORCES_CMPC  (-10)

/* invalid values in parameters */
#define PARAM_VALUE_ERROR_FORCES_CMPC   (-11)

/* too small timeout given */
#define INVALID_TIMEOUT_FORCES_CMPC   (-12)

/* licensing error - solver not valid on this machine */
#define LICENSE_ERROR_FORCES_CMPC  (-100)


/* PARAMETERS -----------------------------------------------------------*/
/* fill this with data before calling the solver! */
typedef struct FORCES_CMPC_params
{
    /* vector of size 10 */
    FORCES_CMPC_float minusA_times_x0[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs1[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs2[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs3[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs4[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs5[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs6[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs7[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs8[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs9[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs10[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs11[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs12[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs13[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs14[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs15[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs16[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs17[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs18[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs19[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs20[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs21[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs22[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs23[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs24[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs25[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs26[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs27[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs28[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs29[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs30[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs31[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs32[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs33[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs34[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs35[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs36[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs37[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs38[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs39[10];

    /* vector of size 10 */
    FORCES_CMPC_float equality_rhs40[10];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality1[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality2[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality3[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality4[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality5[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality6[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality7[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality8[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality9[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality10[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality11[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality12[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality13[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality14[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality15[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality16[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality17[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality18[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality19[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality20[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality21[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality22[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality23[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality24[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality25[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality26[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality27[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality28[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality29[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality30[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality31[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality32[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality33[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality34[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality35[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality36[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality37[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality38[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality39[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float equality40[130];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H1[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H2[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H3[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H4[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H5[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H6[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H7[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H8[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H9[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H10[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H11[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H12[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H13[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H14[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H15[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H16[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H17[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H18[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H19[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H20[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H21[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H22[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H23[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H24[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H25[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H26[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H27[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H28[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H29[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H30[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H31[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H32[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H33[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H34[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H35[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H36[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H37[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H38[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H39[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H40[169];

    /* matrix of size [13 x 13] (column major format) */
    FORCES_CMPC_float cost_H41[169];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f1[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f2[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f3[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f4[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f5[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f6[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f7[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f8[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f9[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f10[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f11[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f12[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f13[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f14[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f15[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f16[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f17[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f18[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f19[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f20[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f21[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f22[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f23[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f24[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f25[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f26[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f27[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f28[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f29[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f30[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f31[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f32[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f33[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f34[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f35[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f36[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f37[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f38[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f39[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f40[13];

    /* vector of size 13 */
    FORCES_CMPC_float cost_f41[13];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D1[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D2[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D3[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D4[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D5[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D6[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D7[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D8[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D9[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D10[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D11[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D12[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D13[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D14[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D15[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D16[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D17[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D18[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D19[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D20[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D21[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D22[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D23[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D24[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D25[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D26[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D27[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D28[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D29[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D30[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D31[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D32[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D33[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D34[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D35[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D36[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D37[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D38[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D39[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D40[130];

    /* matrix of size [10 x 13] (column major format) */
    FORCES_CMPC_float eq_D41[130];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A1[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A2[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A3[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A4[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A5[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A6[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A7[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A8[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A9[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A10[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A11[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A12[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A13[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A14[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A15[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A16[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A17[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A18[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A19[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A20[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A21[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A22[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A23[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A24[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A25[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A26[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A27[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A28[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A29[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A30[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A31[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A32[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A33[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A34[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A35[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A36[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A37[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A38[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A39[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A40[26];

    /* matrix of size [2 x 13] (column major format) */
    FORCES_CMPC_float polytopic_A41[26];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b1[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b2[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b3[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b4[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b5[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b6[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b7[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b8[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b9[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b10[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b11[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b12[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b13[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b14[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b15[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b16[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b17[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b18[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b19[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b20[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b21[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b22[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b23[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b24[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b25[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b26[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b27[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b28[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b29[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b30[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b31[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b32[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b33[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b34[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b35[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b36[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b37[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b38[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b39[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b40[2];

    /* vector of size 2 */
    FORCES_CMPC_float polytopic_b41[2];

} FORCES_CMPC_params;


/* OUTPUTS --------------------------------------------------------------*/
/* the desired variables are put here by the solver */
typedef struct FORCES_CMPC_output
{
    /* vector of size 533 */
    FORCES_CMPC_float z[533];

} FORCES_CMPC_output;


/* SOLVER INFO ----------------------------------------------------------*/
/* diagnostic data from last interior point step */
typedef struct FORCES_CMPC_info
{
    /* iteration number */
    solver_int32_default it;

	/* number of iterations needed to optimality (branch-and-bound) */
	solver_int32_default it2opt;
	
    /* inf-norm of equality constraint residuals */
    FORCES_CMPC_float res_eq;
	
    /* inf-norm of inequality constraint residuals */
    FORCES_CMPC_float res_ineq;

    /* primal objective */
    FORCES_CMPC_float pobj;	
	
    /* dual objective */
    FORCES_CMPC_float dobj;	

    /* duality gap := pobj - dobj */
    FORCES_CMPC_float dgap;		
	
    /* relative duality gap := |dgap / pobj | */
    FORCES_CMPC_float rdgap;		

	/* infinity norm of gradient of Lagrangian*/
	FORCES_CMPC_float gradient_lag_norm;

    /* duality measure */
    FORCES_CMPC_float mu;

	/* duality measure (after affine step) */
    FORCES_CMPC_float mu_aff;
	
    /* centering parameter */
    FORCES_CMPC_float sigma;
	
    /* number of backtracking line search steps (affine direction) */
    solver_int32_default lsit_aff;
    
    /* number of backtracking line search steps (combined direction) */
    solver_int32_default lsit_cc;
    
    /* step size (affine direction) */
    FORCES_CMPC_float step_aff;
    
    /* step size (combined direction) */
    FORCES_CMPC_float step_cc;    

	/* solvertime */
	FORCES_CMPC_float solvetime;   

} FORCES_CMPC_info;









/* SOLVER FUNCTION DEFINITION -------------------------------------------*/
/* Time of Solver Generation: (UTC) Sunday, February 21, 2021 1:48:11 AM */
/* User License expires on: (UTC) Tuesday, July 6, 2021 10:00:00 PM (approx.) (at the time of code generation) */
/* Solver Static License expires on: (UTC) Tuesday, July 6, 2021 10:00:00 PM (approx.) */
/* Solver Generation Request Id: cdbea546-0e7b-4cab-80be-f8b507ae4c6e */
/* examine exitflag before using the result! */
#ifdef __cplusplus
extern "C" {
#endif
extern solver_int32_default FORCES_CMPC_solve(FORCES_CMPC_params *params, FORCES_CMPC_output *output, FORCES_CMPC_info *info, FILE *fs);


#ifdef __cplusplus
}
#endif

#endif
