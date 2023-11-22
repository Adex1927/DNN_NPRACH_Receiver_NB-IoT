/****************************************************************************
* Copyright   : All rights reserved. This document/code contains information
* that is proprietary to Lekha Wireless Solutions Pvt. Ltd. No part of this
* document/code may be reproduced or used in whole or part in any form or
* by any means- graphic, electronic or mechanical without the written
* permission of Lekha Wireless Solutions Pvt. Ltd.
*
* Company     : Lekha Wireless Solutions Pvt. Ltd.
* File Name   : main.c
* Description : Main function which calls the supporting functions
                NPRACHConfig() and NPRACHDetector() and finally stores the
                result in a file
* Comments    : Calls NPRACHConfig(), NPRACHDetector() and FwriteResults()
                functions
****************************************************************************/

/** PROJECT INCLUDES *********************************************************/
#include "NPRACH_Fixed.h"

/** GLOBAL VARIABLE DEFINITIONS **********************************************/

UINT8  ui8CvAreaRx       = 3;

/* For testing purpose */
UINT16 ui16IterTestcase;

/**
===============================================================================
To test for different test cases change the variables in "NPRACH_Fixed.h"
header file before running main() function
===============================================================================
**/

int main()
{
  /** System Configurations **/

  NPRACHConfig(ui8CvAreaRx);

  printf("************************** NPRACH Configurations *****************************\n");
  printf("Preamble format : %u\n",PRM);
  printf("FFT size : M1 = %u, M2 =%u || CP length : %u\n",stTxParams.ui16FFT2M1,stTxParams.ui16FFT2M2,stTxParams.ui16CpLen);
  printf("******************************************************************************\n\n");

  printf("***************************** TEST CASE Type ********************************\n");
  if (DYNDET == 0)
  {
    printf("No Dynamic coverage area detection. All UE's are from CVA %u\n",CVA);
  }
  else
  {
      printf("Dynamic coverage area detection enabled.\n");
      if (TESTCASEINDEX == 4)
      {
        printf("Set of UE's consists of UE's from CVA 1 and CVA 2\n");
      }
      else if (TESTCASEINDEX == 5)
      {
        printf("Set of UE's consists of UE's from CVA 2 and CVA 3\n");
      }
      else if (TESTCASEINDEX == 6)
      {
        printf("Set of UE's consists of UE's from CVA 1 and CVA 3\n");
      }
      else if (TESTCASEINDEX == 7)
      {
        printf("Set of UE's consists of UE's from All CVA(i.e, 1,2 and 3)\n");
      }
      else
      {
        printf("All UE's are from CVA %u\n",TESTCASEINDEX);
      }
  }
  printf("******************************************************************************\n\n");

  /** Loop for TEST CASES **/

  for (ui16IterTestcase = 0; ui16IterTestcase<NUMTESTCASES; ui16IterTestcase++)
  {
      printf("\nRunning 'NPRACH Detector' for Test case %u........\n",ui16IterTestcase+1);

      /** NPRACH Receiver **/
      NPRACHDetector(ui16IterTestcase);

      /** Writing results obtained i.e, ToA,RCFO,CVA and UAD into separate file and comparing it with the Matlab results **/
      FwriteResults(stOut, ui16IterTestcase);
  }

  return 0;
}

/********************** End of file main.c ***********************/
