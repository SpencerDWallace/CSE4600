/***************************************
Student: Spencer Wallace
Instructor: Dr. Khan
CSUSB - CSE 4600

Template provided by Dr Khan
***************************************/
/*
pthreads_demo.cpp
  A very simple example demonstrating the usage of pthreads.
  Compile: g++ -o pthreads_demo pthreads_demo.cpp -lpthread
  Execute: ./pthreads_demo
*/

#include <pthread.h>
#include <stdio.h>
using namespace std;
//The thread
void * thread_func_one (void *data)
{
  char *tname = (char *) data;
  printf("This is thread function one, my thread name is: %s.\n", tname);
  pthread_exit (0);
}

void * thread_func_two (void *data)
{
  char *tname = (char *) data;
  printf("This is thread function two, my thread name is: %s.\n", tname);
  pthread_exit (0);
}

void * thread_func_three (void *data)
{
  char *tname = (char *) data;
  printf("This is thread function three, my thread name is: %s.\n", tname);
  pthread_exit (0);
}

int main ()
{
  pthread_t id1, id2, id3;           //thread identifiers
  pthread_attr_t attr1, attr2, attr3;  //set of thread attributes
  char *tnames[3] = { "Thread 1", "Thread 2", "Thread 3" }; //names of threads

  pthread_attr_init (&attr1);
  pthread_attr_init (&attr2);
  pthread_attr_init (&attr3);
  //create the threads
  pthread_create (&id1, &attr1, thread_func_one, tnames[0]);
  pthread_create (&id2, &attr2, thread_func_two, tnames[1]);
  pthread_create (&id3, &attr3, thread_func_three, tnames[2]);
  //wait for the threads to exit
  pthread_join (id1, NULL);
  pthread_join (id2, NULL);
  pthread_join (id3, NULL);
  return 0;
}
