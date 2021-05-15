#include "Card.h"

Card::Card() {

}

Card::Card(sf::RenderWindow* window_, sf::Font* font_, sf::Texture& texture_, int player_, int cardId_, string name_, int attack_, int health_, int manaCost_)
{
	window = window_;
	font = font_;
	player = player_;
	cardId = cardId_;
	name = name_;
	attack = attack_;
	health = health_;
	manaCost = manaCost_;


	targeted = false;
	selected = false;
	selectPointX = 0;
	selectPointY = 0;

	updateWindow();

	//Setting up shapes.
	selectedCard.setFillColor(Color::White);
	selectedAttackCircle.setOutlineColor(Color::Black);
	selectedAttackCircle.setOutlineThickness(2);
	selectedAttackCircle.setFillColor(Color::Yellow);
	selectedHealthCircle.setOutlineColor(Color::Black);
	selectedHealthCircle.setOutlineThickness(2);
	selectedHealthCircle.setFillColor(Color::Red);
	selectedManaCrystal.setPointCount(6);
	selectedManaCrystal.setFillColor(Color::Cyan);
	selectedManaCrystal.setOutlineColor(Color::Black);
	selectedManaCrystal.setOutlineThickness(2);
	selectedManaCrystal.setRotation(30);

	targetedCard.setFillColor(Color::White);
	targetedAttackCircle.setOutlineColor(Color::Black);
	targetedAttackCircle.setOutlineThickness(2);
	targetedAttackCircle.setFillColor(Color::Yellow);
	targetedHealthCircle.setOutlineColor(Color::Black);
	targetedHealthCircle.setOutlineThickness(2);
	targetedHealthCircle.setFillColor(Color::Red);
	targetedManaCrystal.setPointCount(6);
	targetedManaCrystal.setFillColor(Color::Cyan);
	targetedManaCrystal.setOutlineColor(Color::Black);
	targetedManaCrystal.setOutlineThickness(2);
	targetedManaCrystal.setRotation(30);

	miniCard.setFillColor(sf::Color::White);
	miniCard.setPointCount(4);
	miniManaCrystal.setPointCount(6);
	miniManaCrystal.setFillColor(Color::Cyan);
	miniManaCrystal.setOutlineColor(Color::Black);
	miniManaCrystal.setOutlineThickness(2);
	miniCardManaCrystalPosX = 0;
	miniCardManaCrystalPosY = 0;
	miniCardManaCrystalTextPosX = 0;
	miniCardManaCrystalTextPosY = 0;

	//Initializing variables.
	radius = translate(window->getSize().y, 300); 
	posX = 0;
	posY = 0;
	A = 0;
	B = 0;
	h = PI / 2;		
	cardRise = 0;
	miniCardRise = 0;
	topLeftX = 0;
	topLeftY = 0;
	topRightX = 0;
	topRightY = 0;
	bottomLeftX = 0;
	bottomLeftY = 0;
	bottomRightX = 0;
	bottomRightY = 0;
}

Card::~Card()
{
}

