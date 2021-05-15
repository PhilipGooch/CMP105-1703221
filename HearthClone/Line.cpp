#include "Line.h"

Line::Line()
{
	x1 = 0;		//can i initialize these in the header file?
	y1 = 0;
	x2 = 0;
	y2 = 0;
	m = 0;
	c = 0;
}

Line::~Line()
{
}

//GETTERS
float Line::getX1() { return x1; }
float Line::getY1() { return y1; }
float Line::getX2() { return x2; }
float Line::getY2() { return y2; }
float Line::getM() { return m; }
float Line::getC() { return c; }

//SETTERS
void Line::setX1(float x1_) { x1 = x1_; }
void Line::setY1(float y1_) { y1 = y1_; }
void Line::setX2(float x2_) { x2 = x2_; }
void Line::setY2(float y2_) { y2 = y2_; }

void Line::update(float x1_, float y1_, float x2_, float y2_)
{
	x1 = x1_;
	y1 = y1_;
	x2 = x2_;
	y2 = y2_;
}

void Line::equation()
{
	m = (y2 - y1) / (x2 - x1);  //gradient = dy / dx
	c = y1 - m * x1;			//y = mx + c
}

void Line::update()
{
	line[0].position.x = x1;
	line[0].position.y = y1;
	line[1].position.x = x2;
	line[1].position.y = y2;
}

void Line::render()
{
	
}

