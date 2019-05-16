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
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include "displayFunctions.h"

int main(int argc, char *argv[]) {
  unsigned long int niceIncr;
  char *printChar;
  ErrCode err;
  
  err = SyntaxCheck(argc, argv);  // Check the command-line parameters
  if(err != NO_ERR) {
    DisplayError(err);        // Print an error message
  } else {

      niceIncr = strtoul(argv[3], NULL, 10);

      int idChild;
      int nbChild = argc-4;
      for (int iChild=0; iChild<nbChild; iChild++){
	idChild = fork();
	if (idChild != 0) {
	  continue;
	}
	printChar = argv[iChild+4];
	nice(iChild*niceIncr);
	printf("iChild= %d, iChild*niceIncr= %ld, iChild-th= %c, priority= %d\n", iChild, iChild*niceIncr, printChar[0], getpriority(PRIO_PROCESS, 0));
	execl("../ex02/display", "display", argv[1], argv[2], printChar, (char*) NULL);  // Return value only if it's not a succeed // Print character
	perror("Perror: ");
	break;
      }
      if (idChild != 0){
	for (int i=0; i<nbChild; i++){ 
	  printf("Child with PID %d has stopped\n", wait(NULL));
	}
	printf("All children have finished");
      }
  }
  printf("\n");  // Newline at end
  return 0;
}
