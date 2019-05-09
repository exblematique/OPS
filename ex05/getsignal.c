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
#include <unistd.h>

char digit = '0';
void changeDigit(int sig);

int main(int argc, char *argv[]) {
  
  struct sigaction signal;

  //Define signal
  memset(&signal, '\0', sizeof(signal));
  signal.sa_handler = changeDigit;
  signal.sa_flags = 0;
  sigemptyset(&signal.sa_mask);
  sigaction(25, &signal, NULL);

  printf("PID's program is: %i\n", getpid());
  
  while (1){
    write(1, &digit, sizeof(digit));
    sleep(1);
  }
  return 0;
}

void changeDigit(int sig){
  if (digit == '9') {
    digit = '0';
  } else {
    digit += 1;
  }
}  
