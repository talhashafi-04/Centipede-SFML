#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// The following exist purely for readability.

const int x = 0;
const int y = 1;
const int exists = 2;
const int lives = 3;
const int isleft = 3;
const int length = 4;
const int isred = 4;
const int segmentExists = 5;
const int ishead = 6;
const int restricted = 7;
const int is_up = 8;
const int mushroomsEaten = 9;
const int speed = 10;
const int is_fast = 11;


const int resolutionX = 960;
const int resolutionY = 960;
const int boxPixelsX = 32;
const int boxPixelsY = 32;
const int gameRows = resolutionX / boxPixelsX; // Total rows on grid
const int gameColumns = resolutionY / boxPixelsY; // Total columns on grid

//Following also exists only for accessibility
const int initial_length = 12;
const int player_speed = 65;        //(10 -- 10) 

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void drawFlea(sf::Clock& fleaCrawlingClock, float flea[], sf::RenderWindow& window, sf::Sprite fleaSprite);
void drawPlayer(sf::RenderWindow& window, float player[], sf::Sprite& playerSprite);
void drawBullet(sf::RenderWindow& window, float bullet[], sf::Sprite& bulletSprite);
void drawMushrooms(sf::RenderWindow& window, float  mushrooms[][6], sf::Sprite& mushroomSprite1, sf::Sprite& mushroomSprite2);
void drawCentipede(sf::RenderWindow& window, sf::Clock& crawlingClock, float centipede[30][30][12], sf::Sprite& centipedeSpritel1, sf::Sprite& centipedeSpritel2, sf::Sprite& centipedeSpriter1, sf::Sprite& centipedeSpriter2);
void drawScorpian(sf::Clock& scorpianCrawlingClock, float scorpian[], sf::RenderWindow& window, sf::Sprite scorpianSprite);
void drawSpider(sf::Clock& spiderCrawlingClock, float spider[], sf::RenderWindow& window, sf::Sprite spiderSprite);
//THe functions above are just for displaying game objects like player , centipede ,bullet etc on the window
// some of them have crawling clock integrated which control rate of change of rectsizes to craetemovemen effect












/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void drawPlayer(sf::RenderWindow& window, float player[], sf::Sprite& playerSprite)
{
	playerSprite.setPosition(player[x], player[y]);
	window.draw(playerSprite);
}

void drawBullet(sf::RenderWindow& window, float bullet[], sf::Sprite& bulletSprite)
{
	bulletSprite.setPosition(bullet[x], bullet[y]);
	window.draw(bulletSprite);
}


void drawMushrooms(sf::RenderWindow& window, float mushrooms[200][6], sf::Sprite& mushroomSprite1, sf::Sprite& mushroomSprite2)
{
	for (int i = 0; i < 200; i++)
	{
		if (mushrooms[i][exists])
		{
			if (mushrooms[i][lives] >= 2)
			{
				mushroomSprite1.setPosition(mushrooms[i][x], mushrooms[i][y]);

				if (mushrooms[i][isred])
					mushroomSprite1.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));
				else
					mushroomSprite1.setTextureRect(sf::IntRect(0, boxPixelsY, boxPixelsX, boxPixelsY));

				window.draw(mushroomSprite1);
			}
			else if (mushrooms[i][lives] == 1)
			{
				mushroomSprite2.setPosition(mushrooms[i][x], mushrooms[i][y]);
				if (mushrooms[i][isred])
					mushroomSprite2.setTextureRect(sf::IntRect(3 * boxPixelsX, 0, boxPixelsX, boxPixelsY));
				else
					mushroomSprite2.setTextureRect(sf::IntRect(3 * boxPixelsX, boxPixelsY, boxPixelsX, boxPixelsY));

				window.draw(mushroomSprite2);
			}
		}

	}

}


