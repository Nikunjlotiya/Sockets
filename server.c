/*This is Server Source Code which will be used to create the server with following features :
 > Multiple Clients Connection Simultaneously.
 > Bidirectional communication.
*/



/*Header Files for the Socket Programming and linux i/o */
//File for sockets api and structures
#include <sys/socket.h>
#include <netinet/in.h>

//Files for i/o operation and system information
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

//Macros

#define SERVPORT  5000
#define BUFFERLEN 1024	
#define CLIENTQ 8 //The number of clients will be in queue while the server is busy

int main(int argc, char * argv[])
{
	//Creating a structure element of socket structure
	struct sockaddr_in ClientAddr;//Structure Which Stores the Client IP and PORT number after accpeting the connection
	struct sockaddr_in ServerAddr;//Structure which store s the Server IP and PORT number

	//Created Sockets descriptors
	int32_t iClientFd = 0;
	int32_t iServerFd = 0;
	int32_t iAgentFd = 0;

	//Buffer for storing data
	char aBuffer[BUFFERLEN];
	
	//Client socket length 
	socklen_t iClientSocLen;
	//Fill the Server Structure with its element i.e. Socket type,ipaddress, port number
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_addr.s_addr = INADDR_ANY;
	ServerAddr.sin_port = htons(SERVPORT);

	//Create the socket
	iServerFd = socket(AF_INET,SOCK_STREAM,0);
	if(iServerFd == -1)
	{
		printf("Server Socket Creation Failed\n");
		exit(0);
	}
	
	//Bining the socket with the ip address and port number
	bind(iServerFd,(struct sockaddr *)&ServerAddr,sizeof(ServerAddr));
	
	//Placin the socket in listening mode
	listen(iServerFd,CLIENTQ);
	printf("\nWaiting for Client......\n");
	for(;;)
	{
		printf("Reached here\n");
		iClientSocLen = sizeof(ClientAddr);

		iAgentFd = accept(iServerFd,(struct sockaddr *)&ClientAddr,&iClientSocLen);
		printf("Connection Successfull");
	}	
}
