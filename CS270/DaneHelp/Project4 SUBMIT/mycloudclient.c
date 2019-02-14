//********************************
// Dane Sears
// CS270-001
// Project 4
// December 1, 2018
// 
// mycloudclient.c
//********************************


#include "csapp.h"


int parseline(char *buf, char **argv);

//Function to parse user input into commands
int parseline(char *buf, char **argv)
{
	char *delim;         /* Points to first space delimiter */
	int argc;            /* Number of args */
    	int bg;              /* Background job? */

    	buf[strlen(buf)-1] = ' ';  /* Replace trailing '\n' with space */
   	while (*buf && (*buf == ' ')) /* Ignore leading spaces */
        	buf++;

    	/* Build the argv list */
    	argc = 0;
    	while ((delim = strchr(buf, ' '))) 	
	{
        	argv[argc++] = buf;
        	*delim = '\0';
        	buf = delim + 1;
        	while (*buf && (*buf == ' ')) /* Ignore spaces */
            	buf++;
    	}
    
	argv[argc] = NULL;

   	if (argc == 0)  /* Ignore blank line */
        	return 1;

    	/* Should the job run in the background? */
    	if ((bg = (*argv[argc-1] == '&')) != 0)
       		argv[--argc] = NULL;

    	return bg;
}




int main(int argc, char **argv) 
{
    	int clientfd;		//Client connection file descriptor
	int bg; 		//for backward compatibility
	int n; 
	int iStatus;
	int seqno = 1;
	int size;
	FILE *fp, *fp2;
    	rio_t rio;
	char filecontent[1000], ch2;
    	char *host, *port, buf[MAXLINE];
	char *my_argv[128]; 	//array for parsed user input
	unsigned int type;

	//Messages sent to server
	struct { 
   		int seqno;  //op
		unsigned int type;
		unsigned int b;
		char file_to_send[40]; 
	} STORE; 

	//Hello message
	struct { 
   		int seqno; 
   		unsigned int type; 
   		unsigned int key; 
	} HELLO; 


	//If user has attempted to start client with invalid arguments
    	if (argc != 4) 
	{
		fprintf(stderr, "usage: %s <host> <port> <key>\n", argv[0]);
		exit(0);
    	}
    	

	//Assign host and port to user inputted arguments
	host = argv[1];
    	port = argv[2];

	//Establish connection with server
	clientfd = Open_clientfd(host, port);

	//Send Hello Message with key
	HELLO.type = 1;
	HELLO.key = atoi(argv[3]);
	Rio_writen(clientfd, &seqno, 4);
	Rio_writen(clientfd, &HELLO.key, 4);
	Rio_writen(clientfd, &HELLO.type, 4);
	seqno++;
	
	//Receive HELLO response status
	Rio_readn(clientfd, &iStatus, 4);

	//Check if key matched
	if(iStatus < 0)
	{
		printf("Connection declined by server.\n");
		exit(0);
	}

	printf("Successfully connected.\n");
	printf("> ");

		
	//Get user input as long as they input
    	while (Fgets(buf, MAXLINE, stdin) != NULL) 
	{
	
	//Parse user input into a command and arguments
	bg = parseline(buf, my_argv); 
	int arrSize;

	//Count number of arguments		
	for(arrSize=0; my_argv[arrSize] != NULL; arrSize++);

	if(arrSize != 0)
	{
		char *command = my_argv[0];

		//user wants to copy
		if((strstr(command, "cp")) && (arrSize==3))
		{	
			char *ret1, *ret2;
			const char ch = ':';

			ret1 = strchr(my_argv[1], ch);
			ret2 = strchr(my_argv[2], ch);
	
		
//	----------------COPY MESSAGE-----------------------------------------
			if((ret1 != NULL) && (ret2 != NULL))
			{
				type = 4;	
				Rio_writen(clientfd, &seqno, 4);
				Rio_writen(clientfd, &type, 4);
				
				//Trim the c: from the argument
				char *filename = my_argv[1];
				filename = filename + 2;

				//Send filename to server and recieve status if exists
				Rio_writen(clientfd, filename, 40);
				Rio_readn(clientfd, &iStatus, 4);

				//File does not exist on server
				if(iStatus < 0)
					printf("File %s does not exist on cloud.\n", filename);
		
				//File exists
				else
				{
					//Trim c: from second argument
					char *filename2 = my_argv[2];
					filename2 = filename2 + 2;
			
					//Send destination filename to server
					Rio_writen(clientfd, filename2, 40);
                       		}
			seqno++;
			}

		
//	----------------STORE MESSAGE-----------------------------------------
			else if((ret1 == NULL) && (ret2 !=NULL))
			{
				//Trim c: from user argument
				char *file = my_argv[2];
				file = file + 2;

				char filename[40];	
				strcpy(filename, file);

				//Attempt to open file
				fp = fopen(my_argv[1], "r"); 
				type = 2;				

				//If file does not exist
				if (fp == NULL) 
					printf("Cannot open %s\n", my_argv[1]); 
				
				//File exists
				else 
				{ 
					//Send sequencey number and type
					Rio_writen(clientfd, &seqno, 4);
					Rio_writen(clientfd, &type, 4);
			
					Rio_writen(clientfd, filename, 40);
					Rio_readn(clientfd, &iStatus, 4);
					
					//File can be copied to server
					if(iStatus < 0)
						printf("File %s cannot be copied to server.\n", file);
				
					//Copy file to server
					else
					{
						//Read in file data to send and send to server
	   					n = fread(filecontent, 1, 1000, fp); 
   						strcpy(STORE.file_to_send, file);
						STORE.b = n;
   						Rio_writen(clientfd, &(STORE.b), 44); 
   						Rio_writen(clientfd, filecontent, n);
   						fclose(fp); 
					}
				}
			seqno++;
			}
		
	
//	----------------RETRIEVE MESSAGE-----------------------------------------
			else if((ret1 != NULL) && (ret2 == NULL))
			{
				type = 3;	

				//Send sequence no and type to server
				Rio_writen(clientfd, &seqno, 4);
				Rio_writen(clientfd, &type, 4);
				
				//Trim c: from argument
				char *filename = my_argv[1];
				filename = filename + 2;

				//Send filename to check if exist on server and receive status
				Rio_writen(clientfd, filename, 40);
				Rio_readn(clientfd, &iStatus, 4);

				//File does not exist on server
				if(iStatus < 0)
					printf("File %s does not exist.\n", filename);
				
				//File exists
				else
				{
					//Send destination file name
					char *destFile = my_argv[2];
					Rio_writen(clientfd, destFile, 40);

					//Retrieve file from server
					Rio_readn(clientfd, &size, 4);
					Rio_readn(clientfd, filename, 40);
					fp = fopen(filename, "w+");
                                	Rio_readn(clientfd, buf, size);
                             		fwrite(buf, 1, size, fp);
                               	 	fclose(fp);
                       		}
	
			seqno++;
			}
			
		
//	----------------CLIENT COPY ONLY-----------------------------------------
			else
			{
				//Attempt to open file
				fp = fopen(my_argv[1], "r");
				
				//File does not exist
				if(fp==NULL)
					printf("Error: %s does not exist.\n", my_argv[1]);
				
				//File exists
				else
				{
					//Attempt to open destination file to copy to
					fp2 = fopen(my_argv[2], "w");
					
					//If file is NOT okay to open
					if(fp2==NULL)
						printf("Error: %s does not exist.\n", my_argv[2]);
					
					//Open File and write to it
					else
					{
						while((ch2 = fgetc(fp)) != EOF)
							fputc(ch2, fp2);
						fclose(fp);
						fclose(fp2);
					}
				}	
			}

		}
		
//	----------------DELETE FILE-----------------------------------------
		else if(strstr(command, "rm"))
		{
			type = 6;	

			//Send sequence no and type to server
			Rio_writen(clientfd, &seqno, 4);
			Rio_writen(clientfd, &type, 4);

			//Gather filename from argument and send to server
			char *filename = my_argv[1];
			Rio_writen(clientfd, filename, 40);
			Rio_readn(clientfd, &iStatus, 4);
		
			//If file does not exist, prompt user
			if(iStatus < 0)
				printf("File %s does not exist.\n", filename);				

		seqno++;
		}
	
//	----------------LIST DIRECTORY-----------------------------------------
		else if(strstr(command, "ls"))
		{
			int i;
			char filename[40];
			
			//Send sequence no and type to server
			type = 5;
			Rio_writen(clientfd, &seqno, 4);
			Rio_writen(clientfd, &type, 4);

			//Read in number of files in directory on server
			Rio_readn(clientfd, &i, 4);
		
			//Print each file in directory
			for(int j=0; j<i; j++)
			{
				Rio_readn(clientfd, filename, 40);
				printf("%s ", filename);
			}
			printf("\n");
		
		seqno++;
		}

	
//	----------------QUIT-------------------------------------------
		else if((strstr(command, "quit")) || (strstr(command, "QUIT")))
		{
    			Close(clientfd);
    			exit(0);
		}

			
//	----------------INVALID COMMAND-------------------------------------------
		else
			printf("INVALID COMMAND\n");
	}
	printf("> ");

	}
    	Close(clientfd);
    	exit(0);
}
