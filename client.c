#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>

void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{

    int mySocket, portno, n;

    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[1000];
	
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

	//assign port num from args 
    portno = atoi(argv[2]);

    while(1){
	//create a socket: STEP 1
    mySocket = socket(AF_INET, SOCK_STREAM, 0);
    if (mySocket < 0) 
        error("ERROR opening socket");
	
	
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
	
	//Specify address for the socket
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
	
	// Check for error within connection 
	// Connect socket to address of server 
    if (connect(mySocket,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
	
        
                printf("Please enter the message: ");
            
            
            bzero(buffer,1000);
            fgets(buffer,1000,stdin);
            //Create write call STEP 
            n = write(mySocket,buffer,strlen(buffer));
            
            
            if (n < 0) 
                error("ERROR writing to socket");
            bzero(buffer,1000);
            n = read(mySocket,buffer,1000);
            if (n < 0) 
                error("ERROR reading from socket");
            
            //Print server response 
            printf("%s\n",buffer);
        
	
    }
	//Close the socket????? 
    
}