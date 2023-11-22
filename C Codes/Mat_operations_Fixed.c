/****************************************************************************
* Copyright   : All rights reserved. This document/code contains information
* that is proprietary to Lekha Wireless Solutions Pvt. Ltd. No part of this
* document/code may be reproduced or used in whole or part in any form or
* by any means- graphic, electronic or mechanical without the written
* permission of Lekha Wireless Solutions Pvt. Ltd.
*
* Company     : Lekha Wireless Solutions Pvt. Ltd.
* File Name   : Mat_operations_Fixed.c
* Description : Contains function definitions related to matrix operations and complex numbers
* Comments    : NONE
*********************************************************************************************/

/** PROJECT INCLUDES *********************************************************/
#include "NPRACH_Fixed.h"


/**
This function writes (er-sr) x (ec-sc) values into (er-sr) x (ec-sc) dimension  matrix 'out_mat'
taking values from 'mat' starting from row = sr till row = er from the columns
from col = sc till col = ec
**/
void MatSlice (CPLX16 *pcplx16Input, CPLX16 *pcplx16Output, UINT16 ui16StRow, UINT16 ui16EnRow, UINT16 ui16StCol, UINT16 ui16EnCol, UINT16 ui16Ncols)
{

  for (ui32Row = ui16StRow; ui32Row < ui16EnRow; ui32Row++)
  {
    for (ui32Col = ui16StCol; ui32Col < ui16EnCol; ui32Col++)
    {
      pcplx16Output[(ui32Row - ui16StRow)*(ui16EnCol - ui16StCol) + (ui32Col - ui16StCol)]  = pcplx16Input[ui32Row*ui16Ncols + ui32Col];
    }
  }

}


/**
This function takes pointer to array as the input
(array can be 1D or 2D(in this case it is viewed as flattened 1D array)
and returns the maximum value in the array
**/

INT32 FindMax (INT32 *ai32Arr,UINT32 ui32ArrLen)
{
  /** PRIVATE VARIABLE DEFINITIONS *********************************************/
  UINT32 ui32Len = 0;
  INT32  i32Max  = 0;

  for (ui32Len = 0; ui32Len < ui32ArrLen; ui32Len++)
  {
    if (ai32Arr[ui32Len] > i32Max)
    {
        i32Max = ai32Arr[ui32Len];}
    }

  return i32Max;
}


/**
This function takes pointer to array as the input
(array can be 1D or 2D(in this case it is viewed as flattened 1D array)
and returns the mean value of the elements in the array
**/

INT32 FindMean (INT32 *ai32Arr,UINT32 ui32ArrLen)
{
  /** PRIVATE VARIABLE DEFINITIONS *********************************************/
  UINT32 ui32Len = 0;
  INT32  i32Mean = 0;
  INT64  i64Sum  = 0;

  for (ui32Len = 0; ui32Len < ui32ArrLen; ui32Len++)
  {
      i64Sum += (INT32)ai32Arr[ui32Len];
  }
  i32Mean = i64Sum /ui32ArrLen ;

  return i32Mean ;

}


/**
This function takes pointer to array as the input
(array can be 1D or 2D(in this case it is viewed as flattened 1D array)
and returns the mean value of the selected elements in the array
i.e, elements from index 'sr' till(including) index 'er'
**/

INT16 FindMeanSel (INT32 *ai32Arr,UINT8 ui8Sind,UINT8 ui8Eind)
{
  /** PRIVATE VARIABLE DEFINITIONS *********************************************/
  UINT8 ui8Ind     = 0;
  INT16 i16MeanSel = 0;
  INT16 i16Sum     = 0;

  for (ui8Ind = ui8Sind; ui8Ind <= ui8Eind; ui8Ind++)
  {
      i16Sum+= ai32Arr[ui8Ind];
  }

  i16MeanSel = i16Sum /(ui8Eind-ui8Sind+1);

  return i16MeanSel;

}

void Mulcom (CPLX16 *pcplx16Input1, CPLX16 *pcplx16Input2, CPLX16 *pcplx16Output, UINT32 ui32Arrsize)
{

  for (ui32Row = 0; ui32Row < ui32Arrsize; ui32Row++)
  {
      pcplx16Output[ui32Row].real  = ((pcplx16Input1[ui32Row].real*pcplx16Input2[ui32Row].real) - (pcplx16Input1[ui32Row].imag*pcplx16Input2[ui32Row].imag))/256;
      pcplx16Output[ui32Row].imag  = ((pcplx16Input1[ui32Row].real*pcplx16Input2[ui32Row].imag) + (pcplx16Input1[ui32Row].imag*pcplx16Input2[ui32Row].real))/256;
  }

}


/**
This function takes estimated outputs and actual outputs as input
Finds number of failed and passed test cases, writes results for each
test case into a file and also creates a summary file of all the test cases
**/

