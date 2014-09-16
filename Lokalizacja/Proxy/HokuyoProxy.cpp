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


	/*char *packetBytes;
	amber::hokuyo_proto::Scan* tmp_scan;
	
	do
	{
		udp->Send(requestScan,requestScanLength);
		packetBytes = udp->Receive();
	}
	while(udp->n < 0);
	
	tmp_scan = scanRequest(packetBytes);
	
	ScanLengthAll = tmp_scan->distances_size();

	angles = new double[ScanLengthAll];
	distances = new int[ScanLengthAll];*/

		ScanLengthAll = 682;
		distances = new int[ScanLengthAll];
		ScanLength = ScanLengthAll;

		for(int i = 0; i< ScanLengthAll; i++)
			distances[i] = i;

		 angles = new double[ScanLengthAll]{ -2.092388,-2.086243,-2.080098,-2.073953,-2.067808,-2.061663,-2.055518,-2.049373,-2.043228,-2.037083,-2.030938,-2.024792,-2.018647,-2.012502,-2.006357,-2.000212,-1.994067,-1.987922,-1.981777,-1.975632,-1.969487,-1.963342,-1.957197,-1.951052,-1.944907,-1.938762,-1.932617,-1.926472,-1.920327,-1.914182,-1.908037,-1.901892,-1.895747,-1.889601,-1.883456,-1.877311,-1.871166,-1.865021,-1.858876,-1.852731,-1.846586,-1.840441,-1.834296,-1.828151,-1.822006,-1.815861,-1.809716,-1.803571,-1.797426,-1.791281,-1.785136,-1.778991,-1.772846,-1.766701,-1.760556,-1.754410,-1.748265,-1.742120,-1.735975,-1.729830,-1.723685,-1.717540,-1.711395,-1.705250,-1.699105,-1.692960,-1.686815,-1.680670,-1.674525,-1.668380,-1.662235,-1.656090,-1.649945,-1.643800,-1.637655,-1.631510,-1.625365,-1.619219,-1.613074,-1.606929,-1.600784,-1.594639,-1.588494,-1.582349,-1.576204,-1.570059,-1.563914,-1.557769,-1.551624,-1.545479,-1.539334,-1.533189,-1.527044,-1.520899,-1.514754,-1.508609,-1.502464,-1.496319,-1.490174,-1.484028,-1.477883,-1.471738,-1.465593,-1.459448,-1.453303,-1.447158,-1.441013,-1.434868,-1.428723,-1.422578,-1.416433,-1.410288,-1.404143,-1.397998,-1.391853,-1.385708,-1.379563,-1.373418,-1.367273,-1.361128,-1.354983,-1.348837,-1.342692,-1.336547,-1.330402,-1.324257,-1.318112,-1.311967,-1.305822,-1.299677,-1.293532,-1.287387,-1.281242,-1.275097,-1.268952,-1.262807,-1.256662,-1.250517,-1.244372,-1.238227,-1.232082,-1.225937,-1.219792,-1.213646,-1.207501,-1.201356,-1.195211,-1.189066,-1.182921,-1.176776,-1.170631,-1.164486,-1.158341,-1.152196,-1.146051,-1.139906,-1.133761,-1.127616,-1.121471,-1.115326,-1.109181,-1.103036,-1.096891,-1.090746,-1.084601,-1.078455,-1.072310,-1.066165,-1.060020,-1.053875,-1.047730,-1.041585,-1.035440,-1.029295,-1.023150,-1.017005,-1.010860,-1.004715,-0.998570,-0.992425,-0.986280,-0.980135,-0.973990,-0.967845,-0.961700,-0.955555,-0.949410,-0.943264,-0.937119,-0.930974,-0.924829,-0.918684,-0.912539,-0.906394,-0.900249,-0.894104,-0.887959,-0.881814,-0.875669,-0.869524,-0.863379,-0.857234,-0.851089,-0.844944,-0.838799,-0.832654,-0.826509,-0.820364,-0.814219,-0.808073,-0.801928,-0.795783,-0.789638,-0.783493,-0.777348,-0.771203,-0.765058,-0.758913,-0.752768,-0.746623,-0.740478,-0.734333,-0.728188,-0.722043,-0.715898,-0.709753,-0.703608,-0.697463,-0.691318,-0.685173,-0.679028,-0.672882,-0.666737,-0.660592,-0.654447,-0.648302,-0.642157,-0.636012,-0.629867,-0.623722,-0.617577,-0.611432,-0.605287,-0.599142,-0.592997,-0.586852,-0.580707,-0.574562,-0.568417,-0.562272,-0.556127,-0.549982,-0.543837,-0.537691,-0.531546,-0.525401,-0.519256,-0.513111,-0.506966,-0.500821,-0.494676,-0.488531,-0.482386,-0.476241,-0.470096,-0.463951,-0.457806,-0.451661,-0.445516,-0.439371,-0.433226,-0.427081,-0.420936,-0.414791,-0.408646,-0.402500,-0.396355,-0.390210,-0.384065,-0.377920,-0.371775,-0.365630,-0.359485,-0.353340,-0.347195,-0.341050,-0.334905,-0.328760,-0.322615,-0.316470,-0.310325,-0.304180,-0.298035,-0.291890,-0.285745,-0.279600,-0.273455,-0.267309,-0.261164,-0.255019,-0.248874,-0.242729,-0.236584,-0.230439,-0.224294,-0.218149,-0.212004,-0.205859,-0.199714,-0.193569,-0.187424,-0.181279,-0.175134,-0.168989,-0.162844,-0.156699,-0.150554,-0.144409,-0.138264,-0.132118,-0.125973,-0.119828,-0.113683,-0.107538,-0.101393,-0.095248,-0.089103,-0.082958,-0.076813,-0.070668,-0.064523,-0.058378,-0.052233,-0.046088,-0.039943,-0.033798,-0.027653,-0.021508,-0.015363,-0.009218,-0.003073,0.003073,0.009218,0.015363,0.021508,0.027653,0.033798,0.039943,0.046088,0.052233,0.058378,0.064523,0.070668,0.076813,0.082958,0.089103,0.095248,0.101393,0.107538,0.113683,0.119828,0.125973,0.132118,0.138264,0.144409,0.150554,0.156699,0.162844,0.168989,0.175134,0.181279,0.187424,0.193569,0.199714,0.205859,0.212004,0.218149,0.224294,0.230439,0.236584,0.242729,0.248874,0.255019,0.261164,0.267309,0.273455,0.279600,0.285745,0.291890,0.298035,0.304180,0.310325,0.316470,0.322615,0.328760,0.334905,0.341050,0.347195,0.353340,0.359485,0.365630,0.371775,0.377920,0.384065,0.390210,0.396355,0.402500,0.408646,0.414791,0.420936,0.427081,0.433226,0.439371,0.445516,0.451661,0.457806,0.463951,0.470096,0.476241,0.482386,0.488531,0.494676,0.500821,0.506966,0.513111,0.519256,0.525401,0.531546,0.537691,0.543837,0.549982,0.556127,0.562272,0.568417,0.574562,0.580707,0.586852,0.592997,0.599142,0.605287,0.611432,0.617577,0.623722,0.629867,0.636012,0.642157,0.648302,0.654447,0.660592,0.666737,0.672882,0.679028,0.685173,0.691318,0.697463,0.703608,0.709753,0.715898,0.722043,0.728188,0.734333,0.740478,0.746623,0.752768,0.758913,0.765058,0.771203,0.777348,0.783493,0.789638,0.795783,0.801928,0.808073,0.814219,0.820364,0.826509,0.832654,0.838799,0.844944,0.851089,0.857234,0.863379,0.869524,0.875669,0.881814,0.887959,0.894104,0.900249,0.906394,0.912539,0.918684,0.924829,0.930974,0.937119,0.943264,0.949410,0.955555,0.961700,0.967845,0.973990,0.980135,0.986280,0.992425,0.998570,1.004715,1.010860,1.017005,1.023150,1.029295,1.035440,1.041585,1.047730,1.053875,1.060020,1.066165,1.072310,1.078455,1.084601,1.090746,1.096891,1.103036,1.109181,1.115326,1.121471,1.127616,1.133761,1.139906,1.146051,1.152196,1.158341,1.164486,1.170631,1.176776,1.182921,1.189066,1.195211,1.201356,1.207501,1.213646,1.219792,1.225937,1.232082,1.238227,1.244372,1.250517,1.256662,1.262807,1.268952,1.275097,1.281242,1.287387,1.293532,1.299677,1.305822,1.311967,1.318112,1.324257,1.330402,1.336547,1.342692,1.348837,1.354983,1.361128,1.367273,1.373418,1.379563,1.385708,1.391853,1.397998,1.404143,1.410288,1.416433,1.422578,1.428723,1.434868,1.441013,1.447158,1.453303,1.459448,1.465593,1.471738,1.477883,1.484028,1.490174,1.496319,1.502464,1.508609,1.514754,1.520899,1.527044,1.533189,1.539334,1.545479,1.551624,1.557769,1.563914,1.570059,1.576204,1.582349,1.588494,1.594639,1.600784,1.606929,1.613074,1.619219,1.625365,1.631510,1.637655,1.643800,1.649945,1.656090,1.662235,1.668380,1.674525,1.680670,1.686815,1.692960,1.699105,1.705250,1.711395,1.717540,1.723685,1.729830,1.735975,1.742120,1.748265,1.754410,1.760556,1.766701,1.772846,1.778991,1.785136,1.791281,1.797426,1.803571,1.809716,1.815861,1.822006,1.828151,1.834296,1.840441,1.846586,1.852731,1.858876,1.865021,1.871166,1.877311,1.883456,1.889601,1.895747,1.901892,1.908037,1.914182,1.920327,1.926472,1.932617,1.938762,1.944907,1.951052,1.957197,1.963342,1.969487,1.975632,1.981777,1.987922,1.994067,2.000212,2.006357,2.012502,2.018647,2.024792,2.030938,2.037083,2.043228,2.049373,2.055518,2.061663,2.067808,2.073953,2.080098,2.086243,2.092388};
	//	}
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
	/*char *packetBytes;
	amber::hokuyo_proto::Scan* tmp_scan;

	do
	{
		udp->Send(requestScan,requestScanLength);
		packetBytes = udp->Receive();
	}
	while(udp->n < 0);
	
	tmp_scan = scanRequest(packetBytes);
	
	for(int i = 0,index = 0; i < ScanLengthAll;i += PRZLIECZENIE_DLA_POMIARU_SKANERA,index++)
	{
		//angles[index] = tmp_scan->angles(i);
		angles[index] =  ConvertToRadian(tmp_scan->angles(i));
		distances[index] = tmp_scan->distances(i);

		ScanLength = index;
	}*/
}

inline double HokuyoProxy::ConvertToRadian(double degree)
{
	return ((degree * M_PI) / 180);
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
