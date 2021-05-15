#include "Minion.h"

Minion::Minion()
{

}

Minion::Minion(sf::RenderWindow* window_, sf::Font* font_, int player_, int minID_, string description_, int attack_, int health_, Texture& texture_, AudioManager* audioManager_)
{
	window = window_;
	font = font_;
	minId = minID_;
	description = description_;
	attack = attack_;
	health = health_;
	player = player_;
	waveTexture = texture_;
	audioManager = audioManager_;
	renderAttack = attack;
	renderHealth = health;

	wave.addFrame(sf::IntRect(0, 0, 140, 232));
	wave.addFrame(sf::IntRect(140, 0, 140, 232));
	wave.addFrame(sf::IntRect(280, 0, 140, 232));
	wave.addFrame(sf::IntRect(420, 0, 140, 232));
	wave.addFrame(sf::IntRect(280, 0, 140, 232));
	wave.addFrame(sf::IntRect(140, 0, 140, 232));
	wave.addFrame(sf::IntRect(0, 0, 140, 232));
	wave.setFrameSpeed(1.f / 10.f);
	wave.setLooping(true);

	doubleWave.addFrame(sf::IntRect(0, 233, 140, 232));
	doubleWave.addFrame(sf::IntRect(140, 233, 140, 232));
	doubleWave.addFrame(sf::IntRect(280, 233, 140, 232));
	doubleWave.addFrame(sf::IntRect(420, 233, 140, 232));
	doubleWave.addFrame(sf::IntRect(280, 233, 140, 232));
	doubleWave.addFrame(sf::IntRect(140, 233, 140, 232));
	doubleWave.addFrame(sf::IntRect(0, 233, 140, 232));
	doubleWave.setFrameSpeed(1.f / 10.f);
	doubleWave.setLooping(true);

	setTargetPos(0, 0);
	setRenderPos(0, 0);
	setPos(0, 0);
	alive = true;
	renderAlive = true;
	targeted = false;
	selected = false;
	ready = false;
	points = 40;
	scale = 1.3f;
	minionConvex.setFillColor(Color::White);
	minionConvex.setOutlineColor(Color::Black);
	minionConvex.setOutlineThickness(2);
	minionConvex.setPointCount(points);
	resizeWindow();
	attackCircle.setOutlineThickness(2);
	attackCircle.setOutlineColor(Color::Black);
	attackCircle.setFillColor(sf::Color::Yellow);
	healthCircle.setOutlineThickness(2);
	healthCircle.setOutlineColor(Color::Black);
	healthCircle.setFillColor(sf::Color::Red);
	animate = false;
	seperating = false;
	attacking = false;
	collided = false;
	animating = false;
	lastTargetPos = targetPos;
}

Minion::~Minion()
{
}

void Minion::setTexture(Texture* texture_)
{
	waveSprite.setTexture(*texture_);
	waveSprite.setPosition(pos);
	waveSprite.setScale(translate((float)window->getSize().y, 0.3f), translate((float)window->getSize().y, 0.3f));
}

void Minion::resizeWindow()		//Resizing everything using static translate() function.
{
	textSize = (int)translate((float)window->getSize().y, 30);
	radius = translate((float)window->getSize().y, 42);
	float step = PI * 2 / points;		//Drawing the oval for the minion.
	float twoPI = PI * 2;
	int counter = 0;
	for (float theta = 0; theta < twoPI; theta += step) {
		minionConvex.setPoint(counter++, Vector2f((float)(cos(theta) * radius), (float)(sin(theta) * radius * scale)));
	}
	pos.x = (float)window->getSize().x / 2;
	if (player == 0) {				//Setting position of the minion.
		pos.y = window->getSize().y / 2 + radius * scale + translate((float)window->getSize().y, 15);
	}
	else if (player == 1) {
		pos.y = window->getSize().y / 2 - radius * scale - translate((float)window->getSize().y, 15);
	}
	renderPos = pos;
	circleRadius = translate((float)window->getSize().y, 15);
	attackCircle.setRadius(circleRadius);
	healthCircle.setRadius(circleRadius);
	attackCirclePos = Vector2f(-radius - circleRadius * 0.2f, radius * scale - circleRadius * 1.8f);
	healthCirclePos = Vector2f(radius - circleRadius * 1.8f, radius * scale - circleRadius * 1.8f);
	circleTextPos = Vector2f(circleRadius * 0.55f, -circleRadius * 0.35f);
	waveSprite.setScale(translate((float)window->getSize().y, 0.3f), translate((float)window->getSize().y, 0.3f));
}

