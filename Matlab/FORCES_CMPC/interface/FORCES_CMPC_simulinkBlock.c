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


#define S_FUNCTION_LEVEL 2
#define S_FUNCTION_NAME FORCES_CMPC_simulinkBlock

#include "simstruc.h"



/* include FORCESPRO functions and defs */
#include "../include/FORCES_CMPC.h" 

/* SYSTEM INCLUDES FOR TIMING ------------------------------------------ */


#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#include "rtwtypes.h"
#endif

typedef FORCES_CMPCinterface_float FORCES_CMPCnmpc_float;





/*====================*
 * S-function methods *
 *====================*/
/* Function: mdlInitializeSizes =========================================
 * Abstract:
 *   Setup sizes of the various vectors.
 */
static void mdlInitializeSizes(SimStruct *S)
{

    DECL_AND_INIT_DIMSINFO(inputDimsInfo);
    DECL_AND_INIT_DIMSINFO(outputDimsInfo);
    ssSetNumSFcnParams(S, 0);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) 
	{
		return; /* Parameter mismatch will be reported by Simulink */
    }

	/* initialize size of continuous and discrete states to zero */
    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

	/* initialize input ports - there are 286 in total */
    if (!ssSetNumInputPorts(S, 286)) return;
    	
	/* Input Port 0 */
    ssSetInputPortMatrixDimensions(S,  0, 10, 1);
    ssSetInputPortDataType(S, 0, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 0, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 0, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 0, 1); /*direct input signal access*/	
	/* Input Port 1 */
    ssSetInputPortMatrixDimensions(S,  1, 10, 1);
    ssSetInputPortDataType(S, 1, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 1, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 1, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 1, 1); /*direct input signal access*/	
	/* Input Port 2 */
    ssSetInputPortMatrixDimensions(S,  2, 10, 1);
    ssSetInputPortDataType(S, 2, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 2, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 2, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 2, 1); /*direct input signal access*/	
	/* Input Port 3 */
    ssSetInputPortMatrixDimensions(S,  3, 10, 1);
    ssSetInputPortDataType(S, 3, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 3, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 3, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 3, 1); /*direct input signal access*/	
	/* Input Port 4 */
    ssSetInputPortMatrixDimensions(S,  4, 10, 1);
    ssSetInputPortDataType(S, 4, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 4, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 4, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 4, 1); /*direct input signal access*/	
	/* Input Port 5 */
    ssSetInputPortMatrixDimensions(S,  5, 10, 1);
    ssSetInputPortDataType(S, 5, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 5, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 5, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 5, 1); /*direct input signal access*/	
	/* Input Port 6 */
    ssSetInputPortMatrixDimensions(S,  6, 10, 1);
    ssSetInputPortDataType(S, 6, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 6, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 6, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 6, 1); /*direct input signal access*/	
	/* Input Port 7 */
    ssSetInputPortMatrixDimensions(S,  7, 10, 1);
    ssSetInputPortDataType(S, 7, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 7, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 7, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 7, 1); /*direct input signal access*/	
	/* Input Port 8 */
    ssSetInputPortMatrixDimensions(S,  8, 10, 1);
    ssSetInputPortDataType(S, 8, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 8, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 8, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 8, 1); /*direct input signal access*/	
	/* Input Port 9 */
    ssSetInputPortMatrixDimensions(S,  9, 10, 1);
    ssSetInputPortDataType(S, 9, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 9, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 9, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 9, 1); /*direct input signal access*/	
	/* Input Port 10 */
    ssSetInputPortMatrixDimensions(S,  10, 10, 1);
    ssSetInputPortDataType(S, 10, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 10, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 10, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 10, 1); /*direct input signal access*/	
	/* Input Port 11 */
    ssSetInputPortMatrixDimensions(S,  11, 10, 1);
    ssSetInputPortDataType(S, 11, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 11, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 11, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 11, 1); /*direct input signal access*/	
	/* Input Port 12 */
    ssSetInputPortMatrixDimensions(S,  12, 10, 1);
    ssSetInputPortDataType(S, 12, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 12, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 12, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 12, 1); /*direct input signal access*/	
	/* Input Port 13 */
    ssSetInputPortMatrixDimensions(S,  13, 10, 1);
    ssSetInputPortDataType(S, 13, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 13, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 13, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 13, 1); /*direct input signal access*/	
	/* Input Port 14 */
    ssSetInputPortMatrixDimensions(S,  14, 10, 1);
    ssSetInputPortDataType(S, 14, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 14, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 14, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 14, 1); /*direct input signal access*/	
	/* Input Port 15 */
    ssSetInputPortMatrixDimensions(S,  15, 10, 1);
    ssSetInputPortDataType(S, 15, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 15, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 15, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 15, 1); /*direct input signal access*/	
	/* Input Port 16 */
    ssSetInputPortMatrixDimensions(S,  16, 10, 1);
    ssSetInputPortDataType(S, 16, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 16, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 16, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 16, 1); /*direct input signal access*/	
	/* Input Port 17 */
    ssSetInputPortMatrixDimensions(S,  17, 10, 1);
    ssSetInputPortDataType(S, 17, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 17, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 17, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 17, 1); /*direct input signal access*/	
	/* Input Port 18 */
    ssSetInputPortMatrixDimensions(S,  18, 10, 1);
    ssSetInputPortDataType(S, 18, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 18, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 18, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 18, 1); /*direct input signal access*/	
	/* Input Port 19 */
    ssSetInputPortMatrixDimensions(S,  19, 10, 1);
    ssSetInputPortDataType(S, 19, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 19, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 19, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 19, 1); /*direct input signal access*/	
	/* Input Port 20 */
    ssSetInputPortMatrixDimensions(S,  20, 10, 1);
    ssSetInputPortDataType(S, 20, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 20, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 20, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 20, 1); /*direct input signal access*/	
	/* Input Port 21 */
    ssSetInputPortMatrixDimensions(S,  21, 10, 1);
    ssSetInputPortDataType(S, 21, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 21, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 21, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 21, 1); /*direct input signal access*/	
	/* Input Port 22 */
    ssSetInputPortMatrixDimensions(S,  22, 10, 1);
    ssSetInputPortDataType(S, 22, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 22, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 22, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 22, 1); /*direct input signal access*/	
	/* Input Port 23 */
    ssSetInputPortMatrixDimensions(S,  23, 10, 1);
    ssSetInputPortDataType(S, 23, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 23, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 23, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 23, 1); /*direct input signal access*/	
	/* Input Port 24 */
    ssSetInputPortMatrixDimensions(S,  24, 10, 1);
    ssSetInputPortDataType(S, 24, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 24, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 24, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 24, 1); /*direct input signal access*/	
	/* Input Port 25 */
    ssSetInputPortMatrixDimensions(S,  25, 10, 1);
    ssSetInputPortDataType(S, 25, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 25, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 25, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 25, 1); /*direct input signal access*/	
	/* Input Port 26 */
    ssSetInputPortMatrixDimensions(S,  26, 10, 1);
    ssSetInputPortDataType(S, 26, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 26, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 26, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 26, 1); /*direct input signal access*/	
	/* Input Port 27 */
    ssSetInputPortMatrixDimensions(S,  27, 10, 1);
    ssSetInputPortDataType(S, 27, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 27, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 27, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 27, 1); /*direct input signal access*/	
	/* Input Port 28 */
    ssSetInputPortMatrixDimensions(S,  28, 10, 1);
    ssSetInputPortDataType(S, 28, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 28, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 28, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 28, 1); /*direct input signal access*/	
	/* Input Port 29 */
    ssSetInputPortMatrixDimensions(S,  29, 10, 1);
    ssSetInputPortDataType(S, 29, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 29, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 29, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 29, 1); /*direct input signal access*/	
	/* Input Port 30 */
    ssSetInputPortMatrixDimensions(S,  30, 10, 1);
    ssSetInputPortDataType(S, 30, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 30, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 30, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 30, 1); /*direct input signal access*/	
	/* Input Port 31 */
    ssSetInputPortMatrixDimensions(S,  31, 10, 1);
    ssSetInputPortDataType(S, 31, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 31, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 31, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 31, 1); /*direct input signal access*/	
	/* Input Port 32 */
    ssSetInputPortMatrixDimensions(S,  32, 10, 1);
    ssSetInputPortDataType(S, 32, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 32, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 32, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 32, 1); /*direct input signal access*/	
	/* Input Port 33 */
    ssSetInputPortMatrixDimensions(S,  33, 10, 1);
    ssSetInputPortDataType(S, 33, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 33, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 33, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 33, 1); /*direct input signal access*/	
	/* Input Port 34 */
    ssSetInputPortMatrixDimensions(S,  34, 10, 1);
    ssSetInputPortDataType(S, 34, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 34, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 34, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 34, 1); /*direct input signal access*/	
	/* Input Port 35 */
    ssSetInputPortMatrixDimensions(S,  35, 10, 1);
    ssSetInputPortDataType(S, 35, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 35, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 35, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 35, 1); /*direct input signal access*/	
	/* Input Port 36 */
    ssSetInputPortMatrixDimensions(S,  36, 10, 1);
    ssSetInputPortDataType(S, 36, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 36, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 36, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 36, 1); /*direct input signal access*/	
	/* Input Port 37 */
    ssSetInputPortMatrixDimensions(S,  37, 10, 1);
    ssSetInputPortDataType(S, 37, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 37, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 37, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 37, 1); /*direct input signal access*/	
	/* Input Port 38 */
    ssSetInputPortMatrixDimensions(S,  38, 10, 1);
    ssSetInputPortDataType(S, 38, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 38, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 38, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 38, 1); /*direct input signal access*/	
	/* Input Port 39 */
    ssSetInputPortMatrixDimensions(S,  39, 10, 1);
    ssSetInputPortDataType(S, 39, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 39, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 39, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 39, 1); /*direct input signal access*/	
	/* Input Port 40 */
    ssSetInputPortMatrixDimensions(S,  40, 10, 1);
    ssSetInputPortDataType(S, 40, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 40, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 40, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 40, 1); /*direct input signal access*/	
	/* Input Port 41 */
    ssSetInputPortMatrixDimensions(S,  41, 10, 13);
    ssSetInputPortDataType(S, 41, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 41, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 41, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 41, 1); /*direct input signal access*/	
	/* Input Port 42 */
    ssSetInputPortMatrixDimensions(S,  42, 10, 13);
    ssSetInputPortDataType(S, 42, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 42, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 42, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 42, 1); /*direct input signal access*/	
	/* Input Port 43 */
    ssSetInputPortMatrixDimensions(S,  43, 10, 13);
    ssSetInputPortDataType(S, 43, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 43, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 43, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 43, 1); /*direct input signal access*/	
	/* Input Port 44 */
    ssSetInputPortMatrixDimensions(S,  44, 10, 13);
    ssSetInputPortDataType(S, 44, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 44, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 44, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 44, 1); /*direct input signal access*/	
	/* Input Port 45 */
    ssSetInputPortMatrixDimensions(S,  45, 10, 13);
    ssSetInputPortDataType(S, 45, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 45, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 45, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 45, 1); /*direct input signal access*/	
	/* Input Port 46 */
    ssSetInputPortMatrixDimensions(S,  46, 10, 13);
    ssSetInputPortDataType(S, 46, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 46, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 46, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 46, 1); /*direct input signal access*/	
	/* Input Port 47 */
    ssSetInputPortMatrixDimensions(S,  47, 10, 13);
    ssSetInputPortDataType(S, 47, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 47, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 47, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 47, 1); /*direct input signal access*/	
	/* Input Port 48 */
    ssSetInputPortMatrixDimensions(S,  48, 10, 13);
    ssSetInputPortDataType(S, 48, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 48, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 48, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 48, 1); /*direct input signal access*/	
	/* Input Port 49 */
    ssSetInputPortMatrixDimensions(S,  49, 10, 13);
    ssSetInputPortDataType(S, 49, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 49, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 49, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 49, 1); /*direct input signal access*/	
	/* Input Port 50 */
    ssSetInputPortMatrixDimensions(S,  50, 10, 13);
    ssSetInputPortDataType(S, 50, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 50, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 50, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 50, 1); /*direct input signal access*/	
	/* Input Port 51 */
    ssSetInputPortMatrixDimensions(S,  51, 10, 13);
    ssSetInputPortDataType(S, 51, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 51, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 51, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 51, 1); /*direct input signal access*/	
	/* Input Port 52 */
    ssSetInputPortMatrixDimensions(S,  52, 10, 13);
    ssSetInputPortDataType(S, 52, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 52, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 52, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 52, 1); /*direct input signal access*/	
	/* Input Port 53 */
    ssSetInputPortMatrixDimensions(S,  53, 10, 13);
    ssSetInputPortDataType(S, 53, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 53, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 53, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 53, 1); /*direct input signal access*/	
	/* Input Port 54 */
    ssSetInputPortMatrixDimensions(S,  54, 10, 13);
    ssSetInputPortDataType(S, 54, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 54, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 54, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 54, 1); /*direct input signal access*/	
	/* Input Port 55 */
    ssSetInputPortMatrixDimensions(S,  55, 10, 13);
    ssSetInputPortDataType(S, 55, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 55, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 55, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 55, 1); /*direct input signal access*/	
	/* Input Port 56 */
    ssSetInputPortMatrixDimensions(S,  56, 10, 13);
    ssSetInputPortDataType(S, 56, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 56, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 56, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 56, 1); /*direct input signal access*/	
	/* Input Port 57 */
    ssSetInputPortMatrixDimensions(S,  57, 10, 13);
    ssSetInputPortDataType(S, 57, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 57, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 57, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 57, 1); /*direct input signal access*/	
	/* Input Port 58 */
    ssSetInputPortMatrixDimensions(S,  58, 10, 13);
    ssSetInputPortDataType(S, 58, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 58, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 58, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 58, 1); /*direct input signal access*/	
	/* Input Port 59 */
    ssSetInputPortMatrixDimensions(S,  59, 10, 13);
    ssSetInputPortDataType(S, 59, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 59, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 59, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 59, 1); /*direct input signal access*/	
	/* Input Port 60 */
    ssSetInputPortMatrixDimensions(S,  60, 10, 13);
    ssSetInputPortDataType(S, 60, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 60, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 60, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 60, 1); /*direct input signal access*/	
	/* Input Port 61 */
    ssSetInputPortMatrixDimensions(S,  61, 10, 13);
    ssSetInputPortDataType(S, 61, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 61, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 61, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 61, 1); /*direct input signal access*/	
	/* Input Port 62 */
    ssSetInputPortMatrixDimensions(S,  62, 10, 13);
    ssSetInputPortDataType(S, 62, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 62, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 62, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 62, 1); /*direct input signal access*/	
	/* Input Port 63 */
    ssSetInputPortMatrixDimensions(S,  63, 10, 13);
    ssSetInputPortDataType(S, 63, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 63, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 63, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 63, 1); /*direct input signal access*/	
	/* Input Port 64 */
    ssSetInputPortMatrixDimensions(S,  64, 10, 13);
    ssSetInputPortDataType(S, 64, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 64, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 64, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 64, 1); /*direct input signal access*/	
	/* Input Port 65 */
    ssSetInputPortMatrixDimensions(S,  65, 10, 13);
    ssSetInputPortDataType(S, 65, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 65, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 65, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 65, 1); /*direct input signal access*/	
	/* Input Port 66 */
    ssSetInputPortMatrixDimensions(S,  66, 10, 13);
    ssSetInputPortDataType(S, 66, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 66, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 66, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 66, 1); /*direct input signal access*/	
	/* Input Port 67 */
    ssSetInputPortMatrixDimensions(S,  67, 10, 13);
    ssSetInputPortDataType(S, 67, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 67, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 67, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 67, 1); /*direct input signal access*/	
	/* Input Port 68 */
    ssSetInputPortMatrixDimensions(S,  68, 10, 13);
    ssSetInputPortDataType(S, 68, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 68, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 68, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 68, 1); /*direct input signal access*/	
	/* Input Port 69 */
    ssSetInputPortMatrixDimensions(S,  69, 10, 13);
    ssSetInputPortDataType(S, 69, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 69, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 69, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 69, 1); /*direct input signal access*/	
	/* Input Port 70 */
    ssSetInputPortMatrixDimensions(S,  70, 10, 13);
    ssSetInputPortDataType(S, 70, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 70, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 70, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 70, 1); /*direct input signal access*/	
	/* Input Port 71 */
    ssSetInputPortMatrixDimensions(S,  71, 10, 13);
    ssSetInputPortDataType(S, 71, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 71, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 71, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 71, 1); /*direct input signal access*/	
	/* Input Port 72 */
    ssSetInputPortMatrixDimensions(S,  72, 10, 13);
    ssSetInputPortDataType(S, 72, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 72, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 72, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 72, 1); /*direct input signal access*/	
	/* Input Port 73 */
    ssSetInputPortMatrixDimensions(S,  73, 10, 13);
    ssSetInputPortDataType(S, 73, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 73, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 73, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 73, 1); /*direct input signal access*/	
	/* Input Port 74 */
    ssSetInputPortMatrixDimensions(S,  74, 10, 13);
    ssSetInputPortDataType(S, 74, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 74, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 74, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 74, 1); /*direct input signal access*/	
	/* Input Port 75 */
    ssSetInputPortMatrixDimensions(S,  75, 10, 13);
    ssSetInputPortDataType(S, 75, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 75, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 75, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 75, 1); /*direct input signal access*/	
	/* Input Port 76 */
    ssSetInputPortMatrixDimensions(S,  76, 10, 13);
    ssSetInputPortDataType(S, 76, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 76, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 76, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 76, 1); /*direct input signal access*/	
	/* Input Port 77 */
    ssSetInputPortMatrixDimensions(S,  77, 10, 13);
    ssSetInputPortDataType(S, 77, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 77, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 77, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 77, 1); /*direct input signal access*/	
	/* Input Port 78 */
    ssSetInputPortMatrixDimensions(S,  78, 10, 13);
    ssSetInputPortDataType(S, 78, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 78, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 78, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 78, 1); /*direct input signal access*/	
	/* Input Port 79 */
    ssSetInputPortMatrixDimensions(S,  79, 10, 13);
    ssSetInputPortDataType(S, 79, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 79, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 79, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 79, 1); /*direct input signal access*/	
	/* Input Port 80 */
    ssSetInputPortMatrixDimensions(S,  80, 10, 13);
    ssSetInputPortDataType(S, 80, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 80, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 80, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 80, 1); /*direct input signal access*/	
	/* Input Port 81 */
    ssSetInputPortMatrixDimensions(S,  81, 13, 13);
    ssSetInputPortDataType(S, 81, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 81, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 81, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 81, 1); /*direct input signal access*/	
	/* Input Port 82 */
    ssSetInputPortMatrixDimensions(S,  82, 13, 13);
    ssSetInputPortDataType(S, 82, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 82, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 82, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 82, 1); /*direct input signal access*/	
	/* Input Port 83 */
    ssSetInputPortMatrixDimensions(S,  83, 13, 13);
    ssSetInputPortDataType(S, 83, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 83, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 83, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 83, 1); /*direct input signal access*/	
	/* Input Port 84 */
    ssSetInputPortMatrixDimensions(S,  84, 13, 13);
    ssSetInputPortDataType(S, 84, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 84, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 84, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 84, 1); /*direct input signal access*/	
	/* Input Port 85 */
    ssSetInputPortMatrixDimensions(S,  85, 13, 13);
    ssSetInputPortDataType(S, 85, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 85, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 85, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 85, 1); /*direct input signal access*/	
	/* Input Port 86 */
    ssSetInputPortMatrixDimensions(S,  86, 13, 13);
    ssSetInputPortDataType(S, 86, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 86, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 86, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 86, 1); /*direct input signal access*/	
	/* Input Port 87 */
    ssSetInputPortMatrixDimensions(S,  87, 13, 13);
    ssSetInputPortDataType(S, 87, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 87, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 87, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 87, 1); /*direct input signal access*/	
	/* Input Port 88 */
    ssSetInputPortMatrixDimensions(S,  88, 13, 13);
    ssSetInputPortDataType(S, 88, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 88, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 88, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 88, 1); /*direct input signal access*/	
	/* Input Port 89 */
    ssSetInputPortMatrixDimensions(S,  89, 13, 13);
    ssSetInputPortDataType(S, 89, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 89, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 89, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 89, 1); /*direct input signal access*/	
	/* Input Port 90 */
    ssSetInputPortMatrixDimensions(S,  90, 13, 13);
    ssSetInputPortDataType(S, 90, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 90, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 90, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 90, 1); /*direct input signal access*/	
	/* Input Port 91 */
    ssSetInputPortMatrixDimensions(S,  91, 13, 13);
    ssSetInputPortDataType(S, 91, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 91, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 91, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 91, 1); /*direct input signal access*/	
	/* Input Port 92 */
    ssSetInputPortMatrixDimensions(S,  92, 13, 13);
    ssSetInputPortDataType(S, 92, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 92, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 92, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 92, 1); /*direct input signal access*/	
	/* Input Port 93 */
    ssSetInputPortMatrixDimensions(S,  93, 13, 13);
    ssSetInputPortDataType(S, 93, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 93, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 93, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 93, 1); /*direct input signal access*/	
	/* Input Port 94 */
    ssSetInputPortMatrixDimensions(S,  94, 13, 13);
    ssSetInputPortDataType(S, 94, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 94, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 94, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 94, 1); /*direct input signal access*/	
	/* Input Port 95 */
    ssSetInputPortMatrixDimensions(S,  95, 13, 13);
    ssSetInputPortDataType(S, 95, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 95, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 95, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 95, 1); /*direct input signal access*/	
	/* Input Port 96 */
    ssSetInputPortMatrixDimensions(S,  96, 13, 13);
    ssSetInputPortDataType(S, 96, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 96, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 96, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 96, 1); /*direct input signal access*/	
	/* Input Port 97 */
    ssSetInputPortMatrixDimensions(S,  97, 13, 13);
    ssSetInputPortDataType(S, 97, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 97, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 97, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 97, 1); /*direct input signal access*/	
	/* Input Port 98 */
    ssSetInputPortMatrixDimensions(S,  98, 13, 13);
    ssSetInputPortDataType(S, 98, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 98, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 98, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 98, 1); /*direct input signal access*/	
	/* Input Port 99 */
    ssSetInputPortMatrixDimensions(S,  99, 13, 13);
    ssSetInputPortDataType(S, 99, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 99, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 99, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 99, 1); /*direct input signal access*/	
	/* Input Port 100 */
    ssSetInputPortMatrixDimensions(S,  100, 13, 13);
    ssSetInputPortDataType(S, 100, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 100, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 100, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 100, 1); /*direct input signal access*/	
	/* Input Port 101 */
    ssSetInputPortMatrixDimensions(S,  101, 13, 13);
    ssSetInputPortDataType(S, 101, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 101, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 101, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 101, 1); /*direct input signal access*/	
	/* Input Port 102 */
    ssSetInputPortMatrixDimensions(S,  102, 13, 13);
    ssSetInputPortDataType(S, 102, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 102, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 102, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 102, 1); /*direct input signal access*/	
	/* Input Port 103 */
    ssSetInputPortMatrixDimensions(S,  103, 13, 13);
    ssSetInputPortDataType(S, 103, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 103, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 103, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 103, 1); /*direct input signal access*/	
	/* Input Port 104 */
    ssSetInputPortMatrixDimensions(S,  104, 13, 13);
    ssSetInputPortDataType(S, 104, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 104, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 104, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 104, 1); /*direct input signal access*/	
	/* Input Port 105 */
    ssSetInputPortMatrixDimensions(S,  105, 13, 13);
    ssSetInputPortDataType(S, 105, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 105, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 105, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 105, 1); /*direct input signal access*/	
	/* Input Port 106 */
    ssSetInputPortMatrixDimensions(S,  106, 13, 13);
    ssSetInputPortDataType(S, 106, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 106, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 106, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 106, 1); /*direct input signal access*/	
	/* Input Port 107 */
    ssSetInputPortMatrixDimensions(S,  107, 13, 13);
    ssSetInputPortDataType(S, 107, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 107, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 107, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 107, 1); /*direct input signal access*/	
	/* Input Port 108 */
    ssSetInputPortMatrixDimensions(S,  108, 13, 13);
    ssSetInputPortDataType(S, 108, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 108, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 108, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 108, 1); /*direct input signal access*/	
	/* Input Port 109 */
    ssSetInputPortMatrixDimensions(S,  109, 13, 13);
    ssSetInputPortDataType(S, 109, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 109, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 109, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 109, 1); /*direct input signal access*/	
	/* Input Port 110 */
    ssSetInputPortMatrixDimensions(S,  110, 13, 13);
    ssSetInputPortDataType(S, 110, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 110, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 110, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 110, 1); /*direct input signal access*/	
	/* Input Port 111 */
    ssSetInputPortMatrixDimensions(S,  111, 13, 13);
    ssSetInputPortDataType(S, 111, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 111, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 111, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 111, 1); /*direct input signal access*/	
	/* Input Port 112 */
    ssSetInputPortMatrixDimensions(S,  112, 13, 13);
    ssSetInputPortDataType(S, 112, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 112, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 112, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 112, 1); /*direct input signal access*/	
	/* Input Port 113 */
    ssSetInputPortMatrixDimensions(S,  113, 13, 13);
    ssSetInputPortDataType(S, 113, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 113, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 113, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 113, 1); /*direct input signal access*/	
	/* Input Port 114 */
    ssSetInputPortMatrixDimensions(S,  114, 13, 13);
    ssSetInputPortDataType(S, 114, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 114, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 114, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 114, 1); /*direct input signal access*/	
	/* Input Port 115 */
    ssSetInputPortMatrixDimensions(S,  115, 13, 13);
    ssSetInputPortDataType(S, 115, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 115, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 115, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 115, 1); /*direct input signal access*/	
	/* Input Port 116 */
    ssSetInputPortMatrixDimensions(S,  116, 13, 13);
    ssSetInputPortDataType(S, 116, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 116, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 116, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 116, 1); /*direct input signal access*/	
	/* Input Port 117 */
    ssSetInputPortMatrixDimensions(S,  117, 13, 13);
    ssSetInputPortDataType(S, 117, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 117, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 117, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 117, 1); /*direct input signal access*/	
	/* Input Port 118 */
    ssSetInputPortMatrixDimensions(S,  118, 13, 13);
    ssSetInputPortDataType(S, 118, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 118, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 118, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 118, 1); /*direct input signal access*/	
	/* Input Port 119 */
    ssSetInputPortMatrixDimensions(S,  119, 13, 13);
    ssSetInputPortDataType(S, 119, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 119, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 119, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 119, 1); /*direct input signal access*/	
	/* Input Port 120 */
    ssSetInputPortMatrixDimensions(S,  120, 13, 13);
    ssSetInputPortDataType(S, 120, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 120, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 120, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 120, 1); /*direct input signal access*/	
	/* Input Port 121 */
    ssSetInputPortMatrixDimensions(S,  121, 13, 13);
    ssSetInputPortDataType(S, 121, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 121, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 121, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 121, 1); /*direct input signal access*/	
	/* Input Port 122 */
    ssSetInputPortMatrixDimensions(S,  122, 13, 1);
    ssSetInputPortDataType(S, 122, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 122, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 122, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 122, 1); /*direct input signal access*/	
	/* Input Port 123 */
    ssSetInputPortMatrixDimensions(S,  123, 13, 1);
    ssSetInputPortDataType(S, 123, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 123, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 123, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 123, 1); /*direct input signal access*/	
	/* Input Port 124 */
    ssSetInputPortMatrixDimensions(S,  124, 13, 1);
    ssSetInputPortDataType(S, 124, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 124, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 124, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 124, 1); /*direct input signal access*/	
	/* Input Port 125 */
    ssSetInputPortMatrixDimensions(S,  125, 13, 1);
    ssSetInputPortDataType(S, 125, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 125, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 125, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 125, 1); /*direct input signal access*/	
	/* Input Port 126 */
    ssSetInputPortMatrixDimensions(S,  126, 13, 1);
    ssSetInputPortDataType(S, 126, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 126, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 126, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 126, 1); /*direct input signal access*/	
	/* Input Port 127 */
    ssSetInputPortMatrixDimensions(S,  127, 13, 1);
    ssSetInputPortDataType(S, 127, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 127, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 127, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 127, 1); /*direct input signal access*/	
	/* Input Port 128 */
    ssSetInputPortMatrixDimensions(S,  128, 13, 1);
    ssSetInputPortDataType(S, 128, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 128, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 128, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 128, 1); /*direct input signal access*/	
	/* Input Port 129 */
    ssSetInputPortMatrixDimensions(S,  129, 13, 1);
    ssSetInputPortDataType(S, 129, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 129, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 129, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 129, 1); /*direct input signal access*/	
	/* Input Port 130 */
    ssSetInputPortMatrixDimensions(S,  130, 13, 1);
    ssSetInputPortDataType(S, 130, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 130, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 130, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 130, 1); /*direct input signal access*/	
	/* Input Port 131 */
    ssSetInputPortMatrixDimensions(S,  131, 13, 1);
    ssSetInputPortDataType(S, 131, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 131, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 131, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 131, 1); /*direct input signal access*/	
	/* Input Port 132 */
    ssSetInputPortMatrixDimensions(S,  132, 13, 1);
    ssSetInputPortDataType(S, 132, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 132, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 132, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 132, 1); /*direct input signal access*/	
	/* Input Port 133 */
    ssSetInputPortMatrixDimensions(S,  133, 13, 1);
    ssSetInputPortDataType(S, 133, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 133, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 133, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 133, 1); /*direct input signal access*/	
	/* Input Port 134 */
    ssSetInputPortMatrixDimensions(S,  134, 13, 1);
    ssSetInputPortDataType(S, 134, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 134, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 134, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 134, 1); /*direct input signal access*/	
	/* Input Port 135 */
    ssSetInputPortMatrixDimensions(S,  135, 13, 1);
    ssSetInputPortDataType(S, 135, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 135, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 135, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 135, 1); /*direct input signal access*/	
	/* Input Port 136 */
    ssSetInputPortMatrixDimensions(S,  136, 13, 1);
    ssSetInputPortDataType(S, 136, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 136, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 136, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 136, 1); /*direct input signal access*/	
	/* Input Port 137 */
    ssSetInputPortMatrixDimensions(S,  137, 13, 1);
    ssSetInputPortDataType(S, 137, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 137, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 137, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 137, 1); /*direct input signal access*/	
	/* Input Port 138 */
    ssSetInputPortMatrixDimensions(S,  138, 13, 1);
    ssSetInputPortDataType(S, 138, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 138, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 138, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 138, 1); /*direct input signal access*/	
	/* Input Port 139 */
    ssSetInputPortMatrixDimensions(S,  139, 13, 1);
    ssSetInputPortDataType(S, 139, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 139, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 139, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 139, 1); /*direct input signal access*/	
	/* Input Port 140 */
    ssSetInputPortMatrixDimensions(S,  140, 13, 1);
    ssSetInputPortDataType(S, 140, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 140, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 140, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 140, 1); /*direct input signal access*/	
	/* Input Port 141 */
    ssSetInputPortMatrixDimensions(S,  141, 13, 1);
    ssSetInputPortDataType(S, 141, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 141, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 141, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 141, 1); /*direct input signal access*/	
	/* Input Port 142 */
    ssSetInputPortMatrixDimensions(S,  142, 13, 1);
    ssSetInputPortDataType(S, 142, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 142, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 142, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 142, 1); /*direct input signal access*/	
	/* Input Port 143 */
    ssSetInputPortMatrixDimensions(S,  143, 13, 1);
    ssSetInputPortDataType(S, 143, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 143, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 143, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 143, 1); /*direct input signal access*/	
	/* Input Port 144 */
    ssSetInputPortMatrixDimensions(S,  144, 13, 1);
    ssSetInputPortDataType(S, 144, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 144, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 144, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 144, 1); /*direct input signal access*/	
	/* Input Port 145 */
    ssSetInputPortMatrixDimensions(S,  145, 13, 1);
    ssSetInputPortDataType(S, 145, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 145, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 145, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 145, 1); /*direct input signal access*/	
	/* Input Port 146 */
    ssSetInputPortMatrixDimensions(S,  146, 13, 1);
    ssSetInputPortDataType(S, 146, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 146, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 146, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 146, 1); /*direct input signal access*/	
	/* Input Port 147 */
    ssSetInputPortMatrixDimensions(S,  147, 13, 1);
    ssSetInputPortDataType(S, 147, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 147, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 147, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 147, 1); /*direct input signal access*/	
	/* Input Port 148 */
    ssSetInputPortMatrixDimensions(S,  148, 13, 1);
    ssSetInputPortDataType(S, 148, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 148, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 148, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 148, 1); /*direct input signal access*/	
	/* Input Port 149 */
    ssSetInputPortMatrixDimensions(S,  149, 13, 1);
    ssSetInputPortDataType(S, 149, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 149, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 149, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 149, 1); /*direct input signal access*/	
	/* Input Port 150 */
    ssSetInputPortMatrixDimensions(S,  150, 13, 1);
    ssSetInputPortDataType(S, 150, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 150, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 150, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 150, 1); /*direct input signal access*/	
	/* Input Port 151 */
    ssSetInputPortMatrixDimensions(S,  151, 13, 1);
    ssSetInputPortDataType(S, 151, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 151, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 151, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 151, 1); /*direct input signal access*/	
	/* Input Port 152 */
    ssSetInputPortMatrixDimensions(S,  152, 13, 1);
    ssSetInputPortDataType(S, 152, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 152, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 152, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 152, 1); /*direct input signal access*/	
	/* Input Port 153 */
    ssSetInputPortMatrixDimensions(S,  153, 13, 1);
    ssSetInputPortDataType(S, 153, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 153, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 153, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 153, 1); /*direct input signal access*/	
	/* Input Port 154 */
    ssSetInputPortMatrixDimensions(S,  154, 13, 1);
    ssSetInputPortDataType(S, 154, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 154, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 154, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 154, 1); /*direct input signal access*/	
	/* Input Port 155 */
    ssSetInputPortMatrixDimensions(S,  155, 13, 1);
    ssSetInputPortDataType(S, 155, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 155, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 155, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 155, 1); /*direct input signal access*/	
	/* Input Port 156 */
    ssSetInputPortMatrixDimensions(S,  156, 13, 1);
    ssSetInputPortDataType(S, 156, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 156, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 156, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 156, 1); /*direct input signal access*/	
	/* Input Port 157 */
    ssSetInputPortMatrixDimensions(S,  157, 13, 1);
    ssSetInputPortDataType(S, 157, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 157, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 157, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 157, 1); /*direct input signal access*/	
	/* Input Port 158 */
    ssSetInputPortMatrixDimensions(S,  158, 13, 1);
    ssSetInputPortDataType(S, 158, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 158, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 158, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 158, 1); /*direct input signal access*/	
	/* Input Port 159 */
    ssSetInputPortMatrixDimensions(S,  159, 13, 1);
    ssSetInputPortDataType(S, 159, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 159, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 159, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 159, 1); /*direct input signal access*/	
	/* Input Port 160 */
    ssSetInputPortMatrixDimensions(S,  160, 13, 1);
    ssSetInputPortDataType(S, 160, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 160, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 160, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 160, 1); /*direct input signal access*/	
	/* Input Port 161 */
    ssSetInputPortMatrixDimensions(S,  161, 13, 1);
    ssSetInputPortDataType(S, 161, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 161, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 161, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 161, 1); /*direct input signal access*/	
	/* Input Port 162 */
    ssSetInputPortMatrixDimensions(S,  162, 13, 1);
    ssSetInputPortDataType(S, 162, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 162, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 162, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 162, 1); /*direct input signal access*/	
	/* Input Port 163 */
    ssSetInputPortMatrixDimensions(S,  163, 10, 13);
    ssSetInputPortDataType(S, 163, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 163, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 163, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 163, 1); /*direct input signal access*/	
	/* Input Port 164 */
    ssSetInputPortMatrixDimensions(S,  164, 10, 13);
    ssSetInputPortDataType(S, 164, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 164, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 164, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 164, 1); /*direct input signal access*/	
	/* Input Port 165 */
    ssSetInputPortMatrixDimensions(S,  165, 10, 13);
    ssSetInputPortDataType(S, 165, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 165, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 165, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 165, 1); /*direct input signal access*/	
	/* Input Port 166 */
    ssSetInputPortMatrixDimensions(S,  166, 10, 13);
    ssSetInputPortDataType(S, 166, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 166, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 166, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 166, 1); /*direct input signal access*/	
	/* Input Port 167 */
    ssSetInputPortMatrixDimensions(S,  167, 10, 13);
    ssSetInputPortDataType(S, 167, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 167, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 167, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 167, 1); /*direct input signal access*/	
	/* Input Port 168 */
    ssSetInputPortMatrixDimensions(S,  168, 10, 13);
    ssSetInputPortDataType(S, 168, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 168, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 168, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 168, 1); /*direct input signal access*/	
	/* Input Port 169 */
    ssSetInputPortMatrixDimensions(S,  169, 10, 13);
    ssSetInputPortDataType(S, 169, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 169, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 169, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 169, 1); /*direct input signal access*/	
	/* Input Port 170 */
    ssSetInputPortMatrixDimensions(S,  170, 10, 13);
    ssSetInputPortDataType(S, 170, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 170, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 170, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 170, 1); /*direct input signal access*/	
	/* Input Port 171 */
    ssSetInputPortMatrixDimensions(S,  171, 10, 13);
    ssSetInputPortDataType(S, 171, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 171, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 171, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 171, 1); /*direct input signal access*/	
	/* Input Port 172 */
    ssSetInputPortMatrixDimensions(S,  172, 10, 13);
    ssSetInputPortDataType(S, 172, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 172, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 172, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 172, 1); /*direct input signal access*/	
	/* Input Port 173 */
    ssSetInputPortMatrixDimensions(S,  173, 10, 13);
    ssSetInputPortDataType(S, 173, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 173, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 173, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 173, 1); /*direct input signal access*/	
	/* Input Port 174 */
    ssSetInputPortMatrixDimensions(S,  174, 10, 13);
    ssSetInputPortDataType(S, 174, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 174, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 174, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 174, 1); /*direct input signal access*/	
	/* Input Port 175 */
    ssSetInputPortMatrixDimensions(S,  175, 10, 13);
    ssSetInputPortDataType(S, 175, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 175, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 175, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 175, 1); /*direct input signal access*/	
	/* Input Port 176 */
    ssSetInputPortMatrixDimensions(S,  176, 10, 13);
    ssSetInputPortDataType(S, 176, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 176, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 176, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 176, 1); /*direct input signal access*/	
	/* Input Port 177 */
    ssSetInputPortMatrixDimensions(S,  177, 10, 13);
    ssSetInputPortDataType(S, 177, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 177, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 177, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 177, 1); /*direct input signal access*/	
	/* Input Port 178 */
    ssSetInputPortMatrixDimensions(S,  178, 10, 13);
    ssSetInputPortDataType(S, 178, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 178, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 178, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 178, 1); /*direct input signal access*/	
	/* Input Port 179 */
    ssSetInputPortMatrixDimensions(S,  179, 10, 13);
    ssSetInputPortDataType(S, 179, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 179, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 179, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 179, 1); /*direct input signal access*/	
	/* Input Port 180 */
    ssSetInputPortMatrixDimensions(S,  180, 10, 13);
    ssSetInputPortDataType(S, 180, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 180, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 180, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 180, 1); /*direct input signal access*/	
	/* Input Port 181 */
    ssSetInputPortMatrixDimensions(S,  181, 10, 13);
    ssSetInputPortDataType(S, 181, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 181, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 181, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 181, 1); /*direct input signal access*/	
	/* Input Port 182 */
    ssSetInputPortMatrixDimensions(S,  182, 10, 13);
    ssSetInputPortDataType(S, 182, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 182, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 182, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 182, 1); /*direct input signal access*/	
	/* Input Port 183 */
    ssSetInputPortMatrixDimensions(S,  183, 10, 13);
    ssSetInputPortDataType(S, 183, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 183, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 183, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 183, 1); /*direct input signal access*/	
	/* Input Port 184 */
    ssSetInputPortMatrixDimensions(S,  184, 10, 13);
    ssSetInputPortDataType(S, 184, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 184, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 184, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 184, 1); /*direct input signal access*/	
	/* Input Port 185 */
    ssSetInputPortMatrixDimensions(S,  185, 10, 13);
    ssSetInputPortDataType(S, 185, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 185, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 185, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 185, 1); /*direct input signal access*/	
	/* Input Port 186 */
    ssSetInputPortMatrixDimensions(S,  186, 10, 13);
    ssSetInputPortDataType(S, 186, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 186, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 186, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 186, 1); /*direct input signal access*/	
	/* Input Port 187 */
    ssSetInputPortMatrixDimensions(S,  187, 10, 13);
    ssSetInputPortDataType(S, 187, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 187, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 187, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 187, 1); /*direct input signal access*/	
	/* Input Port 188 */
    ssSetInputPortMatrixDimensions(S,  188, 10, 13);
    ssSetInputPortDataType(S, 188, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 188, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 188, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 188, 1); /*direct input signal access*/	
	/* Input Port 189 */
    ssSetInputPortMatrixDimensions(S,  189, 10, 13);
    ssSetInputPortDataType(S, 189, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 189, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 189, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 189, 1); /*direct input signal access*/	
	/* Input Port 190 */
    ssSetInputPortMatrixDimensions(S,  190, 10, 13);
    ssSetInputPortDataType(S, 190, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 190, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 190, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 190, 1); /*direct input signal access*/	
	/* Input Port 191 */
    ssSetInputPortMatrixDimensions(S,  191, 10, 13);
    ssSetInputPortDataType(S, 191, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 191, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 191, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 191, 1); /*direct input signal access*/	
	/* Input Port 192 */
    ssSetInputPortMatrixDimensions(S,  192, 10, 13);
    ssSetInputPortDataType(S, 192, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 192, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 192, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 192, 1); /*direct input signal access*/	
	/* Input Port 193 */
    ssSetInputPortMatrixDimensions(S,  193, 10, 13);
    ssSetInputPortDataType(S, 193, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 193, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 193, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 193, 1); /*direct input signal access*/	
	/* Input Port 194 */
    ssSetInputPortMatrixDimensions(S,  194, 10, 13);
    ssSetInputPortDataType(S, 194, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 194, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 194, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 194, 1); /*direct input signal access*/	
	/* Input Port 195 */
    ssSetInputPortMatrixDimensions(S,  195, 10, 13);
    ssSetInputPortDataType(S, 195, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 195, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 195, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 195, 1); /*direct input signal access*/	
	/* Input Port 196 */
    ssSetInputPortMatrixDimensions(S,  196, 10, 13);
    ssSetInputPortDataType(S, 196, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 196, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 196, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 196, 1); /*direct input signal access*/	
	/* Input Port 197 */
    ssSetInputPortMatrixDimensions(S,  197, 10, 13);
    ssSetInputPortDataType(S, 197, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 197, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 197, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 197, 1); /*direct input signal access*/	
	/* Input Port 198 */
    ssSetInputPortMatrixDimensions(S,  198, 10, 13);
    ssSetInputPortDataType(S, 198, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 198, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 198, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 198, 1); /*direct input signal access*/	
	/* Input Port 199 */
    ssSetInputPortMatrixDimensions(S,  199, 10, 13);
    ssSetInputPortDataType(S, 199, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 199, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 199, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 199, 1); /*direct input signal access*/	
	/* Input Port 200 */
    ssSetInputPortMatrixDimensions(S,  200, 10, 13);
    ssSetInputPortDataType(S, 200, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 200, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 200, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 200, 1); /*direct input signal access*/	
	/* Input Port 201 */
    ssSetInputPortMatrixDimensions(S,  201, 10, 13);
    ssSetInputPortDataType(S, 201, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 201, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 201, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 201, 1); /*direct input signal access*/	
	/* Input Port 202 */
    ssSetInputPortMatrixDimensions(S,  202, 10, 13);
    ssSetInputPortDataType(S, 202, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 202, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 202, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 202, 1); /*direct input signal access*/	
	/* Input Port 203 */
    ssSetInputPortMatrixDimensions(S,  203, 10, 13);
    ssSetInputPortDataType(S, 203, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 203, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 203, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 203, 1); /*direct input signal access*/	
	/* Input Port 204 */
    ssSetInputPortMatrixDimensions(S,  204, 2, 13);
    ssSetInputPortDataType(S, 204, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 204, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 204, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 204, 1); /*direct input signal access*/	
	/* Input Port 205 */
    ssSetInputPortMatrixDimensions(S,  205, 2, 13);
    ssSetInputPortDataType(S, 205, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 205, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 205, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 205, 1); /*direct input signal access*/	
	/* Input Port 206 */
    ssSetInputPortMatrixDimensions(S,  206, 2, 13);
    ssSetInputPortDataType(S, 206, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 206, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 206, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 206, 1); /*direct input signal access*/	
	/* Input Port 207 */
    ssSetInputPortMatrixDimensions(S,  207, 2, 13);
    ssSetInputPortDataType(S, 207, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 207, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 207, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 207, 1); /*direct input signal access*/	
	/* Input Port 208 */
    ssSetInputPortMatrixDimensions(S,  208, 2, 13);
    ssSetInputPortDataType(S, 208, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 208, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 208, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 208, 1); /*direct input signal access*/	
	/* Input Port 209 */
    ssSetInputPortMatrixDimensions(S,  209, 2, 13);
    ssSetInputPortDataType(S, 209, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 209, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 209, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 209, 1); /*direct input signal access*/	
	/* Input Port 210 */
    ssSetInputPortMatrixDimensions(S,  210, 2, 13);
    ssSetInputPortDataType(S, 210, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 210, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 210, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 210, 1); /*direct input signal access*/	
	/* Input Port 211 */
    ssSetInputPortMatrixDimensions(S,  211, 2, 13);
    ssSetInputPortDataType(S, 211, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 211, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 211, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 211, 1); /*direct input signal access*/	
	/* Input Port 212 */
    ssSetInputPortMatrixDimensions(S,  212, 2, 13);
    ssSetInputPortDataType(S, 212, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 212, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 212, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 212, 1); /*direct input signal access*/	
	/* Input Port 213 */
    ssSetInputPortMatrixDimensions(S,  213, 2, 13);
    ssSetInputPortDataType(S, 213, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 213, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 213, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 213, 1); /*direct input signal access*/	
	/* Input Port 214 */
    ssSetInputPortMatrixDimensions(S,  214, 2, 13);
    ssSetInputPortDataType(S, 214, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 214, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 214, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 214, 1); /*direct input signal access*/	
	/* Input Port 215 */
    ssSetInputPortMatrixDimensions(S,  215, 2, 13);
    ssSetInputPortDataType(S, 215, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 215, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 215, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 215, 1); /*direct input signal access*/	
	/* Input Port 216 */
    ssSetInputPortMatrixDimensions(S,  216, 2, 13);
    ssSetInputPortDataType(S, 216, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 216, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 216, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 216, 1); /*direct input signal access*/	
	/* Input Port 217 */
    ssSetInputPortMatrixDimensions(S,  217, 2, 13);
    ssSetInputPortDataType(S, 217, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 217, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 217, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 217, 1); /*direct input signal access*/	
	/* Input Port 218 */
    ssSetInputPortMatrixDimensions(S,  218, 2, 13);
    ssSetInputPortDataType(S, 218, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 218, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 218, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 218, 1); /*direct input signal access*/	
	/* Input Port 219 */
    ssSetInputPortMatrixDimensions(S,  219, 2, 13);
    ssSetInputPortDataType(S, 219, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 219, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 219, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 219, 1); /*direct input signal access*/	
	/* Input Port 220 */
    ssSetInputPortMatrixDimensions(S,  220, 2, 13);
    ssSetInputPortDataType(S, 220, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 220, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 220, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 220, 1); /*direct input signal access*/	
	/* Input Port 221 */
    ssSetInputPortMatrixDimensions(S,  221, 2, 13);
    ssSetInputPortDataType(S, 221, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 221, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 221, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 221, 1); /*direct input signal access*/	
	/* Input Port 222 */
    ssSetInputPortMatrixDimensions(S,  222, 2, 13);
    ssSetInputPortDataType(S, 222, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 222, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 222, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 222, 1); /*direct input signal access*/	
	/* Input Port 223 */
    ssSetInputPortMatrixDimensions(S,  223, 2, 13);
    ssSetInputPortDataType(S, 223, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 223, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 223, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 223, 1); /*direct input signal access*/	
	/* Input Port 224 */
    ssSetInputPortMatrixDimensions(S,  224, 2, 13);
    ssSetInputPortDataType(S, 224, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 224, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 224, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 224, 1); /*direct input signal access*/	
	/* Input Port 225 */
    ssSetInputPortMatrixDimensions(S,  225, 2, 13);
    ssSetInputPortDataType(S, 225, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 225, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 225, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 225, 1); /*direct input signal access*/	
	/* Input Port 226 */
    ssSetInputPortMatrixDimensions(S,  226, 2, 13);
    ssSetInputPortDataType(S, 226, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 226, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 226, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 226, 1); /*direct input signal access*/	
	/* Input Port 227 */
    ssSetInputPortMatrixDimensions(S,  227, 2, 13);
    ssSetInputPortDataType(S, 227, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 227, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 227, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 227, 1); /*direct input signal access*/	
	/* Input Port 228 */
    ssSetInputPortMatrixDimensions(S,  228, 2, 13);
    ssSetInputPortDataType(S, 228, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 228, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 228, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 228, 1); /*direct input signal access*/	
	/* Input Port 229 */
    ssSetInputPortMatrixDimensions(S,  229, 2, 13);
    ssSetInputPortDataType(S, 229, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 229, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 229, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 229, 1); /*direct input signal access*/	
	/* Input Port 230 */
    ssSetInputPortMatrixDimensions(S,  230, 2, 13);
    ssSetInputPortDataType(S, 230, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 230, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 230, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 230, 1); /*direct input signal access*/	
	/* Input Port 231 */
    ssSetInputPortMatrixDimensions(S,  231, 2, 13);
    ssSetInputPortDataType(S, 231, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 231, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 231, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 231, 1); /*direct input signal access*/	
	/* Input Port 232 */
    ssSetInputPortMatrixDimensions(S,  232, 2, 13);
    ssSetInputPortDataType(S, 232, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 232, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 232, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 232, 1); /*direct input signal access*/	
	/* Input Port 233 */
    ssSetInputPortMatrixDimensions(S,  233, 2, 13);
    ssSetInputPortDataType(S, 233, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 233, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 233, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 233, 1); /*direct input signal access*/	
	/* Input Port 234 */
    ssSetInputPortMatrixDimensions(S,  234, 2, 13);
    ssSetInputPortDataType(S, 234, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 234, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 234, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 234, 1); /*direct input signal access*/	
	/* Input Port 235 */
    ssSetInputPortMatrixDimensions(S,  235, 2, 13);
    ssSetInputPortDataType(S, 235, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 235, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 235, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 235, 1); /*direct input signal access*/	
	/* Input Port 236 */
    ssSetInputPortMatrixDimensions(S,  236, 2, 13);
    ssSetInputPortDataType(S, 236, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 236, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 236, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 236, 1); /*direct input signal access*/	
	/* Input Port 237 */
    ssSetInputPortMatrixDimensions(S,  237, 2, 13);
    ssSetInputPortDataType(S, 237, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 237, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 237, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 237, 1); /*direct input signal access*/	
	/* Input Port 238 */
    ssSetInputPortMatrixDimensions(S,  238, 2, 13);
    ssSetInputPortDataType(S, 238, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 238, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 238, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 238, 1); /*direct input signal access*/	
	/* Input Port 239 */
    ssSetInputPortMatrixDimensions(S,  239, 2, 13);
    ssSetInputPortDataType(S, 239, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 239, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 239, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 239, 1); /*direct input signal access*/	
	/* Input Port 240 */
    ssSetInputPortMatrixDimensions(S,  240, 2, 13);
    ssSetInputPortDataType(S, 240, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 240, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 240, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 240, 1); /*direct input signal access*/	
	/* Input Port 241 */
    ssSetInputPortMatrixDimensions(S,  241, 2, 13);
    ssSetInputPortDataType(S, 241, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 241, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 241, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 241, 1); /*direct input signal access*/	
	/* Input Port 242 */
    ssSetInputPortMatrixDimensions(S,  242, 2, 13);
    ssSetInputPortDataType(S, 242, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 242, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 242, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 242, 1); /*direct input signal access*/	
	/* Input Port 243 */
    ssSetInputPortMatrixDimensions(S,  243, 2, 13);
    ssSetInputPortDataType(S, 243, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 243, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 243, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 243, 1); /*direct input signal access*/	
	/* Input Port 244 */
    ssSetInputPortMatrixDimensions(S,  244, 2, 13);
    ssSetInputPortDataType(S, 244, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 244, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 244, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 244, 1); /*direct input signal access*/	
	/* Input Port 245 */
    ssSetInputPortMatrixDimensions(S,  245, 2, 1);
    ssSetInputPortDataType(S, 245, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 245, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 245, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 245, 1); /*direct input signal access*/	
	/* Input Port 246 */
    ssSetInputPortMatrixDimensions(S,  246, 2, 1);
    ssSetInputPortDataType(S, 246, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 246, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 246, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 246, 1); /*direct input signal access*/	
	/* Input Port 247 */
    ssSetInputPortMatrixDimensions(S,  247, 2, 1);
    ssSetInputPortDataType(S, 247, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 247, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 247, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 247, 1); /*direct input signal access*/	
	/* Input Port 248 */
    ssSetInputPortMatrixDimensions(S,  248, 2, 1);
    ssSetInputPortDataType(S, 248, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 248, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 248, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 248, 1); /*direct input signal access*/	
	/* Input Port 249 */
    ssSetInputPortMatrixDimensions(S,  249, 2, 1);
    ssSetInputPortDataType(S, 249, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 249, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 249, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 249, 1); /*direct input signal access*/	
	/* Input Port 250 */
    ssSetInputPortMatrixDimensions(S,  250, 2, 1);
    ssSetInputPortDataType(S, 250, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 250, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 250, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 250, 1); /*direct input signal access*/	
	/* Input Port 251 */
    ssSetInputPortMatrixDimensions(S,  251, 2, 1);
    ssSetInputPortDataType(S, 251, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 251, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 251, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 251, 1); /*direct input signal access*/	
	/* Input Port 252 */
    ssSetInputPortMatrixDimensions(S,  252, 2, 1);
    ssSetInputPortDataType(S, 252, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 252, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 252, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 252, 1); /*direct input signal access*/	
	/* Input Port 253 */
    ssSetInputPortMatrixDimensions(S,  253, 2, 1);
    ssSetInputPortDataType(S, 253, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 253, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 253, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 253, 1); /*direct input signal access*/	
	/* Input Port 254 */
    ssSetInputPortMatrixDimensions(S,  254, 2, 1);
    ssSetInputPortDataType(S, 254, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 254, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 254, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 254, 1); /*direct input signal access*/	
	/* Input Port 255 */
    ssSetInputPortMatrixDimensions(S,  255, 2, 1);
    ssSetInputPortDataType(S, 255, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 255, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 255, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 255, 1); /*direct input signal access*/	
	/* Input Port 256 */
    ssSetInputPortMatrixDimensions(S,  256, 2, 1);
    ssSetInputPortDataType(S, 256, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 256, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 256, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 256, 1); /*direct input signal access*/	
	/* Input Port 257 */
    ssSetInputPortMatrixDimensions(S,  257, 2, 1);
    ssSetInputPortDataType(S, 257, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 257, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 257, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 257, 1); /*direct input signal access*/	
	/* Input Port 258 */
    ssSetInputPortMatrixDimensions(S,  258, 2, 1);
    ssSetInputPortDataType(S, 258, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 258, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 258, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 258, 1); /*direct input signal access*/	
	/* Input Port 259 */
    ssSetInputPortMatrixDimensions(S,  259, 2, 1);
    ssSetInputPortDataType(S, 259, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 259, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 259, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 259, 1); /*direct input signal access*/	
	/* Input Port 260 */
    ssSetInputPortMatrixDimensions(S,  260, 2, 1);
    ssSetInputPortDataType(S, 260, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 260, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 260, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 260, 1); /*direct input signal access*/	
	/* Input Port 261 */
    ssSetInputPortMatrixDimensions(S,  261, 2, 1);
    ssSetInputPortDataType(S, 261, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 261, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 261, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 261, 1); /*direct input signal access*/	
	/* Input Port 262 */
    ssSetInputPortMatrixDimensions(S,  262, 2, 1);
    ssSetInputPortDataType(S, 262, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 262, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 262, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 262, 1); /*direct input signal access*/	
	/* Input Port 263 */
    ssSetInputPortMatrixDimensions(S,  263, 2, 1);
    ssSetInputPortDataType(S, 263, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 263, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 263, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 263, 1); /*direct input signal access*/	
	/* Input Port 264 */
    ssSetInputPortMatrixDimensions(S,  264, 2, 1);
    ssSetInputPortDataType(S, 264, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 264, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 264, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 264, 1); /*direct input signal access*/	
	/* Input Port 265 */
    ssSetInputPortMatrixDimensions(S,  265, 2, 1);
    ssSetInputPortDataType(S, 265, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 265, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 265, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 265, 1); /*direct input signal access*/	
	/* Input Port 266 */
    ssSetInputPortMatrixDimensions(S,  266, 2, 1);
    ssSetInputPortDataType(S, 266, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 266, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 266, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 266, 1); /*direct input signal access*/	
	/* Input Port 267 */
    ssSetInputPortMatrixDimensions(S,  267, 2, 1);
    ssSetInputPortDataType(S, 267, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 267, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 267, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 267, 1); /*direct input signal access*/	
	/* Input Port 268 */
    ssSetInputPortMatrixDimensions(S,  268, 2, 1);
    ssSetInputPortDataType(S, 268, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 268, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 268, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 268, 1); /*direct input signal access*/	
	/* Input Port 269 */
    ssSetInputPortMatrixDimensions(S,  269, 2, 1);
    ssSetInputPortDataType(S, 269, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 269, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 269, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 269, 1); /*direct input signal access*/	
	/* Input Port 270 */
    ssSetInputPortMatrixDimensions(S,  270, 2, 1);
    ssSetInputPortDataType(S, 270, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 270, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 270, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 270, 1); /*direct input signal access*/	
	/* Input Port 271 */
    ssSetInputPortMatrixDimensions(S,  271, 2, 1);
    ssSetInputPortDataType(S, 271, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 271, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 271, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 271, 1); /*direct input signal access*/	
	/* Input Port 272 */
    ssSetInputPortMatrixDimensions(S,  272, 2, 1);
    ssSetInputPortDataType(S, 272, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 272, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 272, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 272, 1); /*direct input signal access*/	
	/* Input Port 273 */
    ssSetInputPortMatrixDimensions(S,  273, 2, 1);
    ssSetInputPortDataType(S, 273, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 273, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 273, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 273, 1); /*direct input signal access*/	
	/* Input Port 274 */
    ssSetInputPortMatrixDimensions(S,  274, 2, 1);
    ssSetInputPortDataType(S, 274, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 274, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 274, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 274, 1); /*direct input signal access*/	
	/* Input Port 275 */
    ssSetInputPortMatrixDimensions(S,  275, 2, 1);
    ssSetInputPortDataType(S, 275, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 275, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 275, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 275, 1); /*direct input signal access*/	
	/* Input Port 276 */
    ssSetInputPortMatrixDimensions(S,  276, 2, 1);
    ssSetInputPortDataType(S, 276, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 276, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 276, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 276, 1); /*direct input signal access*/	
	/* Input Port 277 */
    ssSetInputPortMatrixDimensions(S,  277, 2, 1);
    ssSetInputPortDataType(S, 277, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 277, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 277, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 277, 1); /*direct input signal access*/	
	/* Input Port 278 */
    ssSetInputPortMatrixDimensions(S,  278, 2, 1);
    ssSetInputPortDataType(S, 278, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 278, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 278, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 278, 1); /*direct input signal access*/	
	/* Input Port 279 */
    ssSetInputPortMatrixDimensions(S,  279, 2, 1);
    ssSetInputPortDataType(S, 279, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 279, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 279, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 279, 1); /*direct input signal access*/	
	/* Input Port 280 */
    ssSetInputPortMatrixDimensions(S,  280, 2, 1);
    ssSetInputPortDataType(S, 280, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 280, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 280, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 280, 1); /*direct input signal access*/	
	/* Input Port 281 */
    ssSetInputPortMatrixDimensions(S,  281, 2, 1);
    ssSetInputPortDataType(S, 281, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 281, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 281, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 281, 1); /*direct input signal access*/	
	/* Input Port 282 */
    ssSetInputPortMatrixDimensions(S,  282, 2, 1);
    ssSetInputPortDataType(S, 282, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 282, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 282, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 282, 1); /*direct input signal access*/	
	/* Input Port 283 */
    ssSetInputPortMatrixDimensions(S,  283, 2, 1);
    ssSetInputPortDataType(S, 283, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 283, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 283, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 283, 1); /*direct input signal access*/	
	/* Input Port 284 */
    ssSetInputPortMatrixDimensions(S,  284, 2, 1);
    ssSetInputPortDataType(S, 284, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 284, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 284, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 284, 1); /*direct input signal access*/	
	/* Input Port 285 */
    ssSetInputPortMatrixDimensions(S,  285, 2, 1);
    ssSetInputPortDataType(S, 285, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 285, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 285, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 285, 1); /*direct input signal access*/ 


	/* initialize output ports - there are 1 in total */
    if (!ssSetNumOutputPorts(S, 1)) return;    
		
	/* Output Port 0 */
    ssSetOutputPortMatrixDimensions(S,  0, 533, 1);
    ssSetOutputPortDataType(S, 0, SS_DOUBLE);
    ssSetOutputPortComplexSignal(S, 0, COMPLEX_NO); /* no complex signals suppported */


	/* set sampling time */
    ssSetNumSampleTimes(S, 1);

	/* set internal memory of block */
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 0);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    /* Take care when specifying exception free code - see sfuntmpl_doc.c */
	/* SS_OPTION_USE_TLC_WITH_ACCELERATOR removed */ 
	/* SS_OPTION_USE_TLC_WITH_ACCELERATOR removed */ 
    /* ssSetOptions(S, (SS_OPTION_EXCEPTION_FREE_CODE |
		             SS_OPTION_WORKS_WITH_CODE_REUSE)); */
	ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE );

	
}

