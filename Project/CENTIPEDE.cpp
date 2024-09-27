#include <iostream> 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <ctime>
#include <Windows.h>   //for sleep function for taking pause
//#include <unistdlib.h> only for sleep in linux
#include <cmath>
#include <string>

using namespace std;

// Initializing Dimensions.
// resolutionX and resolutionY determine the rendering resolution.
// Don't edit unless required. Use functions on lines 43, 44, 45 for resizing the game window.
const int resolutionX = 960;
const int resolutionY = 960;
const int boxPixelsX = 32;
const int boxPixelsY = 32;
const int gameRows = resolutionX / boxPixelsX; // Total rows on grid
const int gameColumns = resolutionY / boxPixelsY; // Total columns on grid

// Initializing GameGrid.
int gameGrid[gameRows][gameColumns] = {};

// The following exist purely for readability.
const int x = 0;
const int y = 1;
const int exists = 2;
const int lives = 3 ;
const int isleft = 3 ;
const int length  = 4  ;
const int isred = 4 ;
const int segmentExists = 5;
const int ishead = 6 ;
const int restricted = 7 ; 
const int is_up = 8 ;
const int mushroomsEaten = 9;
const int speed = 10 ;
const int is_fast = 11;

//Following also exists only for accessibility
const int initial_length = 12 ;
const int player_speed = 65  ;        //(10 -- 10)        




//USE OF GPT

/*

0.why incrementing y decrease the player position 
1. how to add sound effect in sfml
2. explain the working of window.open in sfml 
3. how events works in sfml 
4, what colors are present in default in sf :: Color 
5. how to realTime change the ongoing running background music in sfml
6. what is rectsize in sfml
& how to add text in sfml
8 how to add font   in sfml 
9 .ttf font file not loading , possible reasons  in sfml 
10 . how to change brightness of game  in sfml 
11. how to change opacity of the sprite   in sfml 
12 how smooth transition can be achieved in sfml
13 how to take Inputs in sfml 



*/













/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// Write your functions declarations here. Some have been written for you. //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////




void drawFlea ( sf :: Clock & fleaCrawlingClock , float flea [] , sf :: RenderWindow & window ,sf :: Sprite fleaSprite); 
void drawPlayer(sf::RenderWindow& window, float player[], sf::Sprite& playerSprite);
void drawBullet(sf::RenderWindow& window, float bullet[], sf::Sprite& bulletSprite);
void drawMushrooms(sf::RenderWindow& window, float  mushrooms[][6], sf::Sprite & mushroomSprite1 , sf::Sprite & mushroomSprite2);
void drawCentipede(sf::RenderWindow& window,  sf::Clock& crawlingClock ,float centipede[30][30][12], sf::Sprite & centipedeSpritel1 , sf::Sprite & centipedeSpritel2 , sf::Sprite & centipedeSpriter1 , sf::Sprite & centipedeSpriter2);
void drawScorpian ( sf :: Clock & scorpianCrawlingClock , float scorpian [] , sf :: RenderWindow & window ,sf :: Sprite scorpianSprite);
void drawSpider ( sf :: Clock & spiderCrawlingClock , float spider [] , sf :: RenderWindow & window ,sf :: Sprite spiderSprite);
//THe functions above are just for displaying game objects like player , centipede ,bullet etc on the window
// some of them have crawling clock integrated which control rate of change of rectsizes to craetemovemen effect 



void movePlayer(sf::Clock& PlayerClock , float player[]  );
void moveCentipede(float centipede[30][30][12] , float mushrooms[200] [6], sf :: Clock  centipedeClock [] [30] ,int centipedeSpeed );
void moveBullet(float bullet[], sf::Clock& bulletClock , float player []  , bool & bulletbulletfire , int bullet_speed );
void moveFlea(sf :: Clock & fleaClock , float flea [ ], float mushrooms[200][6] , float centipede[30][30][12]);
void moveScorpian(sf :: Clock & scorpianClock , float scorpian [ ], float mushrooms[200][6] , float centipede[30][30][12]);
void moveSpider(sf :: Clock & spiderClock , float spider [ ], float mushrooms[200][6] , float centipede[30][30][12]);
//move player : update position of player whenever certain keys are pressed
//move centipede , changing position of every centipede segment to create effect of movement
// move bullet : simply moving bullet upward untill reaches top 
//move flea : simply smovement of flea from top to bottom
//move scorpian : simply moving from left to right on screen , turning every mushroom red
//movr spider : complex multidirectional movement truly based on rand() values




void collisionBullet_Mushroom( float bullet[] ,float mushrooms[200][6] , float player[]   , bool & bulletfire  , unsigned int & score  );
void collisionCentipede_mushroom(float centtipede[30][30][12] , float mushrooms[200] [6]  , sf :: Sound & mushroomeatsound ) ;
void collisionCentipede_bullet(float player [] ,float centipede[30][30][12] , float bullet [3] , float mushrooms[200][6]  , unsigned int & score , int level , sf :: Sound & killsound) ;
void collisionBullet_Flea (float bullet[] , float flea [] , float mushrooms [][6]);
void collisionBullet_Scorpian (sf :: RenderWindow & window ,float bullet[] , float scorpian [] , float mushrooms [][6] , float player [] , unsigned int & score , sf :: Sound & scorpiandeathSound , sf::Text & scorpiandeathScore);
void collisionBullet_Spider (sf :: RenderWindow & window ,float bullet[] , float spider [] , sf:: Sprite & spiderSprite , float player [],unsigned int & score , sf :: Sound & spiderdeathSound );

//bullet mushroom : checking for collision and decrementing lives of mushroom
//centipedemushroom : checking for collisiom and remove mushrooom from existence , u turning the centipede
//centipede bullet : cheacking for collision and then removing that segment , fragment behind them are transfered to a new index which serves as an independent centipede
//bulletflea , bulletscorpian , bullet spider ; simply looking for collision and removing thsee enemeis , increasing the score 


void makeSpiderExist(int level , float spider[3] );
void makeScorpianExist (int level , float scorpian [3]);
void updateCentipede (float  centipede[30][30][12] ) ;
void changeColor(int level , sf :: Sprite & centipedeSpritel1 , sf :: Sprite & centipedeSpritel2 , sf :: Sprite & centipedeSpriter1 , sf :: Sprite & centipedeSpriter2);
void twiceLength (float centipede [30][30][12]);
void extraLive(unsigned int & score , int & lives  , sf:: Sound & extraLivesound );
//makespider / scorpian exist , check whether to craete them or not based on random value genrated , initialixing their positions randomly also
//change color , randomly changes head color by changing grb valuse of head
// twicelenght , if centipede fragment has eaten 5 mushrooms its lenght will fget doubled , function will first check the number of segment of curremt fragments and add same number asiigning their positions
// extra lives ; check for score and give binus lives



bool isFleaExists(float mushrooms[][6]);
bool isCentipede_not_exist (float centipede[30][30][12]);
bool collisionCentipede_player(float centipede[30][30][12] , float player [] );
bool collisionMushroom_player(float mushrooms[200][6] , float player [] );
bool collisionFlea_Player(float flea [3], float palyer [2]);
bool collisionScorpian_Player(float scorpian [] , float player []) ;
bool collisionSpider_Player(float spider [] , float player []) ;
// used to check whether user wins or losse
//isCentipde notexist , returns true if no segment is left of centipedd , user wins
// all other chaks for collision with enemies or poisunous mushroom




void showScore (unsigned int & score  , sf :: Text & Score ) ;
void showLevel (int &  level  , sf :: Text & Level ) ;
void showLives (sf :: RenderWindow &window  , int & lives , sf :: Sprite & livesSprite) ;
void winEffects ( sf :: Sound  bonusSound);
void lostEffects (sf::RenderWindow& window , float mushrooms[200][6] , sf :: Sound deathSound , sf :: Sound mushroomSound , sf :: Sprite & mushroomSprite1  ,sf :: Sprite & mushroomSprite2);
//used for showing score and level  and lives
// when user wins winefffeeect are added and when user loss , lost affects area added

