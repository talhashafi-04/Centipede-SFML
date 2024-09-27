#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void makeSpiderExist(int level, float spider[3]);
void makeScorpianExist(int level, float scorpian[3]);
//makespider / scorpian exist , check whether to craete them or not based on random value genrated , initialixing their positions randomly also

bool isFleaExists(float mushrooms[][6]);
bool isCentipede_not_exist(float centipede[30][30][12]);

//isCentipde notexist , returns true if no segment is left of centipedd , user wins // used to check whether user wins or losse



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void makeScorpianExist(int level, float scorpian[3])
{
	int temp;

	if (level > 0)
	{
		temp = rand() % 2;
		if (!temp)
		{
			scorpian[x] = 0;
			scorpian[y] = (rand() % 28 + 1) * boxPixelsY;
			scorpian[exists] = true;
		}
	}







}


void makeSpiderExist(int level, float spider[3])
{
	int temp;

	if (level > 0)
	{
		temp = rand() % 2;
		if (!temp)
		{
			if (rand() % 3)
				spider[x] = -2 * boxPixelsX;
			else
				spider[x] = resolutionX;
			spider[y] = (rand() % 7 + 22) * boxPixelsY;
			spider[exists] = true;
		}
	}







}




bool isFleaExists(float mushrooms[][6])
{
	int counter = 0;
	for (int i = 0; i < 200; i++)
	{
		if ((mushrooms[i][y] > 24 * boxPixelsY) && (mushrooms[i][exists] == true))
			counter++;

	}

	if (counter == 3)
		return true;
	else
		return false;
}


bool isCentipede_not_exist(float centipede[30][30][12])
{
	int flag = true;
	for (int j = 0; j < 30; j++)
	{
		if (centipede[j][0][exists])
		{
			for (int k = 0; k < 30; k++)
			{
				if (centipede[j][k][segmentExists])
				{
					if ((centipede[j][k][x] >= 0 && centipede[j][k][x] <= resolutionX) && (centipede[j][k][y] >= 0 && centipede[j][k][y] <= resolutionY))
						return false;
				}

			}

		}
	}

	if (flag)
		return  flag;
	else
		return false;

}

