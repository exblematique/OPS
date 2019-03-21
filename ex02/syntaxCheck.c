/******************************************************************************
 * File:         syntaxCheck.c
 * Version:      1.4
 * Datum:        2018-02-20
 * Author:       M. van der Sluys, J.H.L. Onokiewicz, R.B.A. Elsinghorst, J.G. Rouland
 * Description:  OPS exercise 2:  definitions of test functions for display.c
 ******************************************************************************/

#include <stdlib.h>
#include <stdio.h> //For test only
#include <limits.h> 
#include <string.h>
#include <stdbool.h>
#include "syntaxCheck.h"



// Test whether an argument is one character long and has the correct value (e,p,w):
ErrCode TestType(char *printMethod) {
  ErrCode fout = NO_ERR;

  int size = strlen(printMethod);
  if (size != 1) {
    fout = ERR_TYPE;
  }
  else {
    char letter = *printMethod;
    
    if (letter != 'e' && letter != 'p' && letter != 'w'){
      fout = ERR_TYPE;
      printf("letter = %d", letter);
    }
  }
  return fout;
}


// Test whether an argument contains a non-negative number:
ErrCode TestNr(char *numberOfTimes) {
  ErrCode fout = NO_ERR;
  //bool ok;

  int size = strlen(numberOfTimes);
  char number[size];
  sprintf(number, "%d", atoi(numberOfTimes));

  if (number[0] == '-'){
    fout = ERR_NR;
  }
  else {
    for (int i=0; i<size; i++) {
      if (number[i] != *numberOfTimes++){
	fout = ERR_NR;
	break;
      }
    }
  }
    /*
  for (int i = 0; i<size; i++){
    ok = false;
    for (int j = 0; j<10; j++) {
      if (*numberOfTimes == (char) j){
	ok = true;
	break;
      }
    }
    if (!ok){
      fout = ERR_NR;
      break;
    }
    numberOfTimes++;
    }*/
  return fout;
}


// Test whether an argument contains only one character:
ErrCode TestChar(char *printChar) {
  ErrCode fout = NO_ERR;
  
  if (strlen(printChar) != 1)
    fout = ERR_CHAR;
  
  return fout;
}
