/****************************************************************************
* Copyright : All rights reserved. This document/code contains information
* that is proprietary to Lekha Wireless Solutions Pvt. Ltd. No part of this
* document/code may be reproduced or used in whole or part in any form or
* by any means- graphic, electronic or mechanical without the written
* permission of Lekha Wireless Solutions Pvt. Ltd.
*
* Company           : Lekha Wireless Solutions Pvt. Ltd.
* File Name         : NPRACH_DETECTOR_PRM0_Fixed.c
* Function          : NPRACHDetectorPrm0()
* Description       : NPRACH DETECTOR (PREAMBLE FORMAT 0) - Performs User Activity Detection for
                      each Subcarrier and Estimates the corresponding Time-of-Arrival and
                      Residual Carrier Frequency Offset
* Input parameters  : Flag - 0 when function is called for first time
                             1 when function is called for second time
                             within same execution
* Output parameters : Structure containing following elements:
                      ToA  - Time-of-Arrival Estimates
                      RCFO - Residual CFO Estimates
                      UAD  - User Activity Detection
                      CVA  - Estimated Coverage Area for each UE
* Return value      : stDout - Structure containing estimated results
* Comments          : Files required - Preamble format 0 -> rxDataMat0_xx.txt
                                       Preamble format 0 -> rxDataMat1_xx.txt, rxDataMatsh1_xx.txt
                      References     - 1. X. Lin, A. Adhikary and Y. -. Eric Wang, "Random Access Preamble
                      Design and Detection for 3GPP Narui32Rowband IoT Systems," in IEEE Wireless
                      Communications Letters, 2016
                      Calls Matslice(), NBULFFT2(), FindMax(), FindMean()
                      FindMeanSel() functions
****************************************************************************/

/** PROJECT INCLUDES *********************************************************/
#include "NPRACH_Fixed.h"
#include "NB_UL_FFT.h"

/** GLOBAL VARIABLE DEFINITIONS **********************************************/

CPLX16 acplx16RxSignal   [LEN];

CPLX16 acplx16RefSignal  [LEN];

CPLX16 acplx16CorrSignal [LEN];

CPLX16 acplx16CurrGroup  [SAMPLES_PER_SYMGRP];

CPLX16 acplx16FFTIn      [N];

CPLX16 acplx16CurrSym    [N];

CPLX16 acplx16RxDataMat  [N*NUMSYMS];

CPLX16 acplx16RxDataProc [NUM_SC*NUMSYMS];

UINT8 aui8FreqsHopsSC    [128];

INT32 ai32CorrOutTemp    [N*256];

INT32 ai32CorrOut1   [N*256] ;
INT32 ai32CorrOut2   [N*256] ;
INT32 ai32CorrOutAll [N*256] ;

INT32 *pi32CorrOut;
INT32 *pi32CorrOut1    = ai32CorrOut1;
INT32 *pi32CorrOut2    = ai32CorrOut2;
INT32 *pi32CorrOutAll  = ai32CorrOutAll;

INT32 ai32CVACorr[16];

CPLX16 acplx16FFT2In  [NUM_SC*NUMSYMS_PER_REP];
CPLX16 acplx16TMPCorr [N*256];

INT16  i16CVA3Pmr ;
INT16  i16Cov1Others;
INT16  i16Cov2;
INT16  i16Cov2Others ;
UINT8  ui8CVAindicator;

UINT16 ui16SamplesPerSymGroup;
INT32  i32CorrOutMax;
INT16  i16ToAHat, i16RCFOHat;
UINT16 ui16ToATmp,ui16RCFOTmp;

/* Iteration variables */

UINT8  ui8IterSc;
UINT16 ui16IterSymGrps;
UINT16 ui16IterRepSyms;
UINT16 ui16Ind;
UINT8  ui8IterIdenSymsPerGrp;
UINT8  ui8Count;
UINT8  ui8IterCorr1;
UINT8  ui8IterCorr2;
UINT8  ui8IterInd;

