#include <stdio.h> /* for printf(), fprintf() */
#include <winsock.h> /* for socket(),... */
#include <stdlib.h> /* for exit() */

#define ECHOMAX 255 /* Longest string to echo */

class  UdpClient
{
public:
	UdpClient(unsigned short port);
	~ UdpClient();

	int ReceiveLength; /* Size of received message */
	
	char* Receive();

	void Send(char* dgram,int bytes);

private:
	int sock; /* Socket */
	struct sockaddr_in echoServAddr; /* Local address */
	struct sockaddr_in echoClntAddr; /* Client address */
	char echoBuffer[ECHOMAX]; /* Buffer for echo string */
	unsigned short echoServPort; /* Server port */
	int cliLen; /* Length of incoming message */
	//int recvMsgSize; 
	WSADATA wsaData; /* Structure for WinSock setup communication */

	void DieWithError(char *errorMessage);
};


