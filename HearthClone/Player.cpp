#include "Player.h"
#include <iostream>
using namespace std;

Player::Player() {
}

Player::Player(RenderWindow* window_, Input* input_, Line* mouse_, Font* font_, int player_, AudioManager* audioManager_)
{

	window = window_;
	input = input_;
	mouse = mouse_;
	font = font_;
	player = player_;
	audioManager = audioManager_;

	health = 30;
	heroPowerManaCost = 2;

	hoveringIndex = 10;



	if (player == 0) {			//Giving players starting mana crystals.
		manaCrystals = 1;
	}
	else if (player == 1) {
		manaCrystals = 0;
	}
	mana = manaCrystals;		//Giving them maximum mana allowed by crystals.

	(player == 0) ? turn = true : turn = false;		//Setting if it is this players turn or not.

	dragging = false;			
	cardSelected = false;
	minionSelected = false;


	//Hero heroInitializer(window, font, player);			//This is bad practice.
	//hero = heroInitializer;
	//hero.setRenderWindow(window);			//This method only initializes window font and player. PI for example is not initialized.
	//hero.setFont(font);
	//hero.setPlayer(player);

	mask.loadFromFile("Assets/Dude.png");
	mask.createMaskFromColor(Color::White);
	texture.loadFromImage(mask);

	Hero heroInitializer(window, font, player, texture, audioManager);
	hero = heroInitializer;

	createDeck();

	resizeWindow();

	heroPower.setOutlineColor(Color::Black);
	heroPower.setOutlineThickness(2);
	heroPower.setFillColor(Color::White);

	heroPowerManaCrystal.setOutlineColor(sf::Color::Black);
	heroPowerManaCrystal.setFillColor(sf::Color::Cyan);
	heroPowerManaCrystal.setOutlineThickness(2);
	heroPowerManaCrystal.setPointCount(6);
	heroPowerManaCrystal.setRotation(30);

	manaCrystal.setOutlineColor(sf::Color::Black);
	manaCrystal.setFillColor(sf::Color::Cyan);
	manaCrystal.setOutlineThickness(2);
	manaCrystal.setPointCount(6);
	manaCrystal.setRotation(30);

	minionIDCounter = 0;
}

Player::~Player()
{
}

//RESIZE WINDOW
void Player::resizeWindow()		//Using static translate() function to reposition everything.
{
	minionGap = translate((float)window->getSize().y, 12);

	hero.resizeWindow();

	float rad = translate((float)window->getSize().y, 44);
	heroPower.setOrigin(rad, rad);
	heroPower.setRadius(rad);
	heroPower.setPosition(hero.getHeroConvex().getPosition().x + translate((float)window->getSize().y, 120), hero.getHeroConvex().getPosition().y + translate((float)window->getSize().y, 76));

	rad = translate((float)window->getSize().y, 17);
	heroPowerManaCrystal.setOrigin(rad, rad);
	heroPowerManaCrystal.setRadius(rad);
	heroPowerManaCrystal.setPosition(heroPower.getPosition().x, heroPower.getPosition().y - translate((float)window->getSize().y, 50));

	manaCrystalsPos.x = (float)window->getSize().x / 2 + translate((float)window->getSize().y, 220);
	manaCrystal.setRadius(translate((float)window->getSize().y, 11));
	manaCrystal.setOrigin(translate((float)window->getSize().y, 11), translate((float)window->getSize().y, 11));
	if (player == 0) {
		manaCrystalsPos.y = (float)window->getSize().y - translate((float)window->getSize().y, 70);
	}
	else {
		manaCrystalsPos.y = translate((float)window->getSize().y, 70);
	}

	dropMinionBoundry = (float)window->getSize().y * 0.3f;

	for (unsigned i = 0; i < hand.size(); i++) {
		hand[i].updateWindow();
	}
	calculateCardPositions();
	for (unsigned i = 0; i < minions.size(); i++) {
		minions[i].resizeWindow();
	}
	calculateMinionPositions();
	setMinionsRenderPos();
	//cout << "x" << endl;
}

int Player::getHealth() { return health; }
bool Player::getDragging() { return dragging; }
int Player::getManaCrystals() { return manaCrystals; }
bool Player::getCardSelected() { return cardSelected; }
bool Player::getMinionSelected() { return minionSelected; }
vector<Minion>& Player::getMinions() { return minions; }
vector<Card>& Player::getHand() { return hand; }
Hero& Player::getHero() { return hero; }

