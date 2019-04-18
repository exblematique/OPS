/******************************************************************************
 * File:         display.c
 * Version:      1.4
 * Date:         2018-02-20
 * Author:       M. van der Sluys, J.H.L. Onokiewicz, R.B.A. Elsinghorst, J.G. Rouland
 * Description:  OPS exercise 2: syntax check
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include "displayFunctions.h"

int main(int argc, char *argv[]) {
  unsigned long int numOfTimes, niceIncr;
  char printMethod, printChar;
  ErrCode err;
  
  err = SyntaxCheck(argc, argv);  // Check the command-line parameters
  if(err != NO_ERR) {
    DisplayError(err);        // Print an error message
  } else {
      printMethod = argv[1][0];
      numOfTimes = strtoul(argv[2], NULL, 10);  // String to unsigned long
      niceIncr = strtoul(argv[3], NULL, 10);

      int idChild;
      int nbChild = argc-4;
      for (int iChild=0; iChild<nbChild; iChild++){
	idChild = fork();
	if (idChild != 0) {
	  continue;
	}
	printChar = argv[iChild+4][0];
	printf("iChild= %d, iChild*niceIncr= %ld, iChild-th= %c\n", iChild, iChild*niceIncr, printChar);
	nice(iChild*niceIncr);
	PrintCharacters(printMethod, numOfTimes, printChar);  // Print character
	break;
      }
      if (idChild != 0){
	for (int i=0; i<nbChild; i++){ 
	  printf("Child with PID %d has stopped\n", wait(NULL));
	}
      }
  }
  printf("\n");  // Newline at end
  return 0;
}
