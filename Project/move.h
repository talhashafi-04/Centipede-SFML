#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void movePlayer(sf::Clock& PlayerClock, float player[]);
void moveCentipede(float centipede[30][30][12], float mushrooms[200][6], sf::Clock  centipedeClock[][30], int centipedeSpeed);
void moveBullet(float bullet[], sf::Clock& bulletClock, float player[], bool& bulletbulletfire, int bullet_speed);
void moveFlea(sf::Clock& fleaClock, float flea[], float mushrooms[200][6], float centipede[30][30][12]);
void moveScorpian(sf::Clock& scorpianClock, float scorpian[], float mushrooms[200][6], float centipede[30][30][12]);
void moveSpider(sf::Clock& spiderClock, float spider[], float mushrooms[200][6], float centipede[30][30][12]);
//move player : update position of player whenever certain keys are pressed
//move centipede , changing position of every centipede segment to create effect of movement
// move bullet : simply moving bullet upward untill reaches top 
//move flea : simply smovement of flea from top to bottom
//move scorpian : simply moving from left to right on screen , turning every mushroom red
//movr spider : complex multidirectional movement truly based on rand() values





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





void moveSpider(sf::Clock& spiderClock, float spider[], float mushrooms[200][6], float centipede[30][30][12])
{
	static bool flag = true;
	if (spiderClock.getElapsedTime().asMilliseconds() < 100 || spider[exists] == false)
		return;
	spiderClock.restart();
	static bool is_up = false;
	static bool is_down = false;
	static bool is_up_right = false;
	static bool is_down_right = false;
	static bool is_up_left = false;
	static bool is_down_left = false;


	if (flag)
	{
		if (spider[x] == -2 * boxPixelsX)
			is_down_right = true;
		else
			is_down_left = true;


		flag = false;
	}
	if (is_down_right)
	{
		if (spider[y] < resolutionY - boxPixelsY)
		{
			spider[x] += boxPixelsX;
			spider[y] += boxPixelsY;
		}
		else
		{
			is_down_right = false;


			int temp = rand() % 3;
			if (temp == 0)
				is_up_right = true;
			else if (temp == 1)
				is_up_left = true;
			else
				is_up = true;
		}


	}
	else if (is_down_left)
	{
		if (spider[y] < resolutionY - boxPixelsY)
		{
			spider[x] -= boxPixelsX;
			spider[y] += boxPixelsY;
		}
		else
		{
			is_down_left = false;


			int temp = rand() % 3;
			if (temp == 0)
				is_up_right = true;
			else if (temp == 1)
				is_up_left = true;
			else
				is_up = true;
		}
	}

	else if (is_down)
	{
		if (spider[y] < resolutionY - boxPixelsY)
		{

			spider[y] += boxPixelsY;
		}
		else
		{
			is_down = false;


			int temp = rand() % 3;
			if (temp == 0)
				is_up_right = true;
			else if (temp == 1)
				is_up_left = true;
			else
				is_up = true;

		}


	}
	else if (is_up)
	{
		if (spider[y] > (rand() % 6 + 20) * boxPixelsY)
		{

			spider[y] -= boxPixelsY;
		}
		else
		{
			is_up = false;


			int temp = rand() % 3;
			if (temp == 0)
				is_down_right = true;
			else if (temp == 1)
				is_down_left = true;
			else
				is_down = true;
		}

	}
	else if (is_up_right)
	{
		if (spider[y] > (rand() % 8 + 19) * boxPixelsY)
		{

			spider[y] -= boxPixelsY;
			spider[x] += boxPixelsX;
		}
		else
		{
			is_up_right = false;



			int temp = rand() % 4;
			if (temp == 0 || temp == 3)
				is_down_right = true;
			else if (temp == 1)
				is_down_left = true;
			else
				is_down = true;
		}

	}

	else if (is_up_left)
	{
		if (spider[y] > (rand() % 8 + 19) * boxPixelsY)
		{

			spider[y] -= boxPixelsY;
			spider[x] -= boxPixelsX;
		}
		else
		{
			is_up_left = false;



			int temp = rand() % 3;
			if (temp == 0)
				is_down_right = true;
			else if (temp == 1)
				is_down_left = true;
			else
				is_down = true;
		}

	}

	for (int i = 0; i < 200; i++)
	{
		if ((mushrooms[i][x] == spider[x] || mushrooms[i][x] == spider[x] + boxPixelsX) && mushrooms[i][y] == spider[y] && mushrooms[i][exists])
		{
			mushrooms[i][exists] = false;
		}
	}

	if (spider[x] > resolutionX || spider[x] < -60)
	{
		spider[exists] = false;
		flag = true;
	}

}



