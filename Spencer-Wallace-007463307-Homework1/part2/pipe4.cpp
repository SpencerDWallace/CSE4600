/*****************************
Student: Spencer Wallace
Instructor: Dr. Khan
CSUSB - CSE 4600

Template Provided by Dr. Khan
****************************/
//pipe4.cpp  (data producer)
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char* argv[])
{
    int data_processed;
    int file_pipes[2];
    const char some_data[] = "123";
    char buffer[BUFSIZ + 1];
    pid_t fork_result;

    if(argc > 1)
      {
	int arglength = 0;
	for(int i = 1; i < argc; i++){
	  arglength += strlen(argv[i]);
	}
	
	char* command = (char*)malloc(sizeof(char)*arglength);
	
	for(int i = 1; i < argc; i++){
	  strcat(command, argv[i]);
	  if(i != argc-1)
	    strcat(command, " ");
	}
	
	memset(buffer, '\0', sizeof(buffer));
	if (pipe(file_pipes) == 0) {   //creates pipe
	  fork_result = fork();
	  if (fork_result == (pid_t)-1) {  //fork fails
            fprintf(stderr, "Fork failure");
            exit(EXIT_FAILURE);
	  }
	  if (fork_result == 0) {    //child
            sprintf(buffer, "%d", file_pipes[0]);
            (void)execl("pipe5", "pipe5", buffer, (char *)0);
            exit(EXIT_FAILURE);
	  }
	  else{
	    data_processed = write(file_pipes[1], command,
                                   strlen(command));
            printf("%d - wrote %d bytes\n", getpid(), data_processed);
	  }
	}
	exit(EXIT_SUCCESS);
      }
    else;
}
