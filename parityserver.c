#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>


#define BUFLEN                 1024        /* buffer length */

int main(int argc, char **argv)
{
        int n;
	int yes=1;
        int sd, new_sd, client_len, port;
        struct sockaddr_in server, client;
        char  buf[BUFLEN];

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

        while(1)
        {
                client_len = sizeof(client);

                if((new_sd = accept(sd, (struct sockaddr *) &client, &client_len)) == -1)
                {
                        fprintf(stderr, "can't accept client \n");
                        exit(1);
                }

                n = read(new_sd, buf, sizeof(buf));
		printf("The message  received by client : %s\n",buf);
                write(new_sd, buf,n);
		int c,cnt=0;		
		for(c=0;buf[c]!='\0';c++)
		{
			cnt=cnt+1;
			//data[c]=atoi(buf[c]);
			//printf("\ndata %d = %d ",c,data[c]);
		}
		int bdata[10];
		int p1[10],i,dec[10];
		printf("\nRecieved message\n");	
		for(i=0; i<cnt; i++){
		if(buf[i]=='a'||buf[i]=='A')
		{
			dec[i]=10;		
		}
		
		else if(buf[i]=='b'||buf[i]=='B')
		{
			dec[i]=11;		
		}
		else if(buf[i]=='c'||buf[i]=='C')
		{
			dec[i]=12;		
		}
		else if(buf[i]=='d'||buf[i]=='D')
		{
			dec[i]=13;		
		}
		else if(buf[i]=='e'||buf[i]=='E')
		{
			dec[i]=14;		
		}		
		else if(buf[i]=='f'||buf[i]=='F')
		{
			dec[i]=15;		
		}
		else if(buf[i]>='0' && buf[i]<='9')
		{
			dec[i] = dec[i] * 10 + ( buf[i] - '0' );
			//printf("\ndec %d =%d",i,buf[i]);
		}
		else
		{
			printf("Invalid bit");		
			dec[i]=0;	
		}	
		}
			
		for(i=0;i<cnt;i++)
		{
			bdata[i]=dtob(dec[i]);	
		}
		for(i=0;i<cnt;i++)
		{
			printf("\n%04d",bdata[i]);
			p1[i]=parity(bdata[i]);	
			printf("%d",p1[i]);
			printf(" 0");	
		}
		int par=0;
		par=bdata[0]^bdata[1]^bdata[2];
		printf("\n%04d",par);
		int p2=p1[0]^p1[2]^p1[1];
		printf("%d",p2);
		printf("\t0");
		int p3=0;
		p3=par^bdata[0]^bdata[1]^bdata[2];
		printf("\n\n%05d",p3);
		int p4=parity(p3);
		printf("\t0");
		if(p4==0)
		{
			printf("\nNO ERROR");		
		}
		else 
		{
			printf("\nERROR DETECTED");		
		}
		//printf("\nrow parity =%d",p1[0]);	
		//printf("\t0");		
		printf("\n");       
 		close(new_sd);
        }

        close(sd);
        return(0);
}


int dtob(int n)
{
    int remainder; 
    int binary = 0, i = 1;
  
    while(n != 0) {
        remainder = n%2;
        n = n/2;
        binary= binary + (remainder*i);
        i = i*10;
    }
    return binary;
}

int parity(int n)
{
	int o=0,z=0;
	int d=1,i,nCount=0;
	for(i=0;i<=(sizeof(n));i++)
        {
     	   if(1&n)
	   {
		//printf("\t%d",1&n);
           	nCount++;
     	    }
	    n = n/2;
    	}
	if(nCount%2==0)
	{
		return 0;
	}
	else
	{
		return 1;	
	}
}
