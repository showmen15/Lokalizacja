// Lokalizacja.cpp : Defines the entry point for the console application.
//

//test

//#include "stdafx.h"

#include "BoundingBox.h"
#include "Particle.h"

//Linux 1; Windows 0
/*#define SYSTEM 1

#if SYSTEM == 0
	#include "ProxyWindows\UdpClientWindows.h"
	#include "ProxyWindows\HokuyoProxy.h"
	#include "ProxyWindows\RoboclawProxy.h"
#elif SYSTEM == 1*/
#include "Proxy/UdpClientLinux.h"
#include "Proxy/HokuyoProxy.h"
#include "Proxy/RoboclawProxy.h"
#include "Proxy/LocationProxy.h"
//#endif



#include <stdio.h>
#include <ctime>

#define ILOSC_POMIAROW_SCENNER 10
#define ILOSC_CZASTEK 10
//#define THRESHILD 1.222
#define EPSILON 0.01
#define GENERATION 3
#define ILOSC_LOSOWANYCH_NOWYCH_CZASTEK 2
#define TEST 1


//void InitTablicaCzastek(Particle *tablica,double dMaxX,double dMaxY,double dRMAX)
//{
//	for (int i = 0; i < ILOSC_CZASTEK; i++)
//	{
//		Particle temp(dMaxX,dMaxY, dRMAX); 	
//		tablica[i] = temp;
//	}
//}

void InitTablicaCzastek(Particle *tablica,BoundingBox* bBox,int countBox,double dRMAX)
{
	//int iloscCzastekPerBoundingBox = ILOSC_CZASTEK / countBox;
	
	double dMinX;
	double dMaxX;
	double dMinY;
	double dMaxY;

	for (int i = 0, j = 0; i < ILOSC_CZASTEK; i++, j++)
	{			
		dMinX = bBox[j].X_Left_Bottom;
		dMinY = bBox[j].Y_Left_Bottom;
		dMaxX = bBox[j].X_Right_Bottom;
		dMaxY = bBox[j].Y_Left_Top;
		
		//double X = (bBox[j].X_Right_Bottom - bBox[j].X_Left_Bottom ) / 2;
		//double Y = (bBox[j].Y_Left_Top - bBox[j].Y_Left_Bottom) /2;


		Particle temp(dMinX,dMaxX,dMinY,dMaxY, dRMAX);
		//temp.Losuj(X,Y,100);
		tablica[i] = temp;

		if(j == (countBox - 1))
			j = 0;
	}
}

void SendBox(BoundingBox* bBox, int BoundingBoxCount)
{
 char* sIP = "127.0.0.1";
	UdpClient client(sIP,5555,9000);
	stringstream temp;
	string tmp;

	for (int i = 0; i < BoundingBoxCount; i++)
	{
			temp << "@" << i << ";" << bBox[i].X_Left_Top << ";" << bBox[i].Y_Left_Top << ";" 
								<< bBox[i].X_Left_Bottom << ";" << bBox[i].Y_Left_Bottom << ";" 
								<< bBox[i].X_Right_Top << ";" << bBox[i].Y_Right_Top << ";"
								<< bBox[i].X_Right_Bottom << ";" << bBox[i].Y_Right_Bottom << ";";
	}

	tmp = temp.str();
	client.Send(tmp.c_str(),temp.str().size());
}

const char* SendParticle(string *diagnostic,Particle *tab,int *size)
{
	//string tmp;
	diagnostic->clear();
	for(int i = 0; i < ILOSC_CZASTEK; i++)
	{
		stringstream temp;

		temp << "#" << i << ";" << tab[i].X << ";"  << tab[i].Y << ";" << tab[i].Alfa << ";" << tab[i].Probability << ";";

		(*diagnostic) = (*diagnostic) + temp.str();
	}

	//(*size) = tmp.size();
	//return tmp.c_str();
	return NULL;
}



//void Przesun(Particle *tab,double V,double t)
//{
//	for (int i = 0; i < ILOSC_CZASTEK; i++)
//	{
//		tab[i].ZaktualizujPrzesuniecie(V,t);
//	}
//}

//BoundingBox* GetBoundingBox(BoundingBox* bBox,int length, double X,double Y)
//{
//	for (int i = 0; i < length; i++)
//	{
//		if((X >= bBox[i].X_Left_Bottom) && (X <= bBox[i].X_Right_Bottom) && (Y >=  bBox[i].Y_Left_Bottom) && (Y <=  bBox[i].Y_Left_Top))
//			return &(bBox[i]);
//	}
//	return NULL;
//}

