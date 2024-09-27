#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void updateCentipede(float  centipede[30][30][12]);
void changeColor(int level, sf::Sprite& centipedeSpritel1, sf::Sprite& centipedeSpritel2, sf::Sprite& centipedeSpriter1, sf::Sprite& centipedeSpriter2);
void twiceLength(float centipede[30][30][12]);
void extraLive(unsigned int& score, int& lives, sf::Sound& extraLivesound);

//change color , randomly changes head color by changing grb valuse of head
// twicelenght , if centipede fragment has eaten 5 mushrooms its lenght will fget doubled , function will first check the number of segment of curremt fragments and add same number asiigning their positions
// extra lives ; check for score and give binus lives




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





void updateCentipede(float  centipede[30][30][12])
{
	/*static int update = 1 ;


	for (int m = 0 ; m < 30 ; m++ )
		centipede [update][m][exists]  = true ;


	centipede [update][0][segmentExists] = true ;
	centipede [update][0][isleft] = false ;
	centipede [update][0][ishead] = true ;
	centipede [update][0][length] = 1  ;
	centipede [update][0][restricted] = false ;
	centipede [update][0][is_up] = false ;
	centipede [update][0][x] = gameRows/2 * boxPixelsX ;
	centipede [update][0][y] = gameRows/2 * boxPixelsX ;


	update++ ;
	*/


}


void changeColor(int level, sf::Sprite& centipedeSpritel1, sf::Sprite& centipedeSpritel2, sf::Sprite& centipedeSpriter1, sf::Sprite& centipedeSpriter2)

{
	if (level == 1)
		return;
	else
	{
		int r = rand() % 255;
		//int g = rand() % 255 ;
		int b = rand() % 255;



		centipedeSpritel2.setColor(sf::Color(r, 255, b, 255));
		centipedeSpriter2.setColor(sf::Color(r, 255, b, 255));
	}
}



void twiceLength(float centipede[30][30][12])
{

	for (int i = 0; i < 30; i++)
	{
		if (centipede[i][0][mushroomsEaten] >= 5)
		{

			centipede[i][0][mushroomsEaten] = 0;

			int length = 0;
			bool flag = true;
			for (int j = 0; j < 30; j++)
			{
				if (flag)
				{
					if (centipede[i][j][segmentExists])
						length++;
					else
						break;
				}


			}

			for (int j = length; j < 2 * length; j++)
			{
				if (centipede[i][length - 1][isleft])
				{
					centipede[i][j][segmentExists] = true;
					centipede[i][j][y] = centipede[i][j - 1][y];
					centipede[i][j][x] = centipede[i][j - 1][x] + boxPixelsX;
					centipede[i][j][isleft] = centipede[i][j - 1][isleft];
					centipede[i][j][ishead] = false;
				}
				else
				{
					centipede[i][j][segmentExists] = true;
					centipede[i][j][y] = centipede[i][j - 1][y];
					centipede[i][j][x] = centipede[i][j - 1][x] - boxPixelsX;
					centipede[i][j][isleft] = centipede[i][j - 1][isleft];
					centipede[i][j][ishead] = false;
				}
			}




		}

	}
}
void extraLive(unsigned int& score, int& lives, sf::Sound& extraLivesound)
{
	static bool flag1 = true, flag2 = true, flag3 = true, flag4 = true;

	if (flag1)
	{
		if (score > 10000)
		{
			extraLivesound.play();
			if (lives < 6)
				lives++;
			flag1 = false;
		}
	}
	if (flag2)
	{
		if (score > 12000)
		{
			extraLivesound.play();
			if (lives < 6)
				lives++;
			flag2 = false;
		}
	}
	if (flag3)
	{
		if (score > 15000)
		{
			extraLivesound.play();
			if (lives < 6)
				lives++;
			flag3 = false;
		}
	}
	if (flag3)
	{
		if (score > 20000)
		{
			extraLivesound.play();
			if (lives < 6)
				lives++;
			flag3 = false;
		}
	}
}