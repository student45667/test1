 
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
// configure stimulus
bzero(buffer, 1024);strcpy(buffer, "SENS:FREQ:STAR 1000000000\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); //start freq
bzero(buffer, 1024);strcpy(buffer, "SENS:FREQ:STOP 8000000000\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); //stop freq
bzero(buffer, 1024);strcpy(buffer, "SENS:BWID 500000\n")         ;send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); //set IFBW 500k
bzero(buffer, 1024);strcpy(buffer, "SENS:SWE:TYPE LIN\n")        ;send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); //linear sweep
bzero(buffer, 1024);strcpy(buffer, "SENS:SWE:POIN 100\n")        ;send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); //no of points 100
bzero(buffer, 1024);strcpy(buffer, "SOUR:POW 0\n")               ;send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); //power output, change 0 to -3 for -3dbm output power
// confugure trace
bzero(buffer, 1024);strcpy(buffer, "CALC:PAR:COUN 1\n")          ;send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); //set only one trace
bzero(buffer, 1024);strcpy(buffer, "CALC:PAR1:DEF S21\n")        ;send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); //select trace measurement as S21
bzero(buffer, 1024);strcpy(buffer, "CALC:PAR1:SEL\n")            ;send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); //select trace measurement as S21
bzero(buffer, 1024);strcpy(buffer, "CALC:FORM MLOG\n")           ;send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); //select trace format as Log mag
// Configure Markers
bzero(buffer, 1024);strcpy(buffer, "CALC:MARK3:ACT\n")           ;send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); //activate 3 markers
bzero(buffer, 1024);strcpy(buffer, "CALC:MARK1:X 2000000000\n");send(sock, buffer, strlen(buffer),0);printf   ("%s" , buffer); //marker1 on XGhz
bzero(buffer, 1024);strcpy(buffer, "CALC:MARK2:X 5000000000\n");send(sock, buffer, strlen(buffer),0);printf   ("%s" , buffer); //marker2 on XGhz
bzero(buffer, 1024);strcpy(buffer, "CALC:MARK3:X 7000000000\n");send(sock, buffer, strlen(buffer),0);printf   ("%s" , buffer); //marker3 on XGhz
// Configure Trigger before measurement loop
//bzero(buffer, 1024);strcpy(buffer, "TRIG:SOUR BUS\n");send(sock, buffer, strlen(buffer),0);printf ("Tester sent: %s" , buffer); //select BUS trigger (which means your code triggers the VNA)
bzero(buffer, 1024);strcpy(buffer, "TRIG:SOUR INT\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer); //select trig internal.

//====================================================================================================

//bzero(buffer, 1024);strcpy(buffer, "TRIG:SING\n");send(sock, buffer, strlen(buffer),0);printf ("Tester sent: %s" , buffer); // trigger
//bzero(buffer, 1024);strcpy(buffer, "*OPC?\n");send(sock, buffer, strlen(buffer),0);printf ("Tester sent: %s" , buffer); //wait for trigger

printf ("\n================================================================ \n");


//===============================================================
bzero(buffer, 1024);strcpy(buffer, "CALC:MARK1:Y?\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer);
bzero(buffer, 1024);recv(sock, buffer, sizeof(buffer), 0);
snprintf(result_y_char,sizeof(result_y_char), "%.9s", buffer);
result_y = strtod(result_y_char , &ptr);
printf ("	DB %f " , result_y);

bzero(buffer, 1024);strcpy(buffer, "CALC:MARK1:X?\n");send(sock, buffer, strlen(buffer),0);
bzero(buffer, 1024);recv(sock, buffer, sizeof(buffer), 0); 
snprintf(result_x_char,sizeof(result_x_char), "%.9s", buffer);
result_x = strtod(result_x_char , &ptr);
printf ("Ghz %f\n" , result_x);



//===============================================================
bzero(buffer, 1024);strcpy(buffer, "CALC:MARK2:Y?\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer);
bzero(buffer, 1024);recv(sock, buffer, sizeof(buffer), 0);
snprintf(result_y_char,sizeof(result_y_char), "%.9s", buffer);
result_y = strtod(result_y_char , &ptr);
printf ("	DB %f " , result_y);

bzero(buffer, 1024);strcpy(buffer, "CALC:MARK2:X?\n");send(sock, buffer, strlen(buffer),0);
bzero(buffer, 1024);recv(sock, buffer, sizeof(buffer), 0); 
snprintf(result_x_char,sizeof(result_x_char), "%.9s", buffer);
result_x = strtod(result_x_char , &ptr);
printf ("Ghz %f\n" , result_x);




//===============================================================
bzero(buffer, 1024);strcpy(buffer, "CALC:MARK3:Y?\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer);
bzero(buffer, 1024);recv(sock, buffer, sizeof(buffer), 0);
snprintf(result_y_char,sizeof(result_y_char), "%.9s", buffer);
result_y = strtod(result_y_char , &ptr);
printf ("	DB %f " , result_y);

bzero(buffer, 1024);strcpy(buffer, "CALC:MARK3:X?\n");send(sock, buffer, strlen(buffer),0);
bzero(buffer, 1024);recv(sock, buffer, sizeof(buffer), 0); 
snprintf(result_x_char,sizeof(result_x_char), "%.9s", buffer);
result_x = strtod(result_x_char , &ptr);
printf ("Ghz %f\n " , result_x);


printf ("\n================================================================ \n");




bzero(buffer, 1024);strcpy(buffer, "CALC:DATA:FDAT?\n");send(sock, buffer, strlen(buffer),0);printf ("%s" , buffer);
bzero(buffer, 1024);recv(sock, buffer, sizeof(buffer), 0); printf ("%s \n" , buffer);






// closing the connected socket
close (sock);
printf("client disconnected\n");
return 0;
}


/*
//===========================================================================

# Configure stimulus
 SENS:FREQ:STAR 1000000000\n # start freq
 SENS:FREQ:STOP 9000000000\n # stop freq
 SENS:SWE:TYPE LIN\n # sweep type linear
 SENS:BWID 300000\n # IFBW
 SENS:SWE:POIN 100\n # number of points
 SOUR:POW 0\n # power output, change 0 to -3 for -3dbm output power
# Configure trace
      CALC:PAR:COUN 1\n # set only one trace
      CALC:PAR1:DEF S21\n # select trace measurement as S21
      CALC:PAR1:SEL\n # select trace 1
      CALC:FORM MLOG\n # select trace format as Log mag
# Configure Markers
      CALC:MARK3:ACT\n # activate 3 markers
      CALC:MARK1:X 2000000000\n
      CALC:MARK2:X 5000000000\n
      CALC:MARK3:X 7000000000\n # set markers on specific frequencies 2G, 5G, 7G
# Configure Trigger before measurement loop
      TRIG:SOUR BUS\n # select BUS trigger (which means your code triggers the VNA)
# Measurement loop
      while true:
           TRIG:SING # trigger measurement once
           query("*OPC?\n") # wait until sweep finishes
           # read marker results and its frequency
           query("CALC:MARK1:X?\n")
           query("CALC:MARK2:X?\n")
           query("CALC:MARK3:X?\n") # read marker frequencies
           query("CALC:MARK1:Y?\n")
           query("CALC:MARK2:Y?\n")
           query("CALC:MARK3:Y?\n") # read marker results
          # read whole array of S21 in db and frequency 
             query("CALC:DATA:FDAT?\n")
# Configure Trigger after measurement loop
      TRIG:SOUR INT\n # change trigger source back to default (Internal trigger)

Please note the marker results and whole array of S21 results may look strange. 
This is because CALC:MARK:Y? always returns 2 values, when the trace format is log mag, 
the second value will be 0 and you just need to ignore that. 
Similar behavior is with the CALC:DATA:FDAT? command, for each frequency point, 
this command always returns 2 values, thus your array will look like this: a,0,b,0,c,0... 
You just need to ignore the 0s. See more details about these two commands here:
https://coppermountaintech.com/help-s4/calcdatafdat.html
https://coppermountaintech.com/help-s4/calcmarky_.html

Also, our online SCPI command finder may be useful to you for future development:
https://coppermountaintech.com/help-s4/search-commands.html


//====================================================================================
*/


