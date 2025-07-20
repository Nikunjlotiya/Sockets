/*The Client code with the following feature :
 > Request the server for connection 
 > The client socket will be created using the USER DEFINED PORT NUMBER
 > Client can send as well as recieve message from server
*/

//The header file for the socket
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

//Files for i/o operation and system variables
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
//For Error handiling
#include <error.h>

//Macros
#define BUFFLEN 1024
#define SERVPORT 5000

int main(int argc , char * argv[])
{
	//Creating a Structure element of socket structure
	struct sockaddr_in ClientAddr;//Structure which stores the Client IP and PORT while creating client 
	struct sockaddr_in ServerAddr;//Structure which stores the server IP and PORT after connection
	
	//Created Sockets descriptor
	int32_t iClientFd = 0;
	int32_t iServerFd = 0;

	//Buffer for Storing data
	char aBuffer[BUFFLEN];

	//Fill the client Structure 
	ClientAddr.sin_family = AF_INET;
	ClientAddr.sin_addr.s_addr = INADDR_ANY;
	ClientAddr.sin_port = htons(atoi(argv[1]));

	iClientFd = socket(AF_INET,SOCK_STREAM,0);

	if(bind(iClientFd,(struct sockaddr *)&ClientAddr,sizeof(ClientAddr))  < 0)
	{
		perror("Socket can't bind to PORT");
		close(iClientFd);
		exit(EXIT_FAILURE);
	}
	
	//Fill the Server Structure with its element i.e. Socket type,ipaddress, port number
        ServerAddr.sin_family = AF_INET;
        ServerAddr.sin_addr.s_addr = inet_addr(argv[2]);
        ServerAddr.sin_port = htons(SERVPORT);
	

	//Connect to server
	if(connect(iClientFd,(struct sockaddr*)&ServerAddr, sizeof(ServerAddr)) < 0 )
	{
		perror("Connection failed\n");
		close(iClientFd);
		exit(EXIT_FAILURE);
	}
	printf("Connected to Server\n");
	for(;;)
	{
		printf("Enter the Message \n");
		fgets(aBuffer,BUFFLEN,stdin);
		send(iClientFd,aBuffer,strlen(aBuffer),0);		
	}


}