Room* GetRoom(Room* bBox,int length, double X,double Y)
{
	for (int i = 0; i < length; i++)
	{
		if((X >= bBox[i].Box.X_Left_Bottom) && (X <= bBox[i].Box.X_Right_Bottom) && (Y >=  bBox[i].Box.Y_Left_Bottom) && (Y <=  bBox[i].Box.Y_Left_Top))
			return &(bBox[i]);
	}
	return NULL;
}

inline int wylosujBB(int fMin, int fMax)
{
	    int f = rand() / RAND_MAX;
	    return fMin + f * (fMax - fMin);
}

void UsunWylosujNoweCzastki(Particle* tablicaCzastek,int length,int iloscCzastekDoUsuniecia,BoundingBox* bBox,unsigned int BoundingBoxCount)
{
	//powiel czastki
	for(int i = 0, j = length - 1; i < (iloscCzastekDoUsuniecia - ILOSC_LOSOWANYCH_NOWYCH_CZASTEK); i++, j-- )
		tablicaCzastek[j].LosujSasiada(tablicaCzastek[i].X,tablicaCzastek[i].Y,tablicaCzastek[i].Alfa);


	for(int u = 0, index = ((length - 1) - (iloscCzastekDoUsuniecia - ILOSC_LOSOWANYCH_NOWYCH_CZASTEK)); u < (iloscCzastekDoUsuniecia - ILOSC_LOSOWANYCH_NOWYCH_CZASTEK); u++)
	{
		#if TEST == 1
			if(index < 0)
				printf("UsunWylosujNoweCzastki index,%d",index);
			fflush(NULL);
		#endif

		int p = wylosujBB(0,BoundingBoxCount);

		tablicaCzastek[index].LosujPozycje(bBox[p].X_Left_Bottom,bBox[p].X_Right_Bottom,bBox[p].Y_Left_Bottom,bBox[p].Y_Left_Top);
	}
}



int compareMyType (const void * a, const void * b)
{
	if ( (*(Particle*)a).Probability <  (*(Particle*)b).Probability ) return 1;
	else if ( (*(Particle*)a).Probability == (*(Particle*)b).Probability ) return 0;
	else return -1;
}


//inline double getDistnace(MazeWall *wall,double X2,double Y2,double a2)
//{	
//	double W;
//	double Wx;
//	double Wy;
//	double dist = 0.0;
//	double X;
//	double Y;
//	double a1 = wall->A;
//	double b1 = wall->B;
//	double c1 = wall->C;
//
//	double b2 = -1;
//	double c2 =  Y2 - (a2 * Y2);
//
//	W = a1 * b2 - b1 * a2;
//	
//	if(W != 0)
//	{
//		Wx = c1 * b2 - b1 * c2;
//		Wy = a1 * c2 - c1 * a2;
//
//		X = Wx / W;
//		Y = Wy / W;
//
//		if((wall->From_X <= X <= wall->To_X) && (wall->From_Y <= Y <= wall->To_Y))
//			dist = sqrt(pow(X - X2 ,2) + pow( Y - Y2,2)); //wartosc oczekiwana
//	}
//
//	return dist;
//}


inline double getDistnace(MazeWall *wall,double alfa,double X2,double Y2)
{	
	double W;
	double Wx;
	double Wy;
	double dist = 0.0;
	double X;
	double Y;
	double a1 = wall->A;
	double b1 = wall->B;
	double c1 = wall->C;

	double a2 = tan( alfa * M_PI / 180.0);
	double b2 = -1;
 	double c2 =  Y2 - (a2 * Y2);

	W = a1 * b2 - b1 * a2;
	
	if(W != 0)
	{
		Wx = c1 * b2 - b1 * c2;
		Wy = a1 * c2 - c1 * a2;

		X = Wx / W;
		Y = Wy / W;

		if((wall->From_X <= X <= wall->To_X) && (wall->From_Y <= Y <= wall->To_Y))
			dist = sqrt(pow(X - X2 ,2) + pow( Y - Y2,2)); //wartosc oczekiwana
	}

	return dist;
}

