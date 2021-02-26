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

#include "mex.h"
#include "math.h"
#include "../include/FORCES_CMPC.h"
#ifndef SOLVER_STDIO_H
#define SOLVER_STDIO_H
#include <stdio.h>
#endif



/* copy functions */

void copyCArrayToM_double(double *src, double *dest, solver_int32_default dim) 
{
    solver_int32_default i;
    for( i = 0; i < dim; i++ ) 
    {
        *dest++ = (double)*src++;
    }
}

void copyMArrayToC_double(double *src, double *dest, solver_int32_default dim) 
{
    solver_int32_default i;
    for( i = 0; i < dim; i++ ) 
    {
        *dest++ = (double) (*src++) ;
    }
}

void copyMValueToC_double(double * src, double * dest)
{
	*dest = (double) *src;
}





/* Some memory for mex-function */
static FORCES_CMPC_params params;
static FORCES_CMPC_output output;
static FORCES_CMPC_info info;

/* THE mex-function */
void mexFunction( solver_int32_default nlhs, mxArray *plhs[], solver_int32_default nrhs, const mxArray *prhs[] )  
{
	/* file pointer for printing */
	FILE *fp = NULL;

	/* define variables */	
	mxArray *par;
	mxArray *outvar;
	const mxArray *PARAMS = prhs[0];
	double *pvalue;
	solver_int32_default i;
	solver_int32_default exitflag;
	const solver_int8_default *fname;
	const solver_int8_default *outputnames[1] = {"z"};
	const solver_int8_default *infofields[16] = { "it", "it2opt", "res_eq", "res_ineq",  "pobj",  "dobj",  "dgap", "rdgap",  "mu",  "mu_aff",  "sigma",  "lsit_aff",  "lsit_cc",  "step_aff",   "step_cc",  "solvetime"};
	
	/* Check for proper number of arguments */
    if (nrhs != 1) 
	{
        mexErrMsgTxt("This function requires exactly 1 input: PARAMS struct.\nType 'help FORCES_CMPC_mex' for details.");
    }    
	if (nlhs > 3) 
	{
        mexErrMsgTxt("This function returns at most 3 outputs.\nType 'help FORCES_CMPC_mex' for details.");
    }

	/* Check whether params is actually a structure */
	if( !mxIsStruct(PARAMS) ) 
	{
		mexErrMsgTxt("PARAMS must be a structure.");
	}

	/* copy parameters into the right location */
	par = mxGetField(PARAMS, 0, "minusA_times_x0");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.minusA_times_x0 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.minusA_times_x0 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.minusA_times_x0 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.minusA_times_x0,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs1");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs1 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs1 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs1 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs1,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs2");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs2 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs2 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs2 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs2,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs3");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs3 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs3 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs3 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs3,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs4");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs4 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs4 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs4 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs4,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs5");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs5 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs5 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs5 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs5,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs6");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs6 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs6 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs6 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs6,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs7");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs7 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs7 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs7 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs7,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs8");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs8 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs8 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs8 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs8,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs9");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs9 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs9 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs9 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs9,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs10");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs10 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs10 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs10 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs10,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs11");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs11 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs11 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs11 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs11,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs12");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs12 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs12 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs12 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs12,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs13");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs13 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs13 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs13 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs13,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs14");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs14 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs14 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs14 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs14,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs15");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs15 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs15 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs15 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs15,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs16");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs16 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs16 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs16 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs16,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs17");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs17 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs17 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs17 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs17,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs18");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs18 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs18 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs18 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs18,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs19");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs19 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs19 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs19 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs19,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs20");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs20 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs20 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs20 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs20,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs21");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs21 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs21 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs21 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs21,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs22");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs22 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs22 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs22 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs22,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs23");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs23 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs23 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs23 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs23,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs24");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs24 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs24 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs24 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs24,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs25");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs25 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs25 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs25 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs25,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs26");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs26 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs26 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs26 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs26,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs27");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs27 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs27 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs27 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs27,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs28");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs28 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs28 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs28 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs28,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs29");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs29 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs29 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs29 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs29,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs30");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs30 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs30 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs30 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs30,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs31");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs31 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs31 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs31 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs31,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs32");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs32 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs32 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs32 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs32,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs33");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs33 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs33 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs33 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs33,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs34");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs34 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs34 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs34 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs34,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs35");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs35 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs35 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs35 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs35,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs36");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs36 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs36 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs36 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs36,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs37");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs37 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs37 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs37 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs37,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs38");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs38 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs38 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs38 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs38,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs39");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs39 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs39 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs39 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs39,10);

	}
	par = mxGetField(PARAMS, 0, "equality_rhs40");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality_rhs40 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality_rhs40 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.equality_rhs40 must be of size [10 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality_rhs40,10);

	}
	par = mxGetField(PARAMS, 0, "equality1");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality1 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality1 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality1 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality1,130);

	}
	par = mxGetField(PARAMS, 0, "equality2");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality2 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality2 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality2 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality2,130);

	}
	par = mxGetField(PARAMS, 0, "equality3");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality3 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality3 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality3 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality3,130);

	}
	par = mxGetField(PARAMS, 0, "equality4");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality4 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality4 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality4 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality4,130);

	}
	par = mxGetField(PARAMS, 0, "equality5");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality5 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality5 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality5 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality5,130);

	}
	par = mxGetField(PARAMS, 0, "equality6");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality6 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality6 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality6 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality6,130);

	}
	par = mxGetField(PARAMS, 0, "equality7");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality7 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality7 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality7 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality7,130);

	}
	par = mxGetField(PARAMS, 0, "equality8");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality8 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality8 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality8 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality8,130);

	}
	par = mxGetField(PARAMS, 0, "equality9");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality9 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality9 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality9 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality9,130);

	}
	par = mxGetField(PARAMS, 0, "equality10");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality10 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality10 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality10 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality10,130);

	}
	par = mxGetField(PARAMS, 0, "equality11");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality11 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality11 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality11 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality11,130);

	}
	par = mxGetField(PARAMS, 0, "equality12");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality12 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality12 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality12 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality12,130);

	}
	par = mxGetField(PARAMS, 0, "equality13");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality13 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality13 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality13 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality13,130);

	}
	par = mxGetField(PARAMS, 0, "equality14");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality14 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality14 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality14 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality14,130);

	}
	par = mxGetField(PARAMS, 0, "equality15");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality15 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality15 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality15 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality15,130);

	}
	par = mxGetField(PARAMS, 0, "equality16");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality16 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality16 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality16 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality16,130);

	}
	par = mxGetField(PARAMS, 0, "equality17");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality17 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality17 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality17 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality17,130);

	}
	par = mxGetField(PARAMS, 0, "equality18");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality18 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality18 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality18 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality18,130);

	}
	par = mxGetField(PARAMS, 0, "equality19");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality19 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality19 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality19 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality19,130);

	}
	par = mxGetField(PARAMS, 0, "equality20");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality20 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality20 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality20 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality20,130);

	}
	par = mxGetField(PARAMS, 0, "equality21");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality21 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality21 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality21 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality21,130);

	}
	par = mxGetField(PARAMS, 0, "equality22");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality22 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality22 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality22 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality22,130);

	}
	par = mxGetField(PARAMS, 0, "equality23");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality23 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality23 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality23 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality23,130);

	}
	par = mxGetField(PARAMS, 0, "equality24");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality24 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality24 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality24 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality24,130);

	}
	par = mxGetField(PARAMS, 0, "equality25");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality25 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality25 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality25 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality25,130);

	}
	par = mxGetField(PARAMS, 0, "equality26");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality26 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality26 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality26 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality26,130);

	}
	par = mxGetField(PARAMS, 0, "equality27");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality27 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality27 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality27 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality27,130);

	}
	par = mxGetField(PARAMS, 0, "equality28");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality28 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality28 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality28 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality28,130);

	}
	par = mxGetField(PARAMS, 0, "equality29");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality29 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality29 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality29 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality29,130);

	}
	par = mxGetField(PARAMS, 0, "equality30");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality30 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality30 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality30 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality30,130);

	}
	par = mxGetField(PARAMS, 0, "equality31");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality31 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality31 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality31 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality31,130);

	}
	par = mxGetField(PARAMS, 0, "equality32");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality32 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality32 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality32 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality32,130);

	}
	par = mxGetField(PARAMS, 0, "equality33");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality33 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality33 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality33 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality33,130);

	}
	par = mxGetField(PARAMS, 0, "equality34");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality34 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality34 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality34 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality34,130);

	}
	par = mxGetField(PARAMS, 0, "equality35");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality35 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality35 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality35 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality35,130);

	}
	par = mxGetField(PARAMS, 0, "equality36");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality36 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality36 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality36 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality36,130);

	}
	par = mxGetField(PARAMS, 0, "equality37");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality37 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality37 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality37 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality37,130);

	}
	par = mxGetField(PARAMS, 0, "equality38");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality38 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality38 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality38 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality38,130);

	}
	par = mxGetField(PARAMS, 0, "equality39");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality39 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality39 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality39 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality39,130);

	}
	par = mxGetField(PARAMS, 0, "equality40");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.equality40 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.equality40 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.equality40 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.equality40,130);

	}
	par = mxGetField(PARAMS, 0, "cost_H1");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H1 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H1 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H1 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H1,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H2");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H2 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H2 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H2 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H2,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H3");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H3 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H3 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H3 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H3,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H4");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H4 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H4 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H4 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H4,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H5");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H5 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H5 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H5 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H5,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H6");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H6 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H6 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H6 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H6,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H7");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H7 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H7 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H7 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H7,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H8");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H8 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H8 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H8 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H8,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H9");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H9 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H9 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H9 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H9,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H10");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H10 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H10 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H10 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H10,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H11");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H11 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H11 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H11 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H11,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H12");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H12 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H12 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H12 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H12,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H13");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H13 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H13 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H13 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H13,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H14");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H14 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H14 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H14 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H14,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H15");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H15 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H15 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H15 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H15,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H16");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H16 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H16 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H16 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H16,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H17");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H17 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H17 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H17 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H17,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H18");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H18 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H18 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H18 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H18,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H19");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H19 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H19 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H19 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H19,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H20");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H20 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H20 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H20 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H20,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H21");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H21 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H21 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H21 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H21,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H22");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H22 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H22 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H22 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H22,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H23");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H23 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H23 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H23 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H23,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H24");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H24 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H24 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H24 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H24,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H25");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H25 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H25 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H25 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H25,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H26");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H26 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H26 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H26 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H26,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H27");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H27 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H27 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H27 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H27,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H28");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H28 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H28 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H28 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H28,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H29");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H29 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H29 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H29 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H29,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H30");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H30 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H30 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H30 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H30,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H31");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H31 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H31 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H31 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H31,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H32");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H32 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H32 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H32 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H32,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H33");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H33 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H33 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H33 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H33,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H34");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H34 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H34 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H34 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H34,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H35");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H35 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H35 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H35 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H35,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H36");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H36 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H36 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H36 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H36,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H37");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H37 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H37 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H37 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H37,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H38");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H38 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H38 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H38 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H38,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H39");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H39 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H39 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H39 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H39,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H40");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H40 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H40 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H40 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H40,169);

	}
	par = mxGetField(PARAMS, 0, "cost_H41");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_H41 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_H41 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.cost_H41 must be of size [13 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_H41,169);

	}
	par = mxGetField(PARAMS, 0, "cost_f1");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f1 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f1 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f1 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f1,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f2");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f2 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f2 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f2 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f2,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f3");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f3 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f3 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f3 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f3,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f4");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f4 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f4 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f4 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f4,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f5");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f5 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f5 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f5 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f5,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f6");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f6 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f6 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f6 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f6,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f7");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f7 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f7 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f7 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f7,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f8");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f8 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f8 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f8 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f8,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f9");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f9 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f9 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f9 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f9,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f10");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f10 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f10 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f10 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f10,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f11");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f11 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f11 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f11 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f11,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f12");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f12 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f12 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f12 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f12,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f13");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f13 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f13 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f13 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f13,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f14");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f14 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f14 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f14 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f14,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f15");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f15 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f15 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f15 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f15,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f16");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f16 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f16 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f16 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f16,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f17");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f17 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f17 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f17 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f17,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f18");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f18 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f18 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f18 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f18,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f19");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f19 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f19 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f19 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f19,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f20");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f20 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f20 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f20 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f20,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f21");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f21 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f21 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f21 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f21,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f22");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f22 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f22 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f22 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f22,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f23");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f23 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f23 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f23 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f23,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f24");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f24 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f24 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f24 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f24,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f25");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f25 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f25 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f25 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f25,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f26");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f26 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f26 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f26 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f26,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f27");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f27 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f27 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f27 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f27,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f28");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f28 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f28 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f28 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f28,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f29");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f29 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f29 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f29 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f29,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f30");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f30 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f30 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f30 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f30,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f31");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f31 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f31 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f31 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f31,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f32");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f32 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f32 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f32 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f32,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f33");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f33 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f33 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f33 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f33,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f34");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f34 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f34 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f34 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f34,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f35");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f35 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f35 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f35 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f35,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f36");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f36 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f36 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f36 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f36,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f37");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f37 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f37 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f37 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f37,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f38");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f38 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f38 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f38 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f38,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f39");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f39 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f39 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f39 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f39,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f40");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f40 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f40 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f40 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f40,13);

	}
	par = mxGetField(PARAMS, 0, "cost_f41");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.cost_f41 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.cost_f41 must be a double.");
    }
    if( mxGetM(par) != 13 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.cost_f41 must be of size [13 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.cost_f41,13);

	}
	par = mxGetField(PARAMS, 0, "eq_D1");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D1 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D1 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D1 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D1,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D2");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D2 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D2 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D2 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D2,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D3");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D3 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D3 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D3 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D3,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D4");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D4 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D4 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D4 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D4,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D5");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D5 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D5 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D5 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D5,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D6");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D6 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D6 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D6 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D6,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D7");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D7 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D7 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D7 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D7,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D8");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D8 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D8 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D8 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D8,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D9");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D9 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D9 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D9 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D9,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D10");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D10 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D10 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D10 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D10,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D11");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D11 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D11 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D11 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D11,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D12");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D12 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D12 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D12 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D12,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D13");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D13 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D13 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D13 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D13,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D14");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D14 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D14 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D14 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D14,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D15");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D15 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D15 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D15 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D15,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D16");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D16 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D16 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D16 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D16,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D17");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D17 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D17 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D17 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D17,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D18");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D18 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D18 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D18 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D18,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D19");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D19 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D19 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D19 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D19,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D20");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D20 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D20 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D20 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D20,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D21");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D21 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D21 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D21 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D21,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D22");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D22 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D22 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D22 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D22,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D23");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D23 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D23 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D23 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D23,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D24");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D24 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D24 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D24 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D24,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D25");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D25 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D25 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D25 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D25,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D26");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D26 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D26 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D26 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D26,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D27");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D27 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D27 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D27 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D27,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D28");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D28 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D28 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D28 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D28,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D29");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D29 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D29 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D29 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D29,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D30");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D30 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D30 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D30 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D30,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D31");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D31 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D31 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D31 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D31,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D32");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D32 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D32 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D32 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D32,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D33");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D33 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D33 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D33 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D33,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D34");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D34 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D34 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D34 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D34,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D35");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D35 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D35 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D35 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D35,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D36");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D36 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D36 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D36 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D36,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D37");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D37 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D37 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D37 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D37,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D38");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D38 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D38 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D38 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D38,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D39");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D39 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D39 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D39 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D39,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D40");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D40 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D40 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D40 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D40,130);

	}
	par = mxGetField(PARAMS, 0, "eq_D41");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.eq_D41 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.eq_D41 must be a double.");
    }
    if( mxGetM(par) != 10 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.eq_D41 must be of size [10 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.eq_D41,130);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A1");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A1 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A1 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A1 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A1,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A2");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A2 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A2 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A2 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A2,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A3");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A3 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A3 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A3 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A3,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A4");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A4 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A4 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A4 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A4,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A5");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A5 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A5 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A5 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A5,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A6");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A6 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A6 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A6 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A6,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A7");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A7 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A7 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A7 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A7,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A8");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A8 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A8 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A8 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A8,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A9");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A9 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A9 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A9 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A9,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A10");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A10 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A10 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A10 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A10,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A11");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A11 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A11 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A11 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A11,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A12");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A12 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A12 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A12 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A12,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A13");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A13 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A13 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A13 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A13,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A14");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A14 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A14 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A14 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A14,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A15");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A15 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A15 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A15 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A15,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A16");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A16 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A16 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A16 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A16,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A17");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A17 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A17 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A17 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A17,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A18");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A18 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A18 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A18 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A18,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A19");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A19 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A19 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A19 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A19,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A20");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A20 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A20 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A20 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A20,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A21");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A21 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A21 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A21 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A21,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A22");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A22 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A22 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A22 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A22,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A23");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A23 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A23 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A23 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A23,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A24");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A24 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A24 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A24 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A24,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A25");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A25 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A25 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A25 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A25,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A26");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A26 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A26 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A26 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A26,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A27");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A27 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A27 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A27 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A27,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A28");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A28 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A28 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A28 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A28,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A29");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A29 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A29 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A29 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A29,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A30");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A30 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A30 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A30 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A30,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A31");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A31 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A31 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A31 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A31,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A32");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A32 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A32 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A32 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A32,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A33");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A33 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A33 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A33 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A33,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A34");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A34 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A34 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A34 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A34,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A35");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A35 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A35 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A35 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A35,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A36");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A36 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A36 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A36 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A36,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A37");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A37 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A37 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A37 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A37,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A38");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A38 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A38 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A38 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A38,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A39");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A39 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A39 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A39 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A39,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A40");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A40 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A40 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A40 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A40,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_A41");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_A41 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_A41 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 13 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_A41 must be of size [2 x 13]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_A41,26);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b1");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b1 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b1 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b1 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b1,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b2");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b2 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b2 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b2 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b2,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b3");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b3 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b3 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b3 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b3,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b4");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b4 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b4 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b4 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b4,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b5");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b5 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b5 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b5 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b5,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b6");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b6 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b6 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b6 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b6,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b7");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b7 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b7 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b7 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b7,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b8");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b8 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b8 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b8 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b8,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b9");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b9 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b9 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b9 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b9,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b10");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b10 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b10 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b10 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b10,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b11");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b11 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b11 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b11 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b11,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b12");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b12 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b12 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b12 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b12,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b13");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b13 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b13 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b13 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b13,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b14");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b14 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b14 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b14 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b14,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b15");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b15 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b15 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b15 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b15,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b16");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b16 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b16 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b16 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b16,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b17");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b17 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b17 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b17 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b17,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b18");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b18 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b18 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b18 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b18,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b19");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b19 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b19 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b19 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b19,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b20");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b20 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b20 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b20 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b20,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b21");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b21 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b21 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b21 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b21,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b22");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b22 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b22 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b22 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b22,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b23");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b23 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b23 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b23 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b23,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b24");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b24 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b24 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b24 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b24,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b25");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b25 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b25 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b25 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b25,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b26");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b26 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b26 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b26 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b26,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b27");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b27 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b27 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b27 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b27,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b28");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b28 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b28 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b28 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b28,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b29");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b29 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b29 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b29 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b29,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b30");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b30 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b30 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b30 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b30,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b31");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b31 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b31 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b31 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b31,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b32");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b32 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b32 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b32 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b32,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b33");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b33 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b33 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b33 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b33,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b34");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b34 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b34 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b34 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b34,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b35");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b35 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b35 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b35 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b35,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b36");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b36 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b36 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b36 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b36,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b37");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b37 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b37 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b37 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b37,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b38");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b38 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b38 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b38 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b38,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b39");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b39 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b39 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b39 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b39,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b40");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b40 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b40 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b40 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b40,2);

	}
	par = mxGetField(PARAMS, 0, "polytopic_b41");
