#include <stdio.h>
#include <sstream>
#include <math.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

#define M_PI       3.14159265358979323846
#define ODCHYLENIE 0.9
#define NEW_MIN 0
#define NEW_MAX 1

//bierzemy co 10 pomiar skanera
#define PRZLIECZENIE_DLA_POMIARU_SKANERA 10 


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

		inline double Normalize(double value,double min,double max) //normalizacja min max
	{
		return (((value - min) * (NEW_MAX - NEW_MIN)) / (max - min)) + NEW_MIN;
	}

		inline double getDistnace(MazeWall *wall,double alfa,double X2,double Y2)
{	
	double W;
	double Wx;
	double Wy;
	double dist = -1.0;
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

		if((wall->From_X <= X) && (X <= wall->To_X) && (wall->From_Y <= Y) && (Y <= wall->To_Y))
			dist = sqrt(pow(X - X2 ,2) + pow( Y - Y2,2)); //wartosc oczekiwana
	}

	return dist;
}

	inline void UpdateCountProbability(Room* box,int scanTable[],double angleTable[],int length)
	{
		double dist;
		double gauss;
		double sumProbability = 0.0;
		int iloscScian = box->ContainerWallCount();

		for (int i = 0; i < length; i = i + PRZLIECZENIE_DLA_POMIARU_SKANERA)
		{
			int test = 0;
			test++;

			for (int j = 0; j < iloscScian; j++)
			{
				dist =  getDistnace(&box->ContainerWallTable[j],angleTable[i],this->X,this->Y); //wartosc oczekiwana

				if(dist > 0)
				{
					double scan = (((double) scanTable[i]) / 1000);
				gauss =  Gauss2(scan,dist); //exp((-1 * pow(scanTable[i] - dist,2)) / ( 2 * ODCHYLENIE * ODCHYLENIE)) / (2 * M_PI * ODCHYLENIE);
				
				sumProbability +=  gauss;//Normalize(gauss,0,dist); 
				}
			}
		}

		Probability = sumProbability;
	}
		

	inline double Gauss2(double prop,double real)
{
double a,b,c,d;
double x = prop;
double delta = sqrt(ODCHYLENIE);
double ni = real;

a = 1 / (delta  *sqrt(2 * M_PI));
b = ni;
c = delta;
d = 0;

return (a * exp( pow(x - b,2) / (-2 * pow(c,2)))) + d; 
}
		
		
		/*
		double sumProbability = 0.0;
		double X;
		double Y;
		double dist;
		double alfa2;
		double b2;
		double gauss;

		double W;
		double Wx;
		double Wy;


		if(box != NULL)
		{
			for(int j = 0; j < box->ContainerWall.size(); j++)
			{
		for (int i = 0; i < length; i++)
		{
			/*alfa2 = tan(angleTable[i]);
			b2 = this->Y - (alfa2 * this->Y);*/

		//	X = (b2 - box->ContainerWall[j].B) / (box->ContainerWall[j].A - alfa2);			
		//	Y = ((box->ContainerWall[j].A  * b2) - (alfa2 * box->ContainerWall[j].B)) / (box->ContainerWall[j].A - alfa2);

		/*	W = alfa2 * box->ContainerWall[j].B + box->ContainerWall[j].A;
			Wx = b2 * box->ContainerWall[j].B + box->ContainerWall[j].C;
			Wy = alfa2 * box->ContainerWall[j].C - box->ContainerWall[j].A * b2;


			if(W == 0)
				continue;
			else*/

			/*{

			X = Wx/W;
			Y = Wy/W;*/


			/*if((box->ContainerWall[j].From_X <= X <= box->ContainerWall[j].To_X) && (box->ContainerWall[j].From_Y <= Y <= box->ContainerWall[j].To_Y))
			{
				dist =  getDistnace(&box->ContainerWall[j],angleTable[i],this->X,this->Y); //wartosc oczekiwana
					
					
					//sqrt(( X - this->X ) * ( X - this->X ) + ( Y - this->Y ) * ( Y - this->Y )); //wartosc oczekiwana
				gauss =  exp((-1 * pow(scanTable[i] - dist,2)) / ( 2 * ODCHYLENIE * ODCHYLENIE)) / (2 * M_PI * ODCHYLENIE);  
				
				sumProbability +=  Normalize(gauss,0,dist); 
			}
			else
	/*			continue;		
			}
		}
			}
		}
		Probability = sumProbability;

		
	}*/



	//inline double Distance(Room* box)
	//{


	//}

	inline void ZaktualizujPrzesuniecie(double V,double alfa,double dt) //liczy droge i aktualizuje przemieszczenie
	{
		double s = V * dt;

		ZaktualizujPrzesuniecie(s,alfa);
	}
	
	inline void ZaktualizujPrzesuniecie(double s,double  alfa)
	{
			X += s * cos((alfa * M_PI) / 180 ); // A'= [x + Sx, ...]
			Y += s * cos(((90 - alfa) * M_PI) / 180); // A' [... ,y + Sy]

			Alfa += alfa;
	}


//	inline void ObrotCzastkiKat(double alfaNew)
//	{
//		X = X * cos((alfaNew * M_PI) / 180) - Y * sin((alfaNew * M_PI) / 180);
	//	Y = X * sin((alfaNew * M_PI) / 180) + Y * cos((alfaNew * M_PI) / 180);

	//	Alfa += alfaNew;

//	}


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