int main()
{
	bool takeName = true ;
	string Username = "";
	
	// Declaring RenderWindow
	sf::RenderWindow window(sf::VideoMode(resolutionX, resolutionY + 3 * boxPixelsY), "Centipede", sf::Style:: Close | sf::Style:: Close );


	// Get the desktop resolution
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

    // Calculate the position to center the window
    int windowPositionX = (desktopMode.width - resolutionX) / 2 ;
    int windowPositionY = (desktopMode.height - resolutionY) / 2 ;

    // Set the position of the window after switching to fullscreen
    window.setPosition(sf::Vector2i(windowPositionX, 0 )) ;

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

	restart :
	
	srand(time(0));
	int level = 1 ;
	unsigned int score = 0 ;
	int playerlives = 4;
	int   centipedeSpeed = 100 ;
	int   bullet_speed = 30  ;		//(10 -- 50 )
	bool showMenu = true ;
	bool takepause = false ;
	bool ispaused = false ;



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
	menuSprite.setColor(sf::Color(255, 255, 255, 255 )); // Reduces Opacity to 25%

	// Initializing Player and Player Sprites.
	sf:: Clock PlayerClock ;
	float player[2] = {};
	player[x] = (gameColumns / 2) * boxPixelsX;
	player[y] = resolutionY - 5 * boxPixelsY ;
	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	playerTexture.loadFromFile("Textures/player.png");
	playerSprite.setTexture(playerTexture);
	

	// Initializing Bullet and Bullet Sprites.
	float bullet[3] = {};
	bullet[x] = player[x];
	bullet[y] = player[y] - boxPixelsY;
	bullet[exists] = true ;
	sf::Clock bulletClock;
	sf::Texture bulletTexture;
	sf::Sprite bulletSprite;
	bulletTexture.loadFromFile("Textures/bullet.png");
	bulletSprite.setTexture(bulletTexture);
	bulletSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

	// Initializing flea and flea Sprites.
	sf:: Clock fleaClock ;
	sf:: Clock isFleaClock ;
	
	 
	sf::Texture fleaTexture;
	sf::Sprite fleaSprite;
	fleaTexture.loadFromFile("Textures/flea.png");
	fleaSprite.setTexture(fleaTexture);
	fleaSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));



	// Initializing scorpian Sprites.
	
	sf:: Clock scorpianClock ;
	sf:: Clock isScorpianClock ;
	sf:: Clock scorpianCrawlingClock ;
	
	 
	sf::Texture scorpianTexture;
	sf::Sprite  scorpianSprite ;
	scorpianTexture.loadFromFile("Textures/scorpion.png");
	scorpianSprite.setTexture(scorpianTexture);
	scorpianSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

	//initializing spider 
	float spider [3]={};
	spider [exists] = false ;
	sf:: Clock spiderClock ;
	sf:: Clock isSpiderClock ;
	sf:: Clock spiderCrawlingClock ;
	sf:: Clock spiderfireClock ;
	
	 
	sf::Texture spiderTexture;
	sf::Sprite  spiderSprite ;
	spiderTexture.loadFromFile("Textures/spider_and_score.png");
	spiderSprite.setTexture(spiderTexture);
	spiderSprite.setTextureRect(sf::IntRect(0, 0, 60 , boxPixelsY));



	//Initializing mushroom sprite
	
	sf::Texture mushroomTexture;
	sf::Sprite mushroomSprite1;
	sf::Sprite mushroomSprite2;
	mushroomTexture.loadFromFile("Textures/mushroom.png");
	mushroomSprite1.setTexture(mushroomTexture);
	mushroomSprite2.setTexture(mushroomTexture);
	mushroomSprite1.setTextureRect(sf::IntRect(0, boxPixelsY, boxPixelsX, boxPixelsY));
	mushroomSprite2.setTextureRect(sf::IntRect (3 * boxPixelsX , boxPixelsY, boxPixelsX, boxPixelsY));
	mushroomSprite1.setColor(sf::Color(255, 255, 255, 255 )); 
	mushroomSprite2.setColor(sf::Color(255, 255, 255, 255 )); 
	//Initializing centipede sprite  

	
	sf:: Clock centipedeClock [30][30];
	sf:: Clock crawlingClock ; 
	sf:: Clock fleaCrawlingClock ;

	sf::Texture centipedeTexturel1 ;
	sf::Sprite centipedeSpritel1 ;
	centipedeTexturel1.loadFromFile("Textures/c_body_left_walk.png");
	centipedeSpritel1.setTexture(centipedeTexturel1);	
	centipedeSpritel1.setTextureRect(sf::IntRect(6*boxPixelsX, 0, boxPixelsX , boxPixelsY ));

	sf::Texture centipedeTexturel2 ;
	sf::Sprite centipedeSpritel2 ;
	centipedeTexturel2.loadFromFile("Textures/c_head_left_walk.png");
	centipedeSpritel2.setTexture(centipedeTexturel2);	
	centipedeSpritel2.setTextureRect(sf::IntRect(6* boxPixelsX, 0, boxPixelsX , boxPixelsY ));
	
	sf::Texture centipedeTexturer1 ;
	sf::Sprite centipedeSpriter1 ;
	centipedeTexturer1.loadFromFile("Textures/c_body_right_walk.png");
	centipedeSpriter1.setTexture(centipedeTexturer1);	
	centipedeSpriter1.setTextureRect(sf::IntRect(0, 0, boxPixelsX , boxPixelsY ));

	sf::Texture centipedeTexturer2 ;
	sf::Sprite centipedeSpriter2 ;
	centipedeTexturer2.loadFromFile("Textures/c_head_right_walk.png");
	centipedeSpriter2.setTexture(centipedeTexturer2);	
	centipedeSpriter2.setTextureRect(sf::IntRect(0, 0, boxPixelsX , boxPixelsY ));


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


    
	sf :: SoundBuffer bonus ;
	bonus.loadFromFile("Sound Effects/1up.wav");
    sf :: Sound bonusSound ;
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
	bool bulletfire = false ;
	bool fleafire = false ;
	bool scorpianfire = false ;
	bool spiderfire = false ;






    
    sf::Font simplefont;
    simplefont.loadFromFile("regular.ttf"); 
        
	sf:: Font arcadefont ;
	arcadefont.loadFromFile("arcade.ttf");
    

	sf::Font boldfont;
    simplefont.loadFromFile("bold.ttf");
       
    
	sf::Text scorpiandeathScore ;
    scorpiandeathScore.setFont(simplefont); 
	scorpiandeathScore.setString("1000"); 
    scorpiandeathScore.setCharacterSize(30);
    scorpiandeathScore.setFillColor(sf::Color:: Yellow ); 
   

    
    sf::Text Score ;
    Score.setFont(simplefont); 
	Score.setString("SCORE :  " + std :: to_string(score)); 
    Score.setCharacterSize(32);
    Score.setFillColor(sf::Color:: Yellow ); 
    Score.setPosition(15, 30.3 * boxPixelsY );

	sf::Text Level ;
    Level.setFont(simplefont); 
	Level.setString("LEVEL :  " + std :: to_string(level)); 
    Level.setCharacterSize(30);
    Level.setFillColor(sf::Color:: Yellow ); 
    Level.setPosition(300, 30.3 * boxPixelsY );

	sf::Text Lives ;
    Lives.setFont(simplefont); 
	Lives.setString("LIVES :  "); 
    Lives.setCharacterSize(30);
    Lives.setFillColor(sf::Color:: Yellow ); 
    Lives.setPosition(470, 30.3 * boxPixelsY );

	// lives sprite

	sf::Texture livesTexture;
	sf::Sprite livesSprite;
	livesTexture.loadFromFile("Textures/lives.png");
	livesSprite.setTexture(livesTexture);
	livesSprite.setTextureRect(sf::IntRect (0,0, boxPixelsX, boxPixelsY));



	// initializing mushrooms 
	static int n = rand() % 11 + 15;

	

	// loop for levels
	loop1 :
	


	
	changeColor ( level , centipedeSpritel1 , centipedeSpritel2 , centipedeSpriter1 , centipedeSpriter2 ) ;
	
	if (n < 130 )
	n = n + (20.0/100 * (float) n);

	

    float mushrooms[200] [6] = {};
	for (int i = 0 ; i < 200; i++)
		{
			mushrooms [i] [lives] = 2 ;
			mushrooms [i] [isred] = false ;
			mushrooms [i][exists] = false ; 
			mushrooms [i][mushroomsEaten]= 0 ;
		}
	for (int i = 0 ; i < n ; i++ )
	{
		
		int xVAL = rand () % 28 + 1;
		int yVAL = rand() % 29 + 1 ;
		
		if (xVAL < 0 )
		xVAL = -xVAL  ;
		if (yVAL < 0 )
		yVAL = -yVAL  ;
		mushrooms[i][x] = xVAL*boxPixelsX ;
		
		mushrooms[i][y] = yVAL * boxPixelsY ;
		
		mushrooms[i] [exists] = true ;
		mushrooms[i] [isred] = false ;
		
		mushrooms[i] [lives] = 2 ;
	}


	loop2 :
	// initializing centipede and flea
	                                                                                                                          
	float scorpian [3]={};
	scorpian [exists] = false ;

	float flea[3] = {};
	flea [exists] = false ;

	float centipede[30][30][12] = {};   
	for (int i = 0 ;  i < 30 ; i++  )
	{
		for ( int j = 0 ; j < 30 ; j++)
		{
			centipede [i] [j] [exists] = false ;
			centipede [i] [j] [segmentExists] = false ;
			centipede [i] [j] [restricted] = false ;
			centipede [i] [j] [mushroomsEaten] = 0 ;
			centipede [i] [j] [speed] = 100 ; 
		}
		

	}
	
	
	

	
	
	int yVAL = rand () %  25 ;
	int	xVAL = rand () % gameColumns - 12 ;

	if (xVAL < 0 )
	xVAL = -xVAL  ;
	if (yVAL < 0 )
	yVAL = -yVAL  ;
	for ( int j = 0 ; j < abs(13-level) ; j++)
	{
		centipede [0] [j] [length] = 12 ;
		centipede [0] [j] [isleft] = true ;
		centipede [0] [j] [exists] = true ;
		centipede [0] [j] [segmentExists] = true;
		if ( level == 1 )
		{
			centipede [0] [j] [x] = ( xVAL + j) * boxPixelsX  ;
			centipede [0] [j] [y] =  ( yVAL ) * boxPixelsY ;
		}
		else
		{
			centipede [0] [j] [x] = ((30 - (12 - level))+j)*boxPixelsX ;
			centipede [0] [j] [y] = 0;
		}
		
		centipede [0] [j] [ishead] = false ;
	}
	
	
	for ( int i  = 0 ; i < 200 ; i++)
	{
		for (int j  = 0 ; j < 30 ; j++)
		{
			while(	mushrooms [i][x] == centipede [0][j][x] && mushrooms [i][y] == centipede [0][j][y] && mushrooms [i][exists] && centipede [0][j][exists])
			{
				int xVAL = rand () % 30 ;
				int yVAL = rand() % 29 ;
				
				if (xVAL < 0 )
				xVAL = -xVAL  ;
				if (yVAL < 0 )
				yVAL = -yVAL  ;
				mushrooms[i][x] = xVAL*boxPixelsX ;
				
				mushrooms[i][y] = yVAL * boxPixelsY ;
				
				mushrooms[i] [exists] = true ;
				
				mushrooms[i] [lives] = 2 ;
			}
		}
	}
	centipede [0][0][ishead] = true ;

	for ( int i = 29 ; i > 30 - level ; i-- )
	{
		for ( int m = 0 ; m < 30 ; m++){
		centipede [i][m][exists] = true ;
		centipede [i][m][length ] = 1 ;}
		centipede [i] [0] [speed] = 150 ; 
		centipede [i] [0][segmentExists ]= true ;
		centipede [i] [0][ is_up]= false ;
		centipede [i] [0][isleft ]= rand() % 2 ;
		centipede [i] [0][ ishead ]= true ;
		centipede [i] [0][ restricted ]= false ;
		centipede [i] [0][x]= (rand () %  28 + 1 ) * boxPixelsX;
		centipede [i] [0][y]= (rand () % 3 )       * boxPixelsX;
		

		
	}

	//for scoring 
	if (level > 1 )
	{
		int counter = 0 ;
		for ( int i = 0 ; i < 200 ; i++)
		{
			if (mushrooms [i][exists]==1)
			{
				if (mushrooms [i][lives] == 1 || mushrooms [i][isred] == 1 )
				{
					mushrooms [i][lives] = 2 ;
					mushrooms [i][ishead]= false ;
					counter++;

				}
			}
		}

		score += counter * 5 ;



	



	}
	while(window.isOpen())
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
				if (e.key.code == sf::Keyboard:: F1 ) 
				{
					ispaused = true ;
					showMenu = true ;
					
				}
		
			}
		}
        

		if(showMenu)
		{
			
			takepause = true ;
			int optionSelected = 0;



			sf::RectangleShape rectangle(sf::Vector2f( 600.f, 960.f)); 
			rectangle.setFillColor(sf::Color:: White );

    		rectangle.setOutlineColor(sf::Color:: White);

			rectangle.setFillColor   (sf::Color(10 , 20 , 15 , 190 ) );

    		rectangle.setOutlineColor(sf::Color(10 , 20 , 15 , 190 ));

    		rectangle.setOutlineThickness(4.f);

			sf::RectangleShape rectangle1(sf::Vector2f( 10 * boxPixelsX
			 , 1.5*boxPixelsX )); 
			rectangle1.setFillColor(sf::Color:: Transparent );

    		rectangle1.setOutlineColor(sf::Color:: Black );

			rectangle1.setFillColor   (sf::Color(10 , 20 , 15 , 0 ) );

    		rectangle1.setOutlineColor(sf::Color(0 , 0 , 0 , 255));

    		rectangle1.setOutlineThickness(4.f);

			sf::Text text1("CENTIPEDE", arcadefont, 110 );

			text1.setFillColor(sf::Color:: Yellow ); 

			sf::Text text2("NEW GAME", simplefont, 40 );

			text2.setFillColor(sf::Color:: Green ); 

			sf::Text text3("HIGH SCORES", simplefont, 40 );

			text3.setFillColor(sf::Color:: Green ); 

			sf::Text text4(" SETTINGS ", simplefont, 40 );

			text4.setFillColor(sf::Color:: Green ); 

			sf::Text text5("MAIN MENU", simplefont, 40 );

			text5.setFillColor(sf::Color:: Green ); 

			sf::Text text6("MAIN MENU", arcadefont, 80 );

			text6.setFillColor(sf::Color:: Green ); 

			sf::Text text7("GAME PAUSED", arcadefont, 80 );

			text7.setFillColor(sf::Color:: Green ); 

			sf::Text text8("RESUME GAME", simplefont, 40 );

			text8.setFillColor(sf::Color:: Green ); 

			
			sf::Text text9("EXIT GAME", simplefont, 40 );

			text9.setFillColor(sf::Color:: Green ); 

			
			sf::Text text10("ENTER YOUR NAME", simplefont, 40 );

			text10.setFillColor(sf::Color:: White ); 

			sf::Text text11("FEATURE COMING SOON", simplefont, 40 );

			text11.setFillColor(sf::Color:: Green ); 

				

			while ( window.isOpen())

			{
				bool flag = false ;
				sf::Event event;
				while (window.pollEvent(event)) 
				{
					if (event.type == sf::Event::Closed) 
					{
						window.close();
					} 
					
					else if (event.type == sf::Event::KeyPressed) 
					{
						if(ispaused)
						{
								
							if (event.key.code == sf::Keyboard:: Down) 
							{
								if(optionSelected<5)
								optionSelected++ ;
								

							}
							if (event.key.code == sf::Keyboard::Up) 
							{
								if(optionSelected > 1)
								optionSelected-- ;


							}

						}
						else
						{
								
							if (event.key.code == sf::Keyboard:: Down) 
							{
								if(optionSelected<4)
								optionSelected++ ;
								

							}
							if (event.key.code == sf::Keyboard::Up) 
							{
								if(optionSelected > 1)
								optionSelected-- ;


							}

						}

						if (event.key.code == sf::Keyboard:: Enter ) 
						{
							if(!ispaused)
							{
								if (optionSelected == 1 )
								{
									showMenu = false ;
									window.clear();
									flag = true ;
								}
								else if (optionSelected == 2 )
								{
									while(window.isOpen())
									{
										bool flag = false ;
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
													flag = true ;
													break;
													

												}
											}

											

										}
										window.clear();
										if(flag)
											break ;
										window.draw(menuSprite);

										rectangle.setPosition(180.f, 0.f);
										window.draw(rectangle);

										text11.setPosition(250,400);
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
									while(window.isOpen())
									{
										bool flag = false ;
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
													flag = true ;
													break;
													

												}
											}

											

										}
										window.clear();
										if(flag)
											break ;
										window.draw(menuSprite);

										

										rectangle.setPosition(180.f, 0.f);
										window.draw(rectangle);

										text11.setPosition(250,400);
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
									return 0 ;
								}


							}
							else
							{
								if (optionSelected == 1 )
								{
									showMenu = false ;
									window.clear();
									flag = true ;
								}
								else if (optionSelected == 3 )
								{
									while(window.isOpen())
									{
										bool flag = false ;
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
													flag = true ;
													break;
													

												}
											}

											

										}
										window.clear();
										if(flag)
											break ;
										window.draw(menuSprite);

										rectangle.setPosition(180.f, 0.f);
										window.draw(rectangle);

										text11.setPosition(250,400);
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
									while(window.isOpen())
									{
										bool flag = false ;
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
													flag = true ;
													break;
													

												}
											}

											

										}
										window.clear();
										if(flag)
											break ;
										window.draw(menuSprite);

										rectangle.setPosition(180.f, 0.f);
										window.draw(rectangle);

										text11.setPosition(250,400);
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
									return 0 ;
								}
								else if(optionSelected == 2 )
								{
									ispaused = false ;
									showMenu = true ;
									goto restart ;
								}

							}

						}
					}
				}

				

				if(takeName)
				{
					while(window.isOpen())
					{

						sf::Text name ;
						name.setFont(simplefont); 
						name.setString( (Username)); 
						name.setCharacterSize(50);
						name.setFillColor(sf::Color:: Red  ); 
						name.setPosition(10 * boxPixelsX +(( (10 * boxPixelsX) - (Username.length()*32))/2) , 15 * boxPixelsY - 19);

						
						bool flag = false ;
						sf::Event event;
						while (window.pollEvent(event)) 
						{
							
							if (event.type == sf::Event::Closed) 
							{
								window.close();
							} 
							else if (event.type == sf::Event::KeyPressed) 
							{
								if (event.key.code == sf::Keyboard:: Enter && Username.length()) 
								{
									flag = true ;
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
						if(flag)
						break;
						window.draw(menuSprite);

						rectangle.setPosition(180.f, 0.f);
						window.draw(rectangle);

						if(true)
						{
							rectangle1.setFillColor   (sf::Color(0 , 0 , 0 , 150) );
						}
						rectangle1.setPosition(10 * boxPixelsX , 15 * boxPixelsY - 9);
						window.draw(rectangle1);
						rectangle1.setFillColor   (sf::Color(0 , 0 , 0 , 0) );

						window.draw(name);

						text10.setPosition(292, 400);
						window.draw(text10);

						text1.setPosition(228, 40);
						window.draw(text1);

						text6.setPosition(292, 200);
						window.draw(text6);

						window.display();

					}

					takeName = false ;
				}



				


				
				window.clear();
				if(flag)
				break ;
			
				window.draw(menuSprite);

				rectangle.setPosition(180.f, 0.f);
				window.draw(rectangle);


				if(optionSelected == 1)
				{
					rectangle1.setFillColor   (sf::Color(0 , 0 , 0 , 150) );
				}
				rectangle1.setPosition(10 * boxPixelsX , 13 * boxPixelsY - 9);
				window.draw(rectangle1);
				rectangle1.setFillColor   (sf::Color(0 , 0 , 0 , 0) );
				


				if(optionSelected == 2)
				{
					rectangle1.setFillColor   (sf::Color(0 , 0 , 0 , 150) );
				}
				rectangle1.setPosition(10 * boxPixelsX , 15 * boxPixelsY - 9);
				window.draw(rectangle1);
				rectangle1.setFillColor   (sf::Color(0 , 0 , 0 , 0) );



				if(optionSelected == 3)
				{
					rectangle1.setFillColor   (sf::Color(0 , 0 , 0 , 150) );
				}
				rectangle1.setPosition(10 * boxPixelsX , 17 * boxPixelsY - 9);
				window.draw(rectangle1);
				rectangle1.setFillColor   (sf::Color(0 , 0 , 0 , 0) );



				if(optionSelected == 4)
				{
					rectangle1.setFillColor   (sf::Color(0 , 0 , 0 , 150) );
				}
				rectangle1.setPosition(10 * boxPixelsX , 19 * boxPixelsY - 9);
				window.draw(rectangle1);
				rectangle1.setFillColor   (sf::Color(0 , 0 , 0 , 0) );

				if(ispaused)
				{
					if(optionSelected == 5)
					{
						rectangle1.setFillColor   (sf::Color(0 , 0 , 0 , 150) );
					}
				
					rectangle1.setPosition(10 * boxPixelsX , 21 * boxPixelsY - 8);
					window.draw(rectangle1);
					rectangle1.setFillColor   (sf::Color(0 , 0 , 0 , 0) );

				}


				// rectangle1.setPosition(10 * boxPixelsX , 23 * boxPixelsY - 8);
				// window.draw(rectangle1);



				if(ispaused == false )
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


					text5.setPosition(355 , 404+64);
					window.draw(text5);

					text3.setPosition(352, 532+64);
					window.draw(text3);


					text4.setPosition(375, 468+64);
					window.draw(text4);


					text9.setPosition(370, 596+64);
					window.draw(text9);

				
				}

				// Display the drawn content
				window.display();
				
			}
			




		}
		

		

		///////////////////////////////////////////////////////////////
		//                                                           //
		// Call Your Functions Here. Some have been written for you. //
		// Be vary of the order you call them, SFML draws in order.  //
		//                                                           //
		///////////////////////////////////////////////////////////////

		window.draw(backgroundSprite);
		
		
		drawMushrooms(window ,  mushrooms , mushroomSprite1 , mushroomSprite2 ) ;
		drawPlayer(window, player, playerSprite);

		drawCentipede(window , crawlingClock , centipede , centipedeSpritel1 , centipedeSpritel2 , centipedeSpriter1 , centipedeSpriter2 ) ;
		if((isCentipede_not_exist (centipede)))
		{
			winEffects(bonusSound);

			//updateCentipede (centipede) ;
			level++ ;
			if (level < 5 )

			for(int i = 0 ; i  < 30 ;i++)
			for(int j =0 ; j < 30 ; j++)
			if(centipede [i][j][exists])
			centipede [i][j][speed] += 10 ;

			else if (level < 10 )

			for(int i = 0 ; i  < 30 ;i++)
			for(int j =0 ; j < 30 ; j++)
			if(centipede [i][j][exists])
			centipede [i][j][speed] += 10 ;

			else
			
			for(int i = 0 ; i  < 30 ;i++)
			for(int j =0 ; j < 30 ; j++)
			if(centipede [i][j][exists])
			centipede [i][j][speed] += 10 ;

			bullet_speed += 0.1 ; 

			goto loop1 ;
		}
		moveCentipede(centipede ,mushrooms, centipedeClock ,  centipedeSpeed ) ;
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard:: X ) ) 	
		{
				
			if (bullet[exists] == true ) 
			{
				moveBullet(bullet, bulletClock , player , bulletfire , bullet_speed);
				drawBullet(window, bullet, bulletSprite);
				
			}
		}
		else 
		{
			if(bullet [exists])
			{	
				bullet[x] = player [x] ;
				bullet [y] = player [y] ;
			}
		}
		if (bulletfire)
		{
		    bulletfiresound.play() ;
		    bulletfire = false ; 
        }


		


		if(collisionCentipede_player (centipede , player)  || collisionMushroom_player(mushrooms,player) || collisionFlea_Player(flea , player) || collisionScorpian_Player(scorpian , player )  || collisionSpider_Player(spider , player ))
		{

			lostEffects(window , mushrooms , deathSound , mushroomSound , mushroomSprite1 , mushroomSprite2) ;
			
			playerlives-- ;
			if(!playerlives)
			{

				sf::RectangleShape rectangle(sf::Vector2f( 600.f, 960.f)); 
				rectangle.setFillColor(sf::Color:: White );

				rectangle.setOutlineColor(sf::Color:: White);

				rectangle.setFillColor   (sf::Color(10 , 20 , 15 , 190 ) );

				rectangle.setOutlineColor(sf::Color(10 , 20 , 15 , 190 ));

				rectangle.setOutlineThickness(4.f);
					
					
				sf::Text text1("CENTIPEDE", arcadefont, 110 );

				text1.setFillColor(sf::Color:: Yellow ); 


				sf::Text text6("GAME OVER", arcadefont, 80 );

				text6.setFillColor(sf::Color:: Green ); 


				sf::Text text2("YOUR SCORE  : " + std :: to_string(score), simplefont, 40 );

				text2.setFillColor(sf::Color:: Green );
				
				bool flag = false ; 
				while(window.isOpen())
				{
					
					sf::Event event;


						window.clear();
						if(flag)
							break ;
						window.draw(menuSprite);
						rectangle.setPosition(180.f, 0.f);
						window.draw(rectangle);


						text1.setPosition(228, 40);
						window.draw(text1);


						text6.setPosition(292, 400);
						window.draw(text6);

						text2.setPosition(280, 600 );
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
							flag = true ;
							break ;
			
			
						}
					
					}	
				}
				goto restart ;
				showMenu = true ;
			}
			goto loop2 ;

		}
		
        if ( flea [exists] == false  && isFleaClock.getElapsedTime().asMilliseconds() > 2000)
		{
			isFleaClock.restart ( );
			if(isFleaExists (mushrooms ))
			{
				fleafire = true ;
				flea [exists]= true ;
				flea [x] = (rand () % 28 + 1 ) * boxPixelsX ;
				flea [y] = 0 ;
			}
		}  
		if ( flea [exists])
		{
			if (fleafire)
			{
				fleasound.play();
				fleafire = false ;
			}
			
			drawFlea(fleaCrawlingClock , flea , window , fleaSprite  );
			moveFlea(fleaClock , flea , mushrooms , centipede);

		} 

		if ( scorpian [exists] == false  && isScorpianClock.getElapsedTime().asMilliseconds() > 10000)
		{
			isScorpianClock.restart ( );
			makeScorpianExist (level , scorpian) ;
			if (scorpian [exists])
			scorpianfire = true ;
		}  
		if ( scorpian [exists])
		{
			if (scorpianfire)
			{
				scorpiansound.play();
				scorpianfire = false ;
			}
			drawScorpian(scorpianCrawlingClock , scorpian , window , scorpianSprite  );
			moveScorpian(scorpianClock , scorpian , mushrooms , centipede);
		} 


		if ( spider [exists] == false  && isSpiderClock.getElapsedTime().asMilliseconds() > 5000)
		{
			isSpiderClock.restart ( );
			makeSpiderExist (level , spider ) ;
			if (spider [exists])
			spiderfire = true ;
		}  

		if ( spider [exists])
		{
			if (spiderfireClock.getElapsedTime().asMilliseconds() > 1200 )
			{
				spidersound.play();
				spiderfireClock.restart();
				
			}
			
			moveSpider(spiderClock , spider , mushrooms , centipede);
			drawSpider(spiderCrawlingClock , spider , window , spiderSprite  );
		} 

	
    	collisionBullet_Mushroom(bullet,mushrooms,player , bulletfire  , score )  ;
		collisionCentipede_mushroom(centipede,mushrooms, mushroomeatsound)  ;

		twiceLength(centipede);






		collisionBullet_Spider(window , bullet,spider , spiderSprite , player , score , spiderdeathsound );
		collisionBullet_Scorpian (window ,bullet , scorpian  , mushrooms , player  , score  , scorpiandeathsound , scorpiandeathScore);
		collisionCentipede_bullet(player , centipede , bullet , mushrooms , score , level  ,killsound);
		collisionBullet_Flea (bullet , flea  , mushrooms );
		

		
		
		
	
		extraLive(score , playerlives , extraLivesound);
		showLevel(level,Level);
	    showLives(window , playerlives , livesSprite);    
		showScore(score , Score ) ;
	    movePlayer(PlayerClock ,player);   
	    window.draw(Score) ;
		window.draw(Level) ;
		window.draw(Lives);
	    window.display();

		if (takepause)
		{
			Sleep (2000) ;
			//sleep(2) in linux
			takepause = false ;
		}
	        
		window.clear();
	}
}























