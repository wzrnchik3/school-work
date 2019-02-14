//********************************
// Dane Sears
// CS270-001
// Project 4
// December 1, 2018
// 
// mycloud.c
//********************************

#include "csapp.h"

		
void mycloud(int connfd) 
{
	size_t n; 
   	char buf[MAXLINE]; 
	char *my_argv[128];
	rio_t rio;
	char filename[40];	
	char destfile[40];
	char filecontent[1000], ch; 
	FILE *sfp, *sfp2; 
	int size; 
	int temp;
	int status;
	int m;
	
	//Store message to recieve
	struct {
                int seqno;  //op
                unsigned int type;
		unsigned int b;
                char file_to_send[40];
        } STORE;


	//Retreive message data
	struct {
                int seqno;  //op
                unsigned int type;
		unsigned int b;
                char file_to_send[40];
        } RETRIEVE;
	

	//Struct to hold sequence type and number
	struct {
		int seqno;
		unsigned int type;
	} typeMessage;


	//Read in sequence number and type of command	
	while((n = Rio_readn(connfd, &typeMessage, 8)) != 0) 
	{
		printf("\nSeq Number = %d\n", typeMessage.seqno);	


//		STORE MESSAGE-----------------------------------
		if(typeMessage.type==2)
		{
			printf("Request type = STORE\n");

			Rio_readn(connfd, filename, 40);

			printf("Filename = %s\n", filename);

			//Attempt to open file for writing
			sfp = fopen(filename, "w+");
	
		 	//if file cannot be opened
			if (sfp == NULL)
			{
				status = -1;
				Rio_writen(connfd, &status, 4);		
        	                printf("Operation Status = FAIL\n");
			}
			//Write file
			else 
			{ 
				status = 1;
				Rio_writen(connfd, &status, 4);
	   			Rio_readn(connfd, &size, 4);
				Rio_readn(connfd, filename, 40);
				Rio_readn(connfd, buf, size); 
	   			fwrite(buf, 1, size, sfp); 
				fclose(sfp);
				printf("Operation Status = SUCCESS\n"); 
			}

		}
		


		
//		RETRIEVE MESSAGE-----------------------------------
		else if(typeMessage.type==3)
		{
			printf("Request type = RETREIVE\n");
		
			//Read in filename
			Rio_readn(connfd, filename, 40);
			printf("Filename = %s\n", filename);
                       
			//Open file on server attempt
			sfp = fopen(filename, "r");

			//If file does not exist
			if(sfp==NULL)
			{
				status = -1;
				Rio_writen(connfd, &status, 4);		
        	                printf("Operation Status = FAIL\n");
			}
			
			//If file exists, send status and file
                        else
                        {
				status = 1;
				Rio_writen(connfd, &status, 4);
                                Rio_readn(connfd, destfile, 40);
				m = fread(filecontent, 1, 1000, sfp);
                                strcpy(RETRIEVE.file_to_send, destfile);
                                RETRIEVE.b = m;
                                Rio_writen(connfd, &(RETRIEVE.b), 44);
                                Rio_writen(connfd, filecontent, m);
                                fclose(sfp);
				printf("Operation Status = SUCCESS\n"); 
                        }

		}

//		COPY MESSAGE-----------------------------------
		else if(typeMessage.type==4)
		{
			printf("Request type = COPY\n");
		
			//Get name of file to copy
			Rio_readn(connfd, filename, 40);
			printf("Filename = %s\n", filename);

			//attempt to open the file to read
			sfp = fopen(filename, "r"); 
			
			//File does not exist
			if (sfp == NULL)
			{
				status = -1;
				Rio_writen(connfd, &status, 4);		
        	                printf("Operation Status = FAIL\n");
			}

			//File exists
			else 
			{
				status = 1;
				Rio_writen(connfd, &status, 4);
                                
				//Read in destination file name
				Rio_readn(connfd, destfile, 40);
				
				//Open destination file and write
				sfp2 = fopen(destfile, "w+");	   		
	   		
				while((ch = fgetc(sfp)) != EOF)
					fputc(ch, sfp2);

				fclose(sfp);
				fclose(sfp2);
				printf("Operation Status = SUCCESS\n"); 
			}
		}


//		LIST DIRECTORY-----------------------------------
		else if(typeMessage.type==5)
		{

			printf("Request type = LIST\n");
			
			int i = 0;
			DIR *d;
			struct dirent *dir;
			char *files;
			d = opendir(".");

			//If directory can be read
			if(d)
			{
				//Count files in directory and send to client
				char *filename;
				while((dir = readdir(d)) != NULL)
					i++;
				Rio_writen(connfd, &i, 4);

				DIR *d;
				struct dirent *dir;
				char *files;
				d = opendir(".");
	
				//Send each filename to client	
				for(int j=0; j < i; j++)
				{
					dir = readdir(d);
					filename = dir->d_name;
					Rio_writen(connfd, filename, 40);
				}	
				
			closedir(d);
			}
			printf("Operation Status = SUCCESS\n"); 
		}


//		DELETE FILE-----------------------------------
		else
		{
			printf("Request type = DELETE\n");
		
			//Read in filename to delete
			Rio_readn(connfd, filename, 40);
			printf("Filename = %s\n", filename);

			//If file does not exist
			if(access(filename, F_OK) == -1)
			{
				status = -1;
				Rio_writen(connfd, &status, 4);
				printf("Operation Status = FAIL\n");
			}

			//File exists
			else
			{
				status = 1;
				Rio_writen(connfd, &status, 4);
				remove(filename);
				printf("Operation Status = SUCCESS\n");
			}
		}
	}
}

