#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//BOOL COLLISION DETECTION

bool collisionCentipede_player(float centipede[30][30][12], float player[]);
bool collisionMushroom_player(float mushrooms[200][6], float player[]);
bool collisionFlea_Player(float flea[3], float palyer[2]);
bool collisionScorpian_Player(float scorpian[], float player[]);
bool collisionSpider_Player(float spider[], float player[]);

// all other chaks for collision with enemies or poisunous mushroom





///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//VOID COLLISION DETECTION

void collisionBullet_Mushroom(float bullet[], float mushrooms[200][6], float player[], bool& bulletfire, unsigned int& score);
void collisionCentipede_mushroom(float centtipede[30][30][12], float mushrooms[200][6], sf::Sound& mushroomeatsound);
void collisionCentipede_bullet(float player[], float centipede[30][30][12], float bullet[3], float mushrooms[200][6], unsigned int& score, int level, sf::Sound& killsound);
void collisionBullet_Flea(float bullet[], float flea[], float mushrooms[][6]);
void collisionBullet_Scorpian(sf::RenderWindow& window, float bullet[], float scorpian[], float mushrooms[][6], float player[], unsigned int& score, sf::Sound& scorpiandeathSound, sf::Text& scorpiandeathScore);
void collisionBullet_Spider(sf::RenderWindow& window, float bullet[], float spider[], sf::Sprite& spiderSprite, float player[], unsigned int& score, sf::Sound& spiderdeathSound);

//bullet mushroom : checking for collision and decrementing lives of mushroom
//centipedemushroom : checking for collisiom and remove mushrooom from existence , u turning the centipede
//centipede bullet : cheacking for collision and then removing that segment , fragment behind them are transfered to a new index which serves as an independent centipede
//bulletflea , bulletscorpian , bullet spider ; simply looking for collision and removing thsee enemeis , increasing the score 



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




bool collisionCentipede_player(float centipede[30][30][12], float player[])
{
	for (int j = 0; j < 30; j++)
	{
		if (centipede[j][0][exists])
		{
			for (int k = 0; k < 30; k++)
			{
				if (centipede[j][k][segmentExists])
				{
					if (centipede[j][k][x] == player[x] && centipede[j][k][y] == player[y])
					{
						return true;
					}
				}

			}

		}
	}
	return false;


}

bool collisionScorpian_Player(float scorpian[], float player[])
{
	if ((player[x] == scorpian[x] || player[x] == scorpian[x] + boxPixelsX) && player[y] == scorpian[y] && scorpian[exists])
	{
		scorpian[exists] = false;
		return true;
	}
	else
		return false;
}

bool collisionSpider_Player(float spider[], float player[])
{

	if ((player[x] == spider[x] || player[x] == spider[x] + boxPixelsX) && player[y] == spider[y] && spider[exists])
	{
		spider[exists] = false;
		return true;
	}
	else
		return false;
}



bool collisionFlea_Player(float flea[3], float player[2])
{
	if (player[x] == flea[x] && player[y] == flea[y])
		return true;
	else
		return false;
}

