
#include <stdio.h>
#include <sstream>
#include <math.h>
#include <iostream>
#include <conio.h>
using namespace std;


#define M_PI       3.14159265358979323846


struct Particle 
{
private:
	double MaxX;
	double MaxY;
	double MaxRadius;
	double rMAX;
public:	

	//Particle();

	Particle(double dMaxX,double dMaxY,double dRMAX)
	{
		MaxX = dMaxX;
		MaxY = dMaxY;
		rMAX = dRMAX;
		MaxRadius = 360;

		Losuj();
	}

	double X;
	double Y;
	double Alfa;
	double Probability;

	short sMarkToDelete;

	void Move(double newX,double newY, double newAlfa);



	inline void Losuj() //Generuj czastki ograniczone do wielosci mapy 
	{
		X = ((double)rand() / RAND_MAX) * MaxX; 
		Y = ((double)rand() / RAND_MAX) * MaxY;
		Alfa = ((double)rand() / RAND_MAX) * 360; //kat ograniczony do 360 stopni
		Probability = 0.0;
		sMarkToDelete = 0;
	}

	inline void Losuj(double X0,double Y0) //Generuj czastke w sasiedztwie innej czastki
	{
		double t = ((double)rand() / RAND_MAX) * 360; //kat ograniczony do 360 stopni
		double R1 =  ((double)rand() / RAND_MAX) * rMAX; //kat ograniczony do 360 stopni 

		X = abs( X0 + R1 * cos(t)); 
		Y = abs(Y0 + R1 * sin(t)); 
		
		if(X > MaxX)
			X = MaxX;

		if(Y > MaxY)
			Y = MaxY;

		Alfa = ((double)rand() / RAND_MAX) * 360; //kat ograniczony do 360 stopni
		Probability = 0.0;
		sMarkToDelete = 0;
	}

	inline void UpdateCountProbability(double scanTable[],int length)
	{
		double sumProbability = 0.0;

		for (int i = 0; i < length; i++)
		{
			if(sMarkToDelete > 0)
			{
				sMarkToDelete++;
				continue;
			}

			sumProbability +=  scanTable[i];
		}
	 Probability = sumProbability;
	}

	inline void ZaktualizujPrzesuniecie(double V,double dt) //liczy droge i aktualizuje przemieszczenie
	{
		double s = V * dt;

		ZaktualizujPrzesuniecie(s);
	}
	
	inline void ZaktualizujPrzesuniecie(double s) 
	{
			X += s * cos((Alfa * M_PI) / 180 ); // A'= [x + Sx, ...]
			Y += s * cos(((90 - Alfa) * M_PI) / 180); // A' [... ,y + Sy]
	}


	inline void ObrotCzastkiKat(double alfaNew)
	{
		X = X * cos((alfaNew * M_PI) / 180) - Y * sin((alfaNew * M_PI) / 180);
		Y = X * sin((alfaNew * M_PI) / 180) + Y * cos((alfaNew * M_PI) / 180);

		Alfa += alfaNew;
	}


	//const char* TransmitParticle(int index)
	//{
	//	stringstream temp; 
	//	string tmp = "rrrrrrwwww";
	//	//const char yy;
	//	
	//	temp << "#" << index << ";" << X << ";" << Y << ";" << Alfa << ";" << Probability << ";" << '\0';	
	//	//tmp = temp.str();

	//	//return tmp.c_str();
	//	return tmp.c_str();
	//}
};