void Card::updateWindow()		//Called when re-sizing the window.
{
	checkPickupDistance = translate(window->getSize().y, 60);
	miniCardRiseTarget = translate(window->getSize().y, 20);
	miniCardRiseTargeted = translate(window->getSize().y, 25);
	cardRiseTarget = translate(window->getSize().y, 25);
	cardRiseSpeed = translate(window->getSize().y, 100);
	miniCardRiseSpeed = translate(window->getSize().y, 100);

	originX = window->getSize().x / 2;
	if (player == 0) {
		originY = translate(window->getSize().y, 916);
	}
	else if (player == 1) {
		originY = translate(window->getSize().y, -148);
	}

	radius = translate(window->getSize().y, 300);
	selectedCircleRadius = translate(window->getSize().y, 20);
	targetedCircleRadius = translate(window->getSize().y, 20);
	selectedManaCrystalRadius = translate(window->getSize().y, 23);
	targetedManaCrystalRadius = translate(window->getSize().y, 23);
	miniCardManaCrystalRadius = translate(window->getSize().y, 18);

	miniCardWidth = translate(window->getSize().y, 97);
	miniCardHeight = translate(window->getSize().y, 135);
	targetedCardWidth = translate(window->getSize().y, 135);
	targetedCardHeight = translate(window->getSize().y, 187);
	selectedCardWidth = translate(window->getSize().y, 135);
	selectedCardHeight = translate(window->getSize().y, 187);

	targetedCircleTextPos.x = translate(window->getSize().y, 11);
	targetedCircleTextPos.y = translate(window->getSize().y, -10);
	selectedCircleTextPos.x = translate(window->getSize().y, 11);
	selectedCircleTextPos.y = translate(window->getSize().y, -10);
	targetedManaCrystalTextPos.x = translate(window->getSize().y, -1);
	targetedManaCrystalTextPos.y = translate(window->getSize().y, -1);
	selectedManaCrystalTextPos.x = translate(window->getSize().y, -1);
	selectedManaCrystalTextPos.y = translate(window->getSize().y, -1);
	targetedCircleTextSize = (int)translate(window->getSize().y, 44);
	selectedCircleTextSize = (int)translate(window->getSize().y, 44);
	targetedManaCrystalTextSize = (int)translate(window->getSize().y, 44);
	selectedManaCrystalTextSize = (int)translate(window->getSize().y, 44);
	miniCardManaCrystalTextSize = (int)translate(window->getSize().y, 30);

	targetedAttackCircle.setRadius(targetedCircleRadius);
	targetedHealthCircle.setRadius(targetedCircleRadius);
	targetedManaCrystal.setRadius(targetedManaCrystalRadius);
	selectedAttackCircle.setRadius(targetedCircleRadius);
	selectedHealthCircle.setRadius(targetedCircleRadius);
	selectedManaCrystal.setRadius(selectedManaCrystalRadius);

	targetedCard.setSize(Vector2f(targetedCardWidth, targetedCardHeight));
	selectedCard.setSize(Vector2f(selectedCardWidth, selectedCardHeight));
	
}

//GETTERS
int Card::getCardId() { return cardId; }
string Card::getName() { return name; }
int Card::getAttack() { return attack; }
int Card::getHealth() { return health; }
int Card::getManaCost() { return manaCost; }
bool Card::getTargeted() { return targeted; }
bool Card::getSelected() { return selected; }
Texture* Card::getTexture() { return &texture; }

//SETTERS
void Card::setAttack(int attack_) { attack = attack_; }
void Card::setHealth(int health_) { health = health_; }
void Card::setManaCost(int manaCost_) { manaCost = manaCost_; }
void Card::setTargeted(bool targeted_) { targeted = targeted_; }
void Card::setSelected(bool selected_) { selected = selected_; }
void Card::setSelectPointX(float selectPointX_) { selectPointX = selectPointX_; }
void Card::setSelectPointY(float selectPointY_) { selectPointY = selectPointY_; }


