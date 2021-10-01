/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int mySocket, newsockfd, portno, clilen;
     //Change to 1000 to fit max char limit as set by description  
     char buffer[1000];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
	 
	 
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
	 //Create a socket with the socket() sys call 
     mySocket = socket(AF_INET, SOCK_STREAM, 0);
     if (mySocket < 0) 
        error("ERROR opening socket");
	
	//bind the socket 
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(mySocket, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
	//Listen for a connection (throws -1 if fails, shall we include an if statement to check if it fails? )
     listen(mySocket,5);
	 
     clilen = sizeof(cli_addr);




	 //Accept a connection 
     while(newsockfd = accept(mySocket, (struct sockaddr *) &cli_addr, &clilen)){
     if (newsockfd < 0) 
          error("ERROR on accept");
     bzero(buffer,1000);
	 
	 //Send the message
     n = read(newsockfd,buffer,999);
     if (n < 0) error("ERROR reading from socket");
     printf("Here is the message: %s\n",buffer);
	 
	 //Recieve the message 
     n = write(newsockfd,"I got your message",18);
     if (n < 0) error("ERROR writing to socket");
     }
	 

      //Shall we close the socket...? return 0 
     
}
