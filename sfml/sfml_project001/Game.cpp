#include "Game.h"

Game::Game()
{
	
	this->initVeriables();
	this->initWindow();
	this->initRod();
//	this->initFonts();
	//this->initText();
	this->initEnemys();
}

Game::~Game()
{
	delete this->window;
}

void Game::update()
{
	this->pollEvents();

	//end game condition
	if(this->health<=0)
	{
		this->endGame = true;
	}
	if(!this->endGame){

	this->updateMousePosition();
	//this->updateText();
	
	this->updateEnemies();
	this->updaterodPosition();
	this->updateRod();
	this->updateRodElif();
	}
}

void Game::updateMousePosition()
{
	/*
	
	updates mouse positions
	-mouse position relative to window
	*/

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->ev)) {

		switch (ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;

		case sf::Event::KeyPressed:
			if(ev.key.code==sf::Keyboard::Escape)
			this->window->close();
			break;

		}

}

}

void Game::render()
{
	/*
	-clear old frame
	-set color
	-render draw objects

	*/
	this->window->clear(sf::Color(0, 0, 0));
	
	//draw game objects
	this->renderRod(*this->window);
	this->renderEnemies(*this->window);
	//this->renderText(*this->window);

	this->window->display();
	
}

void Game::spawnEnemy()
{
	/**

	spawns enemies and sett their color and position
	-set a random position
	-set a rsndom color
	-adds enemy to the vector
	*/

	this->enemy.setPosition(
	static_cast<float>(rand()% static_cast<int>(this->window->getSize().x-this->enemy.getSize().x)),
	0.f
	);

	this->enemy.setFillColor(sf::Color(rand()%255, rand() % 255, rand() % 255));
	//spawn the enemy
	this->enemies.push_back(this->enemy);

	//remove enemies at end of screen
}

void Game::renderEnemies(sf::RenderTarget& target)
{
	//rendering all enemies
	for (auto& e : this->enemies)
	{

		target.draw(e);
	}
}

void Game::updateEnemies()
{

	/**
	* update the enemy spawn time and spawns enemies
	* when the total amount of enemies is smaller than the maximum.
	* moves the enemies downards:
	* removes the enemies at the edge of the screen..//todo
	
	*/
	//update for timer for enemey spawnig 
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer <= this->enemySpawnTimerMax)
		{
			//spawn the enemy reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
			this->enemySpawnTimerMax += 1.f;
	}

	//moving andupdate enemies

	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;
		this->enemies[i].move(0.f, 2.f);

		if (this->enemies[i].getPosition().y > this->window->getSize().y) {
			this->enemies.erase(this->enemies.begin() + i);

			//healt decreasing
			this->health -= 1;
			this->points -= 1;

			//elif
			this->healthElif -= 1;
			this->pointsElif -= 1;
			//std::cout << "Points :" << this->points << "Healt :" << this->health << " \n ";
		}
	}
		//chech if clicked  upon 
		//if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		//	

		//	if (this->mouseHeld == false) {

		//		this->mouseHeld = true;
		//		bool deleted = false;
		//		for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
		//		{
		//			if (this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {

		//				//deleted enemy
		//				deleted = true;
		//				this->enemies.erase(this->enemies.begin() + i);

		//				//game poits
		//				this->points += 10;
		//				std::cout << "Points :" << this->points << "Healt :" << this->health<<" \n ";
		//				
		//			}
		//		}
		//	}
		//	else
		//	{
		//		this->mouseHeld = false;
		//	}
		//}


	
}


void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->iuText);
}

void Game::updateText()
{
	std::stringstream ss;
	ss << "Points : " <<this->points ;
	this->iuText.setString(ss.str());
}

void Game::renderRod(sf::RenderTarget& target)
{
	target.draw(this->rod);
	target.draw(this->rodElif);
}


