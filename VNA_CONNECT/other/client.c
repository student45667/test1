 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5025
#define IP   "10.14.93.23"
int main()
{


int sock, status;
struct sockaddr_in addr;
socklen_t addr_size;
char buffer[1024];
int n;

sock = socket(AF_INET,SOCK_STREAM,0);
if (sock < 0)
     { printf("socket error \n"); exit (1); }
else {printf("TCP socket created\n");}


memset( &addr,'\0' , sizeof(addr));
addr.sin_family = AF_INET;
addr.sin_port = htons(PORT); 
inet_pton(AF_INET, IP , &addr.sin_addr); 


status = connect(sock, (struct sockaddr*)&addr, sizeof(addr));
if (status< 0) 
        { printf("\nConnection Failed %s port %d\n" ,IP , PORT); return -1;}
   else { printf("Connected to: %s port %d\n" ,IP , PORT);} 

 

bzero(buffer, 1024);
strcpy(buffer, "CALC:MARK1:Y?\n");
send(sock, buffer, strlen(buffer),0);
printf ("Tester sent: %s" , buffer);

bzero(buffer, 1024);
recv(sock, buffer, sizeof(buffer), 0);
printf ("Tester recieved: %s\n" , buffer);



// closing the connected socket
close (sock);
printf("client disconnected\n");
return 0;
}


/*

char* message = "CALC:MARK1:Y?\n";
char buffer[1024] = { 0 };

send(client_fd, message, strlen(message), 0);
	printf("SCPI command sent\n");
	valread = read(client_fd, buffer, 1024);
	printf("%s\n", buffer);
    

*/


