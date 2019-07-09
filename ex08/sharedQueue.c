/******************************************************************************
 * File:         main.c
 * Version:      1.2
 * Date:         2017-10-18
 * Author:       J. Onokiewicz, M. van der Sluys
 * Description:  OPS exercise 5: Queues
 ******************************************************************************/

#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>	//threading, mutexes
#include <unistd.h>		//write, sleep
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#include <signal.h>

#include "Queue.h"

#define nbProdThread 3
void *producerThread(void *queue_);		//Producer function
void *consumerThread(void *queue_);		//Consumer function
pthread_mutex_t queueAccess = PTHREAD_MUTEX_INITIALIZER;	//Mutex to lock the modification of queue

void sendStop(int sig);		//SHR for CTRL-C which called to stop the program

int producerRunning = 0;	//Number of producer currently running
bool running = false;		//Start when consumer and all producer are ready and becoming false when the stop signal is detected

int main() {
  struct sigaction act;
  pthread_t thWrite[nbProdThread];
  pthread_t thRead;
  
  data_t data[nbProdThread] = {{5, "I'm for the delay\n"},
					{4, "Three, Two, One\n"},
					{3, "To be or not to be\n"}};
  
  queue_t queue = {NULL};  // Note: element of queue = NULL
  
  //Defining new action for ctrl+c
  memset(&act, '\0', sizeof(act));
  act.sa_handler = sendStop;
  act.sa_flags = 0;
  sigemptyset(&act.sa_mask);
  sigaction(SIGINT, &act, NULL);
  
  //Creating queue to initialize threads
  createQueue(&queue, data[0]);
  pushQueue(&queue, data[1]);
  pushQueue(&queue, data[2]);
  
  /*//Showing set up queue
  printf("\nList the contents of the initialize queue:\n");
  showQueue(&queue);
  */
  
  //Starting threads
  for (int i=0; i<nbProdThread; i++){
    if(pthread_create(&thWrite[i], NULL, producerThread, (void*) &queue)){
      fprintf(stderr, "No thread %d\n", i);
      exit(EXIT_FAILURE);
    }
    sleep(1);
  }
  
  if(pthread_create(&thRead, NULL, consumerThread, (void*) &queue), NULL){
      fprintf(stderr, "No thread read\n");
      exit(EXIT_FAILURE);
  }

  //Because thRead waits that all writing threads stop, main function just needs to wait thRead before to stop program.
  for (int i=0; i<nbProdThread; i++) pthread_join(thWrite[i], NULL);
  pthread_join(thRead, NULL);
  //while(getchar() != '\n' && running);
  //pthread_join(thWrite[0], NULL);
  
  deleteQueue(&queue);
  
  return 0;
}



/* This is the producer thread function.
 * Thanks to initialize queue, the waiting time is known in queue.intVal
 * Loop starts to wait to ensure that all others thread has started.
 * Then every 3, 4 or 5 seconds, the thread lock queueAccess mutex to add these data to the queue
 * producerRunning is a global variable to finish proprely consumer function.
 */
void *producerThread(void *queue_){
  queue_t *queue = (queue_t*) queue_;
  
  data_t data;
  sprintf(data.text, "%s", frontQueue(queue)->text);
  data.intVal = frontQueue(queue)->intVal;
  
  pthread_mutex_lock(&queueAccess);
  popQueue(queue);
  pthread_mutex_unlock(&queueAccess);
  
  producerRunning += 1;
  while (!running);
  
  while (running){ 
    sleep(data.intVal);
	pthread_mutex_lock(&queueAccess);
    pushQueue(queue, data);
	pthread_mutex_unlock(&queueAccess);
  }
  
  producerRunning -= 1;
  pthread_exit(NULL);
}



/* This is the consumer function.
 * This opens (or create) the "save.txt" file to add all new production.
 * Every 15 seconds, this thread locks queueAccess mutex to empty the queue.
 * All values are send to stdout (fd = 1) and saved in "save.txt"
 * When the stopSignal is detected, this threads waits that all producer has finished
 * to save last production before closed the program
 */ 
void *consumerThread(void *queue_){
  queue_t *queue = (queue_t*) queue_;
  char buf[20] = "";
  data_t data = {-1, "Start of queue\n"};
  int file = open("save.txt", O_WRONLY|O_CREAT|O_APPEND);
  if (!file) {
	perror("save.txt");
	exit(1);
  }
  
  while (producerRunning != nbProdThread);
  //Don't need to lock because producer wait running state become true
  deleteQueue(queue);
  createQueue(queue, data);
  running = true;
  
  while (running){
	pthread_mutex_lock(&queueAccess);
	popQueue(queue);	//Remove initializer
	while (!emptyQueue(queue)){
	  sprintf(buf, "%s", frontQueue(queue)->text);
	  write(1, buf, strlen(buf));
	  write(file, buf, strlen(buf));
	  popQueue(queue);
	}
	deleteQueue(queue);
	createQueue(queue, data);
	pthread_mutex_unlock(&queueAccess);
	sleep(15);
  }
  
  
  while (producerRunning);
  popQueue(queue);
  while (!emptyQueue(queue)){
	sprintf(buf, "%s", frontQueue(queue)->text);
	write(1, buf, strlen(buf));
	write(file, buf, strlen(buf));
	popQueue(queue);
  }
  close(file);
  pthread_exit(NULL);
}

/* Function which called when CTRL-C is pressed
 * This just change the running state
 */
void sendStop(int sig){
	printf("\n%d signal detected!\nThe program will be stopped in 20 secondes maximum\nJust waiting...\n\n", sig);
	running = false;
}