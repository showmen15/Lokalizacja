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
	
double RoboclawProxy::GetSpeed()
{
	char *packetBytes;
	double speed;
	amber::roboclaw_proto::MotorsSpeed* currentSpeed;

	udp->Send(requestScan,requestScanLength);
	packetBytes = udp->Receive();
	
	currentSpeed = motorsSpeedRequest(packetBytes);
	
	frontLeftSpeed =   currentSpeed->frontleftspeed(); 
	frontRightSpeed =  currentSpeed->frontrightspeed();
	rearLeftSpeed = currentSpeed->rearleftspeed();
	rearRightSpeed = currentSpeed->rearrightspeed();
		
	speed = ((frontLeftSpeed + frontRightSpeed + rearLeftSpeed + rearRightSpeed) / 4);
	speed = (speed / 1000);

	return speed;
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
	double tmpRight = (double) (frontRightSpeed +  rearRightSpeed);
	double tmpLeftS = (double)(frontLeftSpeed + rearLeftSpeed);

return ((((tmpRight) / 2) - ((tmpLeftS) / 2)) * time) / wheelTrack;
}
