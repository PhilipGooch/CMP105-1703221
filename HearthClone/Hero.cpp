#include "Hero.h"

Hero::Hero()
{

}

Hero::Hero(RenderWindow* window_, Font* font_, int player_, Texture& texture_, AudioManager* audioManager_)
	:Minion(window_, font_, player_, 0, "Hero", 1, 30, texture_, audioManager_)				//Calling this minions consturctor instead of the default constructor to initialize the variables that hero needs.
{

	heroConvex.setPointCount(42);
	heroConvex.setOutlineColor(Color::Black);
	heroConvex.setOutlineThickness(2);
	heroConvex.setFillColor(Color::White);

	heroHealth.setOutlineColor(Color::Black);
	heroHealth.setOutlineThickness(2);
	heroHealth.setFillColor(Color::Red);

	ready = true;

	resizeWindow();
	pos;

	int a = 1;

}

Hero::~Hero()
{
}

void Hero::setRenderWindow(RenderWindow* renderWindow_) { window = renderWindow_; }
void Hero::setFont(Font* font_) { font = font_; }

void Hero::resizeWindow()
{
	textSize = (int)translate((float)window->getSize().y, 30);
	height = translate((float)window->getSize().y, 120);

	heroLeft = translate((float)window->getSize().y, 53);
	heroRight = translate((float)window->getSize().y, 52);
	heroDown = translate((float)window->getSize().y, 120);
	heroRectTop = translate((float)window->getSize().y, 54);
	heroCurveXOffset = translate((float)window->getSize().y, 31);
	heroCurveYOffset = translate((float)window->getSize().y, 82);
	heroCurveRadius = translate((float)window->getSize().y, 88);

	int counter = 0;
	float r = translate((float)window->getSize().y, 88);
	for (float theta = PI * 1.1f; theta < PI * 1.1 + PI * 0.3f; theta += PI * 0.3f / 20) {
		heroConvex.setPoint(counter++, Vector2f(translate((float)window->getSize().y, 31) + (float)(cos(theta) * r), translate((float)window->getSize().y, 82) + (float)(sin(theta) * r)));
	}
	for (float theta = PI / 2 + PI * 1.115f; theta < PI / 2 + PI * 1.115f + PI * 0.3f; theta += PI * 0.3f / 20) {
		heroConvex.setPoint(counter++, Vector2f(translate((float)window->getSize().y, -31) + (float)(cos(theta) * r), translate((float)window->getSize().y, 82) + (float)(sin(theta) * r)));
	}
	heroConvex.setPoint(counter++, Vector2f(translate((float)window->getSize().y, 52.7f), translate((float)window->getSize().y, 120)));
	heroConvex.setPoint(counter++, Vector2f(-translate((float)window->getSize().y, 52.7f), translate((float)window->getSize().y, 120)));

	if (player == 0) {
		pos.x = (float)window->getSize().x / 2;
		pos.y = (float)window->getSize().y - translate((float)window->getSize().y, 118 + 120);
		renderPos.x = (float)window->getSize().x / 2;
		renderPos.y = (float)window->getSize().y - translate((float)window->getSize().y, 118 + 120);
		targetPos.x = (float)window->getSize().x / 2;
		targetPos.y = (float)window->getSize().y - translate((float)window->getSize().y, 118 + 120);
	}
	else {
		pos.x = (float)window->getSize().x / 2;
		pos.y = translate((float)window->getSize().y, 118);
		renderPos.x = (float)window->getSize().x / 2;
		renderPos.y = translate((float)window->getSize().y, 118);
		targetPos.x = (float)window->getSize().x / 2;
		targetPos.y = translate((float)window->getSize().y, 118);
	}
	heroConvex.setPosition(renderPos.x, renderPos.y);

	heroHealth.setOrigin(translate((float)window->getSize().y, 15), translate((float)window->getSize().y, 15));
	heroHealth.setRadius(translate((float)window->getSize().y, 15));
	heroHealth.setPosition(heroConvex.getPosition().x + translate((float)window->getSize().y, 45), heroConvex.getPosition().y + translate((float)window->getSize().y, 112));


}

ConvexShape& Hero::getHeroConvex() { return heroConvex; }



void Hero::render(bool turn, bool minionsSelected)
{
	heroConvex.setPosition(renderPos.x, renderPos.y);
	//HERO
	if (turn) {
		if (ready) {
			if (selected) {
				heroConvex.setOutlineColor(Color::Green);
				heroConvex.setOutlineThickness(6);
				window->draw(heroConvex);
			}
			else if (!minionsSelected) {
				heroConvex.setOutlineColor(Color::Green);
				heroConvex.setOutlineThickness(6);
				window->draw(heroConvex);
			}
		}
	}
	else if (!turn && targeted) {
		heroConvex.setOutlineColor(Color::Red);
		heroConvex.setOutlineThickness(6);
		window->draw(heroConvex);
	}
	heroConvex.setOutlineColor(Color::Black);
	heroConvex.setOutlineThickness(2);
	window->draw(heroConvex);
	heroHealth.setPosition(heroConvex.getPosition().x + translate((float)window->getSize().y, 45), heroConvex.getPosition().y + translate((float)window->getSize().y, 112));
	window->draw(heroHealth);						//this could be calculated using the size of the character!!!
	displayNumber(window, font, text, heroHealth.getPosition().x - translate((float)window->getSize().y, 8), heroHealth.getPosition().y - heroHealth.getRadius() - translate((float)window->getSize().y, 5.3f), renderHealth, textSize, 0);
}						//doing calculations each frame...

bool Hero::checkTargeted(float mouseX, float mouseY)
{
	//HERO
	if ((mouseX >= heroConvex.getPosition().x - translate((float)window->getSize().y, 53) && mouseX <= heroConvex.getPosition().x + translate((float)window->getSize().y, 52) &&
		mouseY < heroConvex.getPosition().y + translate((float)window->getSize().y, 120)) && (mouseY >= heroConvex.getPosition().y + translate((float)window->getSize().y, 54) ||
		(pow(mouseX - heroConvex.getPosition().x + translate((float)window->getSize().y, 31), 2) + pow(mouseY - heroConvex.getPosition().y - translate((float)window->getSize().y, 82), 2) <= pow(translate((float)window->getSize().y, 88), 2) &&
			pow(mouseX - heroConvex.getPosition().x - translate((float)window->getSize().y, 31), 2) + pow(mouseY - heroConvex.getPosition().y - translate((float)window->getSize().y, 82), 2) <= pow(translate((float)window->getSize().y, 88), 2)))) {
		targeted = true;
		return true;
		//(heroConvex.getFillColor() == Color::White) ? heroConvex.setFillColor(Color::Black) : heroConvex.setFillColor(Color::White);
	}
	else {
		targeted = false;
		return false;
	}
}

float Hero::getHeight()
{
	return height;
}