int main1(int argc, char* argv[])
{
		MazeWall wall;

		wall.From_X = 1;
		wall.From_Y = 7;
		wall.To_X = 7;
		wall.To_Y = 7;

		wall.Calculate();

		Particle part;
		part.X = 0;
		part.Y = 0;
	    
		double dist = getDistnace(&wall,45,part.X,part.Y);



	
	/*double X;
		double Y;
		double dist;
		double alfa2;
		double b2;
		double gauss;*/

		



		/*
	MazeWall wall;
	wall.From_X = 6;
		wall.From_Y = 1;

		wall.To_X = 3;
		wall.To_Y = 3;

		wall.Calculate();

		alfa2 = tan(15);
			b2 = Y1 - (alfa2 * Y1);

			W = alfa2 * box->ContainerWall[j].B + box->ContainerWall[j].A;
			Wx = b2 * box->ContainerWall[j].B + box->ContainerWall[j].C;
			Wy = alfa2 * box->ContainerWall[j].C - box->ContainerWall[j].A * b2;


			X = Wx/W;
			Y = Wy/W;*/
		return 0;

}

inline double Gauss(double prop,double real)
{
	return (1/ODCHYLENIE * sqrt(2 * M_PI)) * (exp(-1 * pow(prop - real,2)/(2 * ODCHYLENIE * ODCHYLENIE)));
		//exp((-1 * pow(scanTable[i] - dist,2)) / ( 2 * ODCHYLENIE * ODCHYLENIE)) / (2 * M_PI * ODCHYLENIE); 
}


inline double Gauss2(double prop,double real)
{
double a,b,c,d;
double x = prop;
double delta = sqrt(0.5);
double ni = real;

a = 1 / (delta  *sqrt(2 * M_PI));
b = ni;
c = delta;
d = 0;

return (a * exp( pow(x - b,2) / (-2 * pow(c,2)))) + d; 
}

int main0()
{
	double 	gauss = Gauss2(100,100);

	return 0;
}



int main4(int argc, char* argv[])
{
	Particle* tablicaCzastek = new Particle[1];
	tablicaCzastek[0].X = 12;
	tablicaCzastek[0].Y = 5;

	//Room r;
	BoundingBox* bBox;
	Room*  rooms;
	int countBox;
	int countRoomAndBox;
	Room *currentRoom;
	const int ScanLength = 5;
	int scanTable[ScanLength] = {20,45,55,66,77 };
	double angleTable[ScanLength] = {10,33,55,66,77};

	countRoomAndBox = parseJasonFile("D:\\Moje dokumenty\\Visual Studio 2012\\Projects\\ConsoleApplication4\\ConsoleApplication4\\Debug\\tests\\2ndFloor-rooms.roson",bBox,rooms);

	for (int i = 0; i < 1; i++)
		{
			currentRoom = GetRoom(rooms,countRoomAndBox,tablicaCzastek[i].X,tablicaCzastek[i].Y); //pobranie informacji w ktrorym BB jest czastka
			
			tablicaCzastek[i].UpdateCountProbability(currentRoom, scanTable,angleTable,ScanLength); //przeliczamy prawdopodobienstwa
		}
	return 0;
}

/*

int mainMAIN(int argc, char* argv[])
{
	char* amberUdp = "192.168.0.203"; //przerobic aby bral lokalny adres z robota
	UdpClient clinetAmber(amberUdp,26233,9000);
	BoundingBox* bBox;
	Room*  rooms;
	int countBox;
	int countRoomAndBox;
	int pause;

	countRoomAndBox = parseJasonFile("/home/ubuntu//git//Lokalizacja//Lokalizacja//Debug//2ndFloor-rooms.roson",bBox,rooms);

	Particle* tablicaCzastek = new Particle[ILOSC_CZASTEK];
	int iloscCzastekDoUsuniacia = 0;
	InitTablicaCzastek(tablicaCzastek,bBox,countRoomAndBox,10);
	HokuyoProxy* skaner = new HokuyoProxy(&clinetAmber);
	RoboclawProxy* roboClaw = new RoboclawProxy(&clinetAmber);
	int speedRoboClaw;
	double angleRoboClaw;
	time_t dtime = 0;
	double deletaTime;
	Room* currentRoom;

	time(&dtime);

	while(true)
	{
		deletaTime =  difftime(time(NULL),dtime);
		time(&dtime);

		skaner->GetScan();

		speedRoboClaw = roboClaw->GetSpeed();
		angleRoboClaw = roboClaw->GetAngle(deletaTime);

		for (int i = 0; i < ILOSC_CZASTEK; i++)
		{
			currentRoom = GetRoom(rooms,countRoomAndBox,tablicaCzastek[i].X,tablicaCzastek[i].Y); //pobranie informacji w ktrorym BB jest czastka

			tablicaCzastek[i].UpdateCountProbability(currentRoom, skaner->GetDistances(),skaner->GetAngles(),skaner->ScanLength); //przeliczamy prawdopodobienstwa

			if(tablicaCzastek[i].sMarkToDelete > GENERATION)
				iloscCzastekDoUsuniacia++;
			else
			{
				if(tablicaCzastek[i].Probability < EPSILON)
					tablicaCzastek[i].sMarkToDelete++;

				tablicaCzastek[i].ZaktualizujPrzesuniecie(speedRoboClaw,angleRoboClaw,deletaTime);
			}
		}

		qsort(tablicaCzastek,ILOSC_CZASTEK,sizeof(Particle),compareMyType);

		UsunWylosujNoweCzastki(tablicaCzastek,ILOSC_CZASTEK,iloscCzastekDoUsuniacia);
		iloscCzastekDoUsuniacia = 0;

		scanf("%d",&pause);
	}
	return 0;
}
*/


