#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Input.h"
#include "Line.h"
#include "StaticFunctions.h"
#include "Animation.h"
#include "AudioManager.h"

using namespace std;				//using namespaces is dangerous! You have to be careful there are not duplicate objects and variables.
using namespace sf;
using namespace staticFunctions;

class Minion
{
public:
	Minion();
	Minion(sf::RenderWindow*, sf::Font*, int, int, string, int, int, Texture&, AudioManager*);
	~Minion();

	void setTexture(Texture*);


	int count = 0;

	//GETTERS
	int getMinId();
	string getName();
	string getDescription();
	Vector2f getPos();
	Vector2f getTargetPos();
	Vector2f getRenderPos();
	bool getTargeted();
	bool getSelected();
	float getScale();
	bool getReady();
	int getPlayer();
	ConvexShape* getMinionConvex();
	float getRadius();
	Vector2f getVelocity();
	Vector2f getAcceleration();
	bool getAnimating();
	bool getAlive();			//This is if it is actually alive for checking for legal moves whilst there is a que.
	bool getRenderAlive();		//This is if it alive after it's animation. How the user sees it.
	Minion* getTarget();
	int getAttack();
	int getHealth();

	//SETTERS
	void setDescription(string);
	void setAttack(int);
	void setHealth(int);
	void setPos(float, float);
	void setTargetPos(float, float);
	void setRenderPos(float, float);
	void setTargeted(bool);
	void setSelected(bool);
	void setReady(bool);
	void setVelocity(float, float);
	void setAcceleration(float, float);
	void setTargetVector();					//Where it is aiming for for its animation.
	void setDoubleWaving(bool);				//Is it waving with both hands.
	void setTarget(Minion*);				//Setting it's fight target.
	void setAnimating(bool animating_);

	void update(float);
	void render(bool, bool);
	bool checkTargeted(float, float);
	
	void resizeWindow();
	void fight();							//Fight instantly when clicked.
	void renderFight(Minion * enemy);		//Fight when the animation collides.	
	void takeDamage(int);					//Same with taking damage.
	void renderTakeDamage(int damage);	
	bool animation(float);					//Returning if it is in an animation. Also executing animation code.
	bool repositioning(float);				//Same with repositioning.
	
	//These were all future ideas.
	/*int getMinType();
	
	bool getCharge();
	bool getDivineShield();
	bool getTaunt();
	bool getWindfury();
	bool getLifesteal();
	bool getDeathrattle();
	bool getFrozen();
	bool getSilenced();
	bool getStealth();
	void setCharge(bool);
	void setDivineShield(bool);
	void setTaunt(bool);
	void setWindfury(bool);
	void setLifesteal(bool);
	void setDeathrattle(bool);
	void setFrozen(bool);
	void setSilenced(bool);
	void setStealth(bool);*/
	
protected:							//These variables can only be accessed by this class and classes that inherit from it.
	RenderWindow* window;
	Font* font;
	int attack;
	int health;
	bool targeted;
	bool selected;
	int player;
	bool ready;
	Text text;
	int textSize;
	bool alive;
	bool renderAlive;		//Variables with render at the start mean that these are the variables used when displaying the minions.
	int renderAttack;
	int renderHealth;
	bool animate;
	Vector2f pos;
	Vector2f targetPos;
	Vector2f renderPos;
	Vector2f velocity;
	Vector2f acceleration;
	bool attacking;
	bool collided;
	Vector2f targetVector;
	bool animating;
	Minion* target;
	bool seperating;
	Vector2f EnemyTargetPos;			//The enemy's position.
	Vector2f lastTargetPos;				//The position it just came from.
	AudioManager* audioManager;

private:					//These variables can only be seen by this class.
	int minId;
	string name;
	string description;
	float circleRadius;			//The width of the ellipse to portray the minion.
	int points;					//How many points in the ellipse for the ConvexShape.
	float scale;
	float radius;
	ConvexShape minionConvex;
	CircleShape attackCircle;
	CircleShape healthCircle;
	Vector2f attackCirclePos;
	Vector2f healthCirclePos;
	Vector2f circleTextPos;
	Texture waveTexture;		//Texture used for animation.
	Sprite waveSprite;			//Sprite used for animation.
	Animation wave;				//The sprite animations.
	Animation doubleWave;
	bool doubleWaving = true;	//Used for the different states of the animation.

	//Future ideas.
	//int minType;    // 0=neutral, 1=beast, 2=pirate, 3=elemental, 4=demon
	//bool charge;
	//bool divineShield;
	//bool taunt;
	//bool windfury;
	//bool lifesteal;
	//bool deathrattle;
	//bool frozen;
	//bool silenced;
	//bool stealth;
	
};