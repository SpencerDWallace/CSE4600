//g++ -o call_center call_center.cpp -lpthread
/***************************************************************
exiting program before sem_close is called will cause infinite 
waiting as mutex will not be initialized, if this occurs please 
change the name in sem_open (the first param - initially "5").
***************************************************************/

#include <cstdio>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <atomic>

const int NUM_OPERATORS = 3;
const int NUM_CUSTOMERS = 10;

sem_t *mutex;

void join_call(char* customer)
{
  printf("%s is being connected to the operator.\n", customer);
  int rand_sleep = rand()%5 + 3;
  sleep(rand_sleep);
  printf("%s has finished their call with the operator.\n", customer);
};

void call_center(char* customer)
{
  printf("%s is waiting to be connected.\n", customer);
  sem_wait(mutex);
  join_call(customer);
  sem_post(mutex);
  int numOperators;
  sem_getvalue(mutex, &numOperators);
  printf("Number of operators available = %d.\n", numOperators);

};

int main()
{
  //if infinite waiting change "5" to another character or string
  mutex = sem_open("5", O_CREAT, 0644, 3);

  char* customers[] = {"Alice", "Bob", "John", "Mark", "Alex", "David", "Matthew", "Jonah", "Eli", "Gabriel"};

  for(int i = 0; i < NUM_CUSTOMERS; i++)
    {
      if(fork() == 0){
	call_center(customers[i]);
	return 0;
      }
    }
  
  while(1){
    sleep(5);
    int numOperators;
    sem_getvalue(mutex, &numOperators);
    if(numOperators == 3){
      sem_close(mutex);
      return 0;
    }
  }
  
}
