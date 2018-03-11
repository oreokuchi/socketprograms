/*AUTHOR:Nandini S
  Date:15-2-2018
  Roll no:137*/


#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define  BUFLEN                   1024                 /* buffer length */

int main(int argc, char **argv)
{
        int n;
        int sd, port;
        //char buf[BUFLEN];
char name[100],rcvmsg[100],rcvg[100],fname[100];
char buf[100], buf3[100],command[100],cmd[50],next[50];
int s;
FILE *fp1,*fp;
        
       struct sockaddr_in server;
     while(1)
	{ 
       port=atoi(argv[1]);

        /* create a stream socket */
        if(( sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
                fprintf(stderr, "can't create a socket\n");
                exit(1);
        }

       // bzero((char *)&server, sizeof(struct sockaddr_in));
        server.sin_family = AF_INET;
        server.sin_port = port;
        server.sin_addr.s_addr = inet_addr("127.0.0.1");
	
        /* connecting to the server */
        if(connect(sd, (struct sockaddr *)&server, sizeof(server)) == -1)
        {
                fprintf(stderr, "can't connect\n");
                exit(1);
        }
       /* listen(sd,1);    
        printf("ABC: "); 
	 
        gets(buf); 
	if(strcmp(buf,"exit")==0)break;               /* get user's text */
              /* send it out 
        //printf("Echoed Messege:\n**************\n");
       
        n = read(sd, buf, sizeof(buf));
        //printf("%s\n",buf); 


                n = read(sd, buf, sizeof(buf));
		printf("XYZ: %s\n",buf); 
                write(sd, buf,n);


      }*/
printf("connected\n");
printf("Enter the existing file name\t");
scanf("%s",name);
printf("Enter the new file name\t");
scanf("%s",fname);
fp1=fopen(name,"r");
fp=fopen(fname,"w");
send(sd,name,sizeof(name),0);
while(1)
{
s=recv(sd,rcvg,100,0);
rcvg[s]='\0';
printf("%s",rcvg);
if(strcmp(rcvg,"error")==0)
printf("File is not available\n");
if(strcmp(rcvg,"completed")==0)
{
printf("File is transferred........\n");
fclose(fp);
fclose(fp1);

break;
}
else
fprintf(fp,"%s",rcvg);
//fclose(fp);
}
int test=0;
printf("\nEnter the ftp command to execute : ");       
		test=scanf("%s",cmd);
if(test==1){
strcpy(buf,cmd);
		send(sd, buf, 100, 0);
                recv(sd, buf, 100, 0);
		if(!strcmp(buf,"no"))
		{
			printf("\nEnter the Valid Command !\n");
			//continue;
		}
		if(!strcmp(buf,"nopar"))
		{
			printf("\nNo parent directory in server !\n");
			//continue;
		}
		printf("\n******************************************************\n\nThe recieved List of files in parent directoy are : \n\n");
		while(strcmp(buf,"over")){
			printf("%s\n",buf);
			recv(sd, buf, 100, 0);
			
		}
}
		


close(sd);
return(0);

}
       close(sd);
       return(0); 
}

