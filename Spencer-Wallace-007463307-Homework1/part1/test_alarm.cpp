/***************************************
Student: Spencer Wallace
Instructor: Dr. Khan
CSUSB - CSE 4600

Template provide by Dr.Khan
***************************************/
#include <signal.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <iostream>

void alarm_off(int sig)
{
  std::cout << "Alarm has gone off" << std::endl;
}

int main()
{
  int pid;
  std::cout << "Alarm testing!" << std::endl;

  if(pid = fork() == 0)
    {
      sleep(5);
      kill(getppid(), SIGALRM);
      return 1;
    }
  std::cout << "Waiting for alarm" << std::endl;
  (void) signal(SIGALRM, alarm_off);

  pause();
  std::cout << "Done!" << std::endl;

  return 1;
}
