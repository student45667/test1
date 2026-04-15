 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5025
#define IP   "192.168.0.3"
// #define IP   "10.14.93.23"
int main()
{


int sock, status;
struct sockaddr_in addr;
socklen_t addr_size;
char buffer[1024];
char result_y_char [10];
char result_x_char [10];
double result_y    ;
double result_x    ;
char *ptr;
int n;

printf ("\n================================================================ \n");

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

//============== CHECK IT VNA PRESENT ======================== 
bzero(buffer, 1024);strcpy(buffer, "*IDN?\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer);
bzero(buffer, 1024);recv(sock, buffer, sizeof(buffer), 0);printf ("	%s\n" , buffer);

//============== SETUP VNA ======================== 


bzero(buffer, 1024);strcpy(buffer, "SYST:FPRESET\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); //reset vna
bzero(buffer, 1024);strcpy(buffer, "DISPlay:WINDow1:STATE ON\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); 
bzero(buffer, 1024);strcpy(buffer, "CALCulate:PARameter:DEFine:EXT 'MyMeas',S12\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); 
bzero(buffer, 1024);strcpy(buffer, "DISPlay:WINDow1:TRACe1:FEED 'MyMeas'\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); 

bzero(buffer, 1024);strcpy(buffer, "SENS:FREQ:START 1e9\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); 
bzero(buffer, 1024);strcpy(buffer, "SENS:FREQ:STOP  7e9\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); 
bzero(buffer, 1024);strcpy(buffer, "SENS:BWIDth 300000\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); 
bzero(buffer, 1024);strcpy(buffer, "SENS:SWEep:TYPE LIN\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer);
bzero(buffer, 1024);strcpy(buffer, "SENS:SWEep:POINts 50\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); 
bzero(buffer, 1024);strcpy(buffer, "SOUR:POW 0\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); 



//============== select measurenent and place markers. read them after =============================

printf ("=====================================================\n"); 

bzero(buffer, 1024);strcpy(buffer, "CALC:PAR:SEL 'MyMeas'\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); // select active trace/measuremnt

bzero(buffer, 1024);strcpy(buffer, "CALC:MARK1 ON\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer);  // set marker 1 at 4G
bzero(buffer, 1024);strcpy(buffer, "CALC:MARK1:X 4e9\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); 

bzero(buffer, 1024);strcpy(buffer, "CALC:MARK2 ON\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer);   // set marker 1 at 5G
bzero(buffer, 1024);strcpy(buffer, "CALC:MARK2:X 5e9\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); 

bzero(buffer, 1024);strcpy(buffer, "CALC:MARK3 ON\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer);   // set marker 1 at 6G
bzero(buffer, 1024);strcpy(buffer, "CALC:MARK3:X 6e9\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); 







int i_loop = 0;
for ( i_loop =0 ; i_loop < 100 ; i_loop++)
{


	printf ("=====================================================\n"); 

	bzero(buffer, 1024);strcpy(buffer, "CALC:MARK1:Y?\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); // read marker 1 result
	bzero(buffer, 1024);recv(sock, buffer, sizeof(buffer), 0);printf ("	%s\n" , buffer);

	bzero(buffer, 1024);strcpy(buffer, "CALC:MARK2:Y?\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); // read marker 2 result
	bzero(buffer, 1024);recv(sock, buffer, sizeof(buffer), 0);printf ("	%s\n" , buffer);

	bzero(buffer, 1024);strcpy(buffer, "CALC:MARK3:Y?\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); // read marker 3 result
	bzero(buffer, 1024);recv(sock, buffer, sizeof(buffer), 0);printf ("	%s\n" , buffer);

}

// ============================ closing the connected socket =========================================

close (sock);
printf("client disconnected\n");
return 0;
}



//bzero(buffer, 1024);strcpy(buffer, "SOUR:POW:MODE ON\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); 
//bzero(buffer, 1024);strcpy(buffer, "CALCulate1:FORMat MLOG\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); 
//bzero(buffer, 1024);strcpy(buffer, "Display:WINDow1:TRACe1:STATe ON\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); 
//bzero(buffer, 1024);strcpy(buffer, "DISPlay:WINDow1:TITLe:STATe ON\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); 
//bzero(buffer, 1024);strcpy(buffer, "DISPlay:ANNotation:FREQuency ON\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); 
//bzero(buffer, 1024);strcpy(buffer, "Display:WINDow1:TRACe1:Y:Scale:AUTO\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); 




//bzero(buffer, 1024);strcpy(buffer, "DISPlay:WINDow1:TRACe1:Y:SCALe:PDIVision?\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer);
//bzero(buffer, 1024);recv(sock, buffer, sizeof(buffer), 0);printf ("	%s\n" , buffer);

//bzero(buffer, 1024);strcpy(buffer, "DISPlay:WINDow1:TRACe1:Y:SCALe:RLEVel?\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer);
//bzero(buffer, 1024);recv(sock, buffer, sizeof(buffer), 0);printf ("	%s\n" , buffer);

//bzero(buffer, 1024);strcpy(buffer, "DISPlay:WINDow1:TRACe1:Y:SCALe:RPOSition?\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer);
//bzero(buffer, 1024);recv(sock, buffer, sizeof(buffer), 0);printf ("	%s\n" , buffer);

//bzero(buffer, 1024);strcpy(buffer, "SYST:ACT:CHAN?\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer);
//bzero(buffer, 1024);recv(sock, buffer, sizeof(buffer), 0);printf ("	%s\n" , buffer);

//bzero(buffer, 1024);strcpy(buffer, "SYST:ACT:MEAS?\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer);
//bzero(buffer, 1024);recv(sock, buffer, sizeof(buffer), 0);printf ("	%s\n" , buffer);
