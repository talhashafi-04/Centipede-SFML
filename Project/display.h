#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Windows.h>


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void showScore(unsigned int& score, sf::Text& Score);
void showLevel(int& level, sf::Text& Level);
void showLives(sf::RenderWindow& window, int& lives, sf::Sprite& livesSprite);
void winEffects(sf::Sound  bonusSound);
void lostEffects(sf::RenderWindow& window, float mushrooms[200][6], sf::Sound deathSound, sf::Sound mushroomSound, sf::Sprite& mushroomSprite1, sf::Sprite& mushroomSprite2);
//used for showing score and level  and lives
// when user wins winefffeeect are added and when user loss , lost affects area added




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void showScore(unsigned int& score, sf::Text& Score)
{
	Score.setString("SCORE :  " + std::to_string(score));


}

void showLevel(int& level, sf::Text& Level)
{
	Level.setString("LEVEL :  " + std::to_string(level));


}


void showLives(sf::RenderWindow& window, int& playerlives, sf::Sprite& livesSprite)
{
	for (int i = 0; i < playerlives; i++)
	{
		livesSprite.setPosition(18.5 * boxPixelsX + 2 * i * boxPixelsX, 30.2 * boxPixelsY + 7);
		window.draw(livesSprite);
	}
}



void winEffects(sf::Sound  bonusSound)
{
	bonusSound.play();
	Sleep(2);
}

void lostEffects(sf::RenderWindow& window, float mushrooms[200][6], sf::Sound deathSound, sf::Sound mushroomSound, sf::Sprite& mushroomSprite1, sf::Sprite& mushroomSprite2)
{



	deathSound.play();
	Sleep(2000);


	/*for (int i = 0 ; i < 50 ; i++ )
	{
		if (mushrooms [i] [lives] >= 2 )
		{
			mushroomSprite1.setPosition(mushrooms[i][x], mushrooms[i][y]);
			mushroomSprite1.setColor(sf::Color(255, 255, 255, 255 * 0.25 ));
			if (mushrooms [i] [isred])
			mushroomSprite1.setTextureRect(sf::IntRect(0 , 0, boxPixelsX, boxPixelsY));
			else
			mushroomSprite1.setTextureRect(sf::IntRect(0, boxPixelsY, boxPixelsX, boxPixelsY));

			window.draw(mushroomSprite1);
			mushroomSound.play();
			Sleep(0.5);
			mushroomSprite1.setColor(sf::Color(255, 255, 255, 255 ));
			window.draw(mushroomSprite1);
		}
		else if (mushrooms [i] [lives] == 1 )
		{
			mushroomSprite2.setPosition(mushrooms[i][x], mushrooms[i][y]);

			if (mushrooms [i] [isred])
				mushroomSprite2.setTextureRect(sf::IntRect (3 * boxPixelsX ,  0 , boxPixelsX, boxPixelsY));
			else
				mushroomSprite2.setTextureRect(sf::IntRect (3 * boxPixelsX , boxPixelsY, boxPixelsX, boxPixelsY));

			mushroomSprite2.setColor(sf::Color(255, 255, 255, 255 * 0.25 ));

			window.draw(mushroomSprite2);
			mushroomSound.play();
			Sleep(0.5);
			mushroomSprite2.setColor(sf::Color(255, 255, 255, 255  ));

			window.draw(mushroomSprite2);
		}

	}
	*/
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



