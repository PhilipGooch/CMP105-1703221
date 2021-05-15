#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Line
{
public:
	Line();
	~Line();

	//GETTERS
	float getX1();
	float getY1();
	float getX2();
	float getY2();
	float getM();
	float getC();

	//SETTERS
	void setX1(float);
	void setY1(float);
	void setX2(float);
	void setY2(float);

	//FUNCTIONS
	void update(float, float, float, float);
	void equation();

	void update();

	void render();

private:
	float x1, y1, x2, y2;
	float m, c;

	sf::Vertex line[2];
};