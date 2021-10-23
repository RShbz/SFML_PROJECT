#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <conio.h>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

class Game
{
public:
	//cosntructor / destructor
	Game() ;
	virtual ~Game();

	//functions
	void update();
	void render();
	
	//mouse
	void updateMousePosition();
	void pollEvents();

	//Enemy
	void spawnEnemy();
	void renderEnemies(sf::RenderTarget& target);
	void updateEnemies();
	
	//text
	void renderText(sf::RenderTarget & target);
	void updateText();
	
	//rod
	void renderRod(sf::RenderTarget & target);
	void updateRod();
	void updateRodElif();
	void updaterodPosition();
	//veriables


	//Accerssors
	const bool running() const;
	const bool getEndGame() const;

	//keys push
	void keyPush();
	void isKeyPressed();
private:
	//veriables
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Game Logic
	float window_h;
	float window_w;

	int points;

	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;
	int health;
	bool endGame;
	//rod 
	float rod_h;
	float rod_w;
	//elif
	float rodElif_h;
	float rodElif_w;
	int healthElif;
	int pointsElif;
	int rodElif_r ;

	float rod_x;
	float rod_y;
	float carp_x;
	float rod_r;
	//temp
	size_t t;

	//Game Objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;
	sf::RectangleShape rod;
	sf::RectangleShape rodElif;

	//Mouse Position
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2f rodPosView;

	//Resources
	sf::Font font;

	//Text
	sf::Text iuText;

	//Function 
	void initVeriables();
	void initWindow();
	void initFonts();
	void initText();
	void initEnemys();
	void initRod();

};
enum keys{
			 Left,
	         Right,
	         Up,
	         Down
};
