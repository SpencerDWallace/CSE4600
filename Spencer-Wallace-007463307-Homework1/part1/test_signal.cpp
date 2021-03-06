/***************************************
Student: Spencer Wallace
Instructor: Dr. Khan
CSUSB - CSE 4600

Template provide by Dr.Khan
***************************************/

#include <signal.h>
#include <unistd.h>
#include <iostream>

void func(int sig)
{
  std::cout << "oops -- i got a signal " << sig << std::endl;
}

int main()
{
  (void) signal(SIGINT, func);

  for(int i = 0; i < 20; ++i)
    {
      std::cout << "CSUSB CSE 4600 Operating Systems. Homework on Signals." << std::endl;
      sleep(1);
    }

  return 0;
}
