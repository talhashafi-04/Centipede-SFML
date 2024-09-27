#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
using namespace std;


void drawMenu(sf::RenderWindow& window, bool& showMenu, bool& ispaused, bool& takepause, bool& takeName, bool& restart, bool& end_game, string Username, sf::Sprite menuSprite, sf::Font arcadefont, sf::Font simplefont);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void drawMenu(sf::RenderWindow& window, bool& showMenu, bool& ispaused, bool& takepause,bool & takeName , bool & restart , bool & end_game , string Username ,  sf::Sprite menuSprite, sf::Font arcadefont, sf::Font simplefont)
{



	

		takepause = true;
		int optionSelected = 0;



		sf::RectangleShape rectangle(sf::Vector2f(600.f, 960.f));
		rectangle.setFillColor(sf::Color::White);

		rectangle.setOutlineColor(sf::Color::White);

		rectangle.setFillColor(sf::Color(10, 20, 15, 190));

		rectangle.setOutlineColor(sf::Color(10, 20, 15, 190));

		rectangle.setOutlineThickness(4.f);

		sf::RectangleShape rectangle1(sf::Vector2f(10 * boxPixelsX
			, 1.5 * boxPixelsX));
		rectangle1.setFillColor(sf::Color::Transparent);

		rectangle1.setOutlineColor(sf::Color::Black);

		rectangle1.setFillColor(sf::Color(10, 20, 15, 0));

		rectangle1.setOutlineColor(sf::Color(0, 0, 0, 255));

		rectangle1.setOutlineThickness(4.f);

		sf::Text text1("CENTIPEDE", arcadefont, 110);

		text1.setFillColor(sf::Color::Yellow);

		sf::Text text2("NEW GAME", simplefont, 40);

		text2.setFillColor(sf::Color::Green);

		sf::Text text3("HIGH SCORES", simplefont, 40);

		text3.setFillColor(sf::Color::Green);

		sf::Text text4(" SETTINGS ", simplefont, 40);

		text4.setFillColor(sf::Color::Green);

		sf::Text text5("MAIN MENU", simplefont, 40);

		text5.setFillColor(sf::Color::Green);

		sf::Text text6("MAIN MENU", arcadefont, 80);

		text6.setFillColor(sf::Color::Green);

		sf::Text text7("GAME PAUSED", arcadefont, 80);

		text7.setFillColor(sf::Color::Green);

		sf::Text text8("RESUME GAME", simplefont, 40);

		text8.setFillColor(sf::Color::Green);


		sf::Text text9("EXIT GAME", simplefont, 40);

		text9.setFillColor(sf::Color::Green);


		sf::Text text10("ENTER YOUR NAME", simplefont, 40);

		text10.setFillColor(sf::Color::White);

		sf::Text text11("FEATURE COMING SOON", simplefont, 40);

		text11.setFillColor(sf::Color::Green);



		while (window.isOpen())

		{
			bool flag = false;
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}

				else if (event.type == sf::Event::KeyPressed)
				{
					if (ispaused)
					{

						if (event.key.code == sf::Keyboard::Down)
						{
							if (optionSelected < 5)
								optionSelected++;


						}
						if (event.key.code == sf::Keyboard::Up)
						{
							if (optionSelected > 1)
								optionSelected--;


						}

					}
					else
					{

						if (event.key.code == sf::Keyboard::Down)
						{
							if (optionSelected < 4)
								optionSelected++;


						}
						if (event.key.code == sf::Keyboard::Up)
						{
							if (optionSelected > 1)
								optionSelected--;


						}

					}

					if (event.key.code == sf::Keyboard::Enter)
					{
						if (!ispaused)
						{
							if (optionSelected == 1)
							{
								showMenu = false;
								window.clear();
								flag = true;
							}
							else if (optionSelected == 2)
							{
								while (window.isOpen())
								{
									bool flag = false;
									sf::Event event;
									while (window.pollEvent(event))
									{
										if (event.type == sf::Event::Closed)
										{
											window.close();
										}
										else if (event.type == sf::Event::KeyPressed)
										{
											if (event.key.code == sf::Keyboard::Escape)
											{
												flag = true;
												break;


											}
										}



									}
									window.clear();
									if (flag)
										break;
									window.draw(menuSprite);

									rectangle.setPosition(180.f, 0.f);
									window.draw(rectangle);

									text11.setPosition(250, 400);
									window.draw(text11);

									text1.setPosition(228, 40);
									window.draw(text1);


									text6.setPosition(292, 200);
									window.draw(text6);




									window.display();




								}
							}
							else if (optionSelected == 3)
							{
								while (window.isOpen())
								{
									bool flag = false;
									sf::Event event;
									while (window.pollEvent(event))
									{
										if (event.type == sf::Event::Closed)
										{
											window.close();
										}
										else if (event.type == sf::Event::KeyPressed)
										{
											if (event.key.code == sf::Keyboard::Escape)
											{
												flag = true;
												break;


											}
										}



									}
									window.clear();
									if (flag)
										break;
									window.draw(menuSprite);



									rectangle.setPosition(180.f, 0.f);
									window.draw(rectangle);

									text11.setPosition(250, 400);
									window.draw(text11);

									text1.setPosition(228, 40);
									window.draw(text1);


									text6.setPosition(292, 200);
									window.draw(text6);




									window.display();




								}

							}
							else if (optionSelected == 4)
							{
								end_game = true ;
							}


						}
						else
						{
							if (optionSelected == 1)
							{
								showMenu = false;
								window.clear();
								flag = true;
							}
							else if (optionSelected == 3)
							{
								while (window.isOpen())
								{
									bool flag = false;
									sf::Event event;
									while (window.pollEvent(event))
									{
										if (event.type == sf::Event::Closed)
										{
											window.close();
										}
										else if (event.type == sf::Event::KeyPressed)
										{
											if (event.key.code == sf::Keyboard::Escape)
											{
												flag = true;
												break;


											}
										}



									}
									window.clear();
									if (flag)
										break;
									window.draw(menuSprite);

									rectangle.setPosition(180.f, 0.f);
									window.draw(rectangle);

									text11.setPosition(250, 400);
									window.draw(text11);



									text1.setPosition(228, 40);
									window.draw(text1);


									text7.setPosition(258, 200);
									window.draw(text7);






									window.display();




								}
							}
							else if (optionSelected == 4)
							{
								while (window.isOpen())
								{
									bool flag = false;
									sf::Event event;
									while (window.pollEvent(event))
									{
										if (event.type == sf::Event::Closed)
										{
											window.close();
										}
										else if (event.type == sf::Event::KeyPressed)
										{
											if (event.key.code == sf::Keyboard::Escape)
											{
												flag = true;
												break;


											}
										}



									}
									window.clear();
									if (flag)
										break;
									window.draw(menuSprite);

									rectangle.setPosition(180.f, 0.f);
									window.draw(rectangle);

									text11.setPosition(250, 400);
									window.draw(text11);



									text1.setPosition(228, 40);
									window.draw(text1);


									text7.setPosition(258, 200);
									window.draw(text7);


									window.display();




								}

							}
							else if (optionSelected == 5)
							{
								end_game = true;

							}
							else if (optionSelected == 2)
							{
								ispaused = false;
								showMenu = true;
								restart = true;
							}

						}

					}
				}
			}



			if (takeName)
			{
				while (window.isOpen())
				{

					sf::Text name;
					name.setFont(simplefont);
					name.setString((Username));
					name.setCharacterSize(50);
					name.setFillColor(sf::Color::Red);
					name.setPosition(10 * boxPixelsX + (((10 * boxPixelsX) - (Username.length() * 32)) / 2), 15 * boxPixelsY - 19);


					bool flag = false;
					sf::Event event;
					while (window.pollEvent(event))
					{

						if (event.type == sf::Event::Closed)
						{
							window.close();
						}
						else if (event.type == sf::Event::KeyPressed)
						{
							if (event.key.code == sf::Keyboard::Enter && Username.length())
							{
								flag = true;
								break;

							}
						}
						else if (event.type == sf::Event::TextEntered)
						{
							if (event.text.unicode == '\b' && !Username.empty())
							{

								Username.pop_back();
							}
							else if (event.text.unicode < 128)
							{
								char enteredChar = static_cast<char>(event.text.unicode);
								if (enteredChar >= 'a' && enteredChar <= 'z')
								{
									enteredChar = static_cast<char>(event.text.unicode - 'a' + 'A');
								}
								Username += enteredChar;
							}
						}
					}

					window.clear();
					if (flag)
						break;
					window.draw(menuSprite);

					rectangle.setPosition(180.f, 0.f);
					window.draw(rectangle);

					if (true)
					{
						rectangle1.setFillColor(sf::Color(0, 0, 0, 150));
					}
					rectangle1.setPosition(10 * boxPixelsX, 15 * boxPixelsY - 9);
					window.draw(rectangle1);
					rectangle1.setFillColor(sf::Color(0, 0, 0, 0));

					window.draw(name);

					text10.setPosition(292, 400);
					window.draw(text10);

					text1.setPosition(228, 40);
					window.draw(text1);

					text6.setPosition(292, 200);
					window.draw(text6);

					window.display();

				}

				takeName = false;
			}







			window.clear();
			if (flag)
				break;

			window.draw(menuSprite);

			rectangle.setPosition(180.f, 0.f);
			window.draw(rectangle);


			if (optionSelected == 1)
			{
				rectangle1.setFillColor(sf::Color(0, 0, 0, 150));
			}
			rectangle1.setPosition(10 * boxPixelsX, 13 * boxPixelsY - 9);
			window.draw(rectangle1);
			rectangle1.setFillColor(sf::Color(0, 0, 0, 0));



			if (optionSelected == 2)
			{
				rectangle1.setFillColor(sf::Color(0, 0, 0, 150));
			}
			rectangle1.setPosition(10 * boxPixelsX, 15 * boxPixelsY - 9);
			window.draw(rectangle1);
			rectangle1.setFillColor(sf::Color(0, 0, 0, 0));



			if (optionSelected == 3)
			{
				rectangle1.setFillColor(sf::Color(0, 0, 0, 150));
			}
			rectangle1.setPosition(10 * boxPixelsX, 17 * boxPixelsY - 9);
			window.draw(rectangle1);
			rectangle1.setFillColor(sf::Color(0, 0, 0, 0));



			if (optionSelected == 4)
			{
				rectangle1.setFillColor(sf::Color(0, 0, 0, 150));
			}
			rectangle1.setPosition(10 * boxPixelsX, 19 * boxPixelsY - 9);
			window.draw(rectangle1);
			rectangle1.setFillColor(sf::Color(0, 0, 0, 0));

			if (ispaused)
			{
				if (optionSelected == 5)
				{
					rectangle1.setFillColor(sf::Color(0, 0, 0, 150));
				}

				rectangle1.setPosition(10 * boxPixelsX, 21 * boxPixelsY - 8);
				window.draw(rectangle1);
				rectangle1.setFillColor(sf::Color(0, 0, 0, 0));

			}


			// rectangle1.setPosition(10 * boxPixelsX , 23 * boxPixelsY - 8);
			// window.draw(rectangle1);



			if (ispaused == false)
			{

				text1.setPosition(228, 40);
				window.draw(text1);


				text6.setPosition(292, 200);
				window.draw(text6);


				text2.setPosition(370, 404);
				window.draw(text2);

				text3.setPosition(352, 532);
				window.draw(text3);


				text4.setPosition(375, 468);
				window.draw(text4);


				text9.setPosition(370, 596);
				window.draw(text9);


			}
			else
			{

				text1.setPosition(228, 40);
				window.draw(text1);


				text7.setPosition(258, 200);
				window.draw(text7);


				text8.setPosition(335, 404);
				window.draw(text8);


				text5.setPosition(355, 404 + 64);
				window.draw(text5);

				text3.setPosition(352, 532 + 64);
				window.draw(text3);


				text4.setPosition(375, 468 + 64);
				window.draw(text4);


				text9.setPosition(370, 596 + 64);
				window.draw(text9);


			}

			// Display the drawn content
			window.display();

		}





	

}