int mainObrotCzastkiKat(int argc, char* argv[]) //test ObrotCzastkiKat
{
	double alfaNew = 45;
	double X = 1;
	double Y = 0;
	double Alfa = 20;

	X = X * cos((alfaNew * M_PI) / 180) - Y * sin((alfaNew * M_PI) / 180);
		Y = X * sin((alfaNew * M_PI) / 180) + Y * cos((alfaNew * M_PI) / 180);

		Alfa += alfaNew;

}

void RozmiescCzastki(BoundingBox* bBox,unsigned int BoundingBoxCount,Particle* tablicaCzastek,unsigned int ParticleCount)
{
	for(unsigned int i = 0, p = 0; i < ParticleCount; i++, p++)
	{
		Particle temp;
		temp.LosujPozycje(bBox[p].X_Left_Bottom,bBox[p].X_Right_Bottom,bBox[p].Y_Left_Bottom,bBox[p].Y_Left_Top);
		tablicaCzastek[i] = temp;

		if((p + 1) == BoundingBoxCount)
			p = -1;
	}
}
void aktualizuj(double wheelTrack, int frontRightSpeed, int  rearRightSpeed, int frontLeftSpeed, int rearLeftSpeed ,double time,double alfa1)
{
	double Vr = ((double) (frontRightSpeed +  rearRightSpeed)) / 2 ;
	double Vl = ((double)(frontLeftSpeed + rearLeftSpeed)) / 2;

	double sr = Vr * time;
	double sl = Vl * time;

	double s = (sr + sl) / 2;

	double alfa = ((sr - sl) / wheelTrack) + alfa1;

	double X0 = 0;
	double Y0 = 0;

	X0 = s * cos((alfa * M_PI) / 180) + X0;
	Y0 = s * sin((alfa * M_PI) / 180) + Y0;

	printf("X%f\nY%f",X0,Y0);
		fflush(NULL);
}

/*
double GetAngle(double wheelTrack, int frontRightSpeed, int  rearRightSpeed, int frontLeftSpeed, int rearLeftSpeed ,double time,double alfa)
{
	double Vr = ((double) (frontRightSpeed +  rearRightSpeed)) / 2 ;
	double Vl = ((double)(frontLeftSpeed + rearLeftSpeed)) / 2;

	double sr = Vr * time;
	double sl = Vl * time;


	return ((sr - sl) / wheelTrack) + alfa;
//return ((((tmpRight) / 2) - ((tmpLeftS) / 2)) * time) / wheelTrack;
}


inline void ZaktualizujPrzesuniecie(double s,double  alfa)
{
	 // double X,Y,Alfa;
	  	//  	X += s * cos((alfa * M_PI) / 180 ); // A'= [x + Sx, ...]
	//		Y += s * cos(((90 - alfa) * M_PI) / 180); // A' [... ,y + Sy]

		//	Alfa += alfa;
double X0 = 0;
double Y0 = 0;

X0 = s * cos((alfa * M_PI) / 180) + X0;
Y0 = s * sin(alfa * M_PI) / 180) + Y0;

}

*/


