#include "UdpClient.h"


UdpClient::UdpClient(unsigned short port)
{
	UdpClient(port,ECHOMAX);
}

UdpClient::UdpClient(unsigned short port,unsigned int bufforSize)
{
	echoBuffer = new char[bufforSize];	
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

UdpClient::~UdpClient()
{
	delete[] echoBuffer;
}

//int ReceiveLength; /* Size of received message */

char* UdpClient::Receive()
{
	if ((ReceiveLength = recvfrom(sock, echoBuffer, ECHOMAX, 0,(struct sockaddr *) &echoClntAddr, &cliLen)) < 0)
		DieWithError("recvfrom() failed");	

	return echoBuffer;
}

void UdpClient::Send(char* dgram,int bytes)
{
	if (sendto(sock, dgram, bytes, 0, (struct sockaddr *) &echoClntAddr,sizeof(echoClntAddr)) != bytes)
		DieWithError("sendto() sent a different number of bytes than expected");
}


void UdpClient::DieWithError(char *errorMessage)
{
	fprintf(stderr,"%s: %d\n", errorMessage, WSAGetLastError());
	exit(1);
}



