#include <iostream> 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <ctime>
#include <windows.h> //for Sleep function for taking pause
#include <cmath>
#include <string>


#include "draw.h"
#include "move.h"
#include "exist.h"
#include "collisions.h"
#include "update.h"
#include "display.h"
#include "menu.h"


using namespace std;

/*

// Initializing Dimensions.
// resolutionX and resolutionY determine the rendering resolution.
// Don't edit unless required. Use functions on lines 43, 44, 45 for resizing the game window.
const int resolutionX = 960;
const int resolutionY = 960;
const int boxPixelsX = 32;
const int boxPixelsY = 32;
const int gameRows = resolutionX / boxPixelsX; // Total rows on grid
const int gameColumns = resolutionY / boxPixelsY; // Total columns on grid
*/
// Initializing GameGrid.
int gameGrid[gameRows][gameColumns] = {};

/*
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

//Following also exists only for accessibility
const int initial_length = 12;
const int player_speed = 65;        //(10 -- 10)        

*/


















int main()
{
	bool takeName = true;
	string Username = "";

	// Declaring RenderWindow
	sf::RenderWindow window(sf::VideoMode(resolutionX, resolutionY + 3 * boxPixelsY), "Centipede", sf::Style:: Close| sf::Style::Close);


	// Get the desktop resolution
	sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

	// Calculate the position to center the window
	int windowPositionX = (desktopMode.width - resolutionX) / 2;
	int windowPositionY = (desktopMode.height - resolutionY) / 2;

	// Set the position of the window after switching to fullscreen
	window.setPosition(sf::Vector2i(windowPositionX, 0));

	// Used to resize your window if it's too big or too small. Use according to your needs.
	//window.setSize(sf::Vector2u(, )); // Recommended for 1366x768 (768p) displays.
	//window.setSize(sf::Vector2u(1280, 1280)); // Recommended for 2560x1440 (1440p) displays.
	// window.setSize(sf::Vector2u(1920, 1920)); // Recommended for 3840x2160 (4k) displays.



	// Initializing Background Music.
	sf::Music bgMusic;
	bgMusic.openFromFile("Music/field_of_hopes.ogg");
	bgMusic.play();
	bgMusic.setVolume(50);

	//main


	srand(time(0));




	// Initializing Background.
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	backgroundTexture.loadFromFile("Textures/background.png");
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setColor(sf::Color(255, 255, 255, 255 * 0.20)); // Reduces Opacity to 25%

	// Initializing menu Background.
	sf::Texture menuTexture;
	sf::Sprite menuSprite;
	menuTexture.loadFromFile("Textures/background.png");
	menuSprite.setTexture(menuTexture);
	menuSprite.setColor(sf::Color(255, 255, 255, 255)); // Reduces Opacity to 25%

	// Initializing Player and Player Sprites.
	sf::Clock PlayerClock;
	float player[2] = {};
	player[x] = (gameColumns / 2) * boxPixelsX;
	player[y] = resolutionY - 5 * boxPixelsY;
	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	playerTexture.loadFromFile("Textures/player.png");
	playerSprite.setTexture(playerTexture);


	// Initializing Bullet and Bullet Sprites.
	float bullet[3] = {};
	bullet[x] = player[x];
	bullet[y] = player[y] - boxPixelsY;
	bullet[exists] = true;
	sf::Clock bulletClock;
	sf::Texture bulletTexture;
	sf::Sprite bulletSprite;
	bulletTexture.loadFromFile("Textures/bullet.png");
	bulletSprite.setTexture(bulletTexture);
	bulletSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

	// Initializing flea and flea Sprites.
	sf::Clock fleaClock;
	sf::Clock isFleaClock;


	sf::Texture fleaTexture;
	sf::Sprite fleaSprite;
	fleaTexture.loadFromFile("Textures/flea.png");
	fleaSprite.setTexture(fleaTexture);
	fleaSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));



	// Initializing scorpian Sprites.

	sf::Clock scorpianClock;
	sf::Clock isScorpianClock;
	sf::Clock scorpianCrawlingClock;


	sf::Texture scorpianTexture;
	sf::Sprite  scorpianSprite;
	scorpianTexture.loadFromFile("Textures/scorpion.png");
	scorpianSprite.setTexture(scorpianTexture);
	scorpianSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

	//initializing spider 
	float spider[3] = {};
	spider[exists] = false;
	sf::Clock spiderClock;
	sf::Clock isSpiderClock;
	sf::Clock spiderCrawlingClock;
	sf::Clock spiderfireClock;


	sf::Texture spiderTexture;
	sf::Sprite  spiderSprite;
	spiderTexture.loadFromFile("Textures/spider_and_score.png");
	spiderSprite.setTexture(spiderTexture);
	spiderSprite.setTextureRect(sf::IntRect(0, 0, 60, boxPixelsY));



	//Initializing mushroom sprite

	sf::Texture mushroomTexture;
	sf::Sprite mushroomSprite1;
	sf::Sprite mushroomSprite2;
	mushroomTexture.loadFromFile("Textures/mushroom.png");
	mushroomSprite1.setTexture(mushroomTexture);
	mushroomSprite2.setTexture(mushroomTexture);
	mushroomSprite1.setTextureRect(sf::IntRect(0, boxPixelsY, boxPixelsX, boxPixelsY));
	mushroomSprite2.setTextureRect(sf::IntRect(3 * boxPixelsX, boxPixelsY, boxPixelsX, boxPixelsY));
	mushroomSprite1.setColor(sf::Color(255, 255, 255, 255));
	mushroomSprite2.setColor(sf::Color(255, 255, 255, 255));
	//Initializing centipede sprite  


	sf::Clock centipedeClock[30][30];
	sf::Clock crawlingClock;
	sf::Clock fleaCrawlingClock;

	sf::Texture centipedeTexturel1;
	sf::Sprite centipedeSpritel1;
	centipedeTexturel1.loadFromFile("Textures/c_body_left_walk.png");
	centipedeSpritel1.setTexture(centipedeTexturel1);
	centipedeSpritel1.setTextureRect(sf::IntRect(6 * boxPixelsX, 0, boxPixelsX, boxPixelsY));

	sf::Texture centipedeTexturel2;
	sf::Sprite centipedeSpritel2;
	centipedeTexturel2.loadFromFile("Textures/c_head_left_walk.png");
	centipedeSpritel2.setTexture(centipedeTexturel2);
	centipedeSpritel2.setTextureRect(sf::IntRect(6 * boxPixelsX, 0, boxPixelsX, boxPixelsY));

	sf::Texture centipedeTexturer1;
	sf::Sprite centipedeSpriter1;
	centipedeTexturer1.loadFromFile("Textures/c_body_right_walk.png");
	centipedeSpriter1.setTexture(centipedeTexturer1);
	centipedeSpriter1.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

	sf::Texture centipedeTexturer2;
	sf::Sprite centipedeSpriter2;
	centipedeTexturer2.loadFromFile("Textures/c_head_right_walk.png");
	centipedeSpriter2.setTexture(centipedeTexturer2);
	centipedeSpriter2.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));


	/// for main menue 

	//.setColor(sf::Color(255, 255, 255, 255 )); // Reduces Opacity to 25%





	// Initializing sound effect 

	sf::SoundBuffer buffer;
	buffer.loadFromFile("Sound Effects/fire1.wav");
	sf::Sound bulletfiresound;
	bulletfiresound.setBuffer(buffer);

	sf::SoundBuffer extraLivebuffer;
	extraLivebuffer.loadFromFile("Sound Effects/extralive.wav");
	sf::Sound extraLivesound;
	extraLivesound.setBuffer(extraLivebuffer);

	sf::SoundBuffer mushroomeatbuffer;
	mushroomeatbuffer.loadFromFile("Sound Effects/mushroomeatsound.wav");
	sf::Sound mushroomeatsound;
	mushroomeatsound.setBuffer(mushroomeatbuffer);


	sf::SoundBuffer scorpiandeathbuffer;
	scorpiandeathbuffer.loadFromFile("Sound Effects/scorpiandeath.wav");
	sf::Sound scorpiandeathsound;
	scorpiandeathsound.setBuffer(scorpiandeathbuffer);



	sf::SoundBuffer spiderdeathbuffer;
	spiderdeathbuffer.loadFromFile("Sound Effects/spiderdeath.wav");
	sf::Sound spiderdeathsound;
	spiderdeathsound.setBuffer(spiderdeathbuffer);



	sf::SoundBuffer bonus;
	bonus.loadFromFile("Sound Effects/1up.wav");
	sf::Sound bonusSound;
	bonusSound.setBuffer(bonus);

	sf::SoundBuffer death;
	death.loadFromFile("Sound Effects/death.wav");
	sf::Sound deathSound;
	deathSound.setBuffer(death);

	sf::SoundBuffer mushroomBuffer;
	mushroomBuffer.loadFromFile("Sound Effects/bonus.wav");
	sf::Sound mushroomSound;
	mushroomSound.setBuffer(mushroomBuffer);


	sf::SoundBuffer fleabuffer;
	fleabuffer.loadFromFile("Sound Effects/flea.wav");
	sf::Sound fleasound;
	fleasound.setBuffer(fleabuffer);


	sf::SoundBuffer scorpianbuffer;
	scorpianbuffer.loadFromFile("Sound Effects/scorpion.wav");
	sf::Sound scorpiansound;
	scorpiansound.setBuffer(scorpianbuffer);


	sf::SoundBuffer spiderbuffer;
	spiderbuffer.loadFromFile("Sound Effects/spider (1).wav");
	sf::Sound spidersound;
	spidersound.setBuffer(spiderbuffer);



	sf::SoundBuffer killbuffer;
	killbuffer.loadFromFile("Sound Effects/kill.wav");
	sf::Sound killsound;
	killsound.setBuffer(killbuffer);



	// sound variables 
	bool bulletfire = false;
	bool fleafire = false;
	bool scorpianfire = false;
	bool spiderfire = false;





	//Initializong fonts

	sf::Font simplefont;
	simplefont.loadFromFile("regular.ttf");

	sf::Font arcadefont;
	arcadefont.loadFromFile("arcade.ttf");


	sf::Font boldfont;
	simplefont.loadFromFile("bold.ttf");


	sf::Text scorpiandeathScore;
	scorpiandeathScore.setFont(simplefont);
	scorpiandeathScore.setString("1000");
	scorpiandeathScore.setCharacterSize(30);
	scorpiandeathScore.setFillColor(sf::Color::Yellow);



	sf::Text Score;
	Score.setFont(simplefont);
	Score.setCharacterSize(32);
	Score.setFillColor(sf::Color::Yellow);
	Score.setPosition(15, 30.3 * boxPixelsY);

	sf::Text Level;
	Level.setFont(simplefont);
	Level.setCharacterSize(30);
	Level.setFillColor(sf::Color::Yellow);
	Level.setPosition(300, 30.3 * boxPixelsY);

	sf::Text Lives;
	Lives.setFont(simplefont);
	Lives.setString("LIVES :  ");
	Lives.setCharacterSize(30);
	Lives.setFillColor(sf::Color::Yellow);
	Lives.setPosition(470, 30.3 * boxPixelsY);

	// lives sprite

	sf::Texture livesTexture;
	sf::Sprite livesSprite;
	livesTexture.loadFromFile("Textures/lives.png");
	livesSprite.setTexture(livesTexture);
	livesSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));



	


	// For controlling loops 

	bool restart_game = false;
	bool next_level = false;
	bool life_lost = false;

	//loop for restarting
	while (true)
	{
	restart_game = false;	


		int n = rand() % 11 + 15;

		int level = 1;
		unsigned int score = 0;
		int playerlives = 4;
		int   centipedeSpeed = 100;
		int   bullet_speed = 30;		//(10 -- 50 )
		bool showMenu = true;
		bool takepause = false;
		bool ispaused = false;


		// loop for levels
		while (true)
		{
		next_level = false;





			changeColor(level, centipedeSpritel1, centipedeSpritel2, centipedeSpriter1, centipedeSpriter2);

			if (n < 130)
				n = n + (20.0 / 100 * (float)n);



			float mushrooms[200][6] = {};
			for (int i = 0; i < 200; i++)
			{
				mushrooms[i][lives] = 2;
				mushrooms[i][isred] = false;
				mushrooms[i][exists] = false;
				mushrooms[i][mushroomsEaten] = 0;
			}

			for (int i = 0; i < n; i++)
			{

				int xVAL = rand() % 28 + 1;
				int yVAL = rand() % 29 + 1;

				if (xVAL < 0)
					xVAL = -xVAL;
				if (yVAL < 0)
					yVAL = -yVAL;
				mushrooms[i][x] = xVAL * boxPixelsX;

				mushrooms[i][y] = yVAL * boxPixelsY;

				mushrooms[i][exists] = true;
				mushrooms[i][isred] = false;

				mushrooms[i][lives] = 2;
			}

			float scorpian[3] = {};
			scorpian[exists] = false;

			float flea[3] = {};
			flea[exists] = false;

			//loop for life_lost 
			while (true)
			{
			life_lost = false;

				

				float centipede[30][30][12] = {};
				for (int i = 0; i < 30; i++)
				{
					for (int j = 0; j < 30; j++)
					{
						centipede[i][j][exists] = false;
						centipede[i][j][segmentExists] = false;
						centipede[i][j][restricted] = false;
						centipede[i][j][mushroomsEaten] = 0;
						centipede[i][j][speed] = 100;
					}


				}






				int yVAL = rand() % 25;
				int	xVAL = rand() % gameColumns - 12;

				if (xVAL < 0)
					xVAL = -xVAL;
				if (yVAL < 0)
					yVAL = -yVAL;
				for (int j = 0; j < abs(13 - level); j++)
				{
					centipede[0][j][length] = 12;
					centipede[0][j][isleft] = true;
					centipede[0][j][exists] = true;
					centipede[0][j][segmentExists] = true;
					if (level == 1)
					{
						centipede[0][j][x] = (xVAL + j) * boxPixelsX;
						centipede[0][j][y] = (yVAL)*boxPixelsY;
					}
					else
					{
						centipede[0][j][x] = ((30 - (12 - level)) + j) * boxPixelsX;
						centipede[0][j][y] = 0;
					}

					centipede[0][j][ishead] = false;
				}


				for (int i = 0; i < 200; i++)
				{
					for (int j = 0; j < 30; j++)
					{
						while (mushrooms[i][x] == centipede[0][j][x] && mushrooms[i][y] == centipede[0][j][y] && mushrooms[i][exists] && centipede[0][j][exists])
						{
							int xVAL = rand() % 30;
							int yVAL = rand() % 29;

							if (xVAL < 0)
								xVAL = -xVAL;
							if (yVAL < 0)
								yVAL = -yVAL;
							mushrooms[i][x] = xVAL * boxPixelsX;

							mushrooms[i][y] = yVAL * boxPixelsY;

							mushrooms[i][exists] = true;

							mushrooms[i][lives] = 2;
						}
					}
				}
				centipede[0][0][ishead] = true;

				for (int i = 29; i > 30 - level; i--)
				{
					for (int m = 0; m < 30; m++) {
						centipede[i][m][exists] = true;
						centipede[i][m][length] = 1;
					}
					centipede[i][0][speed] = 150;
					centipede[i][0][segmentExists] = true;
					centipede[i][0][is_up] = false;
					centipede[i][0][isleft] = rand() % 2;
					centipede[i][0][ishead] = true;
					centipede[i][0][restricted] = false;
					centipede[i][0][x] = (rand() % 28 + 1) * boxPixelsX;
					centipede[i][0][y] = (rand() % 3) * boxPixelsX;



				}

				//for scoring 
				if (level > 1)
				{
					int counter = 0;
					for (int i = 0; i < 200; i++)
					{
						if (mushrooms[i][exists] == 1)
						{
							if (mushrooms[i][lives] == 1 || mushrooms[i][isred] == 1)
							{
								mushrooms[i][lives] = 2;
								mushrooms[i][ishead] = false;
								counter++;

							}
						}
					}

					score += counter * 5;







				}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////



				while (window.isOpen())
				{

					sf::Event e;
					while (window.pollEvent(e))
					{
						if (e.type == sf::Event::Closed)
						{
							window.close();
						}
						else if (e.type == sf::Event::KeyPressed)
						{
							if (e.key.code == sf::Keyboard::F1)
							{
								ispaused = true;
								showMenu = true;

							}

						}
					}


					if (showMenu)
					{
						bool goto_restart = false;
						bool end_game = false;

						drawMenu(window, showMenu, ispaused, takepause, takeName, goto_restart, end_game, Username, menuSprite, arcadefont, simplefont);
						if (goto_restart)
						{
							restart_game = true;
							break;

						}
						if (end_game)
						{
							return 0;
						}
					}




					///////////////////////////////////////////////////////////////
					//                                                           //
					// Call Your Functions Here. Some have been written for you. //
					// Be vary of the order you call them, SFML draws in order.  //
					//                                                           //
					///////////////////////////////////////////////////////////////

					window.draw(backgroundSprite);


					drawMushrooms(window, mushrooms, mushroomSprite1, mushroomSprite2);
					drawPlayer(window, player, playerSprite);

					drawCentipede(window, crawlingClock, centipede, centipedeSpritel1, centipedeSpritel2, centipedeSpriter1, centipedeSpriter2);
					if ((isCentipede_not_exist(centipede)))
					{
						winEffects(bonusSound);

						//updateCentipede (centipede) ;
						level++;
						if (level < 5)

							for (int i = 0; i < 30; i++)
								for (int j = 0; j < 30; j++)
									if (centipede[i][j][exists])
										centipede[i][j][speed] += 10;

									else if (level < 10)

										for (int i = 0; i < 30; i++)
											for (int j = 0; j < 30; j++)
												if (centipede[i][j][exists])
													centipede[i][j][speed] += 10;

												else

													for (int i = 0; i < 30; i++)
														for (int j = 0; j < 30; j++)
															if (centipede[i][j][exists])
																centipede[i][j][speed] += 10;

						bullet_speed += 0.1;

						next_level = true;
						break;

					}
					moveCentipede(centipede, mushrooms, centipedeClock, centipedeSpeed);

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
					{

						if (bullet[exists] == true)
						{
							moveBullet(bullet, bulletClock, player, bulletfire, bullet_speed);
							drawBullet(window, bullet, bulletSprite);

						}
					}
					else
					{
						if (bullet[exists])
						{
							bullet[x] = player[x];
							bullet[y] = player[y];
						}
					}
					if (bulletfire)
					{
						bulletfiresound.play();
						bulletfire = false;
					}





					if (collisionCentipede_player(centipede, player) || collisionMushroom_player(mushrooms, player) || collisionFlea_Player(flea, player) || collisionScorpian_Player(scorpian, player) || collisionSpider_Player(spider, player))
					{

						lostEffects(window, mushrooms, deathSound, mushroomSound, mushroomSprite1, mushroomSprite2);

						playerlives--;
						

						if (!playerlives)
						{
							
							draw_Lost_Menu(window, menuSprite, score, arcadefont, simplefont);
							
							restart_game = true;
							break;
							showMenu = true;
						}
						life_lost = true;
						break;

					}

					if (flea[exists] == false && isFleaClock.getElapsedTime().asMilliseconds() > 2000)
					{
						isFleaClock.restart();
						if (isFleaExists(mushrooms))
						{
							fleafire = true;
							flea[exists] = true;
							flea[x] = (rand() % 28 + 1) * boxPixelsX;
							flea[y] = 0;
						}
					}
					if (flea[exists])
					{
						if (fleafire)
						{
							fleasound.play();
							fleafire = false;
						}

						drawFlea(fleaCrawlingClock, flea, window, fleaSprite);
						moveFlea(fleaClock, flea, mushrooms, centipede);

					}

					if (scorpian[exists] == false && isScorpianClock.getElapsedTime().asMilliseconds() > 10000)
					{
						isScorpianClock.restart();
						makeScorpianExist(level, scorpian);
						if (scorpian[exists])
							scorpianfire = true;
					}
					if (scorpian[exists])
					{
						if (scorpianfire)
						{
							scorpiansound.play();
							scorpianfire = false;
						}
						drawScorpian(scorpianCrawlingClock, scorpian, window, scorpianSprite);
						moveScorpian(scorpianClock, scorpian, mushrooms, centipede);
					}


					if (spider[exists] == false && isSpiderClock.getElapsedTime().asMilliseconds() > 5000)
					{
						isSpiderClock.restart();
						makeSpiderExist(level, spider);
						if (spider[exists])
							spiderfire = true;
					}

					if (spider[exists])
					{
						if (spiderfireClock.getElapsedTime().asMilliseconds() > 1200)
						{
							spidersound.play();
							spiderfireClock.restart();

						}

						moveSpider(spiderClock, spider, mushrooms, centipede);
						drawSpider(spiderCrawlingClock, spider, window, spiderSprite);
					}


					collisionBullet_Mushroom(bullet, mushrooms, player, bulletfire, score);
					collisionCentipede_mushroom(centipede, mushrooms, mushroomeatsound);

					twiceLength(centipede);






					collisionBullet_Spider(window, bullet, spider, spiderSprite, player, score, spiderdeathsound);
					collisionBullet_Scorpian(window, bullet, scorpian, mushrooms, player, score, scorpiandeathsound, scorpiandeathScore);
					collisionCentipede_bullet(player, centipede, bullet, mushrooms, score, level, killsound);
					collisionBullet_Flea(bullet, flea, mushrooms);






					extraLive(score, playerlives, extraLivesound);
					showLevel(level, Level);
					showLives(window, playerlives, livesSprite);
					showScore(score, Score);
					movePlayer(PlayerClock, player);
					window.draw(Score);
					window.draw(Level);
					window.draw(Lives);
					window.display();

					if (takepause)
					{
						Sleep(2000);
						takepause = false;
					}

					window.clear();
					
				}
				if (restart_game || next_level || life_lost)
					break;



				if (restart_game || next_level)
					break;
			}
			

		}
		if (restart_game )
			break;


		
	}
	cerr << "Wrong Path";
	return 0;
}








