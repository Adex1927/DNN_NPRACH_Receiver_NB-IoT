/******************************************************************************
* Copyright : All rights reserved. This document/code contains information
* that is proprietary to Lekha Wireless Solutions Pvt. Ltd. No part of this
* document/code may be reproduced or used in whole or part in any form or
* by any means- graphic, electronic or mechanical without the written
* permission of Lekha Wireless Solutions Pvt. Ltd.
*
* Company      : Lekha Wireless Solutions Pvt. Ltd.
* File Name    : NPRACH_Fixed.h
* Description  : File contains Macros,type and functions definitions
* Comments     : NONE
******************************************************************************/

/** FILE GUARDS **************************************************************/
#ifndef NPRACH_FIXED_H
#define NPRACH_FIXED_H

/** PROJECT INCLUDES *********************************************************/
#include "NB_Datatypes.h"

/** MACRO AND TYPE DEFINITIONS ***********************************************/

/*Variables for testing purpose */

#define PRM                     0        // 0 or 1

#if PRM == 0
    #define LEN 344064  // length of UETx for preamble format = 0
#elif PRM == 1
    #define LEN 393216  // length of UETx for preamble format = 1
#endif

#define NUMTESTCASES            50
// As of now code is working for no dynamic coverage area detection
#define DYNDET                  0         // 0 : No dynamic coverage area detection
                                          // 1 : for dynamic coverage area detection
#define CVA                     1         // change it,if DYNDET == 0

#define TESTCASEINDEX           1         // change it,if DYNDET == 1
/*
1 : Case where all UE's are from CVA 1
2 : Case where all UE's are from CVA 2
3 : Case where all UE's are from CVA 3
4 : Case where set of UE's consists of UE's from CVA 1 and CVA 2
5 : Case where set of UE's consists of UE's from CVA 2 and CVA 3
6 : Case where set of UE's consists of UE's from CVA 1 and CVA 3
7 : Case where set of UE's consists of UE's from all CVA(i.e, 1,2 and 3)
*/

#define NUM_SC                  12
#define NUM_SYM_GRPS            128       // for CVA = 3 (32*4)
#define NUM_SYMS_PER_SYMGRP     5
#define NUMSYMS_PER_REP         20        // 4 * NUM_SYMS_PER_SYMGRP
#define NUMSYMS                 640       // for CVA = 3 (128*5)
#define N                       512       // FFT size
#define SAMPLES_PER_SYMGRP      2560      // N * NUM_SYMS_PER_SYMGRP(512 * 5)
#define RCFO_SCALE              131072    // 2^17(N * M2 = 512 * 256)


typedef struct TxParams
{
 UINT8  ui8NumReps;
 UINT8  ui8CvArea;
 UINT8  ui8UADTHCVA1;
 UINT8  ui8UADTHCVA2;
 UINT8  ui8UADTHCVA3;
 UINT8  ui8NumSymGrpsPerRep;
 UINT8  ui8NumIdenSymsPerGrp;
 UINT8  ui8NumUplinkSC;
 UINT8  aui8NprachSC[4];
 UINT8  ui8NPRACHSC;
 UINT8  ui8NPRACHRASC;
 UINT8  aui8NscOffset[7];
 UINT8  ui8NSCOFFSET;
 UINT8  ui8CellID;
 UINT8  ui8PreambleFormat;
 UINT16 ui16OFDMN;
 UINT16 ui16CpLen;
 UINT16 ui16FFT2M1;
 UINT16 ui16FFT2M2;
 UINT8  aui8FreqHops[12][128];
}TxParams_t;

typedef struct Output
{
 INT16   ai16ToA [12];
 UINT8   aui8UAD [12];
 UINT8   aui8CVA [12];
 INT16   ai16RCFO[12];
}Output_t;

/** FUNCTION PROTOTYPES ***********************************************/

void NPRACHConfig (UINT8 ui8CvArea);

void NPRACHDetector (UINT16 ui16IterTestcase);

Output_t NPRACHDetectorPrm0 (UINT16 ui16IterTestcase, UINT8 ui8Flag);

void MatSlice (CPLX16 *pcplx16Input, CPLX16 *pcplx16Output, UINT16 ui16StRow, UINT16 ui16EnRow, UINT16 ui16StCol, UINT16 ui16EnCol, UINT16 ui16Ncols);

INT32 FindMax (INT32 *ai32Arr,UINT32 ui32ArrLen);

INT32 FindMean (INT32 *ai32Arr,UINT32 ui32ArrLen);

INT16 FindMeanSel (INT32 *ai32Arr,UINT8 ui8Sind,UINT8 ui8Eind);

void Mulcom (CPLX16 *pcplx16Input1, CPLX16 *pcplx16Input2, CPLX16 *pcplx16Output, UINT32 ui32Arrsize);

void FwriteResults (Output_t stOut, UINT16 ui16IterTestcase);

/** GENERAL VARIABLES ***********************************************/

UINT32 ui32Iter;
UINT32 ui32Row;
UINT32 ui32Col;
TxParams_t stTxParams;
Output_t   stOut;

/* For testing purpose */
FILE   *pfile;
char   achfname[100];
UINT8  aui8UAD [12];
static UINT8  aui8TestCaseMap[7]   = {1,2,3,12,23,13,123};


#endif

/********************** End of header file NPRACH_Fixed.h ***********************/