void Player::setHealth(int health_) { health = health_; }
void Player::setTurn(bool turn_) { turn = turn_; }
void Player::setMinionSelected(bool minionSelected_) { minionSelected = minionSelected_; }

//HANDLE INPUT
void Player::handleInput()
{
	//MOUSE DOWN
	if (input->isMouseLeftDown())
	{
		//HERO POWER
		if (input->getMouseX() >= heroPower.getPosition().x - heroPower.getRadius() && input->getMouseX() < heroPower.getPosition().x + heroPower.getRadius() &&		//this AABB checking not really necessary.
			input->getMouseY() >= heroPower.getPosition().y - heroPower.getRadius() && input->getMouseY() < heroPower.getPosition().y + heroPower.getRadius()) {
			if (pow(input->getMouseX() - heroPower.getPosition().x, 2) + pow(input->getMouseY() - heroPower.getPosition().y, 2) <= pow(heroPower.getRadius(), 2) && !cardSelected && !dragging) {
				input->setMouseLeftDown(false);		//Checking if you click on the hero power button. This currently has no functionality.
				//(heroPower.getFillColor() == Color::White) ? heroPower.setFillColor(Color::Black) : heroPower.setFillColor(Color::White);
			}
		}
		//HAND
		for (unsigned i = 0; i < hand.size(); i++) {
			if (hand[i].getTargeted() && !hand[i].getSelected() && !cardSelected) { //If a card is targeted and there is no other card selected.
				cardSelected = true;
				if (hand[i].getManaCost() <= mana && minions.size() < 7) {	//If you have enough mana to play it and you do not have 7 minions in play already.
					hand[i].setSelected(true);									//Select the card.
					hand[i].setSelectPointX((float)input->getMouseX());		//Recording where you clicked the card so it can be picked up by dragging a certain distance away from this point.
					hand[i].setSelectPointY((float)input->getMouseY());
					break;
				}
			}
		}
		dragging = true;
	}
	//MOUSE UP
	else
	{
		//HAND
		for (unsigned i = 0; i < hand.size(); i++) {		//Drop card.				
			if (hand[i].getSelected()) {
				hand[i].setSelected(false);
				hoveringIndex = 10;			//Setting hovering index to an out of range value to check against later.
				if ((player == 0 && input->getMouseY() < (float)window->getSize().y - dropMinionBoundry) || (player == 1 && input->getMouseY() > dropMinionBoundry)) {
					mana -= hand[i].getManaCost();		//Place that minion and minus it's mana cost from your mana.
					placeMinion(i);			
				}
				calculateCardPositions();		//Re-calculate where the cards it your hand will be displayed.
				break;	
			}
		}
		dragging = false;
		cardSelected = false;
	}
}

//UPDATE
void Player::update(float dt)
{
	//SPRITE ANIMATION
	for (unsigned i = 0; i < minions.size(); i++) {
		if (minions[i].checkTargeted(input->getMouseX(), input->getMouseY())) {		//If you are hovering over the minion, make him wave with both hands.
			minions[i].setDoubleWaving(true);
		}
		else {
			minions[i].setDoubleWaving(false);
		}
		minions[i].update(dt);
	}
	if (turn) {		//If it is this players turn.
		//Checking if the mouse is within an area before using more intensive collision detection for the cards.
		if ((player == 0 && input->getMouseY() > window->getSize().y - dropMinionBoundry) || (player == 1 && input->getMouseY() < dropMinionBoundry)) {		
			for (unsigned i = 0; i < hand.size(); i++) {
				if (hand[i].getSelected()) {
					return;					//If there is a card selected, break out of the update loop. this needs to go last as i am breaking out of the function if there is a collision. I should have this handled in a seperate function.
				}
			}							//Otherwise look for collisions.
			miniCardCollisions();
		}
	}
}

//RENDER
void Player::render()
{
	//HERO POWER
	window->draw(heroPower);
	window->draw(heroPowerManaCrystal);
	displayNumber(window, font, text, (heroPowerManaCrystal.getPosition().x - translate((float)window->getSize().y, 7)), heroPowerManaCrystal.getPosition().y - translate((float)window->getSize().y, 20.5f), heroPowerManaCost, (int)translate((float)window->getSize().y, 30), 0);

	//MANA CRYSTALS
	for (int j = 0; j < manaCrystals; j++) {
		manaCrystal.setPosition(manaCrystalsPos.x + j * (manaCrystal.getRadius() * 2 + manaCrystal.getRadius() * 0.7f), manaCrystalsPos.y);
		if (j < mana) {
			manaCrystal.setFillColor(Color::Cyan);
		}
		else {
			manaCrystal.setFillColor(Color::White);
		}
		window->draw(manaCrystal);
	}

	//MINIONS
	displayMinions();

	//HERO
	hero.render(turn, otherMinionsSelected(99));	//passing function an index that will never exist so it checks all the minions.

	//CARDS
	displayHand();

}

