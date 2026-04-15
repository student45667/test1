 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5025
#define IP   "10.14.93.23"

int main()
{


int server_sock ,client_sock;
struct sockaddr_in server_addr , client_addr;
socklen_t addr_size;
char buffer[1024];
int n;

server_sock = socket(AF_INET,SOCK_STREAM,0);
if (server_sock <0)
    {
    printf("socket error \n");
    exit (1);
    }
 else printf("TCP socket created\n");

memset( &server_addr,'\0' , sizeof(server_addr));
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(PORT); 
inet_pton(AF_INET, IP , &server_addr.sin_addr);


n= bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
if (n<0)
	{
        printf("bind error \n");
        exit (1);
        }
 else printf("Bind to: %s port %d\n" ,IP , PORT);

listen(server_sock, 5);
printf("-----------------Listening-----------------\n");

int i = 0;
while(1)
	{
        i++;
        printf ("--------attempt %d --------\n" , i);
	addr_size = sizeof(client_addr);
        client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);
        printf("client_connected\n");

	bzero(buffer, 1024);
        recv(client_sock, buffer, sizeof(buffer), 0);
        printf ("VNA recieved: %s\n" , buffer);

        bzero(buffer, 1024);
	strcpy(buffer, "Freq=10G 100db");
	printf ("VNA sent: %s\n" , buffer);
	send(client_sock, buffer, strlen(buffer),0);

        close (client_sock);
        printf("client disconnected\n");

	}




return 0;
}