// |   /
// |  /
// |B/
// |/_A_____
void Card::calculatePosition(int cards, int i)		//i could do all these calculations at the begining and store them in an array and access them when needed.
{
	//A is angle between cards from the origin.	 + 1 to include all divisions including 0.	   + 0.001 for collision detection. Vertical line handling.
	if (player == 0) {
		A = PI / (cards + 1) * i + 0.001f;
	}
	else if (player == 1) {
		A = -PI / (cards + 1) * i + 0.001f;
	}
	B = PI / 2 - A;

	//Adding 90 degrees (h) to start from horizontal.
	posX = originX + sin(h + A) * radius;
	posY = originY + cos(h + A) * radius * 0.8f;

	//Finding the corners of the card. This is used for drawing the ConvexShape and updating the hitbox.
	topLeftX = posX + sin(h + PI - B) * miniCardWidth / 2;
	topLeftY = posY + cos(h + PI - B) * miniCardWidth / 2;
	topRightX = posX + sin(h - B) * miniCardWidth / 2;
	topRightY = posY + cos(h - B) * miniCardWidth / 2;
	bottomRightX = posX + sin(h - B) * miniCardWidth / 2 - sin(h + A) * miniCardHeight;
	bottomRightY = posY + cos(h - B) * miniCardWidth / 2 - cos(h + A) * miniCardHeight;
	bottomLeftX = posX + sin(h + PI - B) * miniCardWidth / 2 - sin(h + A) * miniCardHeight;
	bottomLeftY = posY + cos(h + PI - B) * miniCardWidth / 2 - cos(h + A) * miniCardHeight;
	updateHitbox();

	//Because these cards are on an angle, I can't just adjust the position of the crystal by x and y as it will be scewed so have have to do this maths.
	float up = translate(window->getSize().y, 4);
	float accross = translate(window->getSize().y, -5);
	miniCardManaCrystalPosX = originX + sin(h + A) * (radius + up) + sin(h + PI - B) * (miniCardWidth / 2 + accross);
	miniCardManaCrystalPosY = originY + cos(h + A) * (radius * 0.8f + up) + cos(h + PI - B) * (miniCardWidth / 2 + accross);

	//The same goes for the text on the crystal.
	up = translate(window->getSize().y, 13);
	accross = translate(window->getSize().y, -1);
	int indent = 0;
	switch (manaCost)
	{
	case 0: indent = (int)translate(window->getSize().y, 5); break;			//This is adjusting the indent of the number. 
	case 1: indent = (int)translate(window->getSize().y, 1); break;
	case 2: indent = (int)translate(window->getSize().y, 1); break;
	case 3: indent = (int)translate(window->getSize().y, 2); break;
	case 4: indent = (int)translate(window->getSize().y, 0); break;
	case 5: indent = (int)translate(window->getSize().y, 1); break;
	case 6: indent = (int)translate(window->getSize().y, 0); break;
	case 7: indent = (int)translate(window->getSize().y, 1); break;
	case 8: indent = (int)translate(window->getSize().y, 1); break;
	case 9: indent = (int)translate(window->getSize().y, 1); break;
	default: indent = (int)translate(window->getSize().y, -4); break;
	}
	miniCardManaCrystalTextPosX = originX + sin(h + A) * (radius + up) + sin(h + PI - B) * (miniCardWidth / 2 + accross - indent);
	miniCardManaCrystalTextPosY = originY + cos(h + A) * (radius * 0.8f + up) + cos(h + PI - B) * (miniCardWidth / 2 + accross - indent);
}



void Card::updateHitbox()		//Updating the lines between the corners of the cards that will be used for collision detection.
{
	edges[0].setX1(topLeftX);
	edges[0].setY1(topLeftY);
	edges[0].setX2(topRightX);
	edges[0].setY2(topRightY);
	edges[1].setX1(topRightX);
	edges[1].setY1(topRightY);
	edges[1].setX2(bottomRightX);
	edges[1].setY2(bottomRightY);
	edges[2].setX1(bottomRightX);
	edges[2].setY1(bottomRightY);
	edges[2].setX2(bottomLeftX);
	edges[2].setY2(bottomLeftY);
	edges[3].setX1(bottomLeftX);
	edges[3].setY1(bottomLeftY);
	edges[3].setX2(topLeftX);
	edges[3].setY2(topLeftY);
}

void Card::checkTargeted(Line& mouse) {
	int collisionCount = 0;							//For counting how many of the card's edges the "mouse" line intersects.
	for (int i = 0; i < 4; i++) {
		if (lineCollision(mouse, edges[i])) {
			collisionCount++;
			if (collisionCount == 2) {	//OPTIMISATION. It is only possible for the straight line to intersect two edges of a rectangle so I can half the amount of calculations being done here. Dramatic increase in FPS.
				break;
			}
		}
	}
	if (collisionCount == 1)			//If there is only one collision then the mouse is inside of the object
		targeted = true;
	else
		targeted = false;
}

bool Card::lineCollision(Line& mouse, Line& edge)	//Checking if there is a line collision between the two given lines.
{
	mouse.equation();		//calling functions to update the line's "c" and "m" variables.
	edge.equation();
	//As the "mouse" line will never be vertical or horizontal (apart from the very top and left of screen) there will not be a problem with the lines not intersecting (parallel lines) or "m" and "c" being infinitely large and small resulting in division by 0 error.
	float m = edge.getM() - mouse.getM();			//y = m1x + c1;    y = m2x + c2;   At intersection, the points will be equal;    m1x + c1 = m2x + c2;
	float c = mouse.getC() - edge.getC();			//(m1 - m2)x = c2 - c1;    x = (c2 - c1) / (m1 - m2);
	float x = c / m;								//"x" is the x co-ordinate that the lines intersect
													//Checking whether the intersection is in the bounds of the two line's x co-ordinates.	
	if (x >= min(edge.getX1(), edge.getX2()) && x <= max(edge.getX1(), edge.getX2()) && x >= min(mouse.getX1(), mouse.getX2()) && x <= max(mouse.getX1(), mouse.getX2())) {
		return true;
	}
	else {
		return false;
	}
}

