/*AUTHOR:Nandini S
  Date:15-2-2018
  Roll no:137*/


#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
# include <string.h>
#include <dirent.h>
DIR *d;    					// DIR structure to hold the list of directories 
DIR *d2,*d1;
struct dirent *dir,*dir2,*dir1;

#define BUFLEN                 1024        /* buffer length */

int main(int argc, char **argv)
{
        int n;
	int yes=1;
        int sd, new_sd, client_len, port;
        struct sockaddr_in server, client;
FILE *fp;
        //char  buf[BUFLEN];
char name[100],fileread[100],fname[100],ch,file[100],rcv[100];
char buf[100],buf1[100],buf3[100];

         port = atoi(argv[1]);
     
        /* create a stream socket */
        if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
                fprintf(stderr,"can't create a socket\n");
                exit(1);
        }

        /* Fill the structure fileds with values */

        server.sin_family = AF_INET;
        server.sin_port = port;
        server.sin_addr.s_addr =inet_addr("127.0.0.1");
	
       // Reuse the port and address
	if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
    		perror("setsockopt");
   		 exit(1);
	}

        /* bind an address to the socket */
        if(bind(sd, (struct sockaddr *)&server, sizeof(server)) == -1)
        {
                fprintf(stderr, "can't bind name to socket\n");
                exit(1);
        }

        /* queue up to 5 connect requests */
        listen(sd,5);
	//printf("Aaja aaja\n");

        
                client_len = sizeof(client);

                if((new_sd = accept(sd, (struct sockaddr *) &client, &client_len)) == -1)
                {
                        fprintf(stderr, "can't accept client \n");
                        exit(1);
                }
if(new_sd<0)
{
printf("Cant accept\n");
}
else
printf("Accepted\n");
n=recv(new_sd,rcv,100,0);
rcv[n]='\0';
printf("%s",rcv);

fp=fopen(rcv,"r");
if(fp==NULL)
{
send(new_sd,"error",5,0);

}
else
{

while(fgets(fileread,sizeof(fileread),fp))
{

if(send(new_sd,fileread,sizeof(fileread),0)<0)
{
//printf("hi");
printf("Cant send\n");
}
sleep(1);
}

send(new_sd,"completed",10,0);

}

               /* n = read(new_sd, buf, sizeof(buf));
		printf("ABC: %s\n",buf); 
                write(new_sd, buf,n);
          printf("XYZ: ",sizeof(buf)); 
	 
        gets(buf); 
	if(strcmp(buf,"exit")==0)break;               /* get user's text */
       // write(new_sd, buf, BUFLEN); 
       // listen(new_sd,1);       /* send it out */
       // printf("Echoed Messege:\n**************\n");
       
        //n = read(new_sd, buf, sizeof(buf));
while(1){
     printf("Waiting for command\n");
     recv(new_sd, buf, 100, 0);
      
	if(!strcmp(buf, "cdup"))
	{

	    int flag=1,count1=0,count2=0;
	    d1 = opendir("..");// parent dir
	    d2 = opendir(".");//current dir				 											
	    if (d1)							
	    {								
		while ((dir1 = readdir(d1)) != NULL)			
		{							
		 	count1++;   					
		}							
		closedir(d1);							
	    }								
	    if (d2)							
	    {								
		while ((dir2 = readdir(d2)) != NULL)			
		{							
		 	count2++;   					
		}							
		closedir(d2);						
	    }
	    if(count1==count2){
	  	flag=0;		
	    }


		if(flag==1){

	    d = opendir("..");            
	    if (d)
	    {
		while ((dir = readdir(d)) != NULL)             
		{
		    //printf("%s\n", dir->d_name); 
		    strcpy(buf3,dir->d_name);
		    send(new_sd, buf3, 100, 0);			
		}
		strcpy(buf3,"over");
		send(new_sd, buf3, 100, 0);
		closedir(d);
	    }
	}else if(flag==0){
		strcpy(buf3,"nopar");
		send(new_sd, buf3, 100, 0);

		
	}

}
else
{

}
}
                
 		
        
        close(new_sd);
        close(sd);
        return(0);
}