//MINIONS
//--------------------------------------------------------------------------

void Player::setMinionsTargetPos()
{
	int j;
	for (unsigned un_j = 0; un_j < minions.size(); un_j++) {	//Looping though all of the minions.
		j = static_cast<int>(un_j);				//this is converting unsigned to int for comparisons with hoveringposition.
		if (hoveringIndex == 10) {		//If you are not hovering over the minions.
			minions[j].setTargetPos(minions[j].getPos().x, minions[j].getPos().y);
		}
		else if (hoveringIndex <= j) {					//If you are hovering to the left of the minion.
			minions[j].setTargetPos(minions[j].getPos().x + minions[j].getRadius() + minionGap, minions[j].getPos().y);	//Set the target position(the position it wants to be in) to the right
		}
		else if (hoveringIndex > j) {						//Set the target position to the left
			minions[j].setTargetPos(minions[j].getPos().x - minions[j].getRadius() - minionGap, minions[j].getPos().y);
		}
	}
}

void Player::setMinionsRenderPos()
{
	for (unsigned i = 0; i < minions.size(); i++) {
		minions.at(i).setRenderPos(minions[i].getPos().x, minions[i].getPos().y);
	}
}

void Player::displayMinions()	//Displaying all of the minions.
{
	int j;				//Unsure as to what datatype to use when iterating through vectors.
	for (unsigned un_j = 0; un_j < minions.size(); un_j++) {
		j = static_cast<int>(un_j);
		if (!minions[j].getAnimating()) {
			minions[j].render(turn, otherMinionsSelected(minions[j].getMinId()));
		}
	}																										
	for (unsigned un_j = 0; un_j < minions.size(); un_j++) {
		j = static_cast<int>(un_j);
		if (minions[j].getAnimating()) {
			minions[j].render(turn, otherMinionsSelected(minions[j].getMinId()));
			break;
		}
	}
}

bool Player::otherMinionsSelected(int minionID)		//checking if any other minion is selected.
//this is being called a lot. could be cause of low framerate...
{
	if (minionID != 99) {	//if the minion is not the hero. (hero is esentially a minion.)
		if (hero.getSelected() && hero.getReady()) {
			return true;
		}
	}
	for (unsigned i = 0; i < minions.size(); i++) {
		if (minions[i].getMinId() != minionID) {
			if (minions[i].getSelected() && minions[i].getReady()) {
				return true;
			}
		}
	}
	return false;
}

void Player::minionCollisions()		//Setting the minions' "targeted" booleans. 
{
	for (unsigned i = 0; i < minions.size(); i++) {
		if (minions[i].checkTargeted((float)input->getMouseX(), (float)input->getMouseY())) {	
			minions[i].setTargeted(true);
			for (unsigned j = 0; j < minions.size(); j++) {	//Loop through all of the mininons
				if (i != j)									//Set all other minions targeted booleans to false. Only one card will be targeted at a time.
					minions.at(j).setTargeted(false);
			}
			break;
		}
		else {
			for (unsigned j = 0; j < minions.size(); j++) {
				minions.at(j).setTargeted(false);
			}
		}
	}
}

void Player::checkHoveringIndex()	//Setting the variable "hoveringPosition" to the index of the minions array a new minion would be in if you were to insert a minion here.
{
	if (minions.size() > 0 && ((player == 0 && input->getMouseY() < (float)window->getSize().y - dropMinionBoundry) || (player == 1 && input->getMouseY() > dropMinionBoundry))) {
		hoveringIndex = findMinionIndex();
	}
	else {
		hoveringIndex = 10;
	}
}