///////////////////////////////x/////////////////////////////////////////////
//                                                                        //
// Write your functions definitions here. Some have been written for you. //
//                                                                        //
////////////////////////////////////////////////////////////////////////////

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


void drawMushrooms(sf::RenderWindow& window, float mushrooms[200][6], sf::Sprite & mushroomSprite1, sf::Sprite & mushroomSprite2)
{
	for (int i = 0 ; i < 200 ; i++ )
	{
		if(mushrooms [i][exists])
		{
			if (mushrooms [i] [lives] >= 2 )
			{
				mushroomSprite1.setPosition(mushrooms[i][x], mushrooms[i][y]);
				
				if (mushrooms [i] [isred])
				mushroomSprite1.setTextureRect(sf::IntRect(0 , 0, boxPixelsX, boxPixelsY));
				else
				mushroomSprite1.setTextureRect(sf::IntRect(0, boxPixelsY, boxPixelsX, boxPixelsY));

				window.draw(mushroomSprite1);
			}
			else if (mushrooms [i] [lives] == 1 )
			{
				mushroomSprite2.setPosition(mushrooms[i][x], mushrooms[i][y]);
				if (mushrooms [i] [isred])
					mushroomSprite2.setTextureRect(sf::IntRect (3 * boxPixelsX ,  0 , boxPixelsX, boxPixelsY));
				else
					mushroomSprite2.setTextureRect(sf::IntRect (3 * boxPixelsX , boxPixelsY, boxPixelsX, boxPixelsY));

				window.draw(mushroomSprite2);
			}
		}

	}
	
}


