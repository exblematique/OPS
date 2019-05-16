/******************************************************************************
 * File:         getsignal.c
 * Version:      0.1
 * Date:         2019-04-25
 * Author:       Yoann Chappaz
 * Description:  OPS exercise 5: signals for Synchronisation
 ******************************************************************************/

#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>



int main(int argc, char *argv[]) {
  
  if (argc != 1){
    printf("The function doesn't need argument\n");
    return 1;
  }

  int sig = 25;
  char pipeRead[10];
  pid_t pid;
  int pipe = open("/home/student/.fifo/PIDpipe", O_RDONLY);
  read(pipe, &pipeRead, sizeof(pipeRead));
  pid = atoi(pipeRead);
  close(pipe);
  
  while (1){
    if (kill(pid, sig) != 0){
      printf("The signal cannot be send\n");
      return 1;
    }
    printf("Signal send, the next one will be send in 3 seconds\n");
    sleep(3);
  }
  
  return 0;
}