bool collisionMushroom_player(float mushrooms[200][6], float player[])
{
	for (int i = 0; i < 200; i++)
	{
		if (mushrooms[i][exists] && mushrooms[i][isred])
		{
			if (player[x] == mushrooms[i][x] && player[y] == mushrooms[i][y])
			{
				return true;
			}


		}
	}
	return false;


}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void collisionBullet_Mushroom(float bullet[], float mushrooms[200][6], float player[], bool& bulletfire, unsigned int& score)
{
	for (int i = 0; i < 200; i++)

	{
		if ((bullet[x] < mushrooms[i][x] + boxPixelsX / 2 && bullet[x] > mushrooms[i][x] - boxPixelsX / 2) && (bullet[y] < mushrooms[i][y] + boxPixelsY / 2 && bullet[y] > mushrooms[i][y] - boxPixelsY / 2) && !(player[x] == mushrooms[i][x] && player[y] == mushrooms[i][y]))
		{
			mushrooms[i][lives]--;
			bullet[exists] = true;
			bullet[x] = player[x];
			bullet[y] = player[y] - boxPixelsY;
			bulletfire = true;
			if (mushrooms[i][lives] == 0)
			{


				/*

				int xVAL = rand () % 30 ;
				int yVAL = (rand() * rand () - rand () )% 25 ;

				if (xVAL < 0 )
				xVAL = -xVAL  ;
				if (yVAL < 0 )
				yVAL = -yVAL  ;

				*/

				mushrooms[i][x] = -10;
				mushrooms[i][y] = -10;
				mushrooms[i][exists] = false;
				score += 1;

			}
		}

	}


}
void collisionCentipede_mushroom(float centipede[30][30][12], float mushrooms[200][6], sf::Sound& mushroomeatsound)
{


	for (int j = 0; j < 30; j++)
	{
		if (centipede[j][0][exists])
		{
			for (int k = 0; k < 30; k++)
			{
				if (centipede[j][k][isleft])
				{
					for (int i = 0; i < 200; i++)
					{
						if (centipede[j][k][x] == mushrooms[i][x] && centipede[j][k][y] == mushrooms[i][y] && centipede[j][k][ishead] && mushrooms[i][exists])
						{
							mushroomeatsound.play();
							mushrooms[i][exists] = false;
							centipede[j][0][mushroomsEaten] += 1;
							if (centipede[j][k][is_up] && centipede[j][k][y] != 25 * boxPixelsY)
							{
								centipede[j][k][x] += boxPixelsX;
								centipede[j][k][y] -= boxPixelsY;
							}
							else
							{
								centipede[j][k][x] += boxPixelsX;
								if (centipede[j][k][y] != 29 * boxPixelsY)
									centipede[j][k][y] += boxPixelsY;
							}

							centipede[j][k][isleft] = false;
						}
					}
				}
				else
				{
					for (int i = 0; i < 200; i++)
					{
						if (centipede[j][k][ishead] && centipede[j][k][x] == mushrooms[i][x] && centipede[j][k][y] == mushrooms[i][y] && mushrooms[i][exists])
						{
							mushroomeatsound.play();
							centipede[j][0][mushroomsEaten] += 1;
							mushrooms[i][exists] = false;
							if (centipede[j][k][is_up] && centipede[j][k][y] != 25 * boxPixelsY)
							{
								centipede[j][k][y] -= boxPixelsY;
								centipede[j][k][x] -= boxPixelsX;

							}
							else
							{
								if (centipede[j][k][y] != 29 * boxPixelsY)
									centipede[j][k][y] += boxPixelsY;

								centipede[j][k][x] -= boxPixelsX;
							}


							centipede[j][k][isleft] = true;
						}
					}
				}
			}

		}

	}
}

void collisionCentipede_bullet(float player[], float centipede[30][30][12], float bullet[3], float mushrooms[200][6], unsigned int& score, int level, sf::Sound& killsound)
{
	for (int j = 0; j < 30; j++)
	{

		if (centipede[j][0][exists])
		{
			for (int k = 0; k < 30; k++)
			{
				if (centipede[j][k][segmentExists])
				{

					if (centipede[j][k][x] == bullet[x] && centipede[j][k][y] == bullet[y])
					{

						bullet[y] = player[y];
						bullet[x] = player[x];
						centipede[j][0][mushroomsEaten] = 0;

						for (int o = 199; o >= 0; o--)
						{
							if (!mushrooms[o][exists])
							{
								mushrooms[o][lives] = 2;
								mushrooms[o][exists] = true;
								if (centipede[j][k][y] > 24 * boxPixelsY)
									mushrooms[o][isred] = true;
								mushrooms[o][x] = centipede[j][k][x];
								mushrooms[o][y] = centipede[j][k][y];
								break;
							}
						}



						if (centipede[j][k][ishead])
						{
							killsound.play();

							score += 10;
							if (level < 3)
							{
								centipede[j][0][exists] = false;
								for (int q = 0; q < 30; q++)
									centipede[j][q][segmentExists] = false;
							}
							else
							{

								centipede[j][k][segmentExists] = false;

								float temp1[4];
								float temp2[4];

								temp1[x] = centipede[j][k + 1][x];
								temp1[y] = centipede[j][k + 1][y];
								temp1[isleft] = centipede[j][k + 1][isleft];



								for (int t = k + 2; t < 30; t++)
								{
									if (centipede[j][t][segmentExists]) //&& (!centipede [i][t][ishead])
									{
										temp2[x] = centipede[j][t][x];
										temp2[y] = centipede[j][t][y];
										temp2[isleft] = centipede[j][t][isleft];

										centipede[j][t][x] = temp1[x];
										centipede[j][t][y] = temp1[y];
										centipede[j][t][isleft] = temp1[isleft];

										temp1[x] = temp2[x];
										temp1[y] = temp2[y];
										temp1[isleft] = temp2[isleft];


									}
									else
									{
										break;
									}
								}



								centipede[j][k + 1][ishead] = true;
								centipede[j][k + 1][y] += boxPixelsY;

								if (centipede[j][k + 1][isleft])
									centipede[j][k + 1][isleft] = false;
								else
									centipede[j][k + 1][isleft] = true;



							}


						}
						else
						{
							score += 20;

							float temp1[4];
							float temp2[4];

							temp1[x] = centipede[j][k + 1][x];
							temp1[y] = centipede[j][k + 1][y];
							temp1[isleft] = centipede[j][k + 1][isleft];



							for (int t = k + 2; t < 30; t++)
							{
								if (centipede[j][t][segmentExists]) //&& (!centipede [i][t][ishead])
								{
									temp2[x] = centipede[j][t][x];
									temp2[y] = centipede[j][t][y];
									temp2[isleft] = centipede[j][t][isleft];

									centipede[j][t][x] = temp1[x];
									centipede[j][t][y] = temp1[y];
									centipede[j][t][isleft] = temp1[isleft];

									temp1[x] = temp2[x];
									temp1[y] = temp2[y];
									temp1[isleft] = temp2[isleft];


								}
								else
								{
									break;
								}
							}

							for (int t = 0; t < 30; t++)
							{
								if (centipede[t][0][exists] == false)
								{
									for (int d = 0; d < 30; d++)
										centipede[t][d][exists] = true;
									for (int q = 0, w = k + 1; w < 30; q++, w++)
									{
										if (centipede[j][w][segmentExists])
										{
											centipede[t][q][segmentExists] = true;
											centipede[t][q][x] = centipede[j][w][x];
											centipede[t][q][y] = centipede[j][w][y];
											centipede[t][q][isleft] = centipede[j][w][isleft];
										}
										else
										{
											break;
										}
									}

									centipede[t][0][ishead] = true;
									centipede[t][0][mushroomsEaten] = 0;
									centipede[t][0][y] += boxPixelsY;








									if (centipede[t][0][isleft])
									{

										centipede[t][0][isleft] = false;
									}
									else
									{

										centipede[t][0][isleft] = true;
									}

									break;
								}
							}

							for (int t = k; t < 30; t++)
								centipede[j][t][segmentExists] = false;





						}




					}

				}

			}
		}

	}

}