void drawCentipede(sf::RenderWindow & window  , sf::Clock& crawlingClock, float  centipede[30][30][12], sf::Sprite & centipedeSpritel1 , sf::Sprite & centipedeSpritel2 , sf::Sprite & centipedeSpriter1 , sf::Sprite & centipedeSpriter2)
{
	static int rect = 1 ;
	if (crawlingClock.getElapsedTime().asMilliseconds() > 150 )
	{
		crawlingClock.restart();
		if (rect < 7)
		rect++ ; 
		else
		rect = 1 ;
	
	}
		
	centipedeSpritel1.setTextureRect(sf::IntRect ( rect * (6*boxPixelsX/8.0)+ (rect - 1 )* (boxPixelsX / 8.0), 0, boxPixelsX, boxPixelsY));
	//centipedeSpritel2.setTextureRect(sf::IntRect ( rect * (boxPixelsX - boxPixelsX/ 4 ), 0, boxPixelsX, boxPixelsY));
	centipedeSpriter1.setTextureRect(sf::IntRect ( rect * (boxPixelsX - boxPixelsX/ 4 ), 0, boxPixelsX, boxPixelsY));
	//centipedeSpriter2.setTextureRect(sf::IntRect ( rect * (boxPixelsX - boxPixelsX/ 4 ), 0, boxPixelsX, boxPixelsY));
	for (int j = 0; j < 30; j++)
	{
		if (centipede [j][0][exists]== true )
		{
			for (int  i = 0 ; i < 30  ; i++)
			{
				
				
				if ( centipede [j][i][isleft] == true  )
				{
					
					
					if ( centipede [j] [i] [segmentExists] == true )
					{
						if (centipede [j][i][ishead])
						{
							centipedeSpritel2.setPosition(centipede[j][i][x] , centipede [j][i][y] );
							
							window.draw(centipedeSpritel2);
						}
						else
						{
					
							centipedeSpritel1.setPosition(centipede[j][i][x] , centipede [j][i][y] );
							
							window.draw(centipedeSpritel1);
						}
					
					}
							
					
				}
				else
				{
					
					if ( centipede [j] [i] [segmentExists] == true )
					{
						if (centipede [j][i][ishead])
						{
							centipedeSpritel2.setPosition(centipede[j][i][x], centipede [j][i][y] );
							
							window.draw(centipedeSpritel2);
						}
						else
						{
							centipedeSpritel1.setPosition(centipede[j][i][x] , centipede [j][i][y] );
							
							window.draw(centipedeSpritel1);
						}
					
					}
					
				}
					
			
			}
		}
	}
}