void moveScorpian(sf::Clock& scorpianClock, float scorpian[], float mushrooms[200][6], float centipede[30][30][12])
{
	if (scorpianClock.getElapsedTime().asMilliseconds() < 80)
		return;
	scorpianClock.restart();

	if (scorpian[x] < resolutionX)
	{
		scorpian[x] += boxPixelsX;
		for (int i = 0; i < 200; i++)
		{
			if (mushrooms[i][exists] && mushrooms[i][x] == scorpian[x] && mushrooms[i][y] == scorpian[y])
			{
				mushrooms[i][isred] = true;
			}
		}

	}
	else
	{
		scorpian[exists] = false;
	}



}
void moveFlea(sf::Clock& fleaClock, float flea[3], float mushrooms[200][6], float centipede[30][30][12])
{
	if (fleaClock.getElapsedTime().asMilliseconds() < 60)
		return;
	fleaClock.restart();

	if (flea[y] < resolutionY)
	{
		flea[y] += boxPixelsY;

		int temp = rand() % 3;
		if (!temp && flea[y] <= 28 * boxPixelsY)
		{
			for (int i = 0; i < 200; i++)
			{
				if (!mushrooms[i][exists])
				{

					mushrooms[i][exists] = true;
					mushrooms[i][isred] = false;
					mushrooms[i][lives] = 2;
					mushrooms[i][x] = flea[x];
					mushrooms[i][y] = flea[y];
					break;
				}
			}
		}


	}
	else
		flea[exists] = false;
}




void movePlayer(sf::Clock& playerClock, float player[])
{
	if (playerClock.getElapsedTime().asMilliseconds() < 100 - player_speed)
		return;
	playerClock.restart();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player[x] > 0)
	{
		player[x] -= boxPixelsX;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player[x] < resolutionX - boxPixelsX)
	{
		player[x] += boxPixelsX;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player[y] > resolutionY - 5 * boxPixelsY)
	{
		player[y] -= boxPixelsY;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player[y] < resolutionY - boxPixelsY)
	{
		player[y] += boxPixelsY;
	}

}

void moveCentipede(float centipede[30][30][12], float mushrooms[200][6], sf::Clock  centipedeClock[][30], int centipedeSpeed)
{

	for (int i = 0; i < 30; i++)
	{
		if (centipede[i][0][exists])
		{
			for (int j = 0; j < 30; j++)
			{
				if (centipede[i][j][segmentExists] && centipede[i][j][ishead])
				{
					if (centipedeClock[i][j].getElapsedTime().asMilliseconds() < 250 - centipede[i][j][speed])
					{
						continue;
					}
					else
					{
						centipedeClock[i][j].restart();
					}



					{
						float temp1[4];
						float temp2[4];

						temp1[x] = centipede[i][j][x];
						temp1[y] = centipede[i][j][y];
						temp1[isleft] = centipede[i][j][isleft];
						for (int t = j + 1; t < 30; t++)
						{
							if (centipede[i][t][segmentExists]) //&& (!centipede [i][t][ishead])
							{
								temp2[x] = centipede[i][t][x];
								temp2[y] = centipede[i][t][y];
								temp2[isleft] = centipede[i][t][isleft];

								centipede[i][t][x] = temp1[x];
								centipede[i][t][y] = temp1[y];
								centipede[i][t][isleft] = temp1[isleft];

								temp1[x] = temp2[x];
								temp1[y] = temp2[y];
								temp1[isleft] = temp2[isleft];


							}
							else
							{
								break;
							}
						}
					}




					if (centipede[i][j][isleft])
					{
						if (centipede[i][j][x] > 0)
						{
							centipede[i][j][x] -= boxPixelsX;
						}
						else
						{
							if (centipede[i][j][is_up])
							{
								if (centipede[i][j][y] > 25 * boxPixelsY)
									centipede[i][j][y] -= boxPixelsY;
								else
									centipede[i][j][is_up] = false;
							}
							else
							{
								if (centipede[i][j][y] < 29 * boxPixelsY)
									centipede[i][j][y] += boxPixelsY;
								else
								{
									centipede[i][j][is_up] = true;
									centipede[i][j][y] -= boxPixelsY;
								}
							}
							centipede[i][j][isleft] = false;

						}

					}
					else
					{
						if (centipede[i][j][x] < resolutionX - boxPixelsX)
						{
							centipede[i][j][x] += boxPixelsX;

						}
						else
						{
							if (centipede[i][j][is_up])
							{
								if (centipede[i][j][y] > 25 * boxPixelsY)
									centipede[i][j][y] -= boxPixelsY;
								else
									centipede[i][j][is_up] = false;
							}
							else
							{
								if (centipede[i][j][y] < 29 * boxPixelsY)
									centipede[i][j][y] += boxPixelsY;
								else
								{
									centipede[i][j][is_up] = true;
									centipede[i][j][y] -= boxPixelsY;
								}
							}
							centipede[i][j][isleft] = true;

						}

					}
				}
			}
		}
	}




}

void moveBullet(float bullet[], sf::Clock& bulletClock, float player[], bool& bulletfire, int bullet_speed) {
	if (bulletClock.getElapsedTime().asMilliseconds() < 50 - bullet_speed)
		return;

	bulletClock.restart();
	bullet[y] -= boxPixelsY;
	if (bullet[y] < 0)
	{
		bullet[exists] = true;


		bullet[x] = player[x];
		bullet[y] = player[y] - boxPixelsY;
		bulletfire = true;


	}

}