void draw_Lost_Menu(sf::RenderWindow& window, sf::Sprite& menuSprite, int score, sf::Font arcadefont, sf::Font simplefont)
{


	sf::RectangleShape rectangle(sf::Vector2f(600.f, 960.f));
	rectangle.setFillColor(sf::Color::White);

	rectangle.setOutlineColor(sf::Color::White);

	rectangle.setFillColor(sf::Color(10, 20, 15, 190));

	rectangle.setOutlineColor(sf::Color(10, 20, 15, 190));

	rectangle.setOutlineThickness(4.f);


	sf::Text text1("CENTIPEDE", arcadefont, 110);

	text1.setFillColor(sf::Color::Yellow);


	sf::Text text6("GAME OVER", arcadefont, 80);

	text6.setFillColor(sf::Color::Green);


	sf::Text text2("YOUR SCORE  : " + std::to_string(score), simplefont, 40);

	text2.setFillColor(sf::Color::Green);

	bool flag = false;
	while (window.isOpen())
	{

		sf::Event event;


		window.clear();
		if (flag)
			break;
		window.draw(menuSprite);
		rectangle.setPosition(180.f, 0.f);
		window.draw(rectangle);


		text1.setPosition(228, 40);
		window.draw(text1);


		text6.setPosition(292, 400);
		window.draw(text6);

		text2.setPosition(280, 600);
		window.draw(text2);


		window.display();

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				flag = true;
				break;


			}

		}
	}

}