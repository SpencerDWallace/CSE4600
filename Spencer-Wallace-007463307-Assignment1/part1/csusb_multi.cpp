#include <pthread.h>                                                            
#include <stdio.h>
#include <cstdlib>

int n = 50; //array size
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barrier;
bool allThreadsCreated = false;

struct th_args{
  int *nums = (int*)malloc(sizeof(int) * n);
  int thID;
  th_args();
  th_args(int ar[], int id)
  {
    nums = ar; thID = id;
  }
};

void csu(int num) {
  if(num % 2 == 0 && num % 5 != 0)
    printf("%s", "CSU ");
};

void sb(int num){
  if(num % 5 == 0 && num % 2 != 0)
    printf("%s", "SB ");
};

void csusb(int num){
  if(num % 10 == 0)
    printf("%s", "CSUSB ");
};

void number(int num)
{
  if(num % 2 != 0 && num % 5 != 0)
    printf("%d ", num);
};


void* thread_func(void* data)
{
  struct th_args* args = (struct th_args*)data;
  while(!allThreadsCreated)
    ;

  for(int i = 0; i < n; i++)
    {
      pthread_mutex_lock(&mutex);
      //printf("I, thread: %d have the lock.\n", args->thID);
      switch(args->thID)
	{
	case 3: csusb(args->nums[i]); break;
	case 1: csu(args->nums[i]); break;
	case 2: sb(args->nums[i]); break;
	case 4: number(args->nums[i]); break;
	default: printf("BAD THREAD!\n"); break;
	}
      //      printf("I, thread: %d have released the lock.\n", args->thID);
      pthread_mutex_unlock(&mutex);
      pthread_barrier_wait(&barrier);
    }
  return NULL;
  //  pthread_exit(NULL);
}


int main()
{
  
  int nthreads = 4;
  pthread_barrier_init(&barrier, NULL, nthreads);

  int csusbArray[n];
  printf("\n");
  
  for(int i = 1; i <= n; i++) //initialize array
      csusbArray[i-1] = i;

  pthread_t id1, id2, id3, id4;

  //create the threads
  th_args* th1_args = new th_args(csusbArray, 1);
  th_args* th2_args = new th_args(csusbArray, 2);
  th_args* th3_args = new th_args(csusbArray, 3);
  th_args* th4_args = new th_args(csusbArray, 4);

  pthread_create (&id1, NULL, thread_func, (void*)th1_args);
  pthread_create (&id2, NULL, thread_func, (void*)th2_args);
  pthread_create (&id3, NULL, thread_func, (void*)th3_args);
  pthread_create (&id4, NULL, thread_func, (void*)th4_args);

  allThreadsCreated = true;
  //  printf("\nTHREADS CREATED!!!!!\n");
  
  //wait for the threads to exit
  pthread_join (id1, NULL);
  pthread_join (id2, NULL);
  pthread_join (id3, NULL);
  pthread_join (id4, NULL);

  printf("\n\n");
  // printf("THREADS RETURNED!!!!!\n");

  return 0;
}
