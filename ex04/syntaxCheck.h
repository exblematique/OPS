/******************************************************************************
 * File:         syntaxCheck.h
 * Version:      1.4
 * Datum:        2018-02-20
 * Auhtor:       M. van der Sluys, J.H.L. Onokiewicz, R.B.A. Elsinghorst, J.G. Rouland
 * Description:  Declaration of the test functies defined in testfuncties.c
 *               for display.c
 ******************************************************************************/

#ifndef syntaxCheckH
#define syntaxCheckH

#include "errorCodes.h"

ErrCode TestType(char *printMethod);
/*
  Input:          printMethod = starting address of Type parameter
  Precondition:	  At least one character is present from address printMethod
  Function:       Test whether:
                  - type is a single character
                  - type is e, p or w
  Postcondition:  None
  Output:	  Error code:
                  0 = NO_ERR:    no error
                  2 = ERR_TYPE:	 unknown print method
*/

ErrCode TestNr(char *numberOfTimes);
/*
  Input:          numberOfTimes = starting address of number-of-times parameter
  Precondition:	  At least one character is present from address numberOfTimes
  Function:       Test whether:
                  - string contains a number without + or - sign
                  - string does not contain additional characters
  Postcondition:  None
  Output:	  Error code:
            0 = NO_ERR:	 no error
            3 = ERR_NR:	 incorrect number
*/

ErrCode TestChar(char *printChar);
/*
  Input:          printChar = starting address of print character string
  Precondition:	  At least one character is present from address printChar
  Function:       Test whether:
                  - string contains exactly one character
  Postcondition:  None
  Output:	  Error code:
            0 = NO_ERR:	   no error
            4 = ERR_CHAR:  more than one character present
*/

#endif
