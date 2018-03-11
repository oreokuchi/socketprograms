#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>


#define  BUFLEN                   10                 /* buffer length */

int main(int argc, char **argv)
{
        int n;
        int sd, port;
        char buf[BUFLEN];

       struct sockaddr_in server;

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

        printf("Enter the message to be sent: ");
        scanf("%s",buf);
	int c,cnt=0;
	for(c=0;buf[c]!='\0';c++)
	{
		cnt=cnt+1;
		//data[c]=atoi(buf[c]);
		//printf("\ndata %d = %d ",c,data[c]);
	}
	cnt=cnt;
  	//int len = sizeof(buf);  /* get user's text */
        write(sd, buf, cnt);        /* send it out */
        printf("Echoed Messege:\n**************\n");
        n = read(sd, buf, cnt);
        printf("%s\n",buf);
        int dec[10],i;
	for(i=0;i<10;i++)
	{
		dec[i]=0;	
	}
        int j;
	//printf("\nlen %d",cnt);
	for(i=0; i<cnt; i++){
            
		
		 if(buf[i]>='0' && buf[i]<='9')
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
	/*for(i=0;i<cnt;i++)
	{
		printf(" %d",dec[i]);	
	}*/
	int bdata[10];
	int p1[10];	
	for(i=0;i<cnt;i++)
	{
		bdata[i]=dtob(dec[i]);	
	}
        //int par=0,m,p,sp=0;
        
	for(i=0;i<cnt;i++)
	{
		printf("\n%04d",bdata[i]);
		p1[i]=parity(dec[i]);	
		printf("\t%d",p1[i]);
	        //par=par+bdata[i];
	}
	int par=bdata[0]^bdata[1]^bdata[2];
        
	printf("\n%04d",par);
	int p2=0;
	for(i=0;i<cnt;i++)
	{
		p2=p2^p1[i];
	}
	printf("\t%d",p2);	
	//printf("\nrow parity =%d",p1[0]);	
	printf("\n");       
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
	int d=1,i,nCount;
	for(i=0;i<=(sizeof(n));i++)
        {
     	   if(1&n)
	   {
		//printf("\t%d",1&n);
           	nCount++;
     	    }
	    n >>=1;
    	}
      /* nCount=0;
       while(n)
       {  //printf("\nhi%d\n",n);
          n=n&(n-1);
          nCount++;
          //n>>=1;
          

       }*/
//printf("%d\n",nCount);
	if(nCount%2==0)
	{
		return 0;
	}
	else
	{
		return 1;	
	}
}
