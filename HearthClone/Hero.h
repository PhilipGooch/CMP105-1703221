#pragma once
#include "Minion.h"

class Hero : public Minion
{
public:
	Hero();
	Hero(RenderWindow*, Font*, int, Texture&, AudioManager*);
	~Hero();

	void resizeWindow();

	void render(bool, bool);

	void setRenderWindow(RenderWindow*);
	void setFont(Font*);

	ConvexShape& getHeroConvex();


	bool checkTargeted(float mouseX, float mouseY);

	float getHeight();


private:
	ConvexShape heroConvex;
	CircleShape heroHealth;

	//variables storing the translated values of positions.	
	float heroLeft;
	float heroRight;
	float heroDown;
	float heroRectTop;
	float heroCurveXOffset;						//OPTIMISATION! setting these vlaues so i dont have to translate the number each frame.	(limited effect for effort...)
	float heroCurveYOffset;
	float heroCurveRadius;

	float height;
	
};

