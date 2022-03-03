/***************************************
Student: Spencer Wallace
Instructor: Dr. Khan
CSUSB - CSE 4600

Template provide by Dr.Khan
Referenced IBM documents on sigemptyset
***************************************/
//g++ -o -test_sigaction test_sigaction.cpp
#include <signal.h>
#include <unistd.h>
#include <iostream>

int main()
{
  //begin IBM reference
  struct sigaction ss;
  sigemptyset(&ss.sa_mask);
  ss.sa_handler = SIG_DFL;
  sigaction(SIGQUIT, &ss, 0);
  //end IBM reference
  
  while(1)
    {
      std::cout << "CSUSB CSE 4600 Operating Systems. Homework on Signals." << std::endl;
      sleep(1);
    }

  return 0;
}
