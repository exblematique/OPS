/*****************************************************************************
 * File:         redirect.c
 * Version:      1
 * Date:         2018-04-25
 * Author:       Yoann Chappaz  
******************************************************************************/

#include <unistd.h>   // read(), write(), close(), fork(), pipe()
#include <stdio.h>    // printf(), perror()
#include <sys/wait.h> // wait()
#include <stdlib.h>   // exit()

#define ESC 0x1B
#define R 0
#define W 1

int main(void) {
  int pipeFromFilter[2], pipeToFilter[2];
  char buf;
  
  // Creating pipe
  if (pipe(pipeFromFilter) == -1 || pipe(pipeToFilter) == -1 ) {
    perror("Error pipe: ");
    exit(1);
  }

  //Creating child
  switch(fork()) {
  case -1:
    perror("Error fork: ");
    exit(EXIT_FAILURE);

  case 0:
    close(pipeToFilter[W]);
    dup2(pipeToFilter[R], 0);
    close(pipeToFilter[W]);
    
    close(pipeFromFilter[R]);
    dup2(pipeFromFilter[W], 1);
    close(pipeFromFilter[R]);
    
    execlp("./filter", "filter", NULL);
    perror("Error to call filter: ");
    exit(EXIT_FAILURE);
    
  default:
    close(pipeToFilter[R]);
    close(pipeFromFilter[W]);

    while(read(0, &buf, 1) > 0) {
      write(pipeToFilter[W], &buf, 1);
      if (buf == ESC){
	wait(NULL);
	close(pipeFromFilter[R]);
	close(pipeToFilter[W]);
	exit(EXIT_SUCCESS);
      }
      read(pipeFromFilter[R], &buf, 1);
      write(1, &buf, 1);
    }
  }
}