void FwriteResults (Output_t stOut, UINT16 ui16IterTestcase)
{
  /** PRIVATE VARIABLE DEFINITIONS *********************************************/

  FLOAT  afTrueValues [3*NUM_SC];
  UINT8  ui8IterBuffer;
  UINT8  NUM_CVAerr  = 0;
  static UINT16 NUM_FAIL = 0;
  UINT8  ToA_diff    = 0;
  FLOAT  RCFO_diff   = 0;
  FLOAT  Actual_RCFO = 0;

  /* File includes */
  if (DYNDET == 0)
  {
     sprintf(achfname,"Sample_Test_Data\\PRM_%u\\CVA_%u\\True_values%u_%u.txt",PRM,CVA,PRM,ui16IterTestcase+1);
  }
  else
  {
     sprintf(achfname,"Sample_Test_Data\\PRM_%u\\CVA_%u\\True_values%u_%u.txt",PRM,aui8TestCaseMap[TESTCASEINDEX-1],PRM,ui16IterTestcase+1);
  }

  pfile = fopen(achfname,"r");

  for (ui8IterBuffer = 0; ui8IterBuffer < 3*NUM_SC; ui8IterBuffer++)
   {
    fscanf(pfile,"%f,\n",&afTrueValues[ui8IterBuffer]);
   }

  fclose(pfile);

  if (DYNDET == 1)
  {
      for(ui32Iter = 0 ; ui32Iter < NUM_SC ; ui32Iter++)
      {
        if (stOut.aui8CVA[ui32Iter] != (UINT8)afTrueValues[ui32Iter])
        {
          NUM_CVAerr += 1;
        }
      }

      if (ui16IterTestcase == 0)
      {
        sprintf(achfname,"Sample_Test_Results\\PRM_%u\\CVA_%u\\Summary_%u.txt",PRM,aui8TestCaseMap[TESTCASEINDEX-1],aui8TestCaseMap[TESTCASEINDEX-1]);
        pfile = fopen(achfname,"w");
        if (TESTCASEINDEX == 4)
        {
            fprintf(pfile,"TEST CASE Type : Set of UE's consists of UE's from CVA 1 and CVA 2\n\n");
        }
        else if (TESTCASEINDEX == 5)
        {
            fprintf(pfile,"TEST CASE Type : Set of UE's consists of UE's from CVA 2 and CVA 3\n\n");
        }
        else if (TESTCASEINDEX == 6)
        {
            fprintf(pfile,"TEST CASE Type : Set of UE's consists of UE's from CVA 1 and CVA 3\n\n");
        }
        else if (TESTCASEINDEX == 7)
        {
            fprintf(pfile,"TEST CASE Type : Set of UE's consists of UE's from All CVA(i.e, 1,2 and 3)\n\n");
        }
        else
        {
           fprintf(pfile,"TEST CASE Type : All UE's are from CVA %u\n\n",TESTCASEINDEX);
        }
        fprintf(pfile,"*******************************************************************\n");
        fprintf(pfile,"************* Failed TEST CASES Details ***************************\n");
        fprintf(pfile,"*******************************************************************\n\n");
        fprintf(pfile,"-------------------------------------------------------------------\n");
        fprintf(pfile,"%s %30s\n","TEST CASE No.","No. of CVA detection error");
        fprintf(pfile,"-------------------------------------------------------------------\n");

        fclose(pfile);
      }

      if (NUM_CVAerr == 0)
      {
        sprintf(achfname,"Sample_Test_Results\\PRM_%u\\CVA_%u\\Passed_Testcases\\TESTCASE_%u.txt",PRM,aui8TestCaseMap[TESTCASEINDEX-1],ui16IterTestcase+1);
      }
      else
      {
        NUM_FAIL += 1;
        sprintf(achfname,"Sample_Test_Results\\PRM_%u\\CVA_%u\\Summary_%u.txt",PRM,aui8TestCaseMap[TESTCASEINDEX-1],aui8TestCaseMap[TESTCASEINDEX-1]);
        pfile = fopen(achfname,"a");

        fprintf(pfile,"%4u %22u\n",ui16IterTestcase+1,NUM_CVAerr);

        fclose(pfile);

        sprintf(achfname,"Sample_Test_Results\\PRM_%u\\CVA_%u\\Failed_Testcases\\TESTCASE_%u.txt",PRM,aui8TestCaseMap[TESTCASEINDEX-1],ui16IterTestcase+1);

      }

  }
  else
  {
    sprintf(achfname,"Sample_Test_Results\\PRM_%u\\CVA_%u\\No_DYDET\\TESTCASE_%u.txt",PRM,CVA,ui16IterTestcase+1);
  }


  pfile = fopen(achfname,"w+");

  fprintf(pfile,"**********************************************************************************\n");
  fprintf(pfile,"Preamble format : %u\n",PRM);
  fprintf(pfile,"RCFO scaling    : 2^17\n");
  fprintf(pfile,"UAD format      : Indicator (Actual estimated value before thresholding)\n");
  fprintf(pfile,"RCFO format     : Scaled estimated value (Actual estimated value)\n");
  fprintf(pfile,"**********************************************************************************\n\n");
  fprintf(pfile,"----------------------------------------------------------------------------------\n");
  if (DYNDET == 0)
  {
     fprintf(pfile,"%s %10s %5s %12s %15s %20s \n","UAD","True CVA","ToA","ToA error","RCFO(x 10^-6)","RCFO error(x 10^-6)");
  }
  else
  {
     fprintf(pfile,"%s %7s %10s %5s %12s %15s %20s \n","UAD","CVA","True CVA","ToA","ToA error","RCFO(x 10^-6)","RCFO error(x 10^-6)");
  }

  fprintf(pfile,"----------------------------------------------------------------------------------\n");

  for(ui32Iter = 0 ; ui32Iter < NUM_SC ; ui32Iter++)
  {
    ToA_diff    = abs(stOut.ai16ToA[ui32Iter]  - afTrueValues[ui32Iter+NUM_SC]);
    Actual_RCFO = (FLOAT)stOut.ai16RCFO[ui32Iter]/RCFO_SCALE;
    RCFO_diff   = Actual_RCFO - afTrueValues[ui32Iter+2*NUM_SC];

    if (DYNDET == 0)
    {
        fprintf(pfile,"%u(%u) %4u %9d %8u %8d (%7.2f) %12.2f\n",stOut.aui8UAD[ui32Iter],aui8UAD[ui32Iter],
            (UINT8)afTrueValues[ui32Iter],stOut.ai16ToA[ui32Iter],ToA_diff,stOut.ai16RCFO[ui32Iter],Actual_RCFO*pow(10,6),RCFO_diff*pow(10,6));
    }
    else
    {
       fprintf(pfile,"%u(%u) %4u %7u %9d %8u %8d (%7.2f) %12.2f\n",stOut.aui8UAD[ui32Iter],aui8UAD[ui32Iter],
            stOut.aui8CVA[ui32Iter],(UINT8)afTrueValues[ui32Iter],stOut.ai16ToA[ui32Iter],ToA_diff,stOut.ai16RCFO[ui32Iter],Actual_RCFO*pow(10,6),RCFO_diff*pow(10,6));
    }


  }
  fclose(pfile);
  if (DYNDET == 1)
  {
      if (!NUM_CVAerr)
      {
        printf("\n************************** SUCCESS ***************************************************************\n");
        printf("Detection finished, NO CVA detection error.\n");
        printf("Obtained results stored in '%s'\n",achfname);
        printf("**************************************************************************************************\n\n");
      }
      else
      {
        printf("\n************************** TEST CASE FAILED ******************************************************\n");
        printf("Detection finished, %u CVA detection error found.\n",NUM_CVAerr);
        printf("Obtained results stored in '%s'\n",achfname);
        printf("**************************************************************************************************\n\n");
      }

      if (ui16IterTestcase == NUMTESTCASES-1)
      {
        sprintf(achfname,"Sample_Test_Results\\PRM_%u\\CVA_%u\\Summary_%u.txt",PRM,aui8TestCaseMap[TESTCASEINDEX-1],aui8TestCaseMap[TESTCASEINDEX-1]);
        pfile = fopen(achfname,"a");

        fprintf(pfile,"\n********************* SUMMARY ******************************\n");
        fprintf(pfile,"Number of TEST CASES :%4u\n", NUMTESTCASES);
        fprintf(pfile,"Number of PASSES TEST CASES :%u\n", NUMTESTCASES - NUM_FAIL);
        fprintf(pfile,"Number of FAILED TEST CASES :%u\n", NUM_FAIL);
        fprintf(pfile,"************************************************************\n");

        fclose(pfile);

        printf("\n********************************* END ********************************************\n");
        printf("Finished TESTING the NPRACH Detector code for %u TEST CASES\n",NUMTESTCASES);
        printf("Summary of the TESTING process is stored in '%s'\n",achfname);
        printf("**********************************************************************************\n");
      }
  }
  else
  {
    printf("\n************************** SUCCESS ***************************************************************\n");
    printf("Detection finished.\n");
    printf("Obtained results stored in '%s'\n",achfname);
    printf("**************************************************************************************************\n\n");

    if (ui16IterTestcase == NUMTESTCASES-1)
    {
       printf("\n********************************* END ********************************************\n");
       printf("Finished TESTING the NPRACH Detector code for %u TEST CASES\n",NUMTESTCASES);
       printf("**********************************************************************************\n");
    }
  }


}

/********************** End of file Mat_operations_Fixed.c ***********************/
