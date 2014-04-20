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
	UdpClient client(1234);
	const char* temp;

	//int SkanerLaserowy[ILOSC_POMIAROW_SCENNER];

	Particle tab[ILOSC_CZASTEK];

	//init
	for(int i = 0; i < ILOSC_CZASTEK; i++)
	{
		tab[i].X = rand();
		tab[i].Y = rand();
		tab[i].Alfa = rand();
		tab[i].Probability =  (rand()/(double)(RAND_MAX + 1));
		temp = tab[i].TransmitParticle(i);

		client.Send(temp,strlen(temp));
	}


	

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

