/*
g++ -o matrix matrix.cpp -lpthread
*/
/******** idea for algorithm ********/
//each row in matrix A is assigned a thread
//each thread iterates through all columns in matrix B to produce output
#include <pthread.h>
#include <cstdlib>
#include <cstdio>

const int A_ROWS = 4;
const int A_COLS = 3;
const int B_ROWS = 3;
const int B_COLS = 4;

struct matr_mult{
  const int* A = (int*)malloc(sizeof(int)*A_ROWS*A_COLS); 
  const int* B = (int*)malloc(sizeof(int)*B_ROWS*B_COLS);
  int* output = (int*)malloc(sizeof(int)*A_ROWS*B_COLS);

  matr_mult();
  matr_mult(const int a[], const int b[])
  {
    A = a; B = b;
    for(int i = 0; i < A_ROWS*B_COLS; i++) *(output + i) = 0;
  };
};


void print_output(const int* p)
{
  printf("output matrix is\n");
  for(int i = 0; i < A_ROWS*B_COLS; i++)
    {
      if(i%A_ROWS == 0)
	printf("\n");
      printf("%d ", p[i]);
    }
  printf("\n");
}

const int A[] = {5,2,3,4,5,7,6,3,7,1,3,4};
const int B[] = {4,5,6,1,3,2,3,5,2,8,7,7};
matr_mult* mat = new matr_mult(A,B);

void* mult(void* data)
{
  int* rowA = (int*) data;
  printf("rowA is: %d  |  (thread number)\n", *rowA);
  for(int i = 0; i < B_COLS; i++){
    for(int j = 0; j < B_ROWS; j++){
      // printf("output index is: %d\n", i + *rowA*A_ROWS);
      // printf("A index is: %d\n", *rowA*A_COLS + j);
      // printf("B index is: %d\n", i + j*B_COLS);
      mat->output[i + *rowA*A_ROWS] += *(mat->A + *rowA*A_COLS + j) * *(mat->B + i + j*B_COLS);
    }
  }
  
  return NULL;
}

int main()
{  

  pthread_t id1, id2, id3, id4; //for 4 rows in matrix A
  
  int* t0 = new int; *t0 = 0;
  int* t1 = new int; *t1 = 1;
  int* t2 = new int; *t2 = 2;
  int* t3 = new int; *t3 = 3;
  
  mult((void*)t0);
  mult((void*)t1);
  mult((void*)t2);
  mult((void*)t3);
  
  /*
  pthread_create (&id1, NULL, mult, (void*)t0);
  pthread_create (&id2, NULL, mult, (void*)t1);
  pthread_create (&id3, NULL, mult, (void*)t2);
  pthread_create (&id4, NULL, mult, (void*)t3);
  
  pthread_join (id1, NULL);
  pthread_join (id2, NULL);
  pthread_join (id3, NULL);
  pthread_join (id4, NULL);
  */
  print_output(mat->output);
  return 0;
}
