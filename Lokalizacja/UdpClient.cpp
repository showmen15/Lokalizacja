#include <stdio.h> /* for printf(), fprintf() */
#include <winsock.h> /* for socket(),... */
#include <stdlib.h> /* for exit() */

#define ECHOMAX 255 /* Longest string to echo */

//class Byte
//{
//public:
//	byte* tab;
//	int Length;
//};



class  UdpClient
{
public:
	UdpClient(unsigned short port)
	{
		echoServPort = port;

		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) /* Load Winsock 2.0 DLL */
		{
			fprintf(stderr, "WSAStartup() failed");
			exit(1);
		}

		/* Construct local address structure */
		memset(&echoServAddr, 0, sizeof(echoServAddr)); /* Zero out structure */
		echoServAddr.sin_family = AF_INET; /* Internet address family */
		echoServAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
		echoServAddr.sin_port = htons(echoServPort); /* Local port */

		/* Bind to the local address */
		if (bind(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
			DieWithError("bind() failed");

	}
	~ UdpClient()
	{

	}

	int ReceiveLength; /* Size of received message */
	
	char* Receive()
	{
		if ((ReceiveLength = recvfrom(sock, echoBuffer, ECHOMAX, 0,(struct sockaddr *) &echoClntAddr, &cliLen)) < 0)
			DieWithError("recvfrom() failed");		
	}

	void Send(char* dgram,int bytes)
	{
		if (sendto(sock, dgram, bytes, 0, (struct sockaddr *) &echoClntAddr,sizeof(echoClntAddr)) != bytes)
			DieWithError("sendto() sent a different number of bytes than expected");
	}

private:
	int sock; /* Socket */
	struct sockaddr_in echoServAddr; /* Local address */
	struct sockaddr_in echoClntAddr; /* Client address */
	char echoBuffer[ECHOMAX]; /* Buffer for echo string */
	unsigned short echoServPort; /* Server port */
	int cliLen; /* Length of incoming message */
	//int recvMsgSize; 
	WSADATA wsaData; /* Structure for WinSock setup communication */

	void DieWithError(char *errorMessage)
	{
		fprintf(stderr,"%s: %d\n", errorMessage, WSAGetLastError());
		exit(1);
	}
};


