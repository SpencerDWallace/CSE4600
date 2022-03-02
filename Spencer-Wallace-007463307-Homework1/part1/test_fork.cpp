/***************************************
Student: Spencer Wallace
Instructor: Dr. Khan
CSUSB - CSE 4600

Template provide by Dr.Khan
***************************************/
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

int main()
{
  pid_t pid;
  std::string message;
  int n;
  std::cout << "fork program starting" << std::endl;

  pid = fork();
  switch(pid){
  case -1:
    std::cout << "fork failed" << std::endl;
    return 1;
  case 0:
    message = "this is the child\n";
    n = 5;
    break;
  default:
    message = "this is the parent\n";
    n = 3;
    break;
  }

  for(int i = 0; i < n; i++){
    std::cout << message;
    sleep(1);
  }

  return 0;
}