void movePlayer(sf :: Clock & playerClock , float player[]) 
{
	if (playerClock.getElapsedTime().asMilliseconds() < 100 - player_speed)
	return ;
	playerClock.restart() ;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player[x] > 0) 
	{                                    
        player[x] -= boxPixelsX ;                                                                          
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player[x] < resolutionX - boxPixelsX) 
	{
        player[x] += boxPixelsX ;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player[y] > resolutionY - 5 * boxPixelsY ) 
	{                              
		player[y] -= boxPixelsY ;                                                                          
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player[y] < resolutionY - boxPixelsY) 
	{
        player[y] += boxPixelsY ;
    }
	
}

void moveCentipede( float centipede[30][30][12]  , float mushrooms[200] [6] , sf :: Clock  centipedeClock [][30], int centipedeSpeed )
{

	for ( int i = 0 ; i < 30 ; i++ )
	{
		if (centipede [i][0][exists])
		{
			for ( int j = 0 ; j < 30 ; j++)
			{
				if (centipede [i][j][segmentExists] && centipede [i][j][ishead])
				{
					if(centipedeClock[i][j].getElapsedTime().asMilliseconds() <  250  - centipede [i][j][speed])
					{
						continue ;
					}
					else
					{
						centipedeClock[i][j].restart();
					}



					{
						float temp1  [4] ;
						float temp2  [4] ;
						
						temp1 [x] = centipede [i][j][x]; 
						temp1 [y] = centipede [i][j][y];
						temp1 [isleft] = centipede [i][j][isleft];
						for ( int t = j+1 ; t < 30 ; t++ )
						{
							if(centipede [i][t][segmentExists] ) //&& (!centipede [i][t][ishead])
							{
								temp2 [ x] = centipede [i] [t][x]      ; 
								temp2 [y ] = centipede [i] [t][y]      ; 
								temp2 [isleft ] = centipede [i] [t][isleft] ;
								
								centipede [i] [t][x]      = temp1 [x];
								centipede [i] [t][y]      = temp1 [y];
								centipede [i] [t][isleft] = temp1 [isleft];

								temp1 [x]     = temp2 [x ];
								temp1 [y]     = temp2 [ y];
								temp1 [isleft]= temp2 [ isleft ];
								
								
							}
							else
							{
								break ;
							}
						}
					}




					if ( centipede [i][j][isleft])
					{
						if(centipede [i][j][x] > 0)
						{
							centipede [i][j][x] -= boxPixelsX ;
						}
						else
						{
							if (centipede[i][j][is_up])
							{
								if (centipede [i][j][y]> 25 * boxPixelsY )
								centipede [i] [j][y] -= boxPixelsY ;
								else
								centipede [i][j][is_up] = false ;
							}
							else
							{
								if(centipede [i][j][y]< 29*boxPixelsY  )
								centipede [i] [j][y] += boxPixelsY ;
								else
								{
									centipede [i] [j][is_up] = true ;
									centipede [i] [j][y] -= boxPixelsY ;
								}
							}
							centipede [i][j][isleft] = false ;

						}

					}
					else
					{
						if(centipede [i][j] [x] < resolutionX - boxPixelsX )
						{
							centipede [i][j][x] += boxPixelsX;

						}
						else
						{
							if (centipede[i][j][is_up])
							{
								if (centipede [i][j][y]> 25 * boxPixelsY )
								centipede [i] [j][y] -= boxPixelsY ;
								else
								centipede [i][j][is_up] = false ;
							}
							else
							{
								if(centipede [i][j][y]< 29*boxPixelsY  )
								centipede [i] [j][y] += boxPixelsY ;
								else
								{
									centipede [i] [j][is_up] = true ;
									centipede [i] [j][y] -= boxPixelsY ;
								}
							}
							centipede [i][j][isleft] = true  ;

						}

					}
				}
			}
		}
	}
		


	
}

void moveBullet(float bullet[], sf::Clock& bulletClock , float player []  , bool & bulletfire , int bullet_speed  ) {
	if (bulletClock.getElapsedTime().asMilliseconds() < 50 - bullet_speed)
		return;

	bulletClock.restart();
	bullet[y] -= boxPixelsY ;	
	if (bullet[y]  < 0 )
	{
				bullet[exists] = true ;

		
		bullet[x] = player[x] ;	
		bullet[y] = player[y] - boxPixelsY ;
		bulletfire = true ;
	      
		
	}
		
} 




