#include "UdpClientLinux.h"
#include "HokuyoProxy.h"

HokuyoProxy::HokuyoProxy(UdpClient *client_udp)
{
	udp = client_udp;

	synNum = 100;

	//requestScanLength = 15;
//	requestScan = new char[requestScanLength];//
	char tempTab[] = { 0, 4, 8, 4, 16, 0, 0, 7, 16, 1, 24, 100, 224, 2, 1 };
	//for(int i = 0; i < 	requestScanLength; i++)
	//	requestScan[i] = tempTab[i];

		amber::DriverHdr hdr = buildHeader();
		message = buildMsg(synNum);

		buildSendMessage(hdr,message);
	
		//requestScan =	tempTab;  //ze stala tablica zanakow


	char *packetBytes;
	amber::hokuyo_proto::Scan* tmp_scan;
	
	udp->Send(requestScan,requestScanLength);
	packetBytes = udp->Receive();
	
	tmp_scan = scanRequest(packetBytes);
	
	ScanLengthAll = tmp_scan->distances_size();

	angles = new double[ScanLengthAll];
	distances = new int[ScanLengthAll];
}

HokuyoProxy::~HokuyoProxy()
{
    delete []angles;
	delete [] requestScan;
	delete []distances;
	delete message;
}

double HokuyoProxy::Angle(int index)
{
	return angles[index];
}	

int HokuyoProxy::Distance(int index)
{
	return distances[index];
}
	
void HokuyoProxy::GetScan()
{
	char *packetBytes;
	amber::hokuyo_proto::Scan* tmp_scan;

	udp->Send(requestScan,requestScanLength);
	packetBytes = udp->Receive();
	
	tmp_scan = scanRequest(packetBytes);
	
	for(int i = 0,index = 0; i < ScanLengthAll;i += PRZLIECZENIE_DLA_POMIARU_SKANERA,index++)
	{
		angles[index] = tmp_scan->angles(i);
		distances[index] = tmp_scan->distances(i);

		ScanLength = index;
	}
}

/*

double obliczA(double X1,double Y1,double X2,double Y2)
{
	return ((Y2 - Y1) / (X2 - X1));
}

double obliczB(double A,double X1,double Y1,double X2,double Y2)
{
	return Y2 - (A * X2);
}

double odleglosc(double x0,double y0,double A,double B,double C)
{
	double d;
	d = (A * x0 + B * y0 + C) / sqrt(A * A + B * B);

	if(d < 0)
		d *= -1;

	return d;
}

void HokuyoProxy::GetScan2(double X0,double Y0)
{
	double A166 = obliczA(3.1,3.3,3.1,4.9);
	double B166 = obliczB(A166,3.1,3.3,3.1,4.9);

	double A167 = obliczA(2.1,3.3,3.1,3.3);
	double B167 = obliczB(A167,2.1,3.3,3.1,3.3);

	double A168 = obliczA(2.1,3.3,2.1,3.6);
	double B168 = obliczB(A168,2.1,3.3,2.1,3.6);

	double A170 = obliczA(2.1,4.9,3.1,4.9);
	double B170 = obliczB(A170,2.1,4.9,3.1,4.9);

	angles[0] = 180;
	distances[0] = odleglosc(X0,Y0,);

	angles[1] = 90;
	distances[1] = ;

	angles[2] = 0;
	distances[2] = ;

	angles[3] = -90;
	distances[3] = ;






		angles[i] = tmp_scan->angles(i);
		distances[i] = tmp_scan->distances(i);

}



*/

amber::hokuyo_proto::Scan* HokuyoProxy::scanRequest(char* packetBytes)
{
	int headerLen = (packetBytes[0] << 8) + (packetBytes[1] & 0xff);
	int messageLen = (packetBytes[2 + headerLen] << 8) + (packetBytes[2 + headerLen + 1] & 0xff);
	const char* shiftPacketBytes = &(packetBytes[2 + headerLen + 2]);

	message->ParseFromArray(shiftPacketBytes,messageLen);

	return  message->MutableExtension(amber::hokuyo_proto::scan);
}

double* HokuyoProxy::GetAngles()
{
	return angles;
}

int* HokuyoProxy::GetDistances()
{
	return distances;
}


amber::DriverHdr  HokuyoProxy::buildHeader()
{
	amber::DriverHdr driverHdrBuilder;
	driverHdrBuilder.set_devicetype(DEVICE_TYPE);
	driverHdrBuilder.set_deviceid(DEVICE_ID);

	return driverHdrBuilder;
}

amber::DriverMsg* HokuyoProxy::buildMsg(int synNum)
{
		amber::DriverMsg* message = new amber::DriverMsg();
		message->set_type(amber::DriverMsg::DATA);

		message->SetExtension(amber::hokuyo_proto::get_single_scan,true);
		message->set_synnum(synNum);

	return message;
}


void HokuyoProxy::buildSendMessage(amber::DriverHdr header, amber::DriverMsg* message)
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

}
