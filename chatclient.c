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
        char buf[BUFLEN];
        
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
        server.sin_addr.s_addr = inet_addr("10.2.0.241");
	
        /* connecting to the server */
        if(connect(sd, (struct sockaddr *)&server, sizeof(server)) == -1)
        {
                fprintf(stderr, "can't connect\n");
                exit(1);
        }
        listen(sd,1);    
        printf("ABC: "); 
	 
        gets(buf); 
	if(strcmp(buf,"exit")==0)break;               /* get user's text */
        write(sd, buf, BUFLEN);        /* send it out */
        //printf("Echoed Messege:\n**************\n");
       
        n = read(sd, buf, sizeof(buf));
        //printf("%s\n",buf); 


                n = read(sd, buf, sizeof(buf));
		printf("XYZ: %s\n",buf); 
                write(sd, buf,n);


      }
       close(sd);
       return(0); 
}

