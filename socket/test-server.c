#include <stdio.h>
 #include <sys/socket.h>
 #include <sys/types.h>
 #include <string.h>
 #include <netinet/in.h>
 #include <stdlib.h>
 #include <errno.h>
 #include <unistd.h>
 #include <arpa/inet.h>
 
 #define MAXLINE 1024
 int main(int argc,char **argv)
 {
 int listenfd,connfd;
 struct sockaddr_in sockaddr;
 char buff[MAXLINE];
 int n;
 
 memset(&sockaddr,0,sizeof(sockaddr));
 
 sockaddr.sin_family = AF_INET;
 sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
 sockaddr.sin_port = htons(10004);
 
 listenfd = socket(AF_INET,SOCK_STREAM,0);
 
 bind(listenfd,(struct sockaddr *) &sockaddr,sizeof(sockaddr));
 
 listen(listenfd,1024);

 
 printf("Please wait for the client information\n");
 if((connfd = accept(listenfd,(struct sockaddr*)NULL,NULL))==-1)
 {
 printf("accpet socket error: %s errno :%d\n",strerror(errno),errno);
// continue;
 }
 
//char recvbuf[1024];
//while(n=recv(connfd,buff,MAXLINE,0)) 
for(;;)
{
 n = recv(connfd,buff,MAXLINE,0);
 buff[n] = '\0';
 printf("recv msg from client:%s",buff);

 printf("jason is a good man");

 //close(connfd);
 /*
                memset(recvbuf,0,sizeof(recvbuf));
		int ret = read(connfd,recvbuf,sizeof(recvbuf));
		fputs(recvbuf,stdout);
		write(connfd,recvbuf,ret);
*/
 }
 close(listenfd);
 }