#ifdef MEXARGMUENTCHECKS
    if( par == NULL )	
	{
        mexErrMsgTxt("PARAMS.polytopic_b41 not found");
    }
    if( !mxIsDouble(par) )
    {
    mexErrMsgTxt("PARAMS.polytopic_b41 must be a double.");
    }
    if( mxGetM(par) != 2 || mxGetN(par) != 1 ) 
	{
    mexErrMsgTxt("PARAMS.polytopic_b41 must be of size [2 x 1]");
    }
#endif	 
	if ( (mxGetN(par) != 0) && (mxGetM(par) != 0) )
	{
		copyMArrayToC_double(mxGetPr(par), params.polytopic_b41,2);

	}


	#if SET_PRINTLEVEL_FORCES_CMPC > 0
		/* Prepare file for printfs */
        fp = fopen("stdout_temp","w+");
		if( fp == NULL ) 
		{
			mexErrMsgTxt("freopen of stdout did not work.");
		}
		rewind(fp);
	#endif

	/* call solver */
	exitflag = FORCES_CMPC_solve(&params, &output, &info, fp);
	
	#if SET_PRINTLEVEL_FORCES_CMPC > 0
		/* Read contents of printfs printed to file */
		rewind(fp);
		while( (i = fgetc(fp)) != EOF ) 
		{
			mexPrintf("%c",i);
		}
		fclose(fp);
	#endif

	/* copy output to matlab arrays */
	plhs[0] = mxCreateStructMatrix(1, 1, 1, outputnames);
		outvar = mxCreateDoubleMatrix(533, 1, mxREAL);
	copyCArrayToM_double( output.z, mxGetPr(outvar), 533);
	mxSetField(plhs[0], 0, "z", outvar);

	/* copy exitflag */
	if( nlhs > 1 )
	{
	plhs[1] = mxCreateDoubleMatrix(1, 1, mxREAL);
	*mxGetPr(plhs[1]) = (double)exitflag;
	}

	/* copy info struct */
	if( nlhs > 2 )
	{
	        plhs[2] = mxCreateStructMatrix(1, 1, 16, infofields);
         
		
		/* iterations */
		outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
		*mxGetPr(outvar) = (double)info.it;
		mxSetField(plhs[2], 0, "it", outvar);

		/* iterations to optimality (branch and bound) */
		outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
		*mxGetPr(outvar) = (double)info.it2opt;
		mxSetField(plhs[2], 0, "it2opt", outvar);
		
		/* res_eq */
		outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
		*mxGetPr(outvar) = info.res_eq;
		mxSetField(plhs[2], 0, "res_eq", outvar);

		/* res_ineq */
		outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
		*mxGetPr(outvar) = info.res_ineq;
		mxSetField(plhs[2], 0, "res_ineq", outvar);

		/* pobj */
		outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
		*mxGetPr(outvar) = info.pobj;
		mxSetField(plhs[2], 0, "pobj", outvar);

		/* dobj */
		outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
		*mxGetPr(outvar) = info.dobj;
		mxSetField(plhs[2], 0, "dobj", outvar);

		/* dgap */
		outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
		*mxGetPr(outvar) = info.dgap;
		mxSetField(plhs[2], 0, "dgap", outvar);

		/* rdgap */
		outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
		*mxGetPr(outvar) = info.rdgap;
		mxSetField(plhs[2], 0, "rdgap", outvar);

		/* mu */
		outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
		*mxGetPr(outvar) = info.mu;
		mxSetField(plhs[2], 0, "mu", outvar);

		/* mu_aff */
		outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
		*mxGetPr(outvar) = info.mu_aff;
		mxSetField(plhs[2], 0, "mu_aff", outvar);

		/* sigma */
		outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
		*mxGetPr(outvar) = info.sigma;
		mxSetField(plhs[2], 0, "sigma", outvar);

		/* lsit_aff */
		outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
		*mxGetPr(outvar) = (double)info.lsit_aff;
		mxSetField(plhs[2], 0, "lsit_aff", outvar);

		/* lsit_cc */
		outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
		*mxGetPr(outvar) = (double)info.lsit_cc;
		mxSetField(plhs[2], 0, "lsit_cc", outvar);

		/* step_aff */
		outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
		*mxGetPr(outvar) = info.step_aff;
		mxSetField(plhs[2], 0, "step_aff", outvar);

		/* step_cc */
		outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
		*mxGetPr(outvar) = info.step_cc;
		mxSetField(plhs[2], 0, "step_cc", outvar);

		/* solver time */
		outvar = mxCreateDoubleMatrix(1, 1, mxREAL);
		*mxGetPr(outvar) = info.solvetime;
		mxSetField(plhs[2], 0, "solvetime", outvar);
	}
}