void drawCentipede(sf::RenderWindow& window, sf::Clock& crawlingClock, float  centipede[30][30][12], sf::Sprite& centipedeSpritel1, sf::Sprite& centipedeSpritel2, sf::Sprite& centipedeSpriter1, sf::Sprite& centipedeSpriter2)
{
	static int rect = 1;
	if (crawlingClock.getElapsedTime().asMilliseconds() > 150)
	{
		crawlingClock.restart();
		if (rect < 7)
			rect++;
		else
			rect = 1;

	}

	centipedeSpritel1.setTextureRect(sf::IntRect(rect * (6 * boxPixelsX / 8.0) + (rect - 1) * (boxPixelsX / 8.0), 0, boxPixelsX, boxPixelsY));
	//centipedeSpritel2.setTextureRect(sf::IntRect ( rect * (boxPixelsX - boxPixelsX/ 4 ), 0, boxPixelsX, boxPixelsY));
	centipedeSpriter1.setTextureRect(sf::IntRect(rect * (boxPixelsX - boxPixelsX / 4), 0, boxPixelsX, boxPixelsY));
	//centipedeSpriter2.setTextureRect(sf::IntRect ( rect * (boxPixelsX - boxPixelsX/ 4 ), 0, boxPixelsX, boxPixelsY));
	for (int j = 0; j < 30; j++)
	{
		if (centipede[j][0][exists] == true)
		{
			for (int i = 0; i < 30; i++)
			{


				if (centipede[j][i][isleft] == true)
				{


					if (centipede[j][i][segmentExists] == true)
					{
						if (centipede[j][i][ishead])
						{
							centipedeSpritel2.setPosition(centipede[j][i][x], centipede[j][i][y]);

							window.draw(centipedeSpritel2);
						}
						else
						{

							centipedeSpritel1.setPosition(centipede[j][i][x], centipede[j][i][y]);

							window.draw(centipedeSpritel1);
						}

					}


				}
				else
				{

					if (centipede[j][i][segmentExists] == true)
					{
						if (centipede[j][i][ishead])
						{
							centipedeSpritel2.setPosition(centipede[j][i][x], centipede[j][i][y]);

							window.draw(centipedeSpritel2);
						}
						else
						{
							centipedeSpritel1.setPosition(centipede[j][i][x], centipede[j][i][y]);

							window.draw(centipedeSpritel1);
						}

					}

				}


			}
		}
	}
}


void drawScorpian(sf::Clock& scorpianCrawlingClock, float scorpian[3], sf::RenderWindow& window, sf::Sprite scorpianSprite)
{

	static int rect = 1;
	if (scorpianCrawlingClock.getElapsedTime().asMilliseconds() > 1500)
	{
		scorpianCrawlingClock.restart();
		if (rect < 4)
			rect++;
		else
			rect = 1;

	}


	if (rect == 1)
		scorpianSprite.setTextureRect(sf::IntRect(0, 0, 2 * boxPixelsX, boxPixelsY));
	else if (rect == 2)
		scorpianSprite.setTextureRect(sf::IntRect(2 * boxPixelsX, 0, 2 * boxPixelsX, boxPixelsY));
	else if (rect == 3)
		scorpianSprite.setTextureRect(sf::IntRect(4 * boxPixelsX, 0, 2 * boxPixelsX, boxPixelsY));
	else if (rect == 4)
		scorpianSprite.setTextureRect(sf::IntRect(6 * boxPixelsX, 0, 2 * boxPixelsX, boxPixelsY));





	scorpianSprite.setPosition(scorpian[x], scorpian[y]);
	window.draw(scorpianSprite);


}
void drawFlea(sf::Clock& fleaCrawlingClock, float flea[3], sf::RenderWindow& window, sf::Sprite fleaSprite)
{
	static int rect = 0;
	if (fleaCrawlingClock.getElapsedTime().asMilliseconds() > 150)
	{
		fleaCrawlingClock.restart();
		if (rect < 5)
			rect++;
		else
			rect = 1;

	}


	if (rect = 1)
		fleaSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));
	else if (rect == 2)
		fleaSprite.setTextureRect(sf::IntRect(boxPixelsX, 0, boxPixelsX, boxPixelsY));
	else if (rect == 3)
		fleaSprite.setTextureRect(sf::IntRect(0, boxPixelsY, boxPixelsX, boxPixelsY));
	else if (rect == 4)
		fleaSprite.setTextureRect(sf::IntRect(boxPixelsX, boxPixelsY, boxPixelsX, boxPixelsY));




	fleaSprite.setPosition(flea[x], flea[y]);
	window.draw(fleaSprite);

}
void drawSpider(sf::Clock& spiderCrawlingClock, float spider[3], sf::RenderWindow& window, sf::Sprite spiderSprite)
{
	static int rect = -1;
	if (spiderCrawlingClock.getElapsedTime().asMilliseconds() > 150)
	{
		spiderCrawlingClock.restart();
		if (rect < 7)
			rect++;
		else
			rect = 0;

	}

	spiderSprite.setTextureRect(sf::IntRect(rect * 60, 0, 60, boxPixelsY));





	spiderSprite.setPosition(spider[x], spider[y]);
	window.draw(spiderSprite);

}