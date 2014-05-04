// Lokalizacja.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

#include "Particle.h";
#include "UdpClient.h";

#include "BoundingBox.h";

#include <stdio.h>

#define ILOSC_POMIAROW_SCENNER 800
#define ILOSC_CZASTEK 100
#define THRESHILD 1.222
#define EPSILON 2
#define GENERATION 3
#define ILOSC_LOSOWANYCH_NOWYCH_CZASTEK 2


//void InitTablicaCzastek(Particle *tablica,double dMaxX,double dMaxY,double dRMAX)
//{
//	for (int i = 0; i < ILOSC_CZASTEK; i++)
//	{
//		Particle temp(dMaxX,dMaxY, dRMAX); 	
//		tablica[i] = temp;
//	}
//}


int main(int argc, char* argv[])
{
		parseJasonFile("D:\\Moje dokumenty\\Visual Studio 2012\\Projects\\ConsoleApplication4\\ConsoleApplication4\\Debug\\tests\\2ndFloor-rooms.roson");

	
	double e = 44;

	Particle p(e,e,e);

	p.X = 67;
	p.Y = 554;
	p.Alfa = 278;

	p.ZaktualizujPrzesuniecie(0,0);

	
p.X = 222;


	//Particle tablicaCzastek[ILOSC_CZASTEK];


	/*int WolneMiejscaTablicaCzastek[ILOSC_CZASTEK];
	int index;
	double SkanerLaserowy[ILOSC_POMIAROW_SCENNER];*/

	//InitTablicaCzastek(tablicaCzastek,10,10,10);

	//for (int i = 0; i < ILOSC_CZASTEK; i++)
	//{
	//	Particle temp(100,100, 100); 	
	//	tablicaCzastek[i] = temp;
	//}

 //   tablicaCzastek[0].X = 15;
	//tablicaCzastek[0].Y = 13;



	//UdpClient client("127.0.0.1",1234);


	//for(int i = 0; i < 1000000; i++)
	//{

	//stringstream temp;
	//string tmp;

	//temp.clear();
	//tmp = "";

	///*for(int i = 0; i < ILOSC_CZASTEK; i++)
	//{*/


	//Particle	tablicaCzastek(10,10,10);
		
	/*tablicaCzastek.X = 12 + i * 10;
	tablicaCzastek.Y = 10 + i * 10 ;*/
	/*tablicaCzastek.Losuj(15,15);

	temp << "#" << 0 << ";" << tablicaCzastek.X << ";" << tablicaCzastek.Y << ";" << tablicaCzastek.Alfa << ";" << tablicaCzastek.Probability << ";";
		
*/
		/*tab[i].X = rand();
		tab[i].Y = rand();
		tab[i].Alfa = rand();
		tab[i].Probability =  (rand()/(double)(RAND_MAX + 1));

		temp << "#" << i << ";" << tab[i].X << ";" << tab[i].Y << ";" << tab[i].Alfa << ";" << tab[i].Probability << ";" << '\0';		
		
		client.Send( tmp.c_str(),strlen( tmp.c_str()));*/
	//}

	//	tmp = temp.str();
	//client.Send( tmp.c_str());

	//}
	//int j = 44;

	//double przesuniecieX;
	//double przesuniecieY;
	//double przesuniecieAlfa;

	//while(true)
	//{
	//	index = 0;

	//	for(int i= 0; i < ILOSC_CZASTEK;i++)
	//	{
	//		tablicaCzastek[i].UpdateCountProbability(SkanerLaserowy,ILOSC_POMIAROW_SCENNER); //przeliczamy prawdopodobienstwa

	//		if(tablicaCzastek[i].sMarkToDelete > 0) 
	//		{
	//			if((tablicaCzastek[i].Probability < EPSILON) && (tablicaCzastek[i].sMarkToDelete > GENERATION)) //usuwamy te kt�re s� poza epsilonem
	//			{
	//				WolneMiejscaTablicaCzastek[index] = i;
	//				index++;
	//			}
	//		}
	//		else
	//			tablicaCzastek[i].Move(przesuniecieX,przesuniecieY,przesuniecieAlfa);
	//	}

	/*	for (int i = 0; i < length; i++)
		{

		}*/

	//}




	//tab = new 



	//Particle *tab;
	//tab = new Particle(10,10)[ILOSC_CZASTEK];
	/*	Particle part(10,10,2);
	Particle part1(10,10,2);


	part1.Losuj(part.X,part.Y);*/




	//part.Losuj();

	int i = 323;

	/*Particle tab(222,333)[ILOSC_CZASTEK];

	for(int i = 0; i < ILOSC_CZASTEK; i++)
	{
	tab[i].X = rand();
	tab[i].Y = rand();
	tab[i].Alfa = rand();
	tab[i].Probability =  (rand()/(double)(RAND_MAX + 1));
	}

	*/
	//
	//UdpClient client("127.0.0.1",1234);
	////const char* str = "jakis teekst";

	//stringstream temp;
	//string tmp;

	//temp.clear();
	//tmp = "";

	//for(int i = 0; i < ILOSC_CZASTEK; i++)
	//{
	//	temp << "#" << i << ";" << tab[i].X << ";" << tab[i].Y << ";" << tab[i].Alfa << ";" << tab[i].Probability << ";";
	//	

	//	/*tab[i].X = rand();
	//	tab[i].Y = rand();
	//	tab[i].Alfa = rand();
	//	tab[i].Probability =  (rand()/(double)(RAND_MAX + 1));

	//	temp << "#" << i << ";" << tab[i].X << ";" << tab[i].Y << ";" << tab[i].Alfa << ";" << tab[i].Probability << ";" << '\0';		
	//	tmp = temp.str();
	//	client.Send( tmp.c_str(),strlen( tmp.c_str()));*/
	//}

	//tmp += temp.str();

	//client.Send(tmp.c_str());

	//int it = 44;

	//const char* s;
	//Particle p;
	//p.Alfa = 444;
	//p.X =4333;
	//p.Y = 111;
	//p.Probability = 0.3344;

	////s = p.TransmitParticle(0);








	//client.Send(str,strlen(str));
	//const char* temp;

	//int SkanerLaserowy[ILOSC_POMIAROW_SCENNER];

	/*Particle tab[ILOSC_CZASTEK];
	stringstream temp;
	string tmp;

	for(int i = 0; i < ILOSC_CZASTEK; i++)
	{

	tab[i].X = rand();
	tab[i].Y = rand();
	tab[i].Alfa = rand();
	tab[i].Probability =  (rand()/(double)(RAND_MAX + 1));

	temp << "#" << i << ";" << tab[i].X << ";" << tab[i].Y << ";" << tab[i].Alfa << ";" << tab[i].Probability << ";" << '\0';		
	tmp = temp.str();
	client.Send( tmp.c_str(),strlen( tmp.c_str()));
	}*/

	/*char* tablica = new char[sizeof(tab)];

	Particle test;
	test.Alfa =111;
	test.X = 333;
	test.Y = 999;

	char* tab1 = new char[sizeof(tab)];

	memcpy(tab1,&tab,sizeof(Particle) * ILOSC_CZASTEK);


	Particle tab2[ILOSC_CZASTEK];
	*/


	/*memcpy(&tab2,tab1,sizeof(tab1));


	delete [] tablica;
	delete [] tab1;
	*/
	//memcpy(tab1,&test,sizeof(Particle));


	//Particle test99;

	//memcpy(&test99,tab1,sizeof(Particle));



	//	copy(

	//tablica = copy(tablica,

	//memcpy(tablica,&tab,sizeof(tab));

	/*for(int i = 0; i < ILOSC_CZASTEK; i++ )
	{
	tablica = copy(
	}
	*/


	//////init
	//for(int i = 0; i < ILOSC_CZASTEK; i++)
	//{
	//	tab[i].X = rand();
	//	tab[i].Y = rand();
	//	tab[i].Alfa = rand();
	//	tab[i].Probability =  (rand()/(double)(RAND_MAX + 1));
	//	temp = tab[i].TransmitParticle(i);

	//	client.Send(temp,strlen(temp));
	//}

	//int size = sizeof(tab);

	//const char* gg = (char*) tab;

	//for(int i = 0; i < sizeof(gg);i++)
	//{
	//	gg[i];
	//}

	//char* gg = new char[size];



	//gg


	//tab[0].X = 0;
	//tab[0].Y = 3;
	//tab[0].Alfa =11;
	//tab[0].prowdopodobienstwo = 3.33333;


	//
	//zm= tab[0].TransmitParticle(0);



	//UdpClient *cli = new UdpClient(1234);
	//char* tabliczka;

	//char* tablica = "ff";

	//cli->Send(tablica,2);

	//tabliczka = cli->Receive();

	//return 0;
}

