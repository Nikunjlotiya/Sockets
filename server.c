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

//Macros
#define SERVPORT
#define BUFFERLEN 1024	
#define CLIENTQ 8 //The number of clients will be in queue while the server is busy

int main(int argc, char * argv[])
{
	//Creating a structure element of socket structure
	struct sockaddr_in ClientAddr;//Structure Which Stores the Client IP and PORT number after accpeting the connection
	struct sockaddr_in ServeAddr;//Structure which store s the Server IP and PORT number

	//Created Sockets descriptors
	int32_t iClientFd = 0;
	int32_t iServerFd = 0;
	int32_t iAgentFd = 0;

	//Buffer for storing data
	char aBuffer[BUFFERLEN];
	
	//Client socket length 
	socketlen_t iClientSocLen;
	//Fill the Server Structure with its element i.e. Socket type,ipaddress, port number
	ServAddr.sin_family = AF_INET;
	ServAddr.sin_addr.s_addr = INADDR_ANY;
	ServAddr.sin_port = htons(SERVPORT);

	//Create the socket
	iServerFd = socket(AF_INET,SOCK_STREAM,0);
	if(iServerFd == -1)
	{
		printf("Server Socket Creation Failed\n");
		exit();
	}
	
	//Bining the socket with the ip address and port number
	bind(iServerFd,(struct sockaddr *)&ServAddr,sizeof(ServAddr));
	
	//Placin the socket in listening mode
	listen(iServerFd,CLIENTQ);
	printf("\nWaiting for Client......\n");
	for(;;)
	{
		iClientSocLen = sizeof(ClientAddr);
		iAgentFd = accept(iServeFd,(struct Sockaddr *)&ClientAddr,&iClientSocLen);

}
