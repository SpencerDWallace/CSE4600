// g++ -o server server.cpp

#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <unistd.h>
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h>
#include <vector>
#include <pthread.h>
#define MAX 80 
#define PORT 54551 
#define SA struct sockaddr 

struct clientDetails{
  int sock;
  char* cName;
  clientDetails(){};
  clientDetails(int s, char*n)
  {sock = s; cName = n;};
};

// Function designed for chat between client and server. 
void openChat(clientDetails* client) 
{
  int n;  
  // infinite loop for chat 
  for (;;) {
    char BUFF[MAX];// clientName[MAX];     
    int sockfd = client->sock;
    char* name = client->cName;
    bzero(BUFF, MAX); 
    // read the message from client and copy it in buffer 
    read(sockfd, BUFF, sizeof(BUFF)); 
    // print buffer which contains the client contents 
    printf("From client (%s): %s \n", name, BUFF); 
    bzero(BUFF, MAX); 
    
    n = 0;
    // copy server message in the buffer 
    while ((BUFF[n++] = getchar()) != '\n')
      ;
    
    // and send that buffer to client
    write(sockfd, BUFF, sizeof(BUFF)); 
    printf("Message sent to client (%s). Waiting for client\n", name);
    // if msg contains "Exit" then server exit and chat ended. 
    if (strncmp("exit", BUFF, 4) == 0) { 
      printf("Server Exit...\n"); 
      break;  
    }
  } 
};

// Driver function 
int main(int arc, char *argv[]) 
{ 
  int sockfd, connfd, len; 
  struct sockaddr_in servaddr, cli;
  socklen_t addr_size;
  
  //char *name = argv[1];
  // socket create and verification 
  sockfd = socket(AF_INET, SOCK_STREAM, 0); 
  if (sockfd == -1) { 
    printf("socket creation failed...\n"); 
    exit(0); 
  } 
  else
    printf("Socket successfully created..\n"); 
  bzero(&servaddr, sizeof(servaddr)); 
  
  // assign IP, PORT 
  servaddr.sin_family = AF_INET; 
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
  servaddr.sin_port = htons(PORT); 
  
  // Binding newly created socket to given IP and verification 
  if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
    printf("socket bind failed...\n"); 
    exit(0); 
  } 
  else
    printf("Socket successfully binded..\n"); 
  
  // Now server is ready to listen and verification 
  if ((listen(sockfd, 5)) != 0) { 
    printf("Listen failed...\n"); 
    exit(0); 
  } 
  else
    printf("Server listening..\n"); 
  len = sizeof(cli); 
  
  // Accept the data packet from client and verification
  bool forked = false;
  int numThreads = 49; //char for 1
  for(;;){
    connfd = accept(sockfd, (SA*)&cli, &addr_size); 
    if (connfd < 0) { 
      printf("server acccept failed...\n"); 
      exit(0); 
    } 
    else
      printf("server acccepted the client...\n");
    
    int pid = fork();
    if(pid == 0){
      char* name = (char*)malloc(sizeof(char*));
      *name = (char)numThreads;
      clientDetails* newClient = new clientDetails(connfd, name);
      openChat(newClient); 
      break;
    }
    numThreads++;
    
  }
  
  // After chatting close the socket 
  close(sockfd); 
}