void collisionBullet_Mushroom(float bullet[] ,float mushrooms[200][6] , float player [] , bool & bulletfire  , unsigned int & score)
{
	for(int i = 0 ; i < 200; i++ )

	    {
			if ((bullet[x] < mushrooms[i][x] + boxPixelsX/2 && bullet[x] > mushrooms[i][x] - boxPixelsX/2  )  &&  (bullet[y] < mushrooms[i][y] + boxPixelsY/2   && bullet[y] > mushrooms[i][y] -boxPixelsY/2  )  && !(player [x] == mushrooms [i][x]&& player [y]== mushrooms [i] [y]))
	        {
	            mushrooms[i][lives] -- ;
                bullet[exists] = true ;	
		        bullet[x] = player[x] ;	
		        bullet[y] = player[y] - boxPixelsY ;
		        bulletfire = true ;   
	            if(mushrooms [i] [lives] == 0 )
	            {
	                            
		                    
		        	/*
					
					int xVAL = rand () % 30 ;
					int yVAL = (rand() * rand () - rand () )% 25 ;	

	            	if (xVAL < 0 )
	            	xVAL = -xVAL  ;
	            	if (yVAL < 0 )
	            	yVAL = -yVAL  ;
					
					*/

	            	mushrooms[i][x] = -10 ;	
					mushrooms[i][y] = -10 ;
	                mushrooms[i] [exists] = false ;
	                score += 1 ;
	               
	            }
	        }

	    }


}
void collisionCentipede_mushroom(float centipede[30][30][12] , float mushrooms[200] [6]  ,  sf :: Sound & mushroomeatsound )
{
	

	for ( int j = 0 ; j < 30 ; j ++ )
		{
			if (centipede [j][0][exists] )
			{
				for (int k = 0 ; k < 30 ; k++)
				{
					if (centipede [j][k][isleft])
					{
						for (int i = 0 ; i < 200 ; i++ )
						{
							if ( centipede [j][k] [x] == mushrooms [i][x] &&  centipede [j][k] [y] == mushrooms [i][y] && centipede [j][k][ishead]  && mushrooms [i][exists] )
							{
								mushroomeatsound.play();
								mushrooms [i][exists] = false ;
								centipede [j][0][mushroomsEaten] += 1;
								if (centipede [j][k][is_up] && centipede [j][k][y] != 25 * boxPixelsY)
								{
									centipede [j][k][x] += boxPixelsX ;
									centipede [j][k][y] -= boxPixelsY ;
								}
								else
								{
									centipede [j][k][x] += boxPixelsX ;
									if(centipede [j][k][y] != 29 * boxPixelsY )
									centipede [j][k][y] += boxPixelsY ;
								}

								centipede [j][k][isleft] = false ;
							}
						}
					}
					else
					{
						for (int i = 0 ; i < 200 ; i++ )
						{
							if ( centipede [j][k][ishead]  && centipede [j][k][x]  == mushrooms [i][x]  && centipede [j][k] [y]  == mushrooms [i][y]  && mushrooms [i][exists])
							{
								mushroomeatsound.play();
								centipede [j][0][mushroomsEaten] += 1;
								mushrooms [i][exists] = false ;
								if (centipede [j][k][is_up] && centipede [j][k][y] != 25 * boxPixelsY)
								{
									centipede [j][k][y] -= boxPixelsY ;
									centipede [j][k][x] -= boxPixelsX ;
									
								}
								else
								{
									if(centipede [j][k][y] != 29 * boxPixelsY )
									centipede [j][k][y] += boxPixelsY ;
									
									centipede [j][k][x] -= boxPixelsX ;
								}


								centipede [j][k][isleft] = true ;
							}
						}
					}
				}

			}
			
		}
}

bool isCentipede_not_exist (float centipede[30][30][12])
{
	int flag = true ;
	for ( int j = 0 ; j < 30 ; j ++ )
	{
		if (centipede [j][0][exists] )
		{
			for (int k = 0 ; k < 30  ; k++)
			{
				if (centipede [j][k][segmentExists])
				{
					if((centipede [j][k][x] >= 0 &&  centipede [j][k][x] <= resolutionX) && (centipede [j][k][y] >= 0 &&  centipede [j][k][y] <= resolutionY))
					return false ;
				}
				
			}

		}
	}

	if (flag)
	return  flag ;
	else
	return false ;

}

bool collisionCentipede_player(float centipede[30][30][12] , float player [] )
{
	for ( int j = 0 ; j < 30 ; j ++ )
	{
		if (centipede [j][0][exists] )
		{
			for (int k = 0 ; k < 30  ; k++)
			{
				if (centipede [j][k][segmentExists])
				{
					if(centipede [j][k][x] == player[x] && centipede [j][k][y] == player[y] )
					{
						return true ;
					}
				}
				
			}

		}
	}
	return false ;


}

bool collisionScorpian_Player(float scorpian [] , float player []) 
{
	if ((player[x]== scorpian [x] || player [x] == scorpian [x] + boxPixelsX ) && player [y] ==  scorpian [y]  && scorpian [exists])
	{
		scorpian [exists] = false ;
		return true ;
	}
	else
	return false;
}

bool collisionSpider_Player(float spider [] , float player []) 
{

	if ((player[x]== spider [x] || player [x] == spider [x] + boxPixelsX ) && player [y] ==  spider [y]  && spider [exists])
	{
		spider [exists] = false;
		return true ;
	}
	else
	return false;
}



bool collisionFlea_Player(float flea [3], float player [2])
{
	if (player[x]== flea [x] && player [y] == flea [y] )
	return true ;
	else
	return false;
}

bool collisionMushroom_player(float mushrooms[200][6] , float player [] )
{
	for  (int i = 0 ; i < 200  ; i++)
	{
		if (mushrooms [i][exists] && mushrooms [i][isred])
		{
			if(player [x] == mushrooms [i][x] && player [y] == mushrooms [i][y])
			{
				return true ;
			}
			
			
		}
	}
	return false ;


}


void collisionCentipede_bullet(float player [] , float centipede[30][30][12] , float bullet [3] , float mushrooms[200][6] , unsigned int & score , int level , sf :: Sound & killsound )
{
	for ( int j = 0 ; j < 30 ; j ++ )
	{
		
		if (centipede [j][0][exists] )
		{
			for (int k = 0 ; k < 30 ; k++)
			{
				if (centipede[j][k][segmentExists])
				{
					
					if (centipede [j][k][x] == bullet [x] &&  centipede [j][k][y] == bullet [y] )
					{
						
						bullet [y] = player [y];
						bullet [x] = player [x];
						centipede [j][0][mushroomsEaten] = 0 ;

						for ( int o = 199 ; o >= 0 ; o-- )
						{
							if(!mushrooms[o][exists])
							{
								mushrooms [o][lives] = 2 ;
								mushrooms [o][exists] = true ;
								if(centipede [j][k][y]>24  * boxPixelsY)
								mushrooms [o][isred] = true ;
								mushrooms [o][x]= centipede [j][k][x] ;
								mushrooms [o][y]= centipede [j][k][y] ;
								break ;
							}
						}


						
						if (centipede [j][k][ishead])
						{
							killsound.play();
							
							score += 10 ;
							if(level < 3)
							{
								centipede[j][0][exists] = false ;
								for(int q = 0 ; q < 30 ; q++)
								centipede [j][q][segmentExists] = false ;
							}
							else
							{

								centipede [j][k][segmentExists] = false ;

								float temp1  [4] ;
								float temp2  [4] ;
								
								temp1 [x] =      centipede [j][k+1][x]; 
								temp1 [y] =      centipede [j][k+1][y];
								temp1 [isleft] = centipede [j][k+1][isleft];



								for ( int t = k+2 ; t < 30 ; t++ )
								{
									if(centipede [j][t][segmentExists] ) //&& (!centipede [i][t][ishead])
									{
										temp2 [ x] = centipede      [j][t][x]      ; 
										temp2 [y ] = centipede      [j][t][y]      ; 
										temp2 [isleft ] = centipede [j][t][isleft] ;
										
										centipede [j] [t][x]      = temp1 [x];
										centipede [j] [t][y]      = temp1 [y];
										centipede [j] [t][isleft] = temp1 [isleft];

										temp1 [x]     = temp2 [x ];
										temp1 [y]     = temp2 [ y];
										temp1 [isleft]= temp2 [ isleft ];
										
										
									}
									else
									{
										break ;
									}
								}



								centipede [j][k+1][ishead] = true ;
								centipede [j][k+1][y] += boxPixelsY ;
							
								if (centipede [j][k+1][isleft])
								centipede [j][k+1][isleft] = false ;
								else
								centipede [j][k+1][isleft] = true ;
									
								

							}

							
						}
						else
						{
							score += 20 ;

							float temp1  [4] ;
							float temp2  [4] ;
								
								temp1 [x] =      centipede [j][k+1][x]; 
								temp1 [y] =      centipede [j][k+1][y];
								temp1 [isleft] = centipede [j][k+1][isleft];



								for ( int t = k+2 ; t < 30 ; t++ )
								{
									if(centipede [j][t][segmentExists] ) //&& (!centipede [i][t][ishead])
									{
										temp2 [ x] = centipede      [j][t][x]      ; 
										temp2 [y ] = centipede      [j][t][y]      ; 
										temp2 [isleft ] = centipede [j][t][isleft] ;
										
										centipede [j] [t][x]      = temp1 [x];
										centipede [j] [t][y]      = temp1 [y];
										centipede [j] [t][isleft] = temp1 [isleft];

										temp1 [x]     = temp2 [x ];
										temp1 [y]     = temp2 [ y];
										temp1 [isleft]= temp2 [ isleft ];
										
										
									}
									else
									{
										break ;
									}
								}

							for (int t = 0 ; t < 30 ; t++ )
							{
								if (centipede [t][0][exists] == false )
								{
									for(int d = 0 ; d < 30 ;d++)
									centipede [t][d][exists] = true;
									for(int q = 0 , w = k+1 ; w < 30 ; q++ ,w++ )
									{
										if(centipede [j][w][segmentExists])
										{
											centipede [t][q][segmentExists] = true ;
											centipede [t][q][x] = centipede [j][w][x] ;
											centipede [t][q][y] = centipede [j][w][y] ;
											centipede [t][q][isleft] = centipede [j][w][isleft] ;
										}
										else
										{
											break;
										}
									}

									centipede [t][0][ishead] = true ;
									centipede [t][0][mushroomsEaten] = 0 ;
									centipede [t] [0] [y] += boxPixelsY ;





									


									if(centipede [t] [0] [isleft])
									{
										
										centipede [t] [0] [isleft] = false ;
									}
									else
									{
										
										centipede [t] [0] [isleft] = true ;
									}

									break ;
								}
							}

							for(int t = k ; t < 30 ; t++)
							centipede [j][t][segmentExists] = false ;
							

							
						

						}
						
						
						
						
					}

				}
					
			}
		}

	}
			
}