int maintest(int argc, char* argv[])
{
	int frontRightSpeed = 1;
	int  rearRightSpeed = 1;
	int frontLeftSpeed = 1;
	int rearLeftSpeed = 1;

	//double ang = GetAngle(0.26,frontRightSpeed,rearRightSpeed,frontLeftSpeed,rearLeftSpeed,1,0);

	aktualizuj(0.26,frontRightSpeed,rearRightSpeed,frontLeftSpeed,rearLeftSpeed,1,45);

	//printf("%f",ang);
	fflush(NULL);
//	ZaktualizujPrzesuniecie(2,0);

}

int main(int argc, char* argv[])
{
	//char* IPPart = "192.168.2.101";
	//UdpClient clientParticle(IPPart,1234,9000);
//	string diagnostic;
    //int size;
	//const char* wys;

	char* amberUdp = "192.168.2.203"; //przerobic aby bral lokalny adres z robota
	UdpClient clinetAmber(amberUdp,26233,9000);

	LocationProxy* location = new LocationProxy(&clinetAmber);

	double x,y;

	location->GetLocation();

	x = location->X();
	y = location->Y();

	return 0;
}



int mainPrzesuniecie(int argc, char* argv[])
{
	/////// Diagnostic ////////////////
	char* IPPart = "192.168.2.101"; //przerobic aby bral lokalny adres z robota
	UdpClient clientParticle(IPPart,1234,9000);
	string diagnostic;
    int size;
	const char* wys;
	//////////////////////////////////

	char* amberUdp = "192.168.2.203"; //przerobic aby bral lokalny adres z robota
	UdpClient clinetAmber(amberUdp,26233,9000);
	BoundingBox* bBox;
	Room*  rooms;
	int countBox;
	int countRoomAndBox;
	char pause;


	//countRoomAndBox = parseJasonFile("/home/ubuntu//git//Lokalizacja//Lokalizacja//Debug//2ndFloor-rooms.roson",bBox,rooms);
	countRoomAndBox = parseJasonFile("/home/ubuntu//git//Lokalizacja//Lokalizacja//Debug//lab.roson",bBox,rooms);

	Particle* tablicaCzastek = new Particle[ILOSC_CZASTEK];
	int iloscCzastekDoUsuniacia = 0;

	RozmiescCzastki(bBox,countRoomAndBox,tablicaCzastek,ILOSC_CZASTEK); //InitTablicaCzastek(tablicaCzastek,bBox,countRoomAndBox,10);

	SendParticle(&diagnostic,tablicaCzastek,&size);
	wys = diagnostic.c_str();
	size = diagnostic.size();
	clientParticle.Send(wys,size);

	HokuyoProxy* skaner = new HokuyoProxy(&clinetAmber);
	RoboclawProxy* roboClaw = new RoboclawProxy(&clinetAmber);
	double speedRoboClaw;
	double angleRoboClaw;
	time_t dtime = 0;
	double deletaTime;
	Room* currentRoom;

	int petla = 0;

	time(&dtime);

	SendParticle(&diagnostic,tablicaCzastek,&size);
	wys = diagnostic.c_str();
	size = diagnostic.size();
	clientParticle.Send(wys,size);

	tablicaCzastek[0].X = 3;
	tablicaCzastek[0].Y = 3;
	tablicaCzastek[0].Alfa = 0.0;

	sleep(1);
	while(true)
	{
		deletaTime = difftime(time(NULL),dtime); // czas w sekundach
		time(&dtime);

		roboClaw->GetSpeed();

		tablicaCzastek[0].ZaktualizujPrzesuniecie3(roboClaw->wheelTrack,roboClaw->FrontRightSpeed(),roboClaw->RearRightSpeed(),-roboClaw->FrontLeftSpeed(), -roboClaw->RearLeftSpeed(),deletaTime);

		SendParticle(&diagnostic,tablicaCzastek,&size);
		wys = diagnostic.c_str();
		size = diagnostic.size();
		clientParticle.Send(wys,size);

		sleep(2);
	}
	return 0;
}