Output_t NPRACHDetectorPrm0 (UINT16 ui16IterTestcase, UINT8 ui8Flag)
{
  /** PRIVATE VARIABLE DEFINITIONS *********************************************/

  /* FFT Lengths for the 2D FFT Correlation for Joint ToA and CFO Estimation */
  UINT16 ui16M1 = stTxParams.ui16FFT2M1;  // 128(N/4) for preamble format 0, 512(N) for preamble format 1
  UINT16 ui16M2 = stTxParams.ui16FFT2M2;  // 256

  /* Output structure */
  Output_t stDout = {0};

  /*
  Importing RxDataMat (2D complex array of size N x (M = NUMSYMS)) from Matlab
  In Matlab, RxDataMat was flattened to get 1D array of size 2*N*M and was written into a file
  for preamble format-0 : rxDataMat0_xx.txt
  for preamble format-1 : rxDataMat1_xx.txt, rxDataMatsh1_xx.txt
  */

  /** FILE INCLUDES *********************************************************/

  UINT8 covarea;
  covarea = DYNDET == 0 ? CVA : aui8TestCaseMap[TESTCASEINDEX-1];

  if (stTxParams.ui8PreambleFormat == 0)
  {
    // sprintf(achfname,"Sample_Test_Data\\PRM_0\\CVA_%u\\rxDataMat0_%u.txt",covarea,ui16IterTestcase+1);
    pfile = fopen("Sample_Test_Data\\PRM_0\\refSignal_0.txt","r");

    for (ui32Iter = 0; ui32Iter < LEN ; ui32Iter++)
    {
      fscanf(pfile,"%hi,\n",&acplx16RefSignal[ui32Iter].real);
      fscanf(pfile,"%hi,\n",&acplx16RefSignal[ui32Iter].imag);
    }

    fclose(pfile);

    sprintf(achfname,"Sample_Test_Data\\PRM_0\\CVA_%u\\rxSignal0_%u.txt",covarea,ui16IterTestcase+1);

  }

  else
  {
    pfile = fopen("Sample_Test_Data\\PRM_1\\refSignal_1.txt","r");

    for (ui32Iter = 0; ui32Iter < LEN ; ui32Iter++)
    {
      fscanf(pfile,"%hi,\n",&acplx16RefSignal[ui32Iter].real);
      fscanf(pfile,"%hi,\n",&acplx16RefSignal[ui32Iter].imag);
    }

    fclose(pfile);

    if (ui8Flag == 0)
    {
      //sprintf(achfname,"Sample_Test_Data\\PRM_1\\CVA_%u\\rxDataMat1_%u.txt",covarea,ui16IterTestcase+1);
      sprintf(achfname,"Sample_Test_Data\\PRM_1\\CVA_%u\\rxSignal1_%u.txt",covarea,ui16IterTestcase+1);
    }

    else
    {
      //sprintf(achfname,"Sample_Test_Data\\PRM_1\\CVA_%u\\rxDataMatsh1_%u.txt",covarea,ui16IterTestcase+1);
      sprintf(achfname,"Sample_Test_Data\\PRM_1\\CVA_%u\\rxSignalsh1_%u.txt",covarea,ui16IterTestcase+1);
    }
  }

  pfile = fopen(achfname,"r");

//  for (ui32Iter = 0; ui32Iter < N*NUMSYMS ; ui32Iter++)
//    {
//     fscanf(pfile,"%hi,\n",&acplx16RxDataMat[ui32Iter].real);
//     fscanf(pfile,"%hi,\n",&acplx16RxDataMat[ui32Iter].imag);
//    }

  for (ui32Iter = 0; ui32Iter < LEN ; ui32Iter++)
  {
     fscanf(pfile,"%hi,\n",&acplx16RxSignal[ui32Iter].real);
     fscanf(pfile,"%hi,\n",&acplx16RxSignal[ui32Iter].imag);
  }

  fclose(pfile);

  /* Correlating "rxSignal" with the "refSignal" */

  Mulcom (acplx16RxSignal, acplx16RefSignal, acplx16CorrSignal, LEN); // This may not be needed as its not done in matlab

  /* Creating "rxDataMat" */

  ui16SamplesPerSymGroup = NUM_SYMS_PER_SYMGRP * N + stTxParams.ui16CpLen;

  for (ui16IterSymGrps = 0; ui16IterSymGrps < NUM_SYM_GRPS; ui16IterSymGrps++)
  {
     MatSlice (acplx16CorrSignal, acplx16CurrGroup, (ui16IterSymGrps*ui16SamplesPerSymGroup) + stTxParams.ui16CpLen,(ui16IterSymGrps+1)*ui16SamplesPerSymGroup , 0, 1, 1);

     for(ui16IterRepSyms = 0; ui16IterRepSyms < NUM_SYMS_PER_SYMGRP; ui16IterRepSyms++)
     {
        MatSlice (acplx16CurrGroup, acplx16FFTIn, ui16IterRepSyms*N,(ui16IterRepSyms+1)*N , 0, 1, 1);

        NBIOT_UL_FFT(acplx16FFTIn,acplx16CurrSym, 512,512);

        for (ui32Iter = 0; ui32Iter<N; ui32Iter++)
        {
          acplx16RxDataMat[ui32Iter*NUMSYMS+ (ui16IterSymGrps * NUM_SYMS_PER_SYMGRP + ui16IterRepSyms)] = acplx16CurrSym[ui32Iter];
        }
      }
   }


  /**
  =====================================================================================
    2D FFT based Correlation for Joint ToA and RCFO Estimation
  =====================================================================================
  **/

  /*
  Iterating over each possible Hopping Pattern and Correlating with a
  reference signal and extracting spectral components specific to the
  Hopping Pattern. 2D FFT is used to Jointly estimate ToA and RCFO.
  */

  for (ui8IterSc = 0; ui8IterSc < NUM_SC; ui8IterSc++)
  {
    for (ui32Iter = 0; ui32Iter < 128; ui32Iter++)
    {
      aui8FreqsHopsSC[ui32Iter] = stTxParams.aui8FreqHops[ui8IterSc][ui32Iter];
    }

    /*
    Iterating over all the received Symbol Groups and extracting the
    Spectral Components as per the Hopping Pattern for specific user
    */

    memset(acplx16RxDataProc, 0, sizeof(CPLX16) * NUM_SC * NUMSYMS); // Initializing/resetting the memory to 0

    for (ui16IterSymGrps = 0; ui16IterSymGrps < NUM_SYM_GRPS; ui16IterSymGrps++)
    {
      ui16Ind = aui8FreqsHopsSC[ui16IterSymGrps] * NUMSYMS + (ui16IterSymGrps*NUM_SYMS_PER_SYMGRP);

      for (ui8IterIdenSymsPerGrp = 0; ui8IterIdenSymsPerGrp < NUM_SYMS_PER_SYMGRP; ui8IterIdenSymsPerGrp++)
      {
       acplx16RxDataProc[ui16Ind + ui8IterIdenSymsPerGrp] = acplx16RxDataMat[ui16Ind + ui8IterIdenSymsPerGrp];
      }
    }

    /* Handle two repetitions at a time and store the peak to mean ratio */

    memset(ai32CorrOutAll, 0, sizeof(INT32) * ui16M1 * ui16M2); // Initializing/resetting the memory to 0
    ui8Count = 0;

    for(ui8IterCorr1 = 0; ui8IterCorr1 < stTxParams.ui8NumReps-1; ui8IterCorr1 = ui8IterCorr1+2)
      {

        memset(ai32CorrOutTemp , 0, sizeof(INT32) * ui16M1 * ui16M2); // Initializing/resetting the memory to 0

        for(ui8IterCorr2 = 0; ui8IterCorr2 < 2; ui8IterCorr2++)
        {
          ui8IterInd = ui8IterCorr1 + ui8IterCorr2;

          /* Extracting 20(NUMSYMS_PER_REP) Columns(each of length 12) from 'rxDataProc' into 'FFT2In' */

          MatSlice(acplx16RxDataProc, acplx16FFT2In, 0, NUM_SC, ui8IterInd * NUMSYMS_PER_REP, (ui8IterInd + 1) * NUMSYMS_PER_REP, NUMSYMS);

          /* Computing 2D FFT(size: M1 x M2) of the matrix 'FFT2In' of size 12 x 20 */

          NBULFFt2(acplx16FFT2In, acplx16TMPCorr, ui16M1, ui16M2, NUM_SC, NUMSYMS_PER_REP);


          for(ui32Iter = 0; ui32Iter < ui16M1 * ui16M2; ui32Iter++)
           {
            ai32CorrOutTemp[ui32Iter] += pow((acplx16TMPCorr[ui32Iter].real),2)+pow((acplx16TMPCorr[ui32Iter].imag),2);
           }

           memset(acplx16TMPCorr, 0, sizeof(CPLX16)* N * 256);
           memset(acplx16FFT2In,  0, sizeof(CPLX16)* NUM_SC*NUMSYMS_PER_REP);

        }

        /* Store Peak to Mean Ratio */

        ai32CVACorr [ui8Count] = FindMax(ai32CorrOutTemp,ui16M1*ui16M2) / FindMean(ai32CorrOutTemp,ui16M1*ui16M2) ;

        for(ui32Iter = 0; ui32Iter < ui16M1 * ui16M2; ui32Iter++)
        {
            ai32CorrOutAll[ui32Iter] += ai32CorrOutTemp[ui32Iter];
        }

        /*
        Coverage Area 1 is 2 repetitions, Coverage Area 2 is 8
        repetitions. Store the corresponding combining results
        */

        if (ui8IterCorr1 == 0)
        {
         memcpy(pi32CorrOut1,pi32CorrOutAll,sizeof(INT32) * ui16M1 * ui16M2);
        }
        else if (ui8IterCorr1 == 6)
        {
         memcpy(pi32CorrOut2,pi32CorrOutAll,sizeof(INT32) * ui16M1 * ui16M2);
        }

        ui8Count += 1;
      }

    if (DYNDET == 0)
    {
      ui8CVAindicator = 1;
      if (CVA == 1)
      {
        pi32CorrOut = pi32CorrOut1;
      }
      else if (CVA == 2)
      {
        pi32CorrOut = pi32CorrOut2;
      }
      else if (CVA == 3)
      {
         pi32CorrOut = pi32CorrOutAll;
      }
    }

    else
    {
        ui8CVAindicator = 0;

        i16CVA3Pmr    = FindMax(ai32CVACorr ,16) / FindMean(ai32CVACorr ,16);

        i16Cov1Others = FindMeanSel(ai32CVACorr ,1,3);

        i16Cov2       = FindMeanSel(ai32CVACorr ,0,3);

        i16Cov2Others = FindMeanSel(ai32CVACorr ,4,15);

        if (((i16CVA3Pmr >= 0.85) >0) && (i16CVA3Pmr <= 1.65))
        {
          stDout.aui8CVA[ui8IterSc] = 3;
          pi32CorrOut               = pi32CorrOutAll;
          ui8CVAindicator           = 1;
        }

        else
        {
          if(ai32CVACorr [0] > 2.5 * i16Cov1Others)
          {
            stDout.aui8CVA[ui8IterSc] = 1;
            pi32CorrOut               = pi32CorrOut1;
            ui8CVAindicator           = 1;
          }
          else if(i16Cov2 > 1.5 * i16Cov2Others)
          {
            stDout.aui8CVA[ui8IterSc] = 2;
            pi32CorrOut               = pi32CorrOut2;
            ui8CVAindicator           = 1;
          }
        }
    }

    memset(ai32CVACorr,0,sizeof(INT32)*16);

    if (ui8CVAindicator == 1)
    {
      /* The coordinates of maximum correlation are used to estimate ToA and RCFO */

      i32CorrOutMax = FindMax(pi32CorrOut,ui16M1 * ui16M2);

      for (ui32Row = 0; ui32Row < ui16M1; ui32Row++)
      {
        for (ui32Col = 0; ui32Col < ui16M2; ui32Col++)
        {
          if(pi32CorrOut[ui32Row*ui16M2+ui32Col] == i32CorrOutMax )
          {
           ui16ToATmp  = ui32Row;
           ui16RCFOTmp = ui32Col;
           break;
          }
        }
      }

      i16RCFOHat = ui16RCFOTmp >= ui16M2/2 ? (ui16RCFOTmp  - ui16M2) : ui16RCFOTmp ; // scaled up by 2^17

      i16ToAHat  = ui16ToATmp >= ui16M1/2 ? (- (ui16ToATmp - ui16M1) * N / ui16M1) : (- ui16ToATmp * N / ui16M1);

      stDout.ai16ToA [ui8IterSc]  = i16ToAHat< 0 ? i16ToAHat + stTxParams.ui16CpLen : i16ToAHat;
      stDout.ai16RCFO[ui8IterSc]  = i16RCFOHat;
      stDout.aui8UAD [ui8IterSc]  = FindMax(pi32CorrOut,ui16M1*ui16M2) / FindMean(pi32CorrOut,ui16M1*ui16M2);

    }

    else
    {
      stDout.aui8UAD [ui8IterSc]  = FindMax(pi32CorrOutAll,ui16M1*ui16M2) / FindMean(pi32CorrOutAll,ui16M1*ui16M2);
    }

  }

  return stDout;

}

/********************** End of file NPRACH_DETECTOR_PRM0_Fixed.c ***********************/
