/******************************************************************************
 * File:         errorCodes.h
 * Version:      1.4
 * Date:         2018-02-20
 * Author:       M. van der Sluys, J.H.L. Onokiewicz, R.B.A. Elsinghorst, J.G. Rouland
 * Description:  Definition of the type ErrCode containing error codes for the 
 *               functions  in displayFunctions.c and syntaxCheck.c.
 ******************************************************************************/

#ifndef errorCodes_H
#define errorCodes_H

#define NUM_OF_PARS 4  // Number of arguments on the command line, including the program name

typedef enum {NO_ERR, ERR_PARS, ERR_TYPE, ERR_NR, ERR_CHAR} ErrCode;
/*
  NO_ERR    No syntax error occurred in the command line
  ERR_PARS  The number of command-line parameters is not equal to 4
  ERR_TYPE  The print type is incorrect (not one of 'e', 'p' or 'w')
  ERR_NR    The number is not a positive integer
  ERR_CHARS The print text contains more than one character
*/

#endif
