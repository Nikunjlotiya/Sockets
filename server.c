/*This is Server Source Code which will be used to create the server with following features :
  > Multiple Clients Connection Simultaneously.
  > Bidirectional communication.
  */



/*Header Files for the Socket Programming and linux i/o */
//File for sockets api and structures
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <pthread.h>
//Files for i/o operation and system information
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

//Macros

#define SERVPORT  5000
#define BUFFLEN 1024	
#define CLIENTQ 4 //The number of clients will be in queue while the server is busy

typedef struct thread_arg
{
	struct sockaddr_in ClientAddr;
	int32_t iAgentFd;

}thread_arg_t;
void * agentThread(void * arg)
{
	char aBuffer[BUFFLEN];
	int8_t iRecievedByte =0 ;

	thread_arg_t argu = *((thread_arg_t *)arg);

	printf("Client connected: %s:%d\n",inet_ntoa(argu.ClientAddr.sin_addr),ntohs(argu.ClientAddr.sin_port));
	//printf("Client connected: \n");

	while( (iRecievedByte = recv(argu.iAgentFd,aBuffer,BUFFLEN - 1,0)) > 0)
	{
		aBuffer[strlen(aBuffer) - 1] = '\0';
		printf("Recieved Message is %s\n",aBuffer);
		strcpy(aBuffer,"Message Recived\n");
		send(argu.iAgentFd,aBuffer,strlen(aBuffer),0);
		memset(aBuffer,0,BUFFLEN);
	}
	if(iRecievedByte < 1)
	{
		printf("Client disconnected: %s:%d\n",inet_ntoa(argu.ClientAddr.sin_addr),ntohs(argu.ClientAddr.sin_port));
		//printf("Client disconnected\n");
		pthread_exit(NULL);
	}


}
int main(int argc, char * argv[])
{
	//Thread PID and argument element
	pthread_t tAgentThread;
	thread_arg_t arg;

	//Creating a structure element of socket structure
	struct sockaddr_in ClientAddr;//Structure Which Stores the Client IP and PORT number after accpeting the connection
	struct sockaddr_in ServerAddr;//Structure which store s the Server IP and PORT number

	//Created Sockets descriptors
	int32_t iServerFd = 0;
	int32_t iAgentFd = 0;
	int opt = 1;
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

	if (setsockopt(iServerFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
	{
		perror("Setsockopt failed");
		close(iServerFd);
		exit(EXIT_FAILURE);
	}
	//Bining the socket with the ip address and port number
	bind(iServerFd,(struct sockaddr *)&ServerAddr,sizeof(ServerAddr));

	//Placing the socket in listening mode
	listen(iServerFd,CLIENTQ);
	printf("Waiting for Client......\n");
	for(;;)
	{
		iClientSocLen = sizeof(ClientAddr);
		arg.iAgentFd = accept(iServerFd,(struct sockaddr *)&(arg.ClientAddr),&iClientSocLen);
		if(arg.iAgentFd > 0)
		{
			pthread_create(&tAgentThread,NULL,agentThread,&(arg));
		}
	}
}