#if defined(MATLAB_MEX_FILE)
#define MDL_SET_INPUT_PORT_DIMENSION_INFO
static void mdlSetInputPortDimensionInfo(SimStruct        *S, 
                                         int_T            port,
                                         const DimsInfo_T *dimsInfo)
{
    if(!ssSetInputPortDimensionInfo(S, port, dimsInfo)) return;
}
#endif

#define MDL_SET_OUTPUT_PORT_DIMENSION_INFO
#if defined(MDL_SET_OUTPUT_PORT_DIMENSION_INFO)
static void mdlSetOutputPortDimensionInfo(SimStruct        *S, 
                                          int_T            port, 
                                          const DimsInfo_T *dimsInfo)
{
    if (!ssSetOutputPortDimensionInfo(S, port, dimsInfo)) return;
}
#endif
# define MDL_SET_INPUT_PORT_FRAME_DATA
static void mdlSetInputPortFrameData(SimStruct  *S, 
                                     int_T      port,
                                     Frame_T    frameData)
{
    ssSetInputPortFrameData(S, port, frameData);
}
/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    Specifiy  the sample time.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);
}

#define MDL_SET_INPUT_PORT_DATA_TYPE
static void mdlSetInputPortDataType(SimStruct *S, solver_int32_default port, DTypeId dType)
{
    ssSetInputPortDataType( S, 0, dType);
}
#define MDL_SET_OUTPUT_PORT_DATA_TYPE
static void mdlSetOutputPortDataType(SimStruct *S, solver_int32_default port, DTypeId dType)
{
    ssSetOutputPortDataType(S, 0, dType);
}

