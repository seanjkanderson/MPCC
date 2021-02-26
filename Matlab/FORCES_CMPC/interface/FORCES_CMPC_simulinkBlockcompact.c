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
#define S_FUNCTION_NAME FORCES_CMPC_simulinkBlockcompact

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

	/* initialize input ports - there are 7 in total */
    if (!ssSetNumInputPorts(S, 7)) return;
    	
	/* Input Port 0 */
    ssSetInputPortMatrixDimensions(S,  0, 10, 41);
    ssSetInputPortDataType(S, 0, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 0, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 0, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 0, 1); /*direct input signal access*/	
	/* Input Port 1 */
    ssSetInputPortMatrixDimensions(S,  1, 10, 533);
    ssSetInputPortDataType(S, 1, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 1, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 1, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 1, 1); /*direct input signal access*/	
	/* Input Port 2 */
    ssSetInputPortMatrixDimensions(S,  2, 10, 520);
    ssSetInputPortDataType(S, 2, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 2, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 2, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 2, 1); /*direct input signal access*/	
	/* Input Port 3 */
    ssSetInputPortMatrixDimensions(S,  3, 13, 533);
    ssSetInputPortDataType(S, 3, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 3, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 3, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 3, 1); /*direct input signal access*/	
	/* Input Port 4 */
    ssSetInputPortMatrixDimensions(S,  4, 13, 41);
    ssSetInputPortDataType(S, 4, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 4, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 4, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 4, 1); /*direct input signal access*/	
	/* Input Port 5 */
    ssSetInputPortMatrixDimensions(S,  5, 2, 41);
    ssSetInputPortDataType(S, 5, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 5, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 5, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 5, 1); /*direct input signal access*/	
	/* Input Port 6 */
    ssSetInputPortMatrixDimensions(S,  6, 2, 533);
    ssSetInputPortDataType(S, 6, SS_DOUBLE);
    ssSetInputPortComplexSignal(S, 6, COMPLEX_NO); /* no complex signals suppported */
    ssSetInputPortDirectFeedThrough(S, 6, 1); /* Feedthrough enabled */
    ssSetInputPortRequiredContiguous(S, 6, 1); /*direct input signal access*/ 


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
	const real_T *c = (const real_T*) ssGetInputPortSignal(S,0);
	const real_T *D = (const real_T*) ssGetInputPortSignal(S,1);
	const real_T *C = (const real_T*) ssGetInputPortSignal(S,2);
	const real_T *H = (const real_T*) ssGetInputPortSignal(S,3);
	const real_T *f = (const real_T*) ssGetInputPortSignal(S,4);
	const real_T *b = (const real_T*) ssGetInputPortSignal(S,5);
	const real_T *A = (const real_T*) ssGetInputPortSignal(S,6);
	
    real_T *outputs = (real_T*) ssGetOutputPortSignal(S,0);
	
	

	/* Solver data */
	static FORCES_CMPC_params params;
	static FORCES_CMPC_output output;
	static FORCES_CMPC_info info;	
	solver_int32_default exitflag;

	/* Extra NMPC data */
	

	/* Copy inputs */
	for( i=0; i<10; i++)
	{ 
		params.minusA_times_x0[i] = (double) c[i]; 
	}

	j=10; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs1[i] = (double) c[j++]; 
	}

	j=20; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs2[i] = (double) c[j++]; 
	}

	j=30; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs3[i] = (double) c[j++]; 
	}

	j=40; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs4[i] = (double) c[j++]; 
	}

	j=50; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs5[i] = (double) c[j++]; 
	}

	j=60; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs6[i] = (double) c[j++]; 
	}

	j=70; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs7[i] = (double) c[j++]; 
	}

	j=80; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs8[i] = (double) c[j++]; 
	}

	j=90; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs9[i] = (double) c[j++]; 
	}

	j=100; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs10[i] = (double) c[j++]; 
	}

	j=110; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs11[i] = (double) c[j++]; 
	}

	j=120; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs12[i] = (double) c[j++]; 
	}

	j=130; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs13[i] = (double) c[j++]; 
	}

	j=140; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs14[i] = (double) c[j++]; 
	}

	j=150; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs15[i] = (double) c[j++]; 
	}

	j=160; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs16[i] = (double) c[j++]; 
	}

	j=170; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs17[i] = (double) c[j++]; 
	}

	j=180; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs18[i] = (double) c[j++]; 
	}

	j=190; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs19[i] = (double) c[j++]; 
	}

	j=200; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs20[i] = (double) c[j++]; 
	}

	j=210; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs21[i] = (double) c[j++]; 
	}

	j=220; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs22[i] = (double) c[j++]; 
	}

	j=230; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs23[i] = (double) c[j++]; 
	}

	j=240; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs24[i] = (double) c[j++]; 
	}

	j=250; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs25[i] = (double) c[j++]; 
	}

	j=260; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs26[i] = (double) c[j++]; 
	}

	j=270; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs27[i] = (double) c[j++]; 
	}

	j=280; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs28[i] = (double) c[j++]; 
	}

	j=290; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs29[i] = (double) c[j++]; 
	}

	j=300; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs30[i] = (double) c[j++]; 
	}

	j=310; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs31[i] = (double) c[j++]; 
	}

	j=320; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs32[i] = (double) c[j++]; 
	}

	j=330; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs33[i] = (double) c[j++]; 
	}

	j=340; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs34[i] = (double) c[j++]; 
	}

	j=350; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs35[i] = (double) c[j++]; 
	}

	j=360; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs36[i] = (double) c[j++]; 
	}

	j=370; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs37[i] = (double) c[j++]; 
	}

	j=380; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs38[i] = (double) c[j++]; 
	}

	j=390; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs39[i] = (double) c[j++]; 
	}

	j=400; 
	for( i=0; i<10; i++)
	{ 
		params.equality_rhs40[i] = (double) c[j++]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.equality1[i] = (double) C[i]; 
	}

	j=130; 
	for( i=0; i<130; i++)
	{ 
		params.equality2[i] = (double) C[j++]; 
	}

	j=260; 
	for( i=0; i<130; i++)
	{ 
		params.equality3[i] = (double) C[j++]; 
	}

	j=390; 
	for( i=0; i<130; i++)
	{ 
		params.equality4[i] = (double) C[j++]; 
	}

	j=520; 
	for( i=0; i<130; i++)
	{ 
		params.equality5[i] = (double) C[j++]; 
	}

	j=650; 
	for( i=0; i<130; i++)
	{ 
		params.equality6[i] = (double) C[j++]; 
	}

	j=780; 
	for( i=0; i<130; i++)
	{ 
		params.equality7[i] = (double) C[j++]; 
	}

	j=910; 
	for( i=0; i<130; i++)
	{ 
		params.equality8[i] = (double) C[j++]; 
	}

	j=1040; 
	for( i=0; i<130; i++)
	{ 
		params.equality9[i] = (double) C[j++]; 
	}

	j=1170; 
	for( i=0; i<130; i++)
	{ 
		params.equality10[i] = (double) C[j++]; 
	}

	j=1300; 
	for( i=0; i<130; i++)
	{ 
		params.equality11[i] = (double) C[j++]; 
	}

	j=1430; 
	for( i=0; i<130; i++)
	{ 
		params.equality12[i] = (double) C[j++]; 
	}

	j=1560; 
	for( i=0; i<130; i++)
	{ 
		params.equality13[i] = (double) C[j++]; 
	}

	j=1690; 
	for( i=0; i<130; i++)
	{ 
		params.equality14[i] = (double) C[j++]; 
	}

	j=1820; 
	for( i=0; i<130; i++)
	{ 
		params.equality15[i] = (double) C[j++]; 
	}

	j=1950; 
	for( i=0; i<130; i++)
	{ 
		params.equality16[i] = (double) C[j++]; 
	}

	j=2080; 
	for( i=0; i<130; i++)
	{ 
		params.equality17[i] = (double) C[j++]; 
	}

	j=2210; 
	for( i=0; i<130; i++)
	{ 
		params.equality18[i] = (double) C[j++]; 
	}

	j=2340; 
	for( i=0; i<130; i++)
	{ 
		params.equality19[i] = (double) C[j++]; 
	}

	j=2470; 
	for( i=0; i<130; i++)
	{ 
		params.equality20[i] = (double) C[j++]; 
	}

	j=2600; 
	for( i=0; i<130; i++)
	{ 
		params.equality21[i] = (double) C[j++]; 
	}

	j=2730; 
	for( i=0; i<130; i++)
	{ 
		params.equality22[i] = (double) C[j++]; 
	}

	j=2860; 
	for( i=0; i<130; i++)
	{ 
		params.equality23[i] = (double) C[j++]; 
	}

	j=2990; 
	for( i=0; i<130; i++)
	{ 
		params.equality24[i] = (double) C[j++]; 
	}

	j=3120; 
	for( i=0; i<130; i++)
	{ 
		params.equality25[i] = (double) C[j++]; 
	}

	j=3250; 
	for( i=0; i<130; i++)
	{ 
		params.equality26[i] = (double) C[j++]; 
	}

	j=3380; 
	for( i=0; i<130; i++)
	{ 
		params.equality27[i] = (double) C[j++]; 
	}

	j=3510; 
	for( i=0; i<130; i++)
	{ 
		params.equality28[i] = (double) C[j++]; 
	}

	j=3640; 
	for( i=0; i<130; i++)
	{ 
		params.equality29[i] = (double) C[j++]; 
	}

	j=3770; 
	for( i=0; i<130; i++)
	{ 
		params.equality30[i] = (double) C[j++]; 
	}

	j=3900; 
	for( i=0; i<130; i++)
	{ 
		params.equality31[i] = (double) C[j++]; 
	}

	j=4030; 
	for( i=0; i<130; i++)
	{ 
		params.equality32[i] = (double) C[j++]; 
	}

	j=4160; 
	for( i=0; i<130; i++)
	{ 
		params.equality33[i] = (double) C[j++]; 
	}

	j=4290; 
	for( i=0; i<130; i++)
	{ 
		params.equality34[i] = (double) C[j++]; 
	}

	j=4420; 
	for( i=0; i<130; i++)
	{ 
		params.equality35[i] = (double) C[j++]; 
	}

	j=4550; 
	for( i=0; i<130; i++)
	{ 
		params.equality36[i] = (double) C[j++]; 
	}

	j=4680; 
	for( i=0; i<130; i++)
	{ 
		params.equality37[i] = (double) C[j++]; 
	}

	j=4810; 
	for( i=0; i<130; i++)
	{ 
		params.equality38[i] = (double) C[j++]; 
	}

	j=4940; 
	for( i=0; i<130; i++)
	{ 
		params.equality39[i] = (double) C[j++]; 
	}

	j=5070; 
	for( i=0; i<130; i++)
	{ 
		params.equality40[i] = (double) C[j++]; 
	}

	for( i=0; i<169; i++)
	{ 
		params.cost_H1[i] = (double) H[i]; 
	}

	j=169; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H2[i] = (double) H[j++]; 
	}

	j=338; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H3[i] = (double) H[j++]; 
	}

	j=507; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H4[i] = (double) H[j++]; 
	}

	j=676; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H5[i] = (double) H[j++]; 
	}

	j=845; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H6[i] = (double) H[j++]; 
	}

	j=1014; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H7[i] = (double) H[j++]; 
	}

	j=1183; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H8[i] = (double) H[j++]; 
	}

	j=1352; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H9[i] = (double) H[j++]; 
	}

	j=1521; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H10[i] = (double) H[j++]; 
	}

	j=1690; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H11[i] = (double) H[j++]; 
	}

	j=1859; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H12[i] = (double) H[j++]; 
	}

	j=2028; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H13[i] = (double) H[j++]; 
	}

	j=2197; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H14[i] = (double) H[j++]; 
	}

	j=2366; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H15[i] = (double) H[j++]; 
	}

	j=2535; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H16[i] = (double) H[j++]; 
	}

	j=2704; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H17[i] = (double) H[j++]; 
	}

	j=2873; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H18[i] = (double) H[j++]; 
	}

	j=3042; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H19[i] = (double) H[j++]; 
	}

	j=3211; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H20[i] = (double) H[j++]; 
	}

	j=3380; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H21[i] = (double) H[j++]; 
	}

	j=3549; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H22[i] = (double) H[j++]; 
	}

	j=3718; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H23[i] = (double) H[j++]; 
	}

	j=3887; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H24[i] = (double) H[j++]; 
	}

	j=4056; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H25[i] = (double) H[j++]; 
	}

	j=4225; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H26[i] = (double) H[j++]; 
	}

	j=4394; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H27[i] = (double) H[j++]; 
	}

	j=4563; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H28[i] = (double) H[j++]; 
	}

	j=4732; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H29[i] = (double) H[j++]; 
	}

	j=4901; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H30[i] = (double) H[j++]; 
	}

	j=5070; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H31[i] = (double) H[j++]; 
	}

	j=5239; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H32[i] = (double) H[j++]; 
	}

	j=5408; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H33[i] = (double) H[j++]; 
	}

	j=5577; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H34[i] = (double) H[j++]; 
	}

	j=5746; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H35[i] = (double) H[j++]; 
	}

	j=5915; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H36[i] = (double) H[j++]; 
	}

	j=6084; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H37[i] = (double) H[j++]; 
	}

	j=6253; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H38[i] = (double) H[j++]; 
	}

	j=6422; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H39[i] = (double) H[j++]; 
	}

	j=6591; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H40[i] = (double) H[j++]; 
	}

	j=6760; 
	for( i=0; i<169; i++)
	{ 
		params.cost_H41[i] = (double) H[j++]; 
	}

	for( i=0; i<13; i++)
	{ 
		params.cost_f1[i] = (double) f[i]; 
	}

	j=13; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f2[i] = (double) f[j++]; 
	}

	j=26; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f3[i] = (double) f[j++]; 
	}

	j=39; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f4[i] = (double) f[j++]; 
	}

	j=52; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f5[i] = (double) f[j++]; 
	}

	j=65; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f6[i] = (double) f[j++]; 
	}

	j=78; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f7[i] = (double) f[j++]; 
	}

	j=91; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f8[i] = (double) f[j++]; 
	}

	j=104; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f9[i] = (double) f[j++]; 
	}

	j=117; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f10[i] = (double) f[j++]; 
	}

	j=130; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f11[i] = (double) f[j++]; 
	}

	j=143; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f12[i] = (double) f[j++]; 
	}

	j=156; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f13[i] = (double) f[j++]; 
	}

	j=169; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f14[i] = (double) f[j++]; 
	}

	j=182; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f15[i] = (double) f[j++]; 
	}

	j=195; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f16[i] = (double) f[j++]; 
	}

	j=208; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f17[i] = (double) f[j++]; 
	}

	j=221; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f18[i] = (double) f[j++]; 
	}

	j=234; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f19[i] = (double) f[j++]; 
	}

	j=247; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f20[i] = (double) f[j++]; 
	}

	j=260; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f21[i] = (double) f[j++]; 
	}

	j=273; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f22[i] = (double) f[j++]; 
	}

	j=286; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f23[i] = (double) f[j++]; 
	}

	j=299; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f24[i] = (double) f[j++]; 
	}

	j=312; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f25[i] = (double) f[j++]; 
	}

	j=325; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f26[i] = (double) f[j++]; 
	}

	j=338; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f27[i] = (double) f[j++]; 
	}

	j=351; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f28[i] = (double) f[j++]; 
	}

	j=364; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f29[i] = (double) f[j++]; 
	}

	j=377; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f30[i] = (double) f[j++]; 
	}

	j=390; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f31[i] = (double) f[j++]; 
	}

	j=403; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f32[i] = (double) f[j++]; 
	}

	j=416; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f33[i] = (double) f[j++]; 
	}

	j=429; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f34[i] = (double) f[j++]; 
	}

	j=442; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f35[i] = (double) f[j++]; 
	}

	j=455; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f36[i] = (double) f[j++]; 
	}

	j=468; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f37[i] = (double) f[j++]; 
	}

	j=481; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f38[i] = (double) f[j++]; 
	}

	j=494; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f39[i] = (double) f[j++]; 
	}

	j=507; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f40[i] = (double) f[j++]; 
	}

	j=520; 
	for( i=0; i<13; i++)
	{ 
		params.cost_f41[i] = (double) f[j++]; 
	}

	for( i=0; i<130; i++)
	{ 
		params.eq_D1[i] = (double) D[i]; 
	}

	j=130; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D2[i] = (double) D[j++]; 
	}

	j=260; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D3[i] = (double) D[j++]; 
	}

	j=390; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D4[i] = (double) D[j++]; 
	}

	j=520; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D5[i] = (double) D[j++]; 
	}

	j=650; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D6[i] = (double) D[j++]; 
	}

	j=780; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D7[i] = (double) D[j++]; 
	}

	j=910; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D8[i] = (double) D[j++]; 
	}

	j=1040; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D9[i] = (double) D[j++]; 
	}

	j=1170; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D10[i] = (double) D[j++]; 
	}

	j=1300; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D11[i] = (double) D[j++]; 
	}

	j=1430; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D12[i] = (double) D[j++]; 
	}

	j=1560; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D13[i] = (double) D[j++]; 
	}

	j=1690; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D14[i] = (double) D[j++]; 
	}

	j=1820; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D15[i] = (double) D[j++]; 
	}

	j=1950; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D16[i] = (double) D[j++]; 
	}

	j=2080; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D17[i] = (double) D[j++]; 
	}

	j=2210; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D18[i] = (double) D[j++]; 
	}

	j=2340; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D19[i] = (double) D[j++]; 
	}

	j=2470; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D20[i] = (double) D[j++]; 
	}

	j=2600; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D21[i] = (double) D[j++]; 
	}

	j=2730; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D22[i] = (double) D[j++]; 
	}

	j=2860; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D23[i] = (double) D[j++]; 
	}

	j=2990; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D24[i] = (double) D[j++]; 
	}

	j=3120; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D25[i] = (double) D[j++]; 
	}

	j=3250; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D26[i] = (double) D[j++]; 
	}

	j=3380; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D27[i] = (double) D[j++]; 
	}

	j=3510; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D28[i] = (double) D[j++]; 
	}

	j=3640; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D29[i] = (double) D[j++]; 
	}

	j=3770; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D30[i] = (double) D[j++]; 
	}

	j=3900; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D31[i] = (double) D[j++]; 
	}

	j=4030; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D32[i] = (double) D[j++]; 
	}

	j=4160; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D33[i] = (double) D[j++]; 
	}

	j=4290; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D34[i] = (double) D[j++]; 
	}

	j=4420; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D35[i] = (double) D[j++]; 
	}

	j=4550; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D36[i] = (double) D[j++]; 
	}

	j=4680; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D37[i] = (double) D[j++]; 
	}

	j=4810; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D38[i] = (double) D[j++]; 
	}

	j=4940; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D39[i] = (double) D[j++]; 
	}

	j=5070; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D40[i] = (double) D[j++]; 
	}

	j=5200; 
	for( i=0; i<130; i++)
	{ 
		params.eq_D41[i] = (double) D[j++]; 
	}

	for( i=0; i<26; i++)
	{ 
		params.polytopic_A1[i] = (double) A[i]; 
	}

	j=26; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A2[i] = (double) A[j++]; 
	}

	j=52; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A3[i] = (double) A[j++]; 
	}

	j=78; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A4[i] = (double) A[j++]; 
	}

	j=104; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A5[i] = (double) A[j++]; 
	}

	j=130; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A6[i] = (double) A[j++]; 
	}

	j=156; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A7[i] = (double) A[j++]; 
	}

	j=182; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A8[i] = (double) A[j++]; 
	}

	j=208; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A9[i] = (double) A[j++]; 
	}

	j=234; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A10[i] = (double) A[j++]; 
	}

	j=260; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A11[i] = (double) A[j++]; 
	}

	j=286; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A12[i] = (double) A[j++]; 
	}

	j=312; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A13[i] = (double) A[j++]; 
	}

	j=338; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A14[i] = (double) A[j++]; 
	}

	j=364; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A15[i] = (double) A[j++]; 
	}

	j=390; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A16[i] = (double) A[j++]; 
	}

	j=416; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A17[i] = (double) A[j++]; 
	}

	j=442; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A18[i] = (double) A[j++]; 
	}

	j=468; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A19[i] = (double) A[j++]; 
	}

	j=494; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A20[i] = (double) A[j++]; 
	}

	j=520; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A21[i] = (double) A[j++]; 
	}

	j=546; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A22[i] = (double) A[j++]; 
	}

	j=572; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A23[i] = (double) A[j++]; 
	}

	j=598; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A24[i] = (double) A[j++]; 
	}

	j=624; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A25[i] = (double) A[j++]; 
	}

	j=650; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A26[i] = (double) A[j++]; 
	}

	j=676; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A27[i] = (double) A[j++]; 
	}

	j=702; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A28[i] = (double) A[j++]; 
	}

	j=728; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A29[i] = (double) A[j++]; 
	}

	j=754; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A30[i] = (double) A[j++]; 
	}

	j=780; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A31[i] = (double) A[j++]; 
	}

	j=806; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A32[i] = (double) A[j++]; 
	}

	j=832; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A33[i] = (double) A[j++]; 
	}

	j=858; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A34[i] = (double) A[j++]; 
	}

	j=884; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A35[i] = (double) A[j++]; 
	}

	j=910; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A36[i] = (double) A[j++]; 
	}

	j=936; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A37[i] = (double) A[j++]; 
	}

	j=962; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A38[i] = (double) A[j++]; 
	}

	j=988; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A39[i] = (double) A[j++]; 
	}

	j=1014; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A40[i] = (double) A[j++]; 
	}

	j=1040; 
	for( i=0; i<26; i++)
	{ 
		params.polytopic_A41[i] = (double) A[j++]; 
	}

	for( i=0; i<2; i++)
	{ 
		params.polytopic_b1[i] = (double) b[i]; 
	}

	j=2; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b2[i] = (double) b[j++]; 
	}

	j=4; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b3[i] = (double) b[j++]; 
	}

	j=6; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b4[i] = (double) b[j++]; 
	}

	j=8; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b5[i] = (double) b[j++]; 
	}

	j=10; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b6[i] = (double) b[j++]; 
	}

	j=12; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b7[i] = (double) b[j++]; 
	}

	j=14; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b8[i] = (double) b[j++]; 
	}

	j=16; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b9[i] = (double) b[j++]; 
	}

	j=18; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b10[i] = (double) b[j++]; 
	}

	j=20; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b11[i] = (double) b[j++]; 
	}

	j=22; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b12[i] = (double) b[j++]; 
	}

	j=24; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b13[i] = (double) b[j++]; 
	}

	j=26; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b14[i] = (double) b[j++]; 
	}

	j=28; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b15[i] = (double) b[j++]; 
	}

	j=30; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b16[i] = (double) b[j++]; 
	}

	j=32; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b17[i] = (double) b[j++]; 
	}

	j=34; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b18[i] = (double) b[j++]; 
	}

	j=36; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b19[i] = (double) b[j++]; 
	}

	j=38; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b20[i] = (double) b[j++]; 
	}

	j=40; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b21[i] = (double) b[j++]; 
	}

	j=42; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b22[i] = (double) b[j++]; 
	}

	j=44; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b23[i] = (double) b[j++]; 
	}

	j=46; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b24[i] = (double) b[j++]; 
	}

	j=48; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b25[i] = (double) b[j++]; 
	}

	j=50; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b26[i] = (double) b[j++]; 
	}

	j=52; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b27[i] = (double) b[j++]; 
	}

	j=54; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b28[i] = (double) b[j++]; 
	}

	j=56; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b29[i] = (double) b[j++]; 
	}

	j=58; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b30[i] = (double) b[j++]; 
	}

	j=60; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b31[i] = (double) b[j++]; 
	}

	j=62; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b32[i] = (double) b[j++]; 
	}

	j=64; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b33[i] = (double) b[j++]; 
	}

	j=66; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b34[i] = (double) b[j++]; 
	}

	j=68; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b35[i] = (double) b[j++]; 
	}

	j=70; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b36[i] = (double) b[j++]; 
	}

	j=72; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b37[i] = (double) b[j++]; 
	}

	j=74; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b38[i] = (double) b[j++]; 
	}

	j=76; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b39[i] = (double) b[j++]; 
	}

	j=78; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b40[i] = (double) b[j++]; 
	}

	j=80; 
	for( i=0; i<2; i++)
	{ 
		params.polytopic_b41[i] = (double) b[j++]; 
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
		outputs[i] = (real_T) output.z[i]; 
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


