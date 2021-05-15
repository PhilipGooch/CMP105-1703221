#pragma once

#include "Card.h"
#include "Minion.h"
#include "Input.h"
#include "Player.h"
#include <Vector>
#include <deque>
#include <math.h>
#include <deque>
#include <iostream>
#include "AudioManager.h"

using namespace std;
using namespace sf;
using namespace staticFunctions;

class Game
{

public:
	Game(sf::RenderWindow*, Input*, Line*);
	~Game();

	void handleInput();
	void update(float);
	void render();
	void resizeWindow();
	
	void displayArrow();
	void endTurn();
	bool repositioning(float dt);
	void displayBackground();

private:
	sf::RenderWindow* window;
	Input* input;
	Line* mouse;
	AudioManager audioManager;

	Player player1;		//Creating players
	Player player2;

	Player players[2];	//Creating an array for the players for easy access to both. (Stops duplicate code as i can access them through a for loop.)

	Texture backgroundTexture;
	Sprite backgroundSprite;
	Font font;

	Texture pauseTexture;
	Sprite pauseSprite;
	Texture victoryTexture;
	Sprite victorySprite;
	Texture defeatTexture;
	Sprite defeatSprite;

	ConvexShape endTurnButton;
	float endTurnPosX;	//Position of end turn button.
	float endTurnPosY;

	void beginDraw();
	void endDraw();
	Vertex line[2];		//The line splitting the two sides of the board.
	Vertex rope[2];		//The line for the rope.
	Vertex arrow[2];	//For the arrow for where to attack.
	
	Font fpsFont;
	Text fpsText;
	int frameCount;		//Variables used to calculate frames per second.
	float sum;

	bool cardSelected;	//Checking if any card is selected.

	float deltaTime;	

	deque<Vector2i> que;	//This is a deque of vector2i to store the IDs of the minions in a fight. This is read as a list of instructions when annimating.
	Vector2i interaction;	//The IDs of the minions in a fight.

	bool animationState = false;		//This is for the animations. the animation will only move on to the next one in the que when the board is in the right combination of states.
	bool repositioningState = false;	
	bool hoveringState = false;
	bool passiveState = true;

	float turnTimer;	//Timer for the amount of time left in a turn.

	bool paused;		//Game states. (These could be enumerators.)
	bool started;
	bool tutorial;	
	bool victory;
	bool defeat;

	Texture tutorialTexture;	//Textures and Sprites
	Sprite tutorialSprite;

	Texture titleTexture;
	Sprite titleSprite;

	RectangleShape playButton;		//Buttons
	RectangleShape rulesButton;
	Text playText;
	Text rulesText;

	bool mousePressed = false;		//Hacky variable to stop the tutorial page from flicking backwards and forwards when holding mouse down on the tutorial button.

	int turn = 0;		//Keeping track of who's turn it is.
};

