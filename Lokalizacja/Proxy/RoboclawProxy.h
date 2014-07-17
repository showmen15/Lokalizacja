#include "drivermsg.pb.h"
#include "roboclaw.pb.h"

class RoboclawProxy 
{
private:

	static const int wheelTrack = 280; //rozstaw pomiedzy kolami w [mm]

	UdpClient* udp;
	
	int frontLeftSpeed;
	int frontRightSpeed;
	int rearLeftSpeed;
	int rearRightSpeed;

	char* requestScan;
	int requestScanLength;

	amber::DriverMsg *message;
	amber::roboclaw_proto::MotorsSpeed* motorsSpeedRequest(char* packetBytes);
	
public:

	RoboclawProxy(UdpClient* client_udp);
	~RoboclawProxy();
	
	int FrontLeftSpeed();
	int FrontRightSpeed();
	int RearLeftSpeed();
	int RearRightSpeed();
	
    int GetSpeed();

    double GetAngle(double time);
};
