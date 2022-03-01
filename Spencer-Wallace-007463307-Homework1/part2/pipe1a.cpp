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

  if(argc > 1)
    {
      int arglength = 0;
      std::cout << "Made it" << std::endl;
      for(int i = 1; i < argc; i++){
	std::cout << "size of argv of " << i << " is: " << strlen(argv[i]) << std::endl;
	arglength += strlen(argv[i]) + 1;
      }

      char* command = (char*)malloc(sizeof(char)*arglength);
      
      for(int i = 1; i < argc; i++){
	std::cout << "argv of " << i << ": " << argv[i] << std::endl;
       	strcat(command, argv[i]);
	strcat(command, " ");
      }
      std::cout << "arglength is: " << arglength << " command is: " << command << std::endl;
      
      FILE* fpi;
     
      int chars_read;
      memset(buffer, 0, sizeof(buffer));
      fpi = popen(command, "r");
      if(fpi != NULL){
	chars_read = fread(buffer, sizeof(char), BUFSIZ, fpi);
	
	if(chars_read > 0)
	  std::cout << "Output from pipe: " << buffer << std::endl;
	pclose(fpi);
	
	return 0;
      }
    }

  return 1;
}