int mainMAIN(int argc, char* argv[])
{
	/////// Diagnostic ////////////////
	char* IPPart = "192.168.2.101"; //przerobic aby bral lokalny adres z robota
	UdpClient clientParticle(IPPart,1234,9000);
	string diagnostic;
    int size;
	const char* wys;
	//////////////////////////////////

	char* amberUdp = "192.168.2.201"; //przerobic aby bral lokalny adres z robota
	UdpClient clinetAmber(amberUdp,26233,9000);
	BoundingBox* bBox;
	Room*  rooms;
	int countBox;
	int countRoomAndBox;
	char pause;


	//countRoomAndBox = parseJasonFile("/home/ubuntu//git//Lokalizacja//Lokalizacja//Debug//2ndFloor-rooms.roson",bBox,rooms);
	countRoomAndBox = parseJasonFile("/home/ubuntu//git//Lokalizacja//Lokalizacja//Debug//lab.roson",bBox,rooms);

	Particle* tablicaCzastek = new Particle[ILOSC_CZASTEK];
	int iloscCzastekDoUsuniacia = 0;

	RozmiescCzastki(bBox,countRoomAndBox,tablicaCzastek,ILOSC_CZASTEK); //InitTablicaCzastek(tablicaCzastek,bBox,countRoomAndBox,10);

	SendParticle(&diagnostic,tablicaCzastek,&size);
	wys = diagnostic.c_str();
	size = diagnostic.size();
	clientParticle.Send(wys,size);

	RoboclawProxy* roboClaw = new RoboclawProxy(&clinetAmber);
	double speedRoboClaw;
	double angleRoboClaw;




	speedRoboClaw = roboClaw->GetSpeed();


	HokuyoProxy* skaner = new HokuyoProxy(&clinetAmber);


	time_t dtime = 0;
	double deletaTime;
	Room* currentRoom;

	int petla = 0;

	time(&dtime);

	SendParticle(&diagnostic,tablicaCzastek,&size);
	wys = diagnostic.c_str();
	size = diagnostic.size();
	clientParticle.Send(wys,size);


	while(true)
	{
		deletaTime = difftime(time(NULL),dtime); // czas w sekundach
		time(&dtime);

		skaner->GetScan();

		speedRoboClaw = roboClaw->GetSpeed(); //droga w metrach
		angleRoboClaw = roboClaw->GetAngle(deletaTime);
		
		//printf("Czas: %e Kat: %e\n", deletaTime,angleRoboClaw);

		for (int i = 0; i < ILOSC_CZASTEK; i++)
		{
			currentRoom = GetRoom(rooms,countRoomAndBox,tablicaCzastek[i].X,tablicaCzastek[i].Y); //pobranie informacji w ktrorym BB jest czastka
			
			if(currentRoom == NULL)
			{
			 tablicaCzastek[i].Probability = 0.0;
			 iloscCzastekDoUsuniacia++;
			 continue;
			}

			tablicaCzastek[i].UpdateCountProbability3(currentRoom, skaner->GetDistances(),skaner->GetAngles(),skaner->ScanLength); //przeliczamy prawdopodobienstwa

/*			if(tablicaCzastek[i].sMarkToDelete > GENERATION)
				iloscCzastekDoUsuniacia++;
			else
			{*/
				if(tablicaCzastek[i].Probability < EPSILON)
				{
					tablicaCzastek[i].sMarkToDelete++;
					iloscCzastekDoUsuniacia++;

				}
				
				//inline void ZaktualizujPrzesuniecie2(double wheelTrack,int frontRightSpeed, int  rearRightSpeed, int frontLeftSpeed, int rearLeftSpeed ,double time)
				//tablicaCzastek[i].ZaktualizujPrzesuniecie(speedRoboClaw,angleRoboClaw,deletaTime);
				tablicaCzastek[i].ZaktualizujPrzesuniecie2(roboClaw->wheelTrack,roboClaw->FrontRightSpeed(),roboClaw->RearRightSpeed(),roboClaw->FrontLeftSpeed(), roboClaw->RearLeftSpeed(),deletaTime);
		//	}
		}

		SendParticle(&diagnostic,tablicaCzastek,&size);
		wys = diagnostic.c_str();
		size = diagnostic.size();
		clientParticle.Send(wys,size);

		qsort(tablicaCzastek,ILOSC_CZASTEK,sizeof(Particle),compareMyType);


		UsunWylosujNoweCzastki(tablicaCzastek,ILOSC_CZASTEK,iloscCzastekDoUsuniacia,bBox,countRoomAndBox);
		iloscCzastekDoUsuniacia = 0;

		SendParticle(&diagnostic,tablicaCzastek,&size);
		wys = diagnostic.c_str();
		size = diagnostic.size();
		clientParticle.Send(wys,size);

		//printf("Podaj licze %dSpeed: %f",petla,speedRoboClaw);
		//scanf("%c",&pause);
		petla++;
		sleep(1);
	}
	return 0;
}



	

		//	for(int i= 0; i < ILOSC_CZASTEK;i++)
		//{
		//	tablicaCzastek[i].UpdateCountProbability(SkanerLaserowy,ILOSC_POMIAROW_SCENNER); //przeliczamy prawdopodobienstwa

		//	if(tablicaCzastek[i].sMarkToDelete > 0) 
		//	{
		//		if((tablicaCzastek[i].Probability < EPSILON) && (tablicaCzastek[i].sMarkToDelete > GENERATION)) //usuwamy te kt�re s� poza epsilonem
		//		{
		//			WolneMiejscaTablicaCzastek[index] = i;
		//			index++;
		//		}
		//	}
		//	else
		//		tablicaCzastek[i].Move(przesuniecieX,przesuniecieY,przesuniecieAlfa);
		//	}
	//	*/

	//SendBox(bBox,countBox);


	//int WolneMiejscaTablicaCzastek[ILOSC_CZASTEK];
	//int index;
	//double SkanerLaserowy[ILOSC_POMIAROW_SCENNER];

	//UdpClient client("127.0.0.1",1234);


	//SendParticle(tablicaCzastek,client);
	
	//int www = -1;

	//while(www != 0)
	//{
	/*	UdpClient client("127.0.0.1",1234);

		Przesun(tablicaCzastek,1,1);
		SendParticle(tablicaCzastek,client);
		
		printf("Ready");
		cin >> www;
	}*/
	

	//stringstream temp;
	//string tmp;

	//for(int i = 0; i < 1000000; i++)
	////{

	//

	//temp.clear();
	//tmp = "";

	//}


