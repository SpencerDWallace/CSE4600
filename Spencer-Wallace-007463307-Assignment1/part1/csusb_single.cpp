<<<<<<< HEAD
=======
/*
g++ -o csusb_single csusb_single.cpp -lpthread
*/
>>>>>>> refs/remotes/origin/master
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int n = 50; //array size
bool printed;
bool csu(int num) {
  if(num % 2 == 0)
    {
      printf("%s", "CSU ");
      return true;
    }
  return false;
};

bool sb(int num){
  if(num % 5 == 0)
    {
      printf("%s", "SB ");
      return true;
    }
  return false;
};
bool csusb(int num ){
  if(num % 10 == 0)
    {
      printf("%s", "CSUSB ");
      return true;
    }
  return false;
};
bool number(int num)
{
  if(num % 2 != 0 && num % 5 != 0)
    {
      printf("%d ", num);
      return true;
    }
  return false;
};

int main()
{
  int csusbArray[n];

  for(int i = 1; i <= n; i++) //initialize array
    {
      csusbArray[i-1] = i;
    }

  printf("\n\n");
  
  for(int i = 0; i < n; i++)
    {
      int num = csusbArray[i];

      printed = csusb(num);
      if(printed) continue;
      
      printed = csu(num);
      if(printed) continue;

      printed = sb(num);
      if(printed) continue;

      number(num);
    }
  
  printf("\n\n");
  return 0;
}
