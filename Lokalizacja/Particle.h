#include <stdio.h>
#include <sstream>
#include <math.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

#define M_PI       3.14159265358979323846
#define ODCHYLENIE 5


struct Particle 
{
private:
	double MinX;
	double MaxX;
	double MinY;
	double MaxY;
	double MaxRadius;
	double rMAX;
public:	

	Particle()
	{

	}

	Particle(double dMinX,double dMaxX,double dMinY, double dMaxY,double dRMAX)
	{
		MinX = dMinX;
		MaxX = dMaxX;
		MinY = dMinY;
		MaxY = dMaxY;
		rMAX = dRMAX;
		MaxRadius = 360;

		Losuj2();
	}


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
		Y = ( (double)rand() / RAND_MAX) * MaxY;
		Alfa = ((double)rand() / RAND_MAX) * 360; //kat ograniczony do 360 stopni
		Probability = 0.0;
		sMarkToDelete = 0;
	}

	inline void Losuj2()
	{
		X = abs((MaxX - MinX) * ( (double)rand() / (double)RAND_MAX ) + MinX); 	//(MinX + ((double)  rand()) / MaxX);  //X = (MinX +  (double)rand() / RAND_MAX) * MaxX; 
		Y =  abs((MaxY - MinY) * ( (double)rand() / (double)RAND_MAX ) + MinY); //Y = (MinY + ((double)rand() / MaxY); //Y = (MinY + (double)rand() / RAND_MAX) * MaxY;
		
		Alfa = ((double)rand() / RAND_MAX) * 360; //kat ograniczony do 360 stopni
		Probability = 0.0;
		sMarkToDelete = 0;

	}

	inline void Losuj(double X0,double Y0, double alfa) //Generuj czastke w sasiedztwie innej czastki
	{
		double t = ((double)rand() / RAND_MAX) * 360; //kat ograniczony do 360 stopni
		double R1 =  ((double)rand() / RAND_MAX) * rMAX; //kat ograniczony do 360 stopni 

		X = abs( X0 + R1 * cos(t)); 
		Y = abs(Y0 + R1 * sin(t)); 
		
		if(X > MaxX)
			X = MaxX;

		if(Y > MaxY)
			Y = MaxY;

		Alfa =  alfa; //((double)rand() / RAND_MAX) * 360; //kat ograniczony do 360 stopni
		Probability = 0.0;
		sMarkToDelete = 0;
	}

	inline void UpdateCountProbability(Room* box,int scanTable[],double angleTable[],int length)
	{
		double sumProbability = 0.0;
		double X;
		double Y;
		double dist;
		double alfa2;
		double b2;
		double gauss;

		if(box != NULL)
		{
			for(int j = 0; j < box->ContainerWall.size(); j++)
			{
		for (int i = 0; i < length; i++)
		{
			alfa2 = tan(angleTable[i]);
			b2 = this->Y - (alfa2 * this->Y);

			X = (b2 - box->ContainerWall[j].B) / (box->ContainerWall[j].A - alfa2);			
			Y = ((box->ContainerWall[j].A  * b2) - (alfa2 * box->ContainerWall[j].B)) / (box->ContainerWall[j].A - alfa2);
			
			if((box->ContainerWall[j].From_X <= X <= box->ContainerWall[j].To_X) && (box->ContainerWall[j].From_Y <= Y <= box->ContainerWall[j].To_Y))
			{
				dist = sqrt(( X - this->X ) * ( X - this->X ) + ( Y - this->Y ) * ( Y - this->Y )); //wartosc oczekiwana
				gauss =  exp((-1 * pow(scanTable[i] - dist,2)) / ( 2 * ODCHYLENIE * ODCHYLENIE)) / (2 * M_PI * ODCHYLENIE);

				sumProbability +=  scanTable[i];
			}
			else
				continue;		
		}
			}
		}
		Probability = sumProbability;
	}

	inline double Distance(Room* box)
	{


	}

	inline void ZaktualizujPrzesuniecie(double V,double alfa,double dt) //liczy droge i aktualizuje przemieszczenie
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