//
//	
//
//

	//	/*double e = 44;
//
//	Particle p(e,e,e);
//
//	p.X = 67;
//	p.Y = 554;
//	p.Alfa = 278;
//
//	p.ZaktualizujPrzesuniecie(0,0);
//	

//
//	
//p.X = 222;*/
//
//
//	
//
//
//	/*
//	*/
//
//	//
//
//	//for (int i = 0; i < ILOSC_CZASTEK; i++)
//	//{
//	//	Particle temp(100,100, 100); 	
//	//	tablicaCzastek[i] = temp;
//	//}
//
// //   tablicaCzastek[0].X = 15;
//	//tablicaCzastek[0].Y = 13;
//
//
//
//
//
//
//	
//	///*for(int i = 0; i < ILOSC_CZASTEK; i++)
//	//{*/
//
//
//	//Particle	tablicaCzastek(10,10,10);
//		
//	/*tablicaCzastek.X = 12 + i * 10;
//	tablicaCzastek.Y = 10 + i * 10 ;*/
//	/*tablicaCzastek.Losuj(15,15);
//
//		
//*/
//		/*tab[i].X = rand();
//		tab[i].Y = rand();
//		tab[i].Alfa = rand();
//		tab[i].Probability =  (rand()/(double)(RAND_MAX + 1));
//
//		temp << "#" << i << ";" << tab[i].X << ";" << tab[i].Y << ";" << tab[i].Alfa << ";" << tab[i].Probability << ";" << '\0';		
//		
//		client.Send( tmp.c_str(),strlen( tmp.c_str()));*/
//	//}
//
//	//	tmp = temp.str();
//	//client.Send( tmp.c_str());
//
//	//}
//	//int j = 44;
//
//	//double przesuniecieX;
//	//double przesuniecieY;
//	//double przesuniecieAlfa;
//
//	//while(true)
//	//{
//	//	index = 0;
//

