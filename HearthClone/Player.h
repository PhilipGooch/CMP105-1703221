#include <vector>
#include "Minion.h"
#include "Card.h"
#include "Input.h"
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "Hero.h"
#include "StaticFunctions.h"

using namespace std;
using namespace sf;
using namespace staticFunctions;

class Player
{

public:
	Player();
	Player(RenderWindow*, Input*, Line*, Font*, int, AudioManager*);
	~Player();

	void resizeWindow();
	void handleInput();
	void update(float);
	void render();

	//GETTERS
	bool getDragging();		//If the mouse is being dragged.
	int getHealth();
	int getManaCrystals();
	vector<Minion>& getMinions();			//have to pass by reference here as i do not want a copy. was not able to achieve this with pointers.
	bool getCardSelected();
	bool getMinionSelected();
	Hero& getHero();

	//SETTERS
	void setHealth(int);
	void setTurn(bool);
	void setMinionSelected(bool);
	void setMinionsTargetPos();

	//MINIONS
	void displayMinions();
	bool otherMinionsSelected(int);
	void minionCollisions();
	void checkHoveringIndex();
	void setMinionsRenderPos();
	int findMinionIndex();
	void calculateMinionPositions();

	//CARDS
	void displayHand();
	void calculateCardPositions();
	bool miniCardCollisions();

	//GAMEPLAY
	void createDeck();
	void drawCard();
	void gainManaCrystals(int);
	void gainMana(int);
	void placeMinion(int);
	bool checkEndTurn();
	
	
	Minion blueprintMinion;		//used for getting dimensions for collision detection in game class. (should be private but should probably redesign this anyway...)

	bool seperatingState = false;

	vector<Card>& getHand();

	AudioManager* audioManager;


private:
	RenderWindow* window;
	Input* input;
	Line* mouse;
	Font* font;
	int player;

	int manaCrystals;
	int mana;
	int health;
	int heroPowerManaCost;
	bool turn;
	bool dragging;
	bool cardSelected;
	bool minionSelected;

	Hero hero;
	vector<Card> deck;
	vector<Card> hand;
	vector<Minion> minions;
	Text text;
	Image mask;
	Texture texture;
	
	CircleShape heroPower;
	CircleShape heroPowerManaCrystal;
	CircleShape manaCrystal;
	CircleShape circleCrystal;
	

	Vector2f manaCrystalsPos;
	Vector2f heroPowerManaCrystalTextPos;

	int hoveringIndex;			//Index where a minion would be inserted if dropped at this mouse position.
	float dropMinionBoundry;	//Indicates where to start checking for card collisions. If it is not within this hit box then there is no point doing fancy calculations.

	float minionGap;		//Gap between the minions.

	int minionIDCounter;	//Used for giving each minion played a unique ID.

	
};