void showScore (unsigned int & score  , sf :: Text & Score ) 
{
	Score.setString("SCORE :  " + std :: to_string(score)); 

	
}

void showLevel ( int & level  , sf :: Text & Level ) 
{
	Level.setString("LEVEL :  " + std :: to_string(level)); 

	
}


void showLives (sf :: RenderWindow &window  , int & playerlives , sf :: Sprite & livesSprite) 
{
	for ( int i = 0 ; i < playerlives ; i++)
	{
		livesSprite.setPosition ( 18.5* boxPixelsX + 2*i*  boxPixelsX , 30.2 * boxPixelsY + 7);
		window.draw(livesSprite);
	}
}


void updateCentipede ( float  centipede[30][30][12])
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


void winEffects ( sf :: Sound  bonusSound)
{
	bonusSound.play();
	Sleep (2000);
	//sleep(2);   for linux unistdlib.h

}

void lostEffects (sf::RenderWindow& window ,float mushrooms[200][6] , sf :: Sound deathSound , sf :: Sound mushroomSound  ,sf :: Sprite & mushroomSprite1  ,sf :: Sprite & mushroomSprite2)
{
	
	
	
	deathSound.play () ;
	Sleep (2000);
	//sleep(2);   for linux unistdlib.h


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
			sleep(0.5);
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
			sleep(0.5);
			mushroomSprite2.setColor(sf::Color(255, 255, 255, 255  ));
			
    	    window.draw(mushroomSprite2);
		}

	}
	*/
}

void changeColor(int level , sf :: Sprite & centipedeSpritel1 , sf :: Sprite & centipedeSpritel2 , sf :: Sprite & centipedeSpriter1 , sf :: Sprite & centipedeSpriter2)

{
	if (level == 1 )
	return ;
	else 
	{
		int r = rand() % 255 ;
		//int g = rand() % 255 ;
		int b = rand() % 255 ;

		

		centipedeSpritel2.setColor(sf :: Color ( r,255,b,255 ));
		centipedeSpriter2.setColor(sf :: Color ( r,255,b,255 ));
	}
}



bool isFleaExists(float mushrooms[][6])
{
	int counter = 0;
	for ( int i= 0 ; i < 200 ; i++ )
	{
		if (( mushrooms [i][y] > 24 * boxPixelsY) && (mushrooms [i][exists] == true ))
		counter++ ;

	}
	 
	if (counter == 3 )
	return true ;
	else 
	return false ;
}


void drawScorpian( sf :: Clock & scorpianCrawlingClock ,float scorpian [3] ,sf :: RenderWindow & window , sf:: Sprite scorpianSprite)
{

	static int rect = 0 ;
	if (scorpianCrawlingClock.getElapsedTime().asMilliseconds() >  150 )
	{
		scorpianCrawlingClock.restart();
		if (rect < 5 )
		rect++ ; 
		else
		rect = 1 ;
	
	}


	if (rect = 1 )
	scorpianSprite.setTextureRect(sf::IntRect (0 , 0 , 2* boxPixelsX, boxPixelsY));
	else if ( rect == 2)
	scorpianSprite.setTextureRect(sf::IntRect (2 * boxPixelsX, 0 , 2 * boxPixelsX, boxPixelsY));
	else if ( rect == 3)
	scorpianSprite.setTextureRect(sf::IntRect (4 * boxPixelsX ,  0, 2 * boxPixelsX, boxPixelsY));
	else if ( rect == 4)
	scorpianSprite.setTextureRect(sf::IntRect (6 * boxPixelsX, 0 , 2 * boxPixelsX, boxPixelsY));





	scorpianSprite.setPosition(scorpian[x] ,  scorpian [y]);
	window.draw (scorpianSprite);
	

}
void drawFlea( sf :: Clock & fleaCrawlingClock ,float flea [3] ,sf :: RenderWindow & window , sf:: Sprite fleaSprite)
{
	static int rect = 0 ;
	if (fleaCrawlingClock.getElapsedTime().asMilliseconds() > 150 )
	{
		fleaCrawlingClock.restart();
		if (rect < 5 )
		rect++ ; 
		else
		rect = 1 ;
	
	}


	if (rect = 1 )
	fleaSprite.setTextureRect(sf::IntRect (0 , 0 , boxPixelsX, boxPixelsY));
	else if ( rect == 2)
	fleaSprite.setTextureRect(sf::IntRect (boxPixelsX, 0 , boxPixelsX, boxPixelsY));
	else if ( rect == 3)
	fleaSprite.setTextureRect(sf::IntRect (0 , boxPixelsY , boxPixelsX, boxPixelsY));
	else if ( rect == 4)
	fleaSprite.setTextureRect(sf::IntRect (boxPixelsX, boxPixelsY , boxPixelsX, boxPixelsY));
	



	fleaSprite.setPosition(flea[x],flea[y]);
	window.draw(fleaSprite);

}
void drawSpider( sf :: Clock & spiderCrawlingClock ,float spider [3] ,sf :: RenderWindow & window , sf:: Sprite spiderSprite)
{
	static int rect = -1 ;
	if (spiderCrawlingClock.getElapsedTime().asMilliseconds() > 150 )
	{
		spiderCrawlingClock.restart();
		if (rect < 7  )
		rect++ ; 
		else
		rect = 0 ;
	
	}

	spiderSprite.setTextureRect(sf::IntRect (rect* 60  , 0 , 60 , boxPixelsY));
	
	



	spiderSprite.setPosition(spider[x],spider[y]);
	window.draw(spiderSprite);

}

void moveSpider(sf :: Clock & spiderClock , float spider [ ], float mushrooms[200][6] , float centipede[30][30][12])
{
	static bool flag = true ;
	if (spiderClock.getElapsedTime().asMilliseconds() < 100  || spider [exists]== false)
	return ;
	spiderClock.restart () ;
	static bool is_up = false ;  
	static bool is_down     = false ;
	static bool is_up_right = false ;
	static bool is_down_right =  false;
	static bool is_up_left = false ;
	static bool is_down_left = false ;

	
	if (flag)
	{
		if ( spider [x] == -2 * boxPixelsX  )
		is_down_right = true ;
		else
		is_down_left = true ; 


		flag = false ;
	}
	if (is_down_right )
	{
		if ( spider [y] < resolutionY - boxPixelsY )
		{
			spider [x] += boxPixelsX ;
			spider [y] += boxPixelsY ;
		}
		else
		{
			is_down_right = false ;


			int temp = rand () % 3 ;
			if (temp == 0 )
			is_up_right = true;
			else if ( temp == 1 )
			is_up_left= true ;
			else
			is_up = true ; 
		}


	}
	else if (is_down_left )
	{
		if ( spider [y] < resolutionY - boxPixelsY )
		{
			spider [x] -= boxPixelsX ;
			spider [y] += boxPixelsY ;
		}
		else
		{
			is_down_left = false ;


			int temp = rand () % 3 ;
			if (temp == 0 )
			is_up_right = true;
			else if ( temp == 1 )
			is_up_left= true ;
			else
			is_up = true ;
		}
	}

	else if (is_down )
	{
		if ( spider [y] < resolutionY - boxPixelsY )
		{
			
			spider [y] += boxPixelsY ;
		}
		else
		{
			is_down = false ;


			int temp = rand () % 3 ;
			if (temp == 0 )
			is_up_right = true;
			else if ( temp == 1 )
			is_up_left= true ;
			else
			is_up = true ;
 
		}


	}
	else if (is_up)
	{
		if ( spider [y] > (rand() % 6 + 20 )* boxPixelsY )
		{
			
			spider [y] -= boxPixelsY ;
		}
		else
		{
			is_up = false ;

			
			int temp = rand() % 3 ;
			if(temp == 0 )
			is_down_right = true ;
			else if (temp == 1 )
			is_down_left = true ;
			else
			is_down = true ;
		}

	}
	else if (is_up_right)
	{
		if ( spider [y] > (rand() % 8 + 19 )* boxPixelsY )
		{
			
			spider [y] -= boxPixelsY ;
			spider [x]	+= boxPixelsX ;	}
		else
		{
			is_up_right = false ;



			int temp = rand() % 4;
			if(temp == 0 || temp == 3 )
			is_down_right = true ;
			else if (temp == 1 )
			is_down_left = true ;
			else
			is_down = true ;
		}

	}

	else if (is_up_left)
	{
		if ( spider [y] > (rand() % 8+ 19 ) * boxPixelsY )
		{
			
			spider [y] -= boxPixelsY ;
			spider [x]	-= boxPixelsX ;	}
		else
		{
			is_up_left = false ;



			int temp = rand() % 3 ;
			if(temp == 0 )
			is_down_right = true ;
			else if (temp == 1 )
			is_down_left = true ;
			else
			is_down = true ;
		}

	}

	for ( int i = 0 ; i < 200 ; i++ )
	{
		if (( mushrooms [i] [x] == spider [x] || mushrooms [i] [x] == spider [x] + boxPixelsX ) && mushrooms [i][y] == spider [y] && mushrooms [i][exists] )
		{
			mushrooms [i] [exists] = false ;
		}
	}

	if(spider [x] > resolutionX || spider [x] < - 60)
	{
		spider [exists] = false ;
		flag = true ;
	}
	
}



