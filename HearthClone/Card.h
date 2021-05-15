#pragma once
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Line.h"
#include "StaticFunctions.h"

using namespace std;
using namespace sf;
using namespace staticFunctions;

class Card
{
public:
	Card();
	Card(RenderWindow*, Font*, Texture&, int, int, string, int, int, int);
	~Card();

	//GETTERS
	int getCardId();
	string getName();
	int getAttack();
	int getHealth();
	int getManaCost();
	bool getTargeted();
	bool getSelected();
	Texture* getTexture();

	//SETTERS
	void setAttack(int);
	void setHealth(int);
	void setManaCost(int);
	void setTargeted(bool);
	void setSelected(bool);
	void setSelectPointX(float);
	void setSelectPointY(float);

	void displayCard(bool, int, bool);
	void displayTargetedCard(int, bool);
	void displaySelectedCard(float, float, int, bool);

	void calculatePosition(int, int);
	void checkTargeted(Line&);
	void update(float);
	bool checkPickedUp(float, float, int);
	void updateWindow();

private:
	Font* font;
	RenderWindow* window;
	int player;
	int cardId;
	string name;
	int attack;
	int health;
	int manaCost;
	Texture texture;
	Sprite sprite;

	bool targeted;
	bool selected;			
	

	float miniCardWidth;
	float miniCardHeight;
	float targetedCardWidth;
	float targetedCardHeight;
	float selectedCardWidth;
	float selectedCardHeight;

	float radius;		//This is the radius of the circle used for the arc of the cards.
	float originX;		//This is the origin of the circle.
	float originY;
	float posX;			//This is the position of the top-center of the card.
	float posY;
	float A;			//This is angle between cards from the origin.
	float B;			//This is the remaining angle in the right angle.
	float h;			//This stands for horizon. This is to account for arcs in SFML starting from 90 degrees.
	float cardRise;		//The amount the card is raised by when targeted.										//these are not multiplied by delta time!!!
	float miniCardRise;	//The amount the small cards sink.
	float miniCardRiseTarget;	//what it is aiming for when hovering.	(it is actually sinking. the minicards do not rise but sink.)
	float topLeftX;								//could put these straight in to line class? (not worth it i think. more readable how it is.)
	float topLeftY;		//Co-ordinates of each corneer of the card.
	float topRightX;
	float topRightY;		
	float bottomLeftX;
	float bottomLeftY;		//these could be vectors?
	float bottomRightX;
	float bottomRightY;
	float checkPickupDistance;
	float miniCardRiseTargeted;	//Where it is set to when the card is targeted.
	float cardRiseTarget;		//Where targeted card is aiming to rise to.
	float cardRiseSpeed;		//At what speed.
	float miniCardRiseSpeed;

	float selectPointX;		//Where the mouse is when it is selected.
	float selectPointY;

	float miniCardManaCrystalPosX;		//Position of the mana crystal on the card.
	float miniCardManaCrystalPosY;
	float miniCardManaCrystalTextPosX;
	float miniCardManaCrystalTextPosY;
	float miniCardManaCrystalRadius;

	Line edges[4];						//The lines making up the edges of the card.
	void updateHitbox();				//updates the edges when a card is moved or added or the game is resized.
	bool lineCollision(Line&, Line&);	//Function determining if too lines are intersecting.

	RectangleShape targetedCard;		//Rectangle shapes for the targeted and selected cards/
	RectangleShape selectedCard;
	ConvexShape miniCard;				//Convex shape for the angled cards in the hand.
	Text text;

	CircleShape targetedManaCrystal;	//Crystals are just circles with only 6 points to make them a hexagon.
	CircleShape selectedManaCrystal;
	CircleShape miniManaCrystal;
	CircleShape targetedAttackCircle;
	CircleShape targetedHealthCircle;
	CircleShape selectedAttackCircle;
	CircleShape selectedHealthCircle;
	float targetedCircleRadius;
	float selectedCircleRadius;
	float targetedManaCrystalRadius;
	float selectedManaCrystalRadius;

	Vector2f targetedCircleTextPos;
	Vector2f selectedCircleTextPos;
	Vector2f targetedManaCrystalTextPos;
	Vector2f selectedManaCrystalTextPos;
	float targetedCircleTextSize;
	float selectedCircleTextSize;
	int targetedManaCrystalTextSize;
	int selectedManaCrystalTextSize;
	int miniCardManaCrystalTextSize;

};