void Card::displayTargetedCard(int mana, bool full)  //Displaying the targetted card at the desired position.
{
	if (player == 0) {
		targetedCard.setPosition(posX - targetedCardWidth / 2, window->getSize().y - targetedCardHeight - cardRise);
		targetedAttackCircle.setPosition(posX - targetedCardWidth / 2 - targetedCircleRadius * 0.5, window->getSize().y - cardRise - targetedCircleRadius * 1.5);
		targetedHealthCircle.setPosition(posX + targetedCardWidth / 2 - targetedCircleRadius * 1.5, window->getSize().y - cardRise - targetedCircleRadius * 1.5);
		targetedManaCrystal.setPosition(posX - targetedCardWidth / 2 + targetedCircleRadius * 0.1, window->getSize().y - targetedCardHeight - cardRise - targetedCircleRadius * 1);
	}
	else if (player == 1) {
		targetedCard.setPosition(posX - targetedCardWidth / 2, -cardRise);
		targetedAttackCircle.setPosition(posX - targetedCardWidth / 2 - targetedCircleRadius * 0.5, targetedCardHeight - cardRise - targetedCircleRadius * 1.5);
		targetedHealthCircle.setPosition(posX + targetedCardWidth / 2 - targetedCircleRadius * 1.5, targetedCardHeight - cardRise - targetedCircleRadius * 1.5);
		targetedManaCrystal.setPosition(posX - targetedCardWidth / 2 + targetedCircleRadius * 0.1, -cardRise - targetedCircleRadius * 1);
	}
	if (manaCost <= mana && !full) {
		targetedCard.setOutlineColor(sf::Color::Green);
		targetedCard.setOutlineThickness(6);
		window->draw(targetedCard);
	}
	targetedCard.setOutlineColor(sf::Color::Black);
	targetedCard.setOutlineThickness(2);
	window->draw(targetedCard);
	window->draw(targetedManaCrystal);
	window->draw(targetedAttackCircle);
	window->draw(targetedHealthCircle);
	displayNumber(window, font, text, targetedAttackCircle.getPosition().x + targetedCircleTextPos.x, targetedAttackCircle.getPosition().y + targetedCircleTextPos.y, attack, targetedCircleTextSize, 0);
	displayNumber(window, font, text, targetedHealthCircle.getPosition().x + targetedCircleTextPos.x, targetedHealthCircle.getPosition().y + targetedCircleTextPos.y, health, targetedCircleTextSize, 0);
	displayNumber(window, font, text, targetedManaCrystal.getPosition().x + targetedManaCrystalTextPos.x, targetedManaCrystal.getPosition().y + targetedManaCrystalTextPos.y, manaCost, targetedManaCrystalTextSize, 0);
}

void Card::displaySelectedCard(float x, float y, int mana, bool full)		//displaying the selected card.
{
	selectedCard.setPosition(x - selectedCardWidth / 2, y - selectedCardHeight / 2);
	if (manaCost <= mana && !full) {		//If the card is ready.
		selectedCard.setOutlineColor(sf::Color::Green);
		selectedCard.setOutlineThickness(6);
		window->draw(selectedCard);
	}
	selectedCard.setOutlineColor(sf::Color::Black);
	selectedCard.setOutlineThickness(2);
	window->draw(selectedCard);
	selectedManaCrystal.setPosition(x - selectedCardWidth / 2 + selectedCircleRadius * 0.1, y - selectedCardHeight / 2 - selectedCircleRadius * 1);
	selectedAttackCircle.setPosition(x - selectedCardWidth / 2 - selectedCircleRadius * 0.5, y + selectedCardHeight / 2 - selectedCircleRadius * 1.5);
	selectedHealthCircle.setPosition(x + selectedCardWidth / 2 - selectedCircleRadius * 1.5, y + selectedCardHeight / 2 - selectedCircleRadius * 1.5);
	window->draw(selectedAttackCircle);
	window->draw(selectedHealthCircle);
	window->draw(selectedManaCrystal);
	displayNumber(window, font, text, selectedAttackCircle.getPosition().x + selectedCircleTextPos.x, selectedAttackCircle.getPosition().y + selectedCircleTextPos.y, attack, selectedCircleTextSize, 0);
	displayNumber(window, font, text, selectedHealthCircle.getPosition().x + selectedCircleTextPos.x, selectedHealthCircle.getPosition().y + selectedCircleTextPos.y, health, selectedCircleTextSize, 0);
	displayNumber(window, font, text, selectedManaCrystal.getPosition().x + selectedManaCrystalTextPos.x, selectedManaCrystal.getPosition().y + selectedManaCrystalTextPos.y, manaCost, selectedManaCrystalTextSize, 0);
}