void moveScorpian(sf :: Clock & scorpianClock , float scorpian [ ], float mushrooms[200][6] , float centipede[30][30][12])
{
	if (scorpianClock.getElapsedTime().asMilliseconds() < 80 )
	return ;
	scorpianClock.restart () ;

	if (scorpian [x] < resolutionX)
	{
		scorpian [x] += boxPixelsX ;
		for ( int i = 0 ; i < 200 ; i++ )
		{
			if (mushrooms [i] [exists] && mushrooms [i][x] == scorpian [x] && mushrooms [i][y] == scorpian [y])
			{
				mushrooms [i][isred ] = true ;
			}
		}

	}
	else
	{
		scorpian [exists] = false ;
	}



}
void moveFlea(sf :: Clock & fleaClock ,  float flea [3] , float mushrooms[200][6] , float centipede[30][30][12])
{
	if (fleaClock.getElapsedTime().asMilliseconds() < 60)
	return ;
	fleaClock.restart () ;

	if (flea [y] < resolutionY  )
	{
		flea [y] += boxPixelsY ;
		
		int temp = rand() % 3 ; 
		if(!temp && flea [y] <= 28 * boxPixelsY )
		{
			for ( int i = 0 ; i  < 200 ; i++)
			{
				if ( ! mushrooms [i][exists])
				{
					
					mushrooms [i][exists]= true ;
					mushrooms [i][isred]= false ;
					mushrooms [i][lives]= 2 ;
					mushrooms [i][x]= flea [x] ;
					mushrooms [i][y] = flea [y] ;
					break ;
				}
			}
		}
		

	}
	else
	flea [exists] = false ;
}

void collisionBullet_Spider (sf :: RenderWindow & window ,float bullet[] , float spider [] , sf:: Sprite & spiderSprite  , float player [] , unsigned int & score , sf :: Sound & spiderdeathSound)
{
	static bool showScore = false ;
	static sf :: Clock showScoreClock ; 
	static int distance = 0 ;


	if ((bullet [x] == spider [x] || bullet [x] == spider [x] + boxPixelsX )&& bullet [y] == spider [y] && spider [exists] && player [y]!= spider[y] )
	{
		spiderdeathSound.play();
		spider [exists ] = false ; 
		

		distance = abs(player[y]-spider[y]);
		showScore = true ;
		showScoreClock.restart();
		if(distance== boxPixelsY)
		score += 900 ;
		else if (distance == 2* boxPixelsY)
		score+=600 ;
		else
		score+= 300 ;
		
	}


	if(showScore)
	{
		if ( showScoreClock.getElapsedTime().asMilliseconds() < 2000 )
		{
			if(distance== boxPixelsY)
			spiderSprite.setTextureRect(sf::IntRect(120, boxPixelsX , 60 , boxPixelsY));
			else if (distance == 2* boxPixelsY)
			spiderSprite.setTextureRect(sf::IntRect(60, boxPixelsX , 60 , boxPixelsY));
			else
			spiderSprite.setTextureRect(sf::IntRect(0, boxPixelsX , 60 , boxPixelsY));



			spiderSprite.setPosition(spider[x],spider[y]);
			window.draw(spiderSprite);
		}
		else
		{
			showScore = false ;
		}
	}
}


void collisionBullet_Scorpian (sf :: RenderWindow & window , float bullet[] , float scorpian [] , float mushrooms [][6]  , float player [] ,unsigned int & score , sf :: Sound & scorpiandeathSound  , sf::Text & scorpiandeathScore) 
{
	static bool showScore = false ;
	static sf :: Clock showScoreClock ;

	if ((bullet [x] == scorpian [x] || bullet [x] == scorpian [x] + boxPixelsX )&& bullet [y] == scorpian [y] && scorpian [exists] &&  player [y] != scorpian [y]) 
	{
		
		scorpiandeathSound.play();
		scorpian [exists ] = false ; 
		score += 1000 ;
		showScoreClock.restart();
		showScore = true ;

	
	
	}

	if(showScore)
	{
		if ( showScoreClock.getElapsedTime().asMilliseconds() < 2000 )
		{
			scorpiandeathScore.setPosition(scorpian[x],scorpian[y]);
			window.draw(scorpiandeathScore);
		}
		else
		{
			showScore = false ;
		}
	}
}
void collisionBullet_Flea (float bullet[] , float flea [] , float mushrooms [200][6])
{
	if(bullet [x] == flea [x] && bullet [y] == flea [y])
	{
		flea [exists] = false ;

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


void makeScorpianExist(int level , float scorpian[3] )
{
	int temp ;

	if (level > 0 )
	{
		temp = rand () % 2 ;
		if ( !temp )
	{
		scorpian [x]= 0;
		scorpian [y] = (rand () % 28 + 1 ) * boxPixelsY ;
		scorpian [exists] = true  ;
	}
	} 

	
	
	
	
	
	
}


void makeSpiderExist(int level , float spider[3] )
{
	int temp ;

	if (level > 0 )
	{
		temp = rand () % 2 ;
		if ( !temp )
	{
		if(rand() % 3)
		spider [x] = -2 * boxPixelsX ;
		else
		spider [x] = resolutionX ;
		spider [y] = (rand () % 7 + 22 ) * boxPixelsY ;
		spider [exists] = true  ;
	}
	} 

	
	
	
	
	
	
}

void twiceLength (float centipede [30][30][12])
{

	for ( int i = 0 ; i < 30 ; i++ )
	{
		if (centipede [i][0][mushroomsEaten] >= 5 )
		{

			centipede [i][0][mushroomsEaten] = 0 ;

			int length = 0 ;
			bool flag = true ;
			for (int  j = 0 ; j < 30 ; j++)
			{
				if(flag)
				{
					if (centipede [i][j][segmentExists])
					length++;
					else
					break ;
				}
				
				
			}
			
			for (int j = length   ; j < 2*length ; j++)
			{
				if (centipede [i][length-1][isleft])
				{
					centipede [i][j][segmentExists]= true ;
					centipede [i][j][y]= centipede[i][j-1][y];
					centipede [i][j][x]= centipede[i][j-1][x] + boxPixelsX  ;
					centipede [i][j][isleft]= centipede [i][j-1][isleft] ;		
					centipede [i][j][ishead]= false ;
				}
				else
				{
					centipede [i][j][segmentExists]= true ;
					centipede [i][j][y]= centipede[i][j-1][y];
					centipede [i][j][x]= centipede[i][j-1][x]  - boxPixelsX ;
					centipede [i][j][isleft]= centipede [i][j-1][isleft] ;	
					centipede [i][j][ishead]= false ;
				}
			}
		

			

		}
			 
	}
}
void extraLive(unsigned int & score , int & lives  , sf:: Sound & extraLivesound  )
{
	static bool flag1 = true  , flag2 = true , flag3 = true  , flag4 = true ;
	
	if(flag1)
	{
		if (score > 10000)
		{
			extraLivesound.play();
			if(lives < 6 )
			lives++ ;
			flag1 = false;
		}
	}
	if(flag2)
	{
		if (score > 12000)
		{
			extraLivesound.play();
			if(lives < 6 )
			lives++ ;
			flag2 = false;
		}
	}
	if(flag3)
	{
		if (score > 15000)
		{
			extraLivesound.play();
			if(lives < 6 )
			lives++ ;
			flag3 = false ;
		}
	}
	if(flag3)
	{
		if (score > 20000)
		{
			extraLivesound.play();
			if(lives < 6 )
			lives++ ;
			flag3 = false;
		}
	}
}
//end
 