void Player::calculateMinionPositions()		//Calculates and sets the minions positions. This is called when placing a minion or when a minion dies.
{
	float minionX = 0;
	int i;
	for (unsigned un_i = 0; un_i < minions.size(); un_i++) {				//should i be using unsigned, int, size_t or what?
		i = static_cast<int>(un_i);
		if (minions.size() % 2 == 0) {		//ask about static_cast<int>()
			minionX = (float)window->getSize().x / 2 - translate(window->getSize().y, 12) + (i + 1 - static_cast<int>(minions.size()) / 2) * (minions.at(i).getRadius() + translate(window->getSize().y, 12)) * 2 - minions.at(i).getRadius();
		}
		else {
			minionX = (float)window->getSize().x / 2 + (i - static_cast<int>(minions.size()) / 2) * (minions.at(i).getRadius() + translate(window->getSize().y, 12)) * 2;
		}
		minions.at(i).setPos(minionX, minions[i].getPos().y);

		minions.at(i).setTargetPos(minionX, minions[i].getPos().y);

	}
}

int Player::findMinionIndex()		//When hovering over the minions, find the index of the where the minion would be if you were to place it here.
{
	int position = 0;
	for (unsigned i = 0; i < minions.size(); i++) {
		if ((float)input->getMouseX() > minions.at(i).getPos().x) {
			position = i + 1;
		}
		else {
			position = i;
			break;
		}
	}
	return position;
}
//--------------------------------------------------------------------------


//CARDS
//--------------------------------------------------------------------------
void Player::displayHand() {		//Displaying all of the cards in the hand.		
	for (int j = hand.size() - 1; j >= 0; j--) {		//Looping backwards to display back card first
		if (!hand[j].getSelected()) {							//these if statements should be handled in Card?
			hand[j].displayCard(turn, mana, (minions.size() >= 7));
		}
	}
	for (int j = hand.size() - 1; j >= 0; j--) {
		if (hand[j].getSelected() && hand[j].checkPickedUp((float)input->getMouseX(), (float)input->getMouseY(), mana)) {	//Render at the targeted position until the mouse has been dragged a certain distance.
			hand[j].displaySelectedCard((float)input->getMouseX(), (float)input->getMouseY(), mana, (minions.size() >= 7));
		}
		else if (hand[j].getTargeted()) {		//Displaying the targeted card if you are targeting it.
			hand[j].displayTargetedCard(mana, (minions.size() >= 7));
		}
	}
}

void Player::calculateCardPositions()			//For displaying cards in an arc.	
{
	Card* card;
	for (unsigned j = 0; j < hand.size(); j++) {
		card = &hand[j];
		hand[j].calculatePosition(5 * 2 + hand.size(), j + 5 + 1);		
	}
	//I am passing the function 10 extra "invisible" cards. These will not be acknowledged except for using them as an "offset". 10 is card.offset * 2. (offset at both sides).  
	// + 6 is for displaying the first card (at the back of the hand) at the (offset + 1)s position. 
}

bool Player::miniCardCollisions()			//Using ray casting for collision detection for the cards
{
	for (unsigned i = 0; i < hand.size(); i++) {				//THIS COULD BE OPTIMISED FURTHER!
		hand[i].checkTargeted(*mouse);				//Passing a reference to a Line object for the line from (0, 0) to mouse co-ordinates
		if (hand[i].getTargeted()) {					//If the card is targeted
			for (unsigned j = 0; j < hand.size(); j++) {	//Loop through all of the cards
				if (i != j)									//Set all other cards targeted booleans to false. Only one card will be targeted at a time.
					hand.at(j).setTargeted(false);
			}
			return true;
		}
	}
	return false;
}
//--------------------------------------------------------------------------


//GAMEPLAY
//--------------------------------------------------------------------------

