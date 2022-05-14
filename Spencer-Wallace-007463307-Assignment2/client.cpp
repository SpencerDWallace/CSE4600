// g++ -o client client.cpp

#include <netdb.h> 
#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#define MAX 80 
const int PORT = 54551;
#define SA struct sockaddr 
void openChat(int sockfd, char *name) 
{ 
    char buff[MAX], serverName[MAX]; 
    int n;  
    
    for (;;) { 
        bzero(buff, sizeof(buff)); 
        printf("%s : ", name); 
        n = 0; 
        while ((buff[n++] = getchar()) != '\n') 
            ; 
        write(sockfd, buff, sizeof(buff)); 
        printf("Message sent. Waiting for server\n");
        bzero(buff, sizeof(buff)); 
        read(sockfd, buff, sizeof(buff)); 
        printf("From Server : %s", buff); 
        if ((strncmp(buff, "exit", 4)) == 0) { 
            printf("Client Exit...\n"); 
            break; 
        } 
    } 
} 
  
int main(int arc, char *argv[]) 
{  
  int sockfd, connfd; 

  struct sockaddr_in servaddr, cli; 

  char *name = argv[1];
  
  // socket create and varification 
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
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
  servaddr.sin_port = htons(PORT); 
  
  // Client to server socket connection
  if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) { 
    printf("Could not connect with server...\n"); 
    exit(0); 
  } 
    else
      printf("connected to the server..\n"); 
  
  // open chat
  openChat(sockfd, name); 
  
  // close socket 
  close(sockfd); 
}