//
//	/*	for (int i = 0; i < length; i++)
//		{
//
//		}*/
//
//	//}
//
//
//
//
//	//tab = new 
//
//
//
//	//Particle *tab;
//	//tab = new Particle(10,10)[ILOSC_CZASTEK];
//	/*	Particle part(10,10,2);
//	Particle part1(10,10,2);
//
//
//	part1.Losuj(part.X,part.Y);*/
//
//
//
//
//	//part.Losuj();
//
//	//int i = 323;
//
//	/*Particle tab(222,333)[ILOSC_CZASTEK];
//
//	for(int i = 0; i < ILOSC_CZASTEK; i++)
//	{
//	tab[i].X = rand();
//	tab[i].Y = rand();
//	tab[i].Alfa = rand();
//	tab[i].Probability =  (rand()/(double)(RAND_MAX + 1));
//	}
//
//	*/
//	//
//	//UdpClient client("127.0.0.1",1234);
//	////const char* str = "jakis teekst";
//
//	//stringstream temp;
//	//string tmp;
//
//	//temp.clear();
//	//tmp = "";
//
//	//for(int i = 0; i < ILOSC_CZASTEK; i++)
//	//{
//	//	temp << "#" << i << ";" << tab[i].X << ";" << tab[i].Y << ";" << tab[i].Alfa << ";" << tab[i].Probability << ";";
//	//	
//
//	//	/*tab[i].X = rand();
//	//	tab[i].Y = rand();
//	//	tab[i].Alfa = rand();
//	//	tab[i].Probability =  (rand()/(double)(RAND_MAX + 1));
//
//	//	temp << "#" << i << ";" << tab[i].X << ";" << tab[i].Y << ";" << tab[i].Alfa << ";" << tab[i].Probability << ";" << '\0';		
//	//	tmp = temp.str();
//	//	client.Send( tmp.c_str(),strlen( tmp.c_str()));*/
//	//}
//
//	//tmp += temp.str();
//
//	//client.Send(tmp.c_str());
//
//	//int it = 44;
//
//	//const char* s;
//	//Particle p;
//	//p.Alfa = 444;
//	//p.X =4333;
//	//p.Y = 111;
//	//p.Probability = 0.3344;
//
//	////s = p.TransmitParticle(0);
//
//
//
//
//
//
//
//
//	//client.Send(str,strlen(str));
//	//const char* temp;
//
//	//int SkanerLaserowy[ILOSC_POMIAROW_SCENNER];
//
//	/*Particle tab[ILOSC_CZASTEK];
//	stringstream temp;
//	string tmp;
//
//	for(int i = 0; i < ILOSC_CZASTEK; i++)
//	{
//
//	tab[i].X = rand();
//	tab[i].Y = rand();
//	tab[i].Alfa = rand();
//	tab[i].Probability =  (rand()/(double)(RAND_MAX + 1));
//
//	temp << "#" << i << ";" << tab[i].X << ";" << tab[i].Y << ";" << tab[i].Alfa << ";" << tab[i].Probability << ";" << '\0';		
//	tmp = temp.str();
//	client.Send( tmp.c_str(),strlen( tmp.c_str()));
//	}*/
//
//	/*char* tablica = new char[sizeof(tab)];
//
//	Particle test;
//	test.Alfa =111;
//	test.X = 333;
//	test.Y = 999;
//
//	char* tab1 = new char[sizeof(tab)];
//
//	memcpy(tab1,&tab,sizeof(Particle) * ILOSC_CZASTEK);
//
//
//	Particle tab2[ILOSC_CZASTEK];
//	*/
//
//
//	/*memcpy(&tab2,tab1,sizeof(tab1));
//
//
//	delete [] tablica;
//	delete [] tab1;
//	*/
//	//memcpy(tab1,&test,sizeof(Particle));
//
//
//	//Particle test99;
//
//	//memcpy(&test99,tab1,sizeof(Particle));
//
//
//
//	//	copy(
//
//	//tablica = copy(tablica,
//
//	//memcpy(tablica,&tab,sizeof(tab));
//
//	/*for(int i = 0; i < ILOSC_CZASTEK; i++ )
//	{
//	tablica = copy(
//	}
//	*/
//
//
//	//////init
//	//for(int i = 0; i < ILOSC_CZASTEK; i++)
//	//{
//	//	tab[i].X = rand();
//	//	tab[i].Y = rand();
//	//	tab[i].Alfa = rand();
//	//	tab[i].Probability =  (rand()/(double)(RAND_MAX + 1));
//	//	temp = tab[i].TransmitParticle(i);
//
//	//	client.Send(temp,strlen(temp));
//	//}
//
//	//int size = sizeof(tab);
//
//	//const char* gg = (char*) tab;
//
//	//for(int i = 0; i < sizeof(gg);i++)
//	//{
//	//	gg[i];
//	//}
//
//	//char* gg = new char[size];
//
//
//
//	//gg
//
//
//	//tab[0].X = 0;
//	//tab[0].Y = 3;
//	//tab[0].Alfa =11;
//	//tab[0].prowdopodobienstwo = 3.33333;
//
//
//	//
//	//zm= tab[0].TransmitParticle(0);
//
//
//
//	//UdpClient *cli = new UdpClient(1234);
//	//char* tabliczka;
//
//	//char* tablica = "ff";
//
//	//cli->Send(tablica,2);
//
//	//tabliczka = cli->Receive();
//
//	//return 0;