void Player::createDeck()		//Creating the deck. (This should be handled outside of the Game class maybe. In Setup class or similar.)
{
									
	//Kind of stupid way of creating the deck as it does not randomise it. Ran out of time to implement this.
	

	Card one(window, font, texture, player, 1, "", 1, 1, 0);
	Card two(window, font, texture, player, 2, "", 2, 1, 1);
	Card three(window, font, texture, player, 3, "", 1, 3, 1);
	Card four(window, font, texture, player, 4, "", 2, 3, 2);
	Card five(window, font, texture, player, 5, "", 3, 2, 2);
	Card six(window, font, texture, player, 6, "", 3, 4, 3);
	Card seven(window, font, texture, player, 7, "", 5, 1, 3);
	Card eight(window, font, texture, player, 8, "", 4, 5, 4);
	Card nine(window, font, texture, player, 9, "", 2, 8, 4);
	Card ten(window, font, texture, player, 10, "", 5, 6, 5);
	Card eleven(window, font, texture, player, 11, "", 1, 1, 0);
	Card twelve(window, font, texture, player, 12, "", 2, 1, 1);
	Card thirteen(window, font, texture, player, 13, "", 1, 3, 1);
	Card fourteen(window, font, texture, player, 14, "", 2, 3, 2);
	Card fifteen(window, font, texture, player, 15, "", 3, 2, 2);
	Card sixteen(window, font, texture, player, 16, "", 3, 4, 3);
	Card seventeen(window, font, texture, player, 17, "", 5, 1, 3);
	Card eighteen(window, font, texture, player, 18, "", 4, 5, 4);
	Card nineteen(window, font, texture, player, 19, "", 2, 8, 4);
	Card twenty(window, font, texture, player, 20, "", 5, 6, 5);

	if (player == 1) {
		deck.push_back(sixteen);
		deck.push_back(five);
		deck.push_back(fourteen);
		deck.push_back(seven);
		deck.push_back(six);
		deck.push_back(three);
		deck.push_back(nineteen);
		deck.push_back(twenty);
		deck.push_back(eight);
		deck.push_back(twelve);
		deck.push_back(one);
		deck.push_back(nine);
		deck.push_back(ten);
		deck.push_back(seventeen);
		deck.push_back(eleven);
		deck.push_back(thirteen);
		deck.push_back(four);
		deck.push_back(fifteen);
		deck.push_back(eighteen);
		deck.push_back(two);
	}
	else {
		deck.push_back(four);
		deck.push_back(one);
		deck.push_back(eight);
		deck.push_back(nine);
		deck.push_back(ten);
		deck.push_back(eleven);
		deck.push_back(fifteen);
		deck.push_back(twelve);
		deck.push_back(seven);
		deck.push_back(fourteen);
		deck.push_back(six);
		deck.push_back(seventeen);
		deck.push_back(eighteen);
		deck.push_back(thirteen);
		deck.push_back(twenty);
		deck.push_back(five);
		deck.push_back(three);
		deck.push_back(nineteen);
		deck.push_back(sixteen);
		deck.push_back(two);
	}
}

void Player::gainManaCrystals(int manaCrystals_)		//Incrementing the mana crystals the player has by a given amount.
{
	if (manaCrystals < 10) {
		manaCrystals += manaCrystals_;
	}
	if (manaCrystals > 10) {
		manaCrystals = 10;
	}
}

void Player::gainMana(int mana_)		//Incrementing the mana the player has by a given amount.
{
	if (mana + mana_ <= manaCrystals) {
		mana += mana_;
	}
	else {
		mana = manaCrystals;
	}
}

void Player::placeMinion(int cardIndex) {	//Creating a new minion from the stats of the card and inserting it into the minions array at the calculated index.
	Card* card = &hand.at(cardIndex);
	//incrementing minionIDCounter to give minion an ID in order they are played.
	Minion minion(window, font, player, minionIDCounter++, card->getName(), card->getAttack(), card->getHealth(), texture, audioManager);		
	int minionIndex;
	if (minions.size() > 0) {			
		minionIndex = findMinionIndex();
	}
	else {
		minionIndex = 0;
	}
	minions.insert(minions.begin() + minionIndex, minion);	//Have to use begin() as insert() expects an iterator
	minions[minionIndex].setTexture(&texture);
	calculateMinionPositions();					//Updating the positions of the minions.
	setMinionsRenderPos();
	hand.erase(hand.begin() + cardIndex);		//Erasing the card from the hand.
	
}

void Player::drawCard()			//Draws a card from the deck.
{
	if (hand.size() < 10 && deck.size() > 0) {
		hand.insert(hand.begin(), deck.at(deck.size() - 1));	//is this passing a copy of the object?
		deck.pop_back();
		resizeWindow();				//this is overkill as it is resizing everything as aposed to just the card but i will leave it for now until i hit fps problems.
		calculateCardPositions();
	}
}

bool Player::checkEndTurn()			//If there are no cards left that you can play.
{
	if (hero.getReady()) {
		return false;
	}
	for (unsigned i = 0; i < minions.size(); i++) {
		if (minions[i].getReady()) {
			return false;
		}
	}
	for (unsigned i = 0; i < hand.size(); i++) {
		if (hand[i].getManaCost() <= mana) {
			return false;
		}
	}
	return true;
}

//--------------------------------------------------------------------------


