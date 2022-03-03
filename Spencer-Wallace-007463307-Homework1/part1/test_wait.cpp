/***************************************
Student: Spencer Wallace
Instructor: Dr. Khan
CSUSB - CSE 4600

Template provided by Dr. Khan
***************************************/
//g++ -o test_wait test_wait.cpp

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

//linked list seemed like fun
struct Tfork{
  pid_t ID;
  Tfork* child;
  Tfork* parent;
};

void printTfork(Tfork* node)
{
  std::cout << "Starting ancestry list: from newest child to oldest parent" << std::endl;
  std::cout << "Youngest ==> "; 
  while(node != nullptr)
    {
      std::cout << node->ID << " ";
      node = node->parent;
    }
  std::cout << "<== Oldest" << std::endl; 
}

Tfork* newTforkNode(Tfork* node)
{
  Tfork* newNode = new Tfork;
  newNode->parent = node;
  newNode->ID = getpid();
  return newNode;
}

int main()
{
  pid_t pid;
  std::string message;
  int n;
  int exit_code;
  std::cout << "fork program starting" << std::endl;
  Tfork* forkInfo = new Tfork;
  forkInfo->ID = getpid();
  forkInfo->parent = nullptr;

  pid = fork();

  int end = 2;
  for(int i = 0; i < end; i++)
    {
      if(pid == 0)
	{
	  forkInfo->child = newTforkNode(forkInfo);
	  forkInfo = forkInfo->child;
	  if(i < end-1)
	    pid = fork();
	}
    }

  switch(pid){
  case -1:
    std::cout << "fork failed" << std::endl;
    return 1;
  case 0:
    message = "this is the child\n";
    n = 5;
    exit_code = 9;
    break;
  default:
    message = "this is the parent\n";
    n = 3;
    exit_code = 0;
    break;
  }

  for(int i = 0; i < n; i++){
    std::cout << message;
    sleep(1);
  }

  if(pid != 0)
    {
      int stat_val;
      pid_t child_pid;

      child_pid = wait(&stat_val);
      std::cout << "Child finished: PID = " << child_pid << std::endl;
      if(WIFEXITED (stat_val))
	std::cout << "child exited with code " << WEXITSTATUS(stat_val) << std::endl;
      else
	std::cout << "child terminated abnormally!" << std::endl;
    }
  else{
    printTfork(forkInfo);
  
  }
  
  exit(exit_code);
}