//GETTER FUNCTIONS
int Minion::getMinId() { return minId; }
string Minion::getName() { return name; }
string Minion::getDescription() { return description; }
Vector2f Minion::getPos() { return pos; }
Vector2f Minion::getTargetPos() { return targetPos; }
Vector2f Minion::getRenderPos() { return renderPos; }
bool Minion::getTargeted() { return targeted; }
bool Minion::getSelected() { return selected; }
float Minion::getScale() { return scale; }
float Minion::getRadius() { return radius; }
bool Minion::getReady() { return ready; }
int Minion::getPlayer() { return player; }
ConvexShape* Minion::getMinionConvex() { return &minionConvex; }
Vector2f Minion::getVelocity() { return velocity; }
Vector2f Minion::getAcceleration() { return acceleration; }
bool Minion::getAlive() { return alive; }
bool Minion::getRenderAlive() { return renderAlive; }
bool Minion::getAnimating() { return animating; }
Minion* Minion::getTarget() { return target; }
int Minion::getAttack() { return attack; }
int Minion::getHealth() { return health; }

//SETTER FUNCTIONS
void Minion::setDescription(string description_) { description = description_; }
void Minion::setAttack(int attack_) { attack = attack_; }
void Minion::setHealth(int health_) { health = health_; }
void Minion::setTargeted(bool targeted_) { targeted = targeted_; }
void Minion::setSelected(bool selected_) { selected = selected_; }
void Minion::setReady(bool ready_) { ready = ready_; }
void Minion::setPos(float x, float y) { pos.x = x; pos.y = y; }
void Minion::setTargetPos(float x, float y) { targetPos.x = x; targetPos.y = y; }
void Minion::setRenderPos(float x, float y) { renderPos.x = x; renderPos.y = y; }
void Minion::setVelocity(float x, float y) { velocity.x = x; velocity.y = y; }
void Minion::setAcceleration(float x, float y) { acceleration.x = x; acceleration.y = y; }
void Minion::setTargetVector() { targetVector = targetPos - pos; }
void Minion::setTarget(Minion* target_) { target = target_; }
void Minion::setAnimating(bool animating_) { animating = animating_; }
void Minion::setDoubleWaving(bool doubleWaving_) { doubleWaving = doubleWaving_; }

void Minion::update(float dt)
{
	//SPRITE ANIMATIONS
	if (!doubleWaving) {
		waveSprite.setTextureRect(wave.getCurrentFrame());
		wave.animate(dt);
	}
	else {
		waveSprite.setTextureRect(doubleWave.getCurrentFrame());
		doubleWave.animate(dt);
	}
}

bool Minion::repositioning(float dt)
{
	if (targetPos != lastTargetPos) {		//Detecting change in direction. If there is a change then stop moving.
		velocity.x = 0;
	}
	lastTargetPos = targetPos;			
	acceleration.x = 0.02;
	if (renderPos.x < targetPos.x) {		
		velocity += acceleration;
		renderPos.x += velocity.x * dt * 200;		//Shifting the minion to its target position.
	}
	else if (renderPos.x > targetPos.x) {
		velocity += acceleration;
		renderPos.x -= velocity.x * dt * 200;
	}
	if (abs(renderPos.x - targetPos.x) < 1) {  //If it is within a certain distance of its destination.
		acceleration.x = 0.02;
		velocity.x = 0;
		renderPos.x = targetPos.x;
		return false;				//If it has reached its destination then return false, as in it is no longer repositioning
	}
	return true;	//Else return true;
}

bool Minion::animation(float dt) {		//Is the minion in an animation state.

	setAcceleration(targetVector.x * 0.02, targetVector.y * 0.02);		//Setting the acceleration to a division of the target vector
	
	velocity += acceleration;							//Adding the force (acceleration) to the velocity.
	
	renderPos += velocity * dt;		

	if (((player == 0 && renderPos.y <= targetPos.y) || (player == 1 && renderPos.y >= targetPos.y)) && !collided) {	//If it has collided with the target.
		collided = true;
		targetVector = -targetVector;		//Changing direction.
		velocity.x = 0;
		velocity.y = 0;
		renderFight(target);			//Calling the fight function for updating the game state to be rendered.
		setTargetPos(pos.x, pos.y);		//Setting it's new target position to its original position.
		audioManager->playSoundbyName("breaking glass");
	}
	else if (((player == 0 && renderPos.y >= targetPos.y) || (player == 1 && renderPos.y <= targetPos.y)) && collided) {
		renderPos = pos;		//It should now be being displayed at it's actual position.
		velocity.x = 0;			//Resetting the velocity and acceleration vectors.
		velocity.y = 0;
		acceleration.x = 0;
		acceleration.y = 0;
		collided = false;		//Resetting booleans.
		animating = false;
		return false;
	}
	return true;			//If it does not reach the previous if statement then it is in an animation state so return true.
}

