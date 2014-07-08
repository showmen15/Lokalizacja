#define _CRT_SECURE_NO_WARNINGS 1
#define _SCL_SECURE_NO_WARNINGS 1


#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include <float.h>

using std::string;
using namespace std;


struct BoundingBox
{
public:
	double X_Left_Top;
	double Y_Left_Top;

	double X_Left_Bottom;
	double Y_Left_Bottom; 

	double X_Right_Top;
	double Y_Right_Top;

	double X_Right_Bottom;
	double Y_Right_Bottom; 

	BoundingBox()
	{
		X_Left_Top =
		X_Left_Bottom =
		Y_Left_Bottom = 
		X_Right_Bottom = DBL_MAX;//std::numeric_limits<double>::max();

		Y_Left_Top =
		X_Right_Top =
		Y_Right_Top = 
		Y_Right_Bottom = 0;
	}
};

class MazeWall 
{
private :
		double w;
	    double wa;
		double wb;


public :

	string Type;
	string		Id;
	double		Width;
	double		Height;
	string		Color;
	double 		From_X;
	double		From_Y;
	double		To_X;
	double		To_Y;

	double A;
	double B;
	double C;

	
	//void Calculate()
	//{
	//	A = (From_Y - To_Y) / (From_X - To_X);
	//	B = ((From_X * To_Y) - (To_X * From_Y)) / (From_X - To_X);
	//}

	void Calculate()
	{
		if(From_X == To_X)
		{
			A = 1;
			B = 0;
			C = From_X;
		}
		else if(From_Y == To_Y)
		{
			A = 0;
			B = 1;
			C = From_Y;
		}
		else
		{
			A = (From_Y - To_Y) / (From_X - To_X);
			B =  -1;
			C = ((From_X * To_Y) - (To_X * From_Y)) / (From_X - To_X);
		}

		
		
		//w = (To_X * From_Y  - From_X  * To_Y);
		//wa = To_Y - From_Y;
		//wb = To_X - From_X;

		//if(w == 0)
		//	;

		//A = wa / w;
		//B = wb / w;
	}
};

struct MazeSpaces
{
public:
	string Type;
	string SpaceId;
	string WallId;
};

struct Room
{

public:
	string SpaceId;

	vector<MazeWall> ContainerWall;

	BoundingBox Box; 

	int ContainerWallCount()
	{
		return ContainerWall.size();
	}
};


int conteins(vector<Room> rooms,string textToFind);

char* OpenFile(char *filename);

/*  Get Walls */
int GetMazeWalls(cJSON *json,MazeWall* & tableWalls);

int GetMazeSpaces(cJSON *json,MazeSpaces* & tableSpaces);

int GetRooms(MazeWall* wall,int WallsCount,MazeSpaces* spaces,int SpacesCount,Room* & rooms);

int AssignBoundingBox(Room* rooms,int RoomCount,BoundingBox* & box);

int  parseJasonFile(char *filename,BoundingBox* & bBox,Room* & rooms);