#define MDL_SET_DEFAULT_PORT_DATA_TYPES
static void mdlSetDefaultPortDataTypes(SimStruct *S)
{
    ssSetInputPortDataType( S, 0, SS_DOUBLE);
    ssSetOutputPortDataType(S, 0, SS_DOUBLE);
}





/* Function: mdlOutputs =======================================================
 *
*/
static void mdlOutputs(SimStruct *S, int_T tid)
{
	solver_int32_default i, j, k;
	
	/* file pointer for printing */
	FILE *fp = NULL;

	/* Simulink data */
	const real_T *minusA_times_x0 = (const real_T*) ssGetInputPortSignal(S,0);
	const real_T *equality_rhs1 = (const real_T*) ssGetInputPortSignal(S,1);
	const real_T *equality_rhs2 = (const real_T*) ssGetInputPortSignal(S,2);
	const real_T *equality_rhs3 = (const real_T*) ssGetInputPortSignal(S,3);
	const real_T *equality_rhs4 = (const real_T*) ssGetInputPortSignal(S,4);
	const real_T *equality_rhs5 = (const real_T*) ssGetInputPortSignal(S,5);
	const real_T *equality_rhs6 = (const real_T*) ssGetInputPortSignal(S,6);
	const real_T *equality_rhs7 = (const real_T*) ssGetInputPortSignal(S,7);
	const real_T *equality_rhs8 = (const real_T*) ssGetInputPortSignal(S,8);
	const real_T *equality_rhs9 = (const real_T*) ssGetInputPortSignal(S,9);
	const real_T *equality_rhs10 = (const real_T*) ssGetInputPortSignal(S,10);
	const real_T *equality_rhs11 = (const real_T*) ssGetInputPortSignal(S,11);
	const real_T *equality_rhs12 = (const real_T*) ssGetInputPortSignal(S,12);
	const real_T *equality_rhs13 = (const real_T*) ssGetInputPortSignal(S,13);
	const real_T *equality_rhs14 = (const real_T*) ssGetInputPortSignal(S,14);
	const real_T *equality_rhs15 = (const real_T*) ssGetInputPortSignal(S,15);
	const real_T *equality_rhs16 = (const real_T*) ssGetInputPortSignal(S,16);
	const real_T *equality_rhs17 = (const real_T*) ssGetInputPortSignal(S,17);
	const real_T *equality_rhs18 = (const real_T*) ssGetInputPortSignal(S,18);
	const real_T *equality_rhs19 = (const real_T*) ssGetInputPortSignal(S,19);
	const real_T *equality_rhs20 = (const real_T*) ssGetInputPortSignal(S,20);
	const real_T *equality_rhs21 = (const real_T*) ssGetInputPortSignal(S,21);
	const real_T *equality_rhs22 = (const real_T*) ssGetInputPortSignal(S,22);
	const real_T *equality_rhs23 = (const real_T*) ssGetInputPortSignal(S,23);
	const real_T *equality_rhs24 = (const real_T*) ssGetInputPortSignal(S,24);
	const real_T *equality_rhs25 = (const real_T*) ssGetInputPortSignal(S,25);
	const real_T *equality_rhs26 = (const real_T*) ssGetInputPortSignal(S,26);
	const real_T *equality_rhs27 = (const real_T*) ssGetInputPortSignal(S,27);
	const real_T *equality_rhs28 = (const real_T*) ssGetInputPortSignal(S,28);
	const real_T *equality_rhs29 = (const real_T*) ssGetInputPortSignal(S,29);
	const real_T *equality_rhs30 = (const real_T*) ssGetInputPortSignal(S,30);
	const real_T *equality_rhs31 = (const real_T*) ssGetInputPortSignal(S,31);
	const real_T *equality_rhs32 = (const real_T*) ssGetInputPortSignal(S,32);
	const real_T *equality_rhs33 = (const real_T*) ssGetInputPortSignal(S,33);
	const real_T *equality_rhs34 = (const real_T*) ssGetInputPortSignal(S,34);
	const real_T *equality_rhs35 = (const real_T*) ssGetInputPortSignal(S,35);
	const real_T *equality_rhs36 = (const real_T*) ssGetInputPortSignal(S,36);
	const real_T *equality_rhs37 = (const real_T*) ssGetInputPortSignal(S,37);
	const real_T *equality_rhs38 = (const real_T*) ssGetInputPortSignal(S,38);
	const real_T *equality_rhs39 = (const real_T*) ssGetInputPortSignal(S,39);
	const real_T *equality_rhs40 = (const real_T*) ssGetInputPortSignal(S,40);
	const real_T *equality1 = (const real_T*) ssGetInputPortSignal(S,41);
	const real_T *equality2 = (const real_T*) ssGetInputPortSignal(S,42);
	const real_T *equality3 = (const real_T*) ssGetInputPortSignal(S,43);
	const real_T *equality4 = (const real_T*) ssGetInputPortSignal(S,44);
	const real_T *equality5 = (const real_T*) ssGetInputPortSignal(S,45);
	const real_T *equality6 = (const real_T*) ssGetInputPortSignal(S,46);
	const real_T *equality7 = (const real_T*) ssGetInputPortSignal(S,47);
	const real_T *equality8 = (const real_T*) ssGetInputPortSignal(S,48);
	const real_T *equality9 = (const real_T*) ssGetInputPortSignal(S,49);
	const real_T *equality10 = (const real_T*) ssGetInputPortSignal(S,50);
	const real_T *equality11 = (const real_T*) ssGetInputPortSignal(S,51);
	const real_T *equality12 = (const real_T*) ssGetInputPortSignal(S,52);
	const real_T *equality13 = (const real_T*) ssGetInputPortSignal(S,53);
	const real_T *equality14 = (const real_T*) ssGetInputPortSignal(S,54);
	const real_T *equality15 = (const real_T*) ssGetInputPortSignal(S,55);
	const real_T *equality16 = (const real_T*) ssGetInputPortSignal(S,56);
	const real_T *equality17 = (const real_T*) ssGetInputPortSignal(S,57);
	const real_T *equality18 = (const real_T*) ssGetInputPortSignal(S,58);
	const real_T *equality19 = (const real_T*) ssGetInputPortSignal(S,59);
	const real_T *equality20 = (const real_T*) ssGetInputPortSignal(S,60);
	const real_T *equality21 = (const real_T*) ssGetInputPortSignal(S,61);
	const real_T *equality22 = (const real_T*) ssGetInputPortSignal(S,62);
	const real_T *equality23 = (const real_T*) ssGetInputPortSignal(S,63);
	const real_T *equality24 = (const real_T*) ssGetInputPortSignal(S,64);
	const real_T *equality25 = (const real_T*) ssGetInputPortSignal(S,65);
	const real_T *equality26 = (const real_T*) ssGetInputPortSignal(S,66);
	const real_T *equality27 = (const real_T*) ssGetInputPortSignal(S,67);
	const real_T *equality28 = (const real_T*) ssGetInputPortSignal(S,68);
	const real_T *equality29 = (const real_T*) ssGetInputPortSignal(S,69);
	const real_T *equality30 = (const real_T*) ssGetInputPortSignal(S,70);
	const real_T *equality31 = (const real_T*) ssGetInputPortSignal(S,71);
	const real_T *equality32 = (const real_T*) ssGetInputPortSignal(S,72);
	const real_T *equality33 = (const real_T*) ssGetInputPortSignal(S,73);
	const real_T *equality34 = (const real_T*) ssGetInputPortSignal(S,74);
	const real_T *equality35 = (const real_T*) ssGetInputPortSignal(S,75);
	const real_T *equality36 = (const real_T*) ssGetInputPortSignal(S,76);
	const real_T *equality37 = (const real_T*) ssGetInputPortSignal(S,77);
	const real_T *equality38 = (const real_T*) ssGetInputPortSignal(S,78);
	const real_T *equality39 = (const real_T*) ssGetInputPortSignal(S,79);
	const real_T *equality40 = (const real_T*) ssGetInputPortSignal(S,80);
	const real_T *cost_H1 = (const real_T*) ssGetInputPortSignal(S,81);
	const real_T *cost_H2 = (const real_T*) ssGetInputPortSignal(S,82);
	const real_T *cost_H3 = (const real_T*) ssGetInputPortSignal(S,83);
	const real_T *cost_H4 = (const real_T*) ssGetInputPortSignal(S,84);
	const real_T *cost_H5 = (const real_T*) ssGetInputPortSignal(S,85);
	const real_T *cost_H6 = (const real_T*) ssGetInputPortSignal(S,86);
	const real_T *cost_H7 = (const real_T*) ssGetInputPortSignal(S,87);
	const real_T *cost_H8 = (const real_T*) ssGetInputPortSignal(S,88);
	const real_T *cost_H9 = (const real_T*) ssGetInputPortSignal(S,89);
	const real_T *cost_H10 = (const real_T*) ssGetInputPortSignal(S,90);
	const real_T *cost_H11 = (const real_T*) ssGetInputPortSignal(S,91);
	const real_T *cost_H12 = (const real_T*) ssGetInputPortSignal(S,92);
	const real_T *cost_H13 = (const real_T*) ssGetInputPortSignal(S,93);
	const real_T *cost_H14 = (const real_T*) ssGetInputPortSignal(S,94);
	const real_T *cost_H15 = (const real_T*) ssGetInputPortSignal(S,95);
	const real_T *cost_H16 = (const real_T*) ssGetInputPortSignal(S,96);
	const real_T *cost_H17 = (const real_T*) ssGetInputPortSignal(S,97);
	const real_T *cost_H18 = (const real_T*) ssGetInputPortSignal(S,98);
	const real_T *cost_H19 = (const real_T*) ssGetInputPortSignal(S,99);
	const real_T *cost_H20 = (const real_T*) ssGetInputPortSignal(S,100);
	const real_T *cost_H21 = (const real_T*) ssGetInputPortSignal(S,101);
	const real_T *cost_H22 = (const real_T*) ssGetInputPortSignal(S,102);
	const real_T *cost_H23 = (const real_T*) ssGetInputPortSignal(S,103);
	const real_T *cost_H24 = (const real_T*) ssGetInputPortSignal(S,104);
	const real_T *cost_H25 = (const real_T*) ssGetInputPortSignal(S,105);
	const real_T *cost_H26 = (const real_T*) ssGetInputPortSignal(S,106);
	const real_T *cost_H27 = (const real_T*) ssGetInputPortSignal(S,107);
	const real_T *cost_H28 = (const real_T*) ssGetInputPortSignal(S,108);
	const real_T *cost_H29 = (const real_T*) ssGetInputPortSignal(S,109);
	const real_T *cost_H30 = (const real_T*) ssGetInputPortSignal(S,110);
	const real_T *cost_H31 = (const real_T*) ssGetInputPortSignal(S,111);
	const real_T *cost_H32 = (const real_T*) ssGetInputPortSignal(S,112);
	const real_T *cost_H33 = (const real_T*) ssGetInputPortSignal(S,113);
	const real_T *cost_H34 = (const real_T*) ssGetInputPortSignal(S,114);
	const real_T *cost_H35 = (const real_T*) ssGetInputPortSignal(S,115);
	const real_T *cost_H36 = (const real_T*) ssGetInputPortSignal(S,116);
	const real_T *cost_H37 = (const real_T*) ssGetInputPortSignal(S,117);
	const real_T *cost_H38 = (const real_T*) ssGetInputPortSignal(S,118);
	const real_T *cost_H39 = (const real_T*) ssGetInputPortSignal(S,119);
	const real_T *cost_H40 = (const real_T*) ssGetInputPortSignal(S,120);
	const real_T *cost_H41 = (const real_T*) ssGetInputPortSignal(S,121);
	const real_T *cost_f1 = (const real_T*) ssGetInputPortSignal(S,122);
	const real_T *cost_f2 = (const real_T*) ssGetInputPortSignal(S,123);
	const real_T *cost_f3 = (const real_T*) ssGetInputPortSignal(S,124);
	const real_T *cost_f4 = (const real_T*) ssGetInputPortSignal(S,125);
	const real_T *cost_f5 = (const real_T*) ssGetInputPortSignal(S,126);
	const real_T *cost_f6 = (const real_T*) ssGetInputPortSignal(S,127);
	const real_T *cost_f7 = (const real_T*) ssGetInputPortSignal(S,128);
	const real_T *cost_f8 = (const real_T*) ssGetInputPortSignal(S,129);
	const real_T *cost_f9 = (const real_T*) ssGetInputPortSignal(S,130);
	const real_T *cost_f10 = (const real_T*) ssGetInputPortSignal(S,131);
	const real_T *cost_f11 = (const real_T*) ssGetInputPortSignal(S,132);
	const real_T *cost_f12 = (const real_T*) ssGetInputPortSignal(S,133);
	const real_T *cost_f13 = (const real_T*) ssGetInputPortSignal(S,134);
	const real_T *cost_f14 = (const real_T*) ssGetInputPortSignal(S,135);
	const real_T *cost_f15 = (const real_T*) ssGetInputPortSignal(S,136);
	const real_T *cost_f16 = (const real_T*) ssGetInputPortSignal(S,137);
	const real_T *cost_f17 = (const real_T*) ssGetInputPortSignal(S,138);
	const real_T *cost_f18 = (const real_T*) ssGetInputPortSignal(S,139);
	const real_T *cost_f19 = (const real_T*) ssGetInputPortSignal(S,140);
	const real_T *cost_f20 = (const real_T*) ssGetInputPortSignal(S,141);
	const real_T *cost_f21 = (const real_T*) ssGetInputPortSignal(S,142);
	const real_T *cost_f22 = (const real_T*) ssGetInputPortSignal(S,143);
	const real_T *cost_f23 = (const real_T*) ssGetInputPortSignal(S,144);
	const real_T *cost_f24 = (const real_T*) ssGetInputPortSignal(S,145);
	const real_T *cost_f25 = (const real_T*) ssGetInputPortSignal(S,146);
	const real_T *cost_f26 = (const real_T*) ssGetInputPortSignal(S,147);
	const real_T *cost_f27 = (const real_T*) ssGetInputPortSignal(S,148);
	const real_T *cost_f28 = (const real_T*) ssGetInputPortSignal(S,149);
	const real_T *cost_f29 = (const real_T*) ssGetInputPortSignal(S,150);
	const real_T *cost_f30 = (const real_T*) ssGetInputPortSignal(S,151);
	const real_T *cost_f31 = (const real_T*) ssGetInputPortSignal(S,152);
	const real_T *cost_f32 = (const real_T*) ssGetInputPortSignal(S,153);
	const real_T *cost_f33 = (const real_T*) ssGetInputPortSignal(S,154);
	const real_T *cost_f34 = (const real_T*) ssGetInputPortSignal(S,155);
	const real_T *cost_f35 = (const real_T*) ssGetInputPortSignal(S,156);
	const real_T *cost_f36 = (const real_T*) ssGetInputPortSignal(S,157);
	const real_T *cost_f37 = (const real_T*) ssGetInputPortSignal(S,158);
	const real_T *cost_f38 = (const real_T*) ssGetInputPortSignal(S,159);
	const real_T *cost_f39 = (const real_T*) ssGetInputPortSignal(S,160);
	const real_T *cost_f40 = (const real_T*) ssGetInputPortSignal(S,161);
	const real_T *cost_f41 = (const real_T*) ssGetInputPortSignal(S,162);
	const real_T *eq_D1 = (const real_T*) ssGetInputPortSignal(S,163);
	const real_T *eq_D2 = (const real_T*) ssGetInputPortSignal(S,164);
	const real_T *eq_D3 = (const real_T*) ssGetInputPortSignal(S,165);
	const real_T *eq_D4 = (const real_T*) ssGetInputPortSignal(S,166);
	const real_T *eq_D5 = (const real_T*) ssGetInputPortSignal(S,167);
	const real_T *eq_D6 = (const real_T*) ssGetInputPortSignal(S,168);
	const real_T *eq_D7 = (const real_T*) ssGetInputPortSignal(S,169);
	const real_T *eq_D8 = (const real_T*) ssGetInputPortSignal(S,170);
	const real_T *eq_D9 = (const real_T*) ssGetInputPortSignal(S,171);
	const real_T *eq_D10 = (const real_T*) ssGetInputPortSignal(S,172);
	const real_T *eq_D11 = (const real_T*) ssGetInputPortSignal(S,173);
	const real_T *eq_D12 = (const real_T*) ssGetInputPortSignal(S,174);
	const real_T *eq_D13 = (const real_T*) ssGetInputPortSignal(S,175);
	const real_T *eq_D14 = (const real_T*) ssGetInputPortSignal(S,176);
	const real_T *eq_D15 = (const real_T*) ssGetInputPortSignal(S,177);
	const real_T *eq_D16 = (const real_T*) ssGetInputPortSignal(S,178);
	const real_T *eq_D17 = (const real_T*) ssGetInputPortSignal(S,179);
	const real_T *eq_D18 = (const real_T*) ssGetInputPortSignal(S,180);
	const real_T *eq_D19 = (const real_T*) ssGetInputPortSignal(S,181);
	const real_T *eq_D20 = (const real_T*) ssGetInputPortSignal(S,182);
	const real_T *eq_D21 = (const real_T*) ssGetInputPortSignal(S,183);
	const real_T *eq_D22 = (const real_T*) ssGetInputPortSignal(S,184);
	const real_T *eq_D23 = (const real_T*) ssGetInputPortSignal(S,185);
	const real_T *eq_D24 = (const real_T*) ssGetInputPortSignal(S,186);
	const real_T *eq_D25 = (const real_T*) ssGetInputPortSignal(S,187);
	const real_T *eq_D26 = (const real_T*) ssGetInputPortSignal(S,188);
	const real_T *eq_D27 = (const real_T*) ssGetInputPortSignal(S,189);
	const real_T *eq_D28 = (const real_T*) ssGetInputPortSignal(S,190);
	const real_T *eq_D29 = (const real_T*) ssGetInputPortSignal(S,191);
	const real_T *eq_D30 = (const real_T*) ssGetInputPortSignal(S,192);
	const real_T *eq_D31 = (const real_T*) ssGetInputPortSignal(S,193);
	const real_T *eq_D32 = (const real_T*) ssGetInputPortSignal(S,194);
	const real_T *eq_D33 = (const real_T*) ssGetInputPortSignal(S,195);
	const real_T *eq_D34 = (const real_T*) ssGetInputPortSignal(S,196);
	const real_T *eq_D35 = (const real_T*) ssGetInputPortSignal(S,197);
	const real_T *eq_D36 = (const real_T*) ssGetInputPortSignal(S,198);
	const real_T *eq_D37 = (const real_T*) ssGetInputPortSignal(S,199);
	const real_T *eq_D38 = (const real_T*) ssGetInputPortSignal(S,200);
	const real_T *eq_D39 = (const real_T*) ssGetInputPortSignal(S,201);
	const real_T *eq_D40 = (const real_T*) ssGetInputPortSignal(S,202);
	const real_T *eq_D41 = (const real_T*) ssGetInputPortSignal(S,203);
	const real_T *polytopic_A1 = (const real_T*) ssGetInputPortSignal(S,204);
	const real_T *polytopic_A2 = (const real_T*) ssGetInputPortSignal(S,205);
	const real_T *polytopic_A3 = (const real_T*) ssGetInputPortSignal(S,206);
	const real_T *polytopic_A4 = (const real_T*) ssGetInputPortSignal(S,207);
	const real_T *polytopic_A5 = (const real_T*) ssGetInputPortSignal(S,208);
	const real_T *polytopic_A6 = (const real_T*) ssGetInputPortSignal(S,209);
	const real_T *polytopic_A7 = (const real_T*) ssGetInputPortSignal(S,210);
	const real_T *polytopic_A8 = (const real_T*) ssGetInputPortSignal(S,211);
	const real_T *polytopic_A9 = (const real_T*) ssGetInputPortSignal(S,212);
	const real_T *polytopic_A10 = (const real_T*) ssGetInputPortSignal(S,213);
	const real_T *polytopic_A11 = (const real_T*) ssGetInputPortSignal(S,214);
	const real_T *polytopic_A12 = (const real_T*) ssGetInputPortSignal(S,215);
	const real_T *polytopic_A13 = (const real_T*) ssGetInputPortSignal(S,216);
	const real_T *polytopic_A14 = (const real_T*) ssGetInputPortSignal(S,217);
	const real_T *polytopic_A15 = (const real_T*) ssGetInputPortSignal(S,218);
	const real_T *polytopic_A16 = (const real_T*) ssGetInputPortSignal(S,219);
	const real_T *polytopic_A17 = (const real_T*) ssGetInputPortSignal(S,220);
	const real_T *polytopic_A18 = (const real_T*) ssGetInputPortSignal(S,221);
	const real_T *polytopic_A19 = (const real_T*) ssGetInputPortSignal(S,222);
	const real_T *polytopic_A20 = (const real_T*) ssGetInputPortSignal(S,223);
	const real_T *polytopic_A21 = (const real_T*) ssGetInputPortSignal(S,224);
	const real_T *polytopic_A22 = (const real_T*) ssGetInputPortSignal(S,225);
	const real_T *polytopic_A23 = (const real_T*) ssGetInputPortSignal(S,226);
	const real_T *polytopic_A24 = (const real_T*) ssGetInputPortSignal(S,227);
	const real_T *polytopic_A25 = (const real_T*) ssGetInputPortSignal(S,228);
	const real_T *polytopic_A26 = (const real_T*) ssGetInputPortSignal(S,229);
	const real_T *polytopic_A27 = (const real_T*) ssGetInputPortSignal(S,230);
	const real_T *polytopic_A28 = (const real_T*) ssGetInputPortSignal(S,231);
	const real_T *polytopic_A29 = (const real_T*) ssGetInputPortSignal(S,232);
	const real_T *polytopic_A30 = (const real_T*) ssGetInputPortSignal(S,233);
	const real_T *polytopic_A31 = (const real_T*) ssGetInputPortSignal(S,234);
	const real_T *polytopic_A32 = (const real_T*) ssGetInputPortSignal(S,235);
	const real_T *polytopic_A33 = (const real_T*) ssGetInputPortSignal(S,236);
	const real_T *polytopic_A34 = (const real_T*) ssGetInputPortSignal(S,237);
	const real_T *polytopic_A35 = (const real_T*) ssGetInputPortSignal(S,238);
	const real_T *polytopic_A36 = (const real_T*) ssGetInputPortSignal(S,239);
	const real_T *polytopic_A37 = (const real_T*) ssGetInputPortSignal(S,240);
	const real_T *polytopic_A38 = (const real_T*) ssGetInputPortSignal(S,241);
	const real_T *polytopic_A39 = (const real_T*) ssGetInputPortSignal(S,242);
	const real_T *polytopic_A40 = (const real_T*) ssGetInputPortSignal(S,243);
	const real_T *polytopic_A41 = (const real_T*) ssGetInputPortSignal(S,244);
	const real_T *polytopic_b1 = (const real_T*) ssGetInputPortSignal(S,245);
	const real_T *polytopic_b2 = (const real_T*) ssGetInputPortSignal(S,246);
	const real_T *polytopic_b3 = (const real_T*) ssGetInputPortSignal(S,247);
	const real_T *polytopic_b4 = (const real_T*) ssGetInputPortSignal(S,248);
	const real_T *polytopic_b5 = (const real_T*) ssGetInputPortSignal(S,249);
	const real_T *polytopic_b6 = (const real_T*) ssGetInputPortSignal(S,250);
	const real_T *polytopic_b7 = (const real_T*) ssGetInputPortSignal(S,251);
	const real_T *polytopic_b8 = (const real_T*) ssGetInputPortSignal(S,252);
	const real_T *polytopic_b9 = (const real_T*) ssGetInputPortSignal(S,253);
	const real_T *polytopic_b10 = (const real_T*) ssGetInputPortSignal(S,254);
	const real_T *polytopic_b11 = (const real_T*) ssGetInputPortSignal(S,255);
	const real_T *polytopic_b12 = (const real_T*) ssGetInputPortSignal(S,256);
	const real_T *polytopic_b13 = (const real_T*) ssGetInputPortSignal(S,257);
	const real_T *polytopic_b14 = (const real_T*) ssGetInputPortSignal(S,258);
	const real_T *polytopic_b15 = (const real_T*) ssGetInputPortSignal(S,259);
	const real_T *polytopic_b16 = (const real_T*) ssGetInputPortSignal(S,260);
	const real_T *polytopic_b17 = (const real_T*) ssGetInputPortSignal(S,261);
	const real_T *polytopic_b18 = (const real_T*) ssGetInputPortSignal(S,262);
	const real_T *polytopic_b19 = (const real_T*) ssGetInputPortSignal(S,263);
	const real_T *polytopic_b20 = (const real_T*) ssGetInputPortSignal(S,264);
	const real_T *polytopic_b21 = (const real_T*) ssGetInputPortSignal(S,265);
	const real_T *polytopic_b22 = (const real_T*) ssGetInputPortSignal(S,266);
	const real_T *polytopic_b23 = (const real_T*) ssGetInputPortSignal(S,267);
	const real_T *polytopic_b24 = (const real_T*) ssGetInputPortSignal(S,268);
	const real_T *polytopic_b25 = (const real_T*) ssGetInputPortSignal(S,269);
	const real_T *polytopic_b26 = (const real_T*) ssGetInputPortSignal(S,270);
	const real_T *polytopic_b27 = (const real_T*) ssGetInputPortSignal(S,271);
	const real_T *polytopic_b28 = (const real_T*) ssGetInputPortSignal(S,272);
	const real_T *polytopic_b29 = (const real_T*) ssGetInputPortSignal(S,273);
	const real_T *polytopic_b30 = (const real_T*) ssGetInputPortSignal(S,274);
	const real_T *polytopic_b31 = (const real_T*) ssGetInputPortSignal(S,275);
	const real_T *polytopic_b32 = (const real_T*) ssGetInputPortSignal(S,276);
	const real_T *polytopic_b33 = (const real_T*) ssGetInputPortSignal(S,277);
	const real_T *polytopic_b34 = (const real_T*) ssGetInputPortSignal(S,278);
	const real_T *polytopic_b35 = (const real_T*) ssGetInputPortSignal(S,279);
	const real_T *polytopic_b36 = (const real_T*) ssGetInputPortSignal(S,280);
	const real_T *polytopic_b37 = (const real_T*) ssGetInputPortSignal(S,281);
	const real_T *polytopic_b38 = (const real_T*) ssGetInputPortSignal(S,282);
	const real_T *polytopic_b39 = (const real_T*) ssGetInputPortSignal(S,283);
	const real_T *polytopic_b40 = (const real_T*) ssGetInputPortSignal(S,284);
	const real_T *polytopic_b41 = (const real_T*) ssGetInputPortSignal(S,285);
	
    real_T *z = (real_T*) ssGetOutputPortSignal(S,0);
	
	

	/* Solver data */
	static FORCES_CMPC_params params;
	static FORCES_CMPC_output output;
	static FORCES_CMPC_info info;	
	solver_int32_default exitflag;

	/* Extra NMPC data */
	

	/* Copy inputs */
	for( i=0; i<10; i++)
	{ 
		params.minusA_times_x0[i] = (double) minusA_times_x0[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs1[i] = (double) equality_rhs1[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs2[i] = (double) equality_rhs2[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs3[i] = (double) equality_rhs3[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs4[i] = (double) equality_rhs4[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs5[i] = (double) equality_rhs5[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs6[i] = (double) equality_rhs6[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs7[i] = (double) equality_rhs7[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs8[i] = (double) equality_rhs8[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs9[i] = (double) equality_rhs9[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs10[i] = (double) equality_rhs10[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs11[i] = (double) equality_rhs11[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs12[i] = (double) equality_rhs12[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs13[i] = (double) equality_rhs13[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs14[i] = (double) equality_rhs14[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs15[i] = (double) equality_rhs15[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs16[i] = (double) equality_rhs16[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs17[i] = (double) equality_rhs17[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs18[i] = (double) equality_rhs18[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs19[i] = (double) equality_rhs19[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs20[i] = (double) equality_rhs20[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs21[i] = (double) equality_rhs21[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs22[i] = (double) equality_rhs22[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs23[i] = (double) equality_rhs23[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs24[i] = (double) equality_rhs24[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs25[i] = (double) equality_rhs25[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs26[i] = (double) equality_rhs26[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs27[i] = (double) equality_rhs27[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs28[i] = (double) equality_rhs28[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs29[i] = (double) equality_rhs29[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs30[i] = (double) equality_rhs30[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs31[i] = (double) equality_rhs31[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs32[i] = (double) equality_rhs32[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs33[i] = (double) equality_rhs33[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs34[i] = (double) equality_rhs34[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs35[i] = (double) equality_rhs35[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs36[i] = (double) equality_rhs36[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs37[i] = (double) equality_rhs37[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs38[i] = (double) equality_rhs38[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs39[i] = (double) equality_rhs39[i]; 
	}

	for( i=0; i<10; i++)
	{ 
		params.equality_rhs40[i] = (double) equality_rhs40[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality1[i] = (double) equality1[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality2[i] = (double) equality2[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality3[i] = (double) equality3[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality4[i] = (double) equality4[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality5[i] = (double) equality5[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality6[i] = (double) equality6[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality7[i] = (double) equality7[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality8[i] = (double) equality8[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality9[i] = (double) equality9[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality10[i] = (double) equality10[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality11[i] = (double) equality11[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality12[i] = (double) equality12[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality13[i] = (double) equality13[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality14[i] = (double) equality14[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality15[i] = (double) equality15[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality16[i] = (double) equality16[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality17[i] = (double) equality17[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality18[i] = (double) equality18[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality19[i] = (double) equality19[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality20[i] = (double) equality20[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality21[i] = (double) equality21[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality22[i] = (double) equality22[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality23[i] = (double) equality23[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality24[i] = (double) equality24[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality25[i] = (double) equality25[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality26[i] = (double) equality26[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality27[i] = (double) equality27[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality28[i] = (double) equality28[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality29[i] = (double) equality29[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality30[i] = (double) equality30[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality31[i] = (double) equality31[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality32[i] = (double) equality32[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality33[i] = (double) equality33[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality34[i] = (double) equality34[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality35[i] = (double) equality35[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality36[i] = (double) equality36[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality37[i] = (double) equality37[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality38[i] = (double) equality38[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality39[i] = (double) equality39[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality40[i] = (double) equality40[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H1[i] = (double) cost_H1[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H2[i] = (double) cost_H2[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H3[i] = (double) cost_H3[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H4[i] = (double) cost_H4[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H5[i] = (double) cost_H5[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H6[i] = (double) cost_H6[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H7[i] = (double) cost_H7[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H8[i] = (double) cost_H8[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H9[i] = (double) cost_H9[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H10[i] = (double) cost_H10[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H11[i] = (double) cost_H11[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H12[i] = (double) cost_H12[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H13[i] = (double) cost_H13[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H14[i] = (double) cost_H14[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H15[i] = (double) cost_H15[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H16[i] = (double) cost_H16[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H17[i] = (double) cost_H17[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H18[i] = (double) cost_H18[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H19[i] = (double) cost_H19[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H20[i] = (double) cost_H20[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H21[i] = (double) cost_H21[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H22[i] = (double) cost_H22[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H23[i] = (double) cost_H23[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H24[i] = (double) cost_H24[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H25[i] = (double) cost_H25[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H26[i] = (double) cost_H26[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H27[i] = (double) cost_H27[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H28[i] = (double) cost_H28[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H29[i] = (double) cost_H29[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H30[i] = (double) cost_H30[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H31[i] = (double) cost_H31[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H32[i] = (double) cost_H32[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H33[i] = (double) cost_H33[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H34[i] = (double) cost_H34[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H35[i] = (double) cost_H35[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H36[i] = (double) cost_H36[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H37[i] = (double) cost_H37[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H38[i] = (double) cost_H38[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H39[i] = (double) cost_H39[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H40[i] = (double) cost_H40[i]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H41[i] = (double) cost_H41[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f1[i] = (double) cost_f1[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f2[i] = (double) cost_f2[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f3[i] = (double) cost_f3[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f4[i] = (double) cost_f4[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f5[i] = (double) cost_f5[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f6[i] = (double) cost_f6[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f7[i] = (double) cost_f7[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f8[i] = (double) cost_f8[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f9[i] = (double) cost_f9[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f10[i] = (double) cost_f10[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f11[i] = (double) cost_f11[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f12[i] = (double) cost_f12[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f13[i] = (double) cost_f13[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f14[i] = (double) cost_f14[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f15[i] = (double) cost_f15[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f16[i] = (double) cost_f16[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f17[i] = (double) cost_f17[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f18[i] = (double) cost_f18[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f19[i] = (double) cost_f19[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f20[i] = (double) cost_f20[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f21[i] = (double) cost_f21[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f22[i] = (double) cost_f22[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f23[i] = (double) cost_f23[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f24[i] = (double) cost_f24[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f25[i] = (double) cost_f25[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f26[i] = (double) cost_f26[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f27[i] = (double) cost_f27[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f28[i] = (double) cost_f28[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f29[i] = (double) cost_f29[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f30[i] = (double) cost_f30[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f31[i] = (double) cost_f31[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f32[i] = (double) cost_f32[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f33[i] = (double) cost_f33[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f34[i] = (double) cost_f34[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f35[i] = (double) cost_f35[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f36[i] = (double) cost_f36[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f37[i] = (double) cost_f37[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f38[i] = (double) cost_f38[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f39[i] = (double) cost_f39[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f40[i] = (double) cost_f40[i]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f41[i] = (double) cost_f41[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D1[i] = (double) eq_D1[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D2[i] = (double) eq_D2[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D3[i] = (double) eq_D3[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D4[i] = (double) eq_D4[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D5[i] = (double) eq_D5[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D6[i] = (double) eq_D6[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D7[i] = (double) eq_D7[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D8[i] = (double) eq_D8[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D9[i] = (double) eq_D9[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D10[i] = (double) eq_D10[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D11[i] = (double) eq_D11[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D12[i] = (double) eq_D12[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D13[i] = (double) eq_D13[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D14[i] = (double) eq_D14[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D15[i] = (double) eq_D15[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D16[i] = (double) eq_D16[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D17[i] = (double) eq_D17[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D18[i] = (double) eq_D18[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D19[i] = (double) eq_D19[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D20[i] = (double) eq_D20[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D21[i] = (double) eq_D21[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D22[i] = (double) eq_D22[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D23[i] = (double) eq_D23[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D24[i] = (double) eq_D24[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D25[i] = (double) eq_D25[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D26[i] = (double) eq_D26[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D27[i] = (double) eq_D27[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D28[i] = (double) eq_D28[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D29[i] = (double) eq_D29[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D30[i] = (double) eq_D30[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D31[i] = (double) eq_D31[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D32[i] = (double) eq_D32[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D33[i] = (double) eq_D33[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D34[i] = (double) eq_D34[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D35[i] = (double) eq_D35[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D36[i] = (double) eq_D36[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D37[i] = (double) eq_D37[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D38[i] = (double) eq_D38[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D39[i] = (double) eq_D39[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D40[i] = (double) eq_D40[i]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D41[i] = (double) eq_D41[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A1[i] = (double) polytopic_A1[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A2[i] = (double) polytopic_A2[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A3[i] = (double) polytopic_A3[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A4[i] = (double) polytopic_A4[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A5[i] = (double) polytopic_A5[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A6[i] = (double) polytopic_A6[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A7[i] = (double) polytopic_A7[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A8[i] = (double) polytopic_A8[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A9[i] = (double) polytopic_A9[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A10[i] = (double) polytopic_A10[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A11[i] = (double) polytopic_A11[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A12[i] = (double) polytopic_A12[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A13[i] = (double) polytopic_A13[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A14[i] = (double) polytopic_A14[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A15[i] = (double) polytopic_A15[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A16[i] = (double) polytopic_A16[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A17[i] = (double) polytopic_A17[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A18[i] = (double) polytopic_A18[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A19[i] = (double) polytopic_A19[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A20[i] = (double) polytopic_A20[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A21[i] = (double) polytopic_A21[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A22[i] = (double) polytopic_A22[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A23[i] = (double) polytopic_A23[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A24[i] = (double) polytopic_A24[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A25[i] = (double) polytopic_A25[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A26[i] = (double) polytopic_A26[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A27[i] = (double) polytopic_A27[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A28[i] = (double) polytopic_A28[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A29[i] = (double) polytopic_A29[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A30[i] = (double) polytopic_A30[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A31[i] = (double) polytopic_A31[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A32[i] = (double) polytopic_A32[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A33[i] = (double) polytopic_A33[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A34[i] = (double) polytopic_A34[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A35[i] = (double) polytopic_A35[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A36[i] = (double) polytopic_A36[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A37[i] = (double) polytopic_A37[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A38[i] = (double) polytopic_A38[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A39[i] = (double) polytopic_A39[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A40[i] = (double) polytopic_A40[i]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A41[i] = (double) polytopic_A41[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b1[i] = (double) polytopic_b1[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b2[i] = (double) polytopic_b2[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b3[i] = (double) polytopic_b3[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b4[i] = (double) polytopic_b4[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b5[i] = (double) polytopic_b5[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b6[i] = (double) polytopic_b6[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b7[i] = (double) polytopic_b7[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b8[i] = (double) polytopic_b8[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b9[i] = (double) polytopic_b9[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b10[i] = (double) polytopic_b10[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b11[i] = (double) polytopic_b11[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b12[i] = (double) polytopic_b12[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b13[i] = (double) polytopic_b13[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b14[i] = (double) polytopic_b14[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b15[i] = (double) polytopic_b15[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b16[i] = (double) polytopic_b16[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b17[i] = (double) polytopic_b17[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b18[i] = (double) polytopic_b18[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b19[i] = (double) polytopic_b19[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b20[i] = (double) polytopic_b20[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b21[i] = (double) polytopic_b21[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b22[i] = (double) polytopic_b22[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b23[i] = (double) polytopic_b23[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b24[i] = (double) polytopic_b24[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b25[i] = (double) polytopic_b25[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b26[i] = (double) polytopic_b26[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b27[i] = (double) polytopic_b27[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b28[i] = (double) polytopic_b28[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b29[i] = (double) polytopic_b29[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b30[i] = (double) polytopic_b30[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b31[i] = (double) polytopic_b31[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b32[i] = (double) polytopic_b32[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b33[i] = (double) polytopic_b33[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b34[i] = (double) polytopic_b34[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b35[i] = (double) polytopic_b35[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b36[i] = (double) polytopic_b36[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b37[i] = (double) polytopic_b37[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b38[i] = (double) polytopic_b38[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b39[i] = (double) polytopic_b39[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b40[i] = (double) polytopic_b40[i]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b41[i] = (double) polytopic_b41[i]; 
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

	/* Call solver */
	exitflag = FORCES_CMPC_solve(&params, &output, &info, fp );

	#if SET_PRINTLEVEL_FORCES_CMPC > 0
		/* Read contents of printfs printed to file */
		rewind(fp);
		while( (i = fgetc(fp)) != EOF ) 
		{
			ssPrintf("%c",i);
		}
		fclose(fp);
	#endif

	

	/* Copy outputs */
	for( i=0; i<533; i++)
	{ 
		z[i] = (real_T) output.z[i]; 
	}

	
}





/* Function: mdlTerminate =====================================================
 * Abstract:
 *    In this function, you should perform any actions that are necessary
 *    at the termination of a simulation.  For example, if memory was
 *    allocated in mdlStart, this is the place to free it.
 */
static void mdlTerminate(SimStruct *S)
{
}
#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif


