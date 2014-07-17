#include "UdpClientLinux.h"
#include "RoboclawProxy.h"

RoboclawProxy::RoboclawProxy(UdpClient *client_udp)
{
	udp = client_udp;

	requestScanLength = 15;
	requestScan = new char[requestScanLength];
	char tempTab[] = { 0, 4, 8, 2, 16, 0, 0, 7, 16, 1, 24, 100, 168, 1, 1 };	
	for(int i = 0; i < 	requestScanLength; i++)
		requestScan[i] = tempTab[i];

	message = new amber::DriverMsg();
}

RoboclawProxy::~RoboclawProxy()
{
	delete [] requestScan;
	delete message;
}

int RoboclawProxy::FrontLeftSpeed()
{
	return frontLeftSpeed;
}

int RoboclawProxy::FrontRightSpeed()
{
	return frontRightSpeed;
}

int RoboclawProxy::RearLeftSpeed()
{
	return rearLeftSpeed;
}

int RoboclawProxy::RearRightSpeed()
{
	return rearRightSpeed;
}
	
int RoboclawProxy::GetSpeed()
{
	char *packetBytes;
	amber::roboclaw_proto::MotorsSpeed* currentSpeed;

	udp->Send(requestScan,requestScanLength);
	packetBytes = udp->Receive();
	
	currentSpeed = motorsSpeedRequest(packetBytes);
	
	frontLeftSpeed =   currentSpeed->frontleftspeed(); 
	frontRightSpeed =  currentSpeed->frontrightspeed();
	rearLeftSpeed = currentSpeed->rearleftspeed();
	rearRightSpeed = currentSpeed->rearrightspeed();
		
	return (frontLeftSpeed + frontRightSpeed + rearLeftSpeed + rearRightSpeed) / 4;
}

amber::roboclaw_proto::MotorsSpeed* RoboclawProxy::motorsSpeedRequest(char* packetBytes)
{
	int headerLen = (packetBytes[0] << 8) + (packetBytes[1] & 0xff);
	int messageLen = (packetBytes[2 + headerLen] << 8) + (packetBytes[2 + headerLen + 1] & 0xff);
	const char* shiftPacketBytes = &(packetBytes[2 + headerLen + 2]);

	message->ParseFromArray(shiftPacketBytes,messageLen);

	return message->MutableExtension(amber::roboclaw_proto::currentSpeed);
}

double RoboclawProxy::GetAngle(double time)
{
return ((((frontRightSpeed + rearRightSpeed) / 2) - ((frontLeftSpeed + rearLeftSpeed) / 2)) * time) / wheelTrack;
}