void Card::displayCard(bool turn, int mana, bool full)			//Drawing the card in the hand by connecting the four corner points.
{
	if ((player == 0 && miniCardRise < miniCardRiseTarget) || (player == 1 && miniCardRise > -miniCardRiseTarget)) {
		miniCard.setPoint(0, sf::Vector2f(topLeftX, topLeftY - miniCardRise));
		miniCard.setPoint(1, sf::Vector2f(topRightX, topRightY - miniCardRise));
		miniCard.setPoint(2, sf::Vector2f(bottomRightX, bottomRightY - miniCardRise));
		miniCard.setPoint(3, sf::Vector2f(bottomLeftX, bottomLeftY - miniCardRise));
		if (turn && manaCost <= mana && !full) {    //If the card is ready.
			miniCard.setOutlineColor(sf::Color::Green);
			miniCard.setOutlineThickness(6);
			window->draw(miniCard);
		}
		miniCard.setOutlineColor(sf::Color::Black);
		miniCard.setOutlineThickness(2);
		window->draw(miniCard);
		if (player == 0) {			//Rotating the mana crystal.
			miniManaCrystal.setRadius(miniCardManaCrystalRadius);
			miniManaCrystal.setOrigin(miniCardManaCrystalRadius / 2, miniCardManaCrystalRadius / 2);
			miniManaCrystal.setPosition(miniCardManaCrystalPosX, miniCardManaCrystalPosY - miniCardRise);
			miniManaCrystal.setRotation(30 + B * 180 / PI);
			window->draw(miniManaCrystal);
			displayNumber(window, font, text, miniCardManaCrystalTextPosX, miniCardManaCrystalTextPosY - miniCardRise, manaCost, miniCardManaCrystalTextSize, B);
		}
	}
}

bool Card::checkPickedUp(float x, float y, int mana)	//This is for only picking up the card if you have clicked and dragged for a certain distance.
{
	return (manaCost <= mana && sqrt(pow(selectPointX - x, 2) + pow(selectPointY - y, 2)) > checkPickupDistance) ? true : false;		//distance could be calculated for smoother animation.
}

void Card::update(float dt)		//Making the cards rise and sink when selected.
{
	if (targeted) {	//Rising.	
		if (player == 0) {
			miniCardRise = miniCardRiseTargeted;
			if (cardRise < cardRiseTarget) {
				cardRise += cardRiseSpeed * dt;
			}
		}
		else if (player == 1) {
			miniCardRise = -miniCardRiseTargeted;
			if (cardRise > -cardRiseTarget) {
				cardRise -= cardRiseSpeed * dt;
			}
		}
	}
	else {	//Sinking.
		if (player == 0) {
			if (miniCardRise > 0) {
				miniCardRise -= miniCardRiseSpeed * dt;
			}
			else {
				miniCardRise = 0;
			}
			if (cardRise > 0) {
				cardRise -= cardRiseSpeed * dt;
			}
		}
		else if (player == 1) {
			if (miniCardRise < 0) {
				miniCardRise += miniCardRiseSpeed * dt;
			}
			else {
				miniCardRise = 0;
			}
			if (cardRise < 0) {
				cardRise += cardRiseSpeed * dt;
			}
		}
	}
}