void Game::updateRod()
{

	//std::cout << "pozisyon  x:"<<this->rod.getPosition().x<< "y:"<<this->rod.getPosition().y << "\n";

	////chech if clicked  upon 


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {

		if(this->carp_x==0){
			std::cout << "Duvara dayandı\n";
		}
		else {
			
			//this->rod_x += 5;
			this->rod.move(5.f,0.f);
			//this->rod_r = 0.f;
			this->rod.setRotation(this->rod_r);
		}

	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {

		this->rod.move(-5.f, 0.f);
	//	this->rod_r = 0.f;
		this->rod.setRotation(this->rod_r);
		//this->rod_x -= 5;

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

		this->rod.move(0.f, -5.f);
		this->rod_r = 90.f;
		this->rod.setRotation(this->rod_r);
		//this->rod_x -= 5;

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

		this->rod.move(0.f, +5.f);
		this->rod_r = 90.f;
		this->rod.setRotation(this->rod_r);
		//this->rod_x -= 5;

	}

	for (size_t i = 0; i < this->enemies.size(); i++)
	{
		if (this->rod.getGlobalBounds().contains(this->enemies[i].getPosition())) {

			//deleted enemy
			this->enemies.erase(this->enemies.begin() + i);

			//game poits
			this->points += 10;
			this->rod_w += 0.1f;
			this->rod_h += 0.1f;
			std::cout << "Points :" << this->points << "Healt :" << this->health << " \n ";

			//random color with rod
			this->rod.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
		}

	}

}

void Game::updateRodElif()
{

	//std::cout << "pozisyon  x:"<<this->rod.getPosition().x<< "y:"<<this->rod.getPosition().y << "\n";

	////chech if clicked  upon 


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {

			//this->rod_x += 5;
			this->rodElif.move(5.f, 0.f);
			//this->rod_r = 0.f;
			this->rodElif.setRotation(this->rodElif_r);
		

	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {

		this->rodElif.move(-5.f, 0.f);
		//	this->rod_r = 0.f;
		this->rodElif.setRotation(this->rodElif_r);
		//this->rod_x -= 5;

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

		this->rodElif.move(0.f, -5.f);
		this->rodElif_r = 90.f;
		this->rodElif.setRotation(this->rodElif_r);
		//this->rod_x -= 5;

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {

		this->rodElif.move(0.f, +5.f);
		this->rodElif_r = 90.f;
		this->rodElif.setRotation(this->rodElif_r);
		//this->rod_x -= 5;

	}

	for (size_t i = 0; i < this->enemies.size(); i++)
	{
		if (this->rodElif.getGlobalBounds().contains(this->enemies[i].getPosition())) {

			//deleted enemy
			this->enemies.erase(this->enemies.begin() + i);

			//game poits
			this->pointsElif += 10;
			this->rodElif_w += 0.1f;
			this->rodElif_h += 0.1f;
			//std::cout << " Points :" << this->points << "Healt :" << this->health << " \n ";

			//random color with rod
			this->rodElif.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
		}

	}

}

void Game::updaterodPosition()
{
//	this->rod.setPosition(this->rod_x, this->rod_y);
	//std::cout << "carpmaya kalan :"<<this->carp_x<<"\n";
	this->carp_x = this->window_w - this->rod_w - this->rod.getPosition().x;
	//temp
	//this->rod_r = 0.f;
	this->rod.setRotation(this->rod_r);
	this->rod.setSize(sf::Vector2f(this->rod_h, this->rod_w));

	this->rodElif.setRotation(this->rodElif_r);
	this->rodElif.setSize(sf::Vector2f(this->rodElif_h, this->rodElif_w));

	std::cout << " Elif Points  :" << this->pointsElif << " -Healt :" << this->healthElif << " \n ";
	std::cout << " Remzi Points :" << this->points << " -Healt :" << this->health << " \n ";
}



//accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}



void Game::initVeriables()
{
	this->window = nullptr;

	//Game Logic
	this->window_h=600;
	this->window_w=800;

	this-> points=0;
	this->enemySpawnTimerMax=10.f;
	this->enemySpawnTimer= this->enemySpawnTimerMax;
	this->maxEnemies=100;
	this->mouseHeld = false;
	this->health = 1000;

	this->endGame = false;
	this->rod_h = 70;
	this->rod_w = 10;
	//elif
	this->rodElif_h = 70;
	this->rodElif_w = 10;
	this->healthElif = 1000;
	this->pointsElif = 0;
	this->rodElif_r = 0.f;

	this->rod_x = 50;
	this->rod_y = this->window_h - this->rod_h;
	this->carp_x = this->window_w - this->rod_w- this->rod_x;
	this->rod_r = 0.f;
	//temp
	this->t = 0;
}

void Game::initWindow()
{
	this->videoMode.height = this->window_h;
	this->videoMode.width = this->window_w;
	
	this->window= new  sf::RenderWindow(this->videoMode,"FIRST GAME 001",sf::Style::Titlebar| sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
	if (!this->font.loadFromFile("BrowserMDL.ttf")) {
	throw("Game font error");
	}
}

void Game::initText()
{
	this->iuText.setFont(this->font);
	this->iuText.setCharacterSize(32);
	this->iuText.setFillColor(sf::Color::White);
	this->iuText.setString("None");
}

void Game::initEnemys()
{
	this->enemy.setPosition(10.f,10.f);
	this->enemy.setSize(sf::Vector2f(10.f,10.f));
	this->enemy.setScale(sf::Vector2f(0.5f,0.5f));
	this->enemy.setFillColor(sf::Color::Cyan);
	/*this->enemy.setOutlineColor(sf::Color::Green);
	this->enemy.setOutlineThickness(1.f);*/

}

void Game::initRod()
{

	this->rod.setPosition(this->rod_x, this->rod_y);
	this->rod.setSize(sf::Vector2f(this->rod_h, this->rod_w));
	this->rod.setScale(sf::Vector2f(1.f, 1.f));
	this->rod.setFillColor(sf::Color::Color(100,100,300,255));


	this->rodElif.setPosition(this->rod_x+500, this->rod_y);
	this->rodElif.setSize(sf::Vector2f(this->rod_h, this->rod_w));
	this->rodElif.setScale(sf::Vector2f(1.f, 1.f));
	this->rodElif.setFillColor(sf::Color::Color(200, 100, 300, 255));

}
