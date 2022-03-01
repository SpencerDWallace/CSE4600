/*****************************
Student: Spencer Wallace
Instructor: Dr. Khan
CSUSB - CSE 4600

Template Provided by Dr. Khan
*****************************/
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[])
{
  char buffer [BUFSIZ + 1];
  FILE* fpi;
  int chars_read;
  memset(buffer, 0, sizeof(buffer));
  fpi = popen("ps -auxw", "r");
  if(fpi != NULL){
    chars_read = fread(buffer, sizeof(char), BUFSIZ, fpi);
    
    if(chars_read > 0)
	  std::cout << "Output from pipe: " << buffer << std::endl;
    pclose(fpi);
    
    return 0;
  }

  return 1;
}
