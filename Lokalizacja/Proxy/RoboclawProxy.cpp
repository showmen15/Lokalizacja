#include "UdpClientLinux.h"
#include "RoboclawProxy.h"

RoboclawProxy::RoboclawProxy(UdpClient *client_udp)
{
	udp = client_udp;

	synNum = 100;

	amber::DriverHdr hdr = buildHeader();
	message = buildMsg(synNum);

	buildSendMessage(hdr,message);
}

amber::DriverHdr  RoboclawProxy::buildHeader()
{
	amber::DriverHdr driverHdrBuilder;
	driverHdrBuilder.set_devicetype(DEVICE_TYPE);
	driverHdrBuilder.set_deviceid(DEVICE_ID);

	return driverHdrBuilder;
}

amber::DriverMsg* RoboclawProxy::buildMsg(int synNum)
{
		amber::DriverMsg* message = new amber::DriverMsg();
		message->set_type(amber::DriverMsg::DATA);

		message->SetExtension(amber::roboclaw_proto::currentSpeedRequest,true);
		message->set_synnum(synNum);

	return message;
}

void RoboclawProxy::buildSendMessage(amber::DriverHdr header, amber::DriverMsg* message)
{
	int headerLen = header.ByteSize();
	int messageLen = message->ByteSize();
	requestScanLength =  2 + headerLen + 2 + messageLen;

	char* output = new char[requestScanLength];

	output[0] = ((headerLen >> 8) & 0xff);
	output[1] = (headerLen & 0xff);

	header.SerializePartialToArray(&output[2],headerLen);

	output[2 + headerLen] = ((messageLen >> 8) & 0xff);
	output[2 + headerLen + 1] = (messageLen & 0xff);

	message->SerializePartialToArray(&output[2 + headerLen + 2],messageLen);

	requestScan = output;

	//char tempTab[] = { 0, 4, 8, 2, 16, 0, 0, 7, 16, 1, 24, 100, 168, 1, 1 };
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
