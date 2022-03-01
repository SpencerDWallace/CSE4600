/***************************
Student: Spencer Wallace
Instructor: Dr. Khan
CSUSB - CSE 4600

geeksforgeeks was used
to reference stacks and 
template functions
***************************/
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <stack>
#include <sys/types.h>
#include <sys/wait.h>


//removes and returns an item from the stack
template <typename T>
T pop(std:: stack<T> *s)
{
  T item = s->top();
  s->pop();
  return item;
}

//prints the contents of the stack
template <typename T>
void printStack(const std::stack<T> s)
{
  std::stack<T> *copy = new std::stack<T>;
  *copy = s;
  for(int i = 0; i < s.size(); i++)
    {
      std::cout << pop(copy);
      (i < s.size() - 1) ? std::cout << ", " : std::cout << std::endl;
    }
  delete copy;
}


int main(int argc, char* argv[])
{
  int status;
  int parentID = getpid();
  int pid;
  std::stack<int> Ancestors; //using a stack sounded like fun, holds all ancestors

  for(int i = 0; i < 9; i++)
    {
      if(getpid() != parentID) //prevents unnecessary child
	pid = fork();
      else //main parent, initial child creation
	{
	  pid = fork();
	  if(getpid() == parentID){
	  std::cout << "Main process has ID: " << parentID << " and has created child with ID: " << pid << std::endl << std::endl;
	  wait(&status);
	  return 0;
	  }
	}

      if(pid == 0) //current child
	{
	  Ancestors.push(getppid());
	  std::cout << "Process with ID: " << getpid() << " has ancestors with IDs: ";
	  printStack(Ancestors);
	}
      else //parent
	{
	  wait(&status);
	  return 0;
	}
      
    }
  return 0;
}