void collisionBullet_Spider(sf::RenderWindow& window, float bullet[], float spider[], sf::Sprite& spiderSprite, float player[], unsigned int& score, sf::Sound& spiderdeathSound)
{
	static bool showScore = false;
	static sf::Clock showScoreClock;
	static int distance = 0;


	if ((bullet[x] == spider[x] || bullet[x] == spider[x] + boxPixelsX) && bullet[y] == spider[y] && spider[exists] && player[y] != spider[y])
	{
		spiderdeathSound.play();
		spider[exists] = false;


		distance = abs(player[y] - spider[y]);
		showScore = true;
		showScoreClock.restart();
		if (distance == boxPixelsY)
			score += 900;
		else if (distance == 2 * boxPixelsY)
			score += 600;
		else
			score += 300;

	}


	if (showScore)
	{
		if (showScoreClock.getElapsedTime().asMilliseconds() < 2000)
		{
			if (distance == boxPixelsY)
				spiderSprite.setTextureRect(sf::IntRect(120, boxPixelsX, 60, boxPixelsY));
			else if (distance == 2 * boxPixelsY)
				spiderSprite.setTextureRect(sf::IntRect(60, boxPixelsX, 60, boxPixelsY));
			else
				spiderSprite.setTextureRect(sf::IntRect(0, boxPixelsX, 60, boxPixelsY));



			spiderSprite.setPosition(spider[x], spider[y]);
			window.draw(spiderSprite);
		}
		else
		{
			showScore = false;
		}
	}
}


void collisionBullet_Scorpian(sf::RenderWindow& window, float bullet[], float scorpian[], float mushrooms[][6], float player[], unsigned int& score, sf::Sound& scorpiandeathSound, sf::Text& scorpiandeathScore)
{
	static bool showScore = false;
	static sf::Clock showScoreClock;

	if ((bullet[x] == scorpian[x] || bullet[x] == scorpian[x] + boxPixelsX) && bullet[y] == scorpian[y] && scorpian[exists] && player[y] != scorpian[y])
	{

		scorpiandeathSound.play();
		scorpian[exists] = false;
		score += 1000;
		showScoreClock.restart();
		showScore = true;



	}

	if (showScore)
	{
		if (showScoreClock.getElapsedTime().asMilliseconds() < 2000)
		{
			scorpiandeathScore.setPosition(scorpian[x], scorpian[y]);
			window.draw(scorpiandeathScore);
		}
		else
		{
			showScore = false;
		}
	}
}
void collisionBullet_Flea(float bullet[], float flea[], float mushrooms[200][6])
{
	if (bullet[x] == flea[x] && bullet[y] == flea[y])
	{
		flea[exists] = false;

		// for ( int i = 0 ; i  < 200 ; i++)
		// {

		// 	if ( ! mushrooms [i][exists])
		// 	{

		// 		mushrooms [i][exists]= true ;
		// 		mushrooms [i][isred]= false ;
		// 		mushrooms [i][lives]= 2 ;
		// 		if(flea [y] > 24)
		// 		mushrooms [i][isred] = true ;
		// 		mushrooms [i][x]= flea [x] ;
		// 		mushrooms [i][y] = flea [y] ;
		// 		break ;

		// 	}
		// }

	}
}






















/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
