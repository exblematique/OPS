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
#include <stdlib.h>

char digit = '0';
void changeDigit(int sig);

int main(int argc, char *argv[]) {
  
  if (argc != 2){
    printf("The function needs one argument only\n");
    return 1;
  }

  pid_t pid = atoi(argv[1]);
  int sig = 25;
  
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
