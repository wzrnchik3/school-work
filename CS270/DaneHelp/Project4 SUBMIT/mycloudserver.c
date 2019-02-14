//********************************
// Dane Sears
// CS270-001
// Project 4
// December 1, 2018
// 
// mycloudserveri.c
//********************************

#include "csapp.h"

void echo(int connfd);

int main(int argc, char **argv) 
{
    	int listenfd, connfd;
	int iStatus;
	unsigned int servKey, clientKey, requestType;
	socklen_t clientlen;
    	struct sockaddr_storage clientaddr;  /* Enough space for any address */  //line:netp:echoserveri:sockaddrstorage
    	char client_hostname[MAXLINE], client_port[MAXLINE];
	char *strRequest, *strStatus;

	//Hello Response
	struct {
		int seqno;
		unsigned int status;
	} HELLO_response;


	//if user has attempted to run server with invalid arguments
    	if (argc != 3) 
	{
		fprintf(stderr, "usage: %s <port> <key>\n", argv[0]);
		exit(0);
    	}

	
	//Gather server key
	servKey = atoi(argv[2]);

	//Establish connection with client
    	listenfd = Open_listenfd(argv[1]);

	
	while(1){

		//Connect to client
		clientlen = sizeof(struct sockaddr_storage); 
		connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
       		Getnameinfo((SA *) &clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0);
		Rio_readn(connfd, &HELLO_response.seqno, 4);
		printf("\nSeq Number = %d\n", HELLO_response.seqno);

		//Read in secret key from client
		Rio_readn(connfd, &clientKey, 4);
		printf("Secret Key = %d\n", clientKey);

		//Read in hello message
		Rio_readn(connfd, &requestType, 4);
		strRequest = "HELLO";
		printf("Request Type = %s\n", strRequest);


		//Return fail if user entered wrong key
		if(clientKey!=servKey)
		{
			iStatus = -1;
			strStatus = "Authentication Error.";
			printf("Operation Status = %s\n", strStatus);
			Rio_writen(connfd, &iStatus, 4);
		}
		
		//User entered correct key	
		else
		{
			iStatus = 1;
			strStatus = "Authentication Successful.";
			printf("Operation Status = %s\n", strStatus);
			Rio_writen(connfd, &iStatus, 4);
			printf("Connected to (%s, %s)\n", client_hostname, client_port);
			mycloud(connfd);
		}
		Close(connfd);
	}
      	exit(0);
}