void Minion::render(bool turn, bool otherMinionsSelected) {		//Displaying the minion.
	minionConvex.setPosition(renderPos.x, renderPos.y);					
	if (turn) {
		if (ready) {		//If the minion is ready, give it a green outline to indicate.
			if (selected) {
				minionConvex.setOutlineColor(Color::Green);
				minionConvex.setOutlineThickness(6);
				window->draw(minionConvex);
			}
			else if (!otherMinionsSelected) {		
				minionConvex.setOutlineColor(Color::Green);
				minionConvex.setOutlineThickness(6);
				window->draw(minionConvex);
			}
		}
	}
	else if (!turn && targeted && alive) {			//Highlight targeted enemy minion with a red outline.
		minionConvex.setOutlineColor(Color::Red);
		minionConvex.setOutlineThickness(6);
		window->draw(minionConvex);
	}
	minionConvex.setOutlineColor(Color::Black);
	minionConvex.setOutlineThickness(2);
	window->draw(minionConvex);
	waveSprite.setPosition(renderPos.x - translate((float)window->getSize().y, 20), renderPos.y - translate((float)window->getSize().y, 35));
	window->draw(waveSprite);
	attackCircle.setPosition(renderPos.x + attackCirclePos.x, renderPos.y + attackCirclePos.y);
	healthCircle.setPosition(renderPos.x + healthCirclePos.x, renderPos.y + healthCirclePos.y);
	window->draw(attackCircle);
	window->draw(healthCircle);
	displayNumber(window, font, text, (renderPos.x + attackCirclePos.x + circleTextPos.x), (renderPos.y + attackCirclePos.y + circleTextPos.y), renderAttack, textSize, 0);
	displayNumber(window, font, text, (renderPos.x + healthCirclePos.x + circleTextPos.x), (renderPos.y + healthCirclePos.y + circleTextPos.y), renderHealth, textSize, 0);	
}

bool Minion::checkTargeted(float mouseX, float mouseY)	//If the mouse is hovering over the minion's hitbox.
{
	if (mouseX > pos.x - radius && mouseX < pos.x + radius && mouseY > pos.y - radius * scale && mouseY < pos.y + radius * scale) {
		return true;
	}
	else {
		return false;
	}
}

void Minion::fight()				//This function happens instantly when you tell a minion to attack another.
{
	target->takeDamage(attack);
	takeDamage(target->getAttack());
}

void Minion::takeDamage(int damage)		//This function changes the true health values of the minions instantly.
{
	health -= damage;
	if (health <= 0) {
		alive = false;
	}
}

void Minion::renderFight(Minion* enemy)					//This function happens when the minions collide during the animation.
{														//nearly duplicate functions...
	enemy->renderTakeDamage(attack);
	renderTakeDamage(enemy->getAttack());
}

void Minion::renderTakeDamage(int damage)		//This function affects the numbers that are displayed to the user.
{
	renderHealth -= damage;
	if (renderHealth <= 0) {
		renderAlive = false;
	}
}



//Future Ideas...
//int Minion::getMinType() { return minType; }
//bool Minion::getCharge() { return charge; }
//bool Minion::getDivineShield() { return divineShield; }
//bool Minion::getTaunt() { return taunt; }
//bool Minion::getWindfury() { return windfury; }
//bool Minion::getLifesteal() { return lifesteal; }
//bool Minion::getDeathrattle() { return deathrattle; }
//bool Minion::getFrozen() { return frozen; }
//bool Minion::getSilenced() { return silenced; }
//bool Minion::getStealth() { return stealth; }
//void Minion::setCharge(bool charge_) { charge = charge_; }
//void Minion::setDivineShield(bool divineShield_) { divineShield = divineShield_; }
//void Minion::setTaunt(bool taunt_) { taunt = taunt_; }
//void Minion::setWindfury(bool windfury_) { windfury = windfury_; }
//void Minion::setLifesteal(bool lifesteal_) { lifesteal = lifesteal_; }
//void Minion::setDeathrattle(bool deathrattle_) { deathrattle = deathrattle_; }
//void Minion::setFrozen(bool frozen_) { frozen = frozen_; }
//void Minion::setSilenced(bool silenced_) { silenced = silenced_; }
//void Minion::setStealth(bool stealth_) { stealth = stealth_; }










