/***************************************
Student: Spencer Wallace
Instructor: Dr. Khan
CSUSB - CSE 4600
***************************************/


#include <unistd.h>
#include <iostream>

int main(int argc, char* argv[])
{
  if(argc > 1 && argc <= 2){
    std::cout << "Running " << argv[1] << " with execl" << std::endl << std::endl;
  execl(argv[1], argv[1], NULL );

  //only reaches this point if execl cause error
  std::cout << "the program is exiting" << std::endl;
  return 0;
  }
  else if(argc > 2)
    std::cout << "Too many command line arguments. Only enter the name of the program you would like to execute." << std::endl;
  else
    std::cout << "Please provide the name of the program you would like to execute." << std::endl;
  
}
