// Lokalizacja.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

#include "Particle.h";
#include "UdpClient.h";

#include <stdio.h>

#define ILOSC_POMIAROW_SCENNER 800
#define ILOSC_CZASTEK 100


int main(int argc, char* argv[])
{
	//const char* s;
	//Particle p;
	//p.Alfa = 444;
	//p.X =4333;
	//p.Y = 111;
	//p.Probability = 0.3344;

	////s = p.TransmitParticle(0);




	const char* str = "jakis teekst";

	UdpClient client(1234);

	//client.Send(str,strlen(str));
	//const char* temp;

	//int SkanerLaserowy[ILOSC_POMIAROW_SCENNER];

	Particle tab[ILOSC_CZASTEK];
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
	}

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

