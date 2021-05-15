#include "Game.h"

using namespace std;

Game::Game(sf::RenderWindow* window_, Input* input_, Line* mouse_)
{
	window = window_;
	input = input_;
	mouse = mouse_;

	if (!font.loadFromFile("Fonts/belwe_bold.ttf")) {		//Loading font.
		cout << "Error loading font." << endl;
	}

	audioManager.addMusic("Assets/hearthstone_music.ogg", "hyrule");
	audioManager.addSound("Assets/Glass_Break.ogg", "breaking glass");
	audioManager.playMusicbyName("hyrule");

	//backgroundTexture.loadFromFile("Backgrounds/Uldaman_Board.png");

	Player player1Initialaser(window, input, mouse, &font, 0, &audioManager);
	Player player2Initialaser(window, input, mouse, &font, 1, &audioManager);

	players[0] = player1Initialaser;
	players[1] = player2Initialaser;

	for (int i = 0; i < 3; i++) {
		players[0].drawCard();
		players[1].drawCard();
	}

	/*for (int i = 0; i < 10; i++) {
		players[0].drawCard();
		players[1].drawCard();
	}
	for (int i = 0; i < 7; i++) {
		players[0].placeMinion(0);
		players[1].placeMinion(0);
	}
	for (int i = 0; i < 7; i++) {
		players[0].drawCard();
		players[1].drawCard();
	}*/

	if (!fpsFont.loadFromFile("Fonts/arial.ttf")) {
		cout << "Error loading font." << std::endl;
	}
	fpsText.setFont(fpsFont);
	fpsText.setFillColor(sf::Color::Black);

	frameCount = 0;
	sum = 0;

	//turnIndicator.setOutlineColor(Color::Black);
	//turnIndicator.setOutlineThickness(2);
	//turnIndicator.setFillColor(Color::Black);

	endTurnButton.setOutlineColor(Color::Black);
	endTurnButton.setOutlineThickness(2);
	endTurnButton.setFillColor(Color::Transparent);
	endTurnButton.setPointCount(36);

	line[0].color = Color(200, 200, 200, 255);
	line[1].color = Color(200, 200, 200, 255);

	rope[0].color = Color::Black;
	rope[1].color = Color::Black;

	resizeWindow();

	bool foundSelected = false;

	arrow[0].color = Color::Black;
	arrow[1].color = Color::Black;

	turnTimer = 0;

	pauseTexture.loadFromFile("Assets/pause.png");
	pauseSprite.setTexture(pauseTexture);
	pauseSprite.setPosition((float)window->getSize().x / 2, (float)window->getSize().y / 2);
	pauseSprite.setOrigin(pauseTexture.getSize().x / 2, pauseTexture.getSize().y / 2);

	victoryTexture.loadFromFile("Assets/victory.png");
	victorySprite.setTexture(victoryTexture);
	victorySprite.setPosition((float)window->getSize().x / 2, (float)window->getSize().y / 2);
	victorySprite.setOrigin(victoryTexture.getSize().x / 2, victoryTexture.getSize().y / 2);

	defeatTexture.loadFromFile("Assets/defeat.png");
	defeatSprite.setTexture(defeatTexture);
	defeatSprite.setPosition((float)window->getSize().x / 2, (float)window->getSize().y / 2);
	defeatSprite.setOrigin(defeatTexture.getSize().x / 2, defeatTexture.getSize().y / 2);

	paused = false;
	started = false;
	tutorial = false;
	victory = false;
	defeat = false;

	titleTexture.loadFromFile("Assets/title.png");
	titleSprite.setTexture(titleTexture);
	titleSprite.setOrigin(titleTexture.getSize().x / 2, titleTexture.getSize().y / 2);

	animationState = true;

	
	playButton.setFillColor(Color::White);
	playButton.setOutlineColor(Color::Black);
	playButton.setOutlineThickness(3);
	playText.setFont(fpsFont);
	playText.setFillColor(Color::Black);
	playText.setString("Play");
	
	rulesButton.setFillColor(Color::White);
	rulesButton.setOutlineColor(Color::Black);
	rulesButton.setOutlineThickness(3);
	rulesText.setFont(fpsFont);
	rulesText.setFillColor(Color::Black);
	rulesText.setString("Tutorial");

	tutorialTexture.loadFromFile("Assets/Tutorial page.png");
	tutorialSprite.setTexture(tutorialTexture);
}

Game::~Game()
{
}

void Game::resizeWindow()		//resizing everything using my global translate function. Every class has its own resizeWindow() function that scales everything.
{
	playButton.setPosition(((float)window->getSize().x / 2 - translate((float)window->getSize().y, 100)) - translate((float)window->getSize().y, 180), translate((float)window->getSize().y, 500));
	playButton.setSize(Vector2f(translate((float)window->getSize().y, 280), translate((float)window->getSize().y, 100)));
	playText.setCharacterSize(translate((float)window->getSize().y, 70));
	playText.setPosition(playButton.getPosition().x + translate((float)window->getSize().y, 70), playButton.getPosition().y + translate((float)window->getSize().y, 4));

	rulesButton.setPosition(((float)window->getSize().x / 2 - translate((float)window->getSize().y, 100)) + translate((float)window->getSize().y, 180), translate((float)window->getSize().y, 500));
	rulesButton.setSize(Vector2f(translate((float)window->getSize().y, 280), translate((float)window->getSize().y, 100)));
	rulesText.setCharacterSize(translate((float)window->getSize().y, 70));
	rulesText.setPosition(rulesButton.getPosition().x + translate((float)window->getSize().y, 23), rulesButton.getPosition().y + translate((float)window->getSize().y, 4));

	titleSprite.setPosition((float)window->getSize().x / 2, (float)window->getSize().y / 2);
	titleSprite.setScale(translate((float)window->getSize().y, 1), translate((float)window->getSize().y, 1));

	pauseSprite.setPosition((float)window->getSize().x / 2, (float)window->getSize().y / 2);
	pauseSprite.setScale(translate((float)window->getSize().y, 1), translate((float)window->getSize().y, 1));
	victorySprite.setPosition((float)window->getSize().x / 2, (float)window->getSize().y / 2);
	victorySprite.setScale(translate((float)window->getSize().y, 1), translate((float)window->getSize().y, 1));
	defeatSprite.setPosition((float)window->getSize().x / 2, (float)window->getSize().y / 2);
	defeatSprite.setScale(translate((float)window->getSize().y, 1), translate((float)window->getSize().y, 1));

	line[0].position.x = (float)window->getSize().x / 2 - translate((float)window->getSize().y, 400);
	line[0].position.y = (float)window->getSize().y / 2;
	line[1].position.x = (float)window->getSize().x / 2 + translate((float)window->getSize().y, 400);
	line[1].position.y = (float)window->getSize().y / 2;

	//END TURN BUTTON
	int counter = 0;
	float r = translate((float)window->getSize().y, 115);
	float a = PI / 120;		//for tweaking angle.
	float d = 88;
	for (float theta = PI + PI / 3 + a + PI / 3 / 20; theta < PI + PI / 3 * 2 + a - PI / 3 / 20; theta += PI / 3 / 20) {	//drawing an arc.
		endTurnButton.setPoint(counter++, Vector2f((float)(cos(theta) * r), translate((float)window->getSize().y, d) + (float)(sin(theta) * r)));
	}
	for (float theta = PI / 3 + a + PI / 3 / 20; theta < PI / 3 * 2 - PI / 3 / 20 * 2 + a; theta += PI / 3 * 1 / 20) {
		endTurnButton.setPoint(counter++, Vector2f((float)(cos(theta) * r), -translate((float)window->getSize().y, d) + (float)(sin(theta) * r)));
	}
	endTurnButton.setPosition(Vector2f((float)window->getSize().x / 2 + translate((float)window->getSize().y, 450), (float)window->getSize().y / 2));

	fpsText.setCharacterSize((int)translate((float)window->getSize().y, 30));
	fpsText.setPosition(translate((float)window->getSize().y, 50), translate((float)window->getSize().y, 700));

	players[0].resizeWindow();
	players[1].resizeWindow();
}

void Game::endTurn()		//Functionality for when the end turn button is pressed or you time out.
{
									//BUG!!! If you are holding cards when the turn ends there are problems.
	turnTimer = 0;
	(turn == 0) ? turn = 1 : turn = 0;	//Switching turn of the players.
	players[(turn == 0) ? 1 : 0].setTurn(false);										//Setting the "turn" booleans of the players.
	players[turn].setTurn(true);
	players[turn].drawCard();							//The player draws a card, gains a mana crystal and refreshes mana.
	players[turn].gainManaCrystals(1);
	players[turn].gainMana(players[turn].getManaCrystals());
	for (unsigned i = 0; i < players[(turn == 0) ? 1 : 0].getMinions().size(); i++) {		//Setting all of the OTHER player's minions "ready" state to false.
		players[(turn == 0) ? 1 : 0].getMinions()[i].setReady(false);
	}
	for (unsigned i = 0; i < players[turn].getMinions().size(); i++) {		//Setting all of THIS player's minions "ready" state to true if their attack is greater than 0.
		if (players[turn].getMinions()[i].getAttack() > 0) {
			players[turn].getMinions()[i].setReady(true);
		}
	}
	if (players[turn].getHero().getAttack() > 0) {		//Set the player's hero's boolean to true if it's attack is greater than 0.
		players[turn].getHero().setReady(true);
	}
}

void Game::handleInput()
{
	//EXIT
	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		window->close();
	}

	//PAUSE
	if (input->isKeyDown(sf::Keyboard::Space))
	{
		input->setKeyUp(sf::Keyboard::Space);
		if (!victory && !defeat) {
			if (paused) {
				paused = false;
			}
			else {
				paused = true;
			}
		}
	}

	if (!input->isMouseLeftDown()) {
		mousePressed = false;			
	}
	if (!started) {			//Display the menu screen if the game has not started. 
		if (input->isMouseLeftDown()) {
			if (tutorial && !mousePressed) {		//Hacky bit of code to stop flickering between screens.
				tutorial = false; 
			}
			else{
				//If you click you play.
				if (input->getMouseX() >= playButton.getPosition().x && input->getMouseX() <= playButton.getPosition().x + translate((float)window->getSize().y, 280) &&
					input->getMouseY() >= playButton.getPosition().y && input->getMouseY() <= playButton.getPosition().y + translate((float)window->getSize().y, 100) && !mousePressed) {
					started = true;
				}
				//If you click on Tutorial.
				if (input->getMouseX() >= rulesButton.getPosition().x && input->getMouseX() <= rulesButton.getPosition().x + translate((float)window->getSize().y, 280) &&
					input->getMouseY() >= rulesButton.getPosition().y && input->getMouseY() <= rulesButton.getPosition().y + translate((float)window->getSize().y, 100) && !mousePressed) {
					tutorial = true;
				}
			}
			mousePressed = true;
		}
	}
	//If the game has started.
	else {
		if (!paused) {		//If the game is not paused.
			//MOUSE DOWN
			if (input->isMouseLeftDown()) {
				//MINION SELECTION
				//------------------------------------------------------------------------
				for (int i = 0; i < 2; i++) {			//For each player.					
					if (!players[i].getMinionSelected() && !players[i].getDragging()) {	//If it is targeted and you press the mouse down. (and it is not already selected and you are not dragging the mouse.)
						//HERO
						if (players[i].getHero().getTargeted()) {
							players[i].getHero().setSelected(true);
							players[i].setMinionSelected(true);			//Boolean saying if any minion is selected. (Hero is a minion.) (This is so I don't have to loop each time to check if any are selected.)
						}
						//MINIONS				
						for (unsigned j = 0; j < players[i].getMinions().size(); j++) {
							if (players[i].getMinions()[j].getPlayer() == turn && players[i].getMinions()[j].getTargeted()) {
								players[i].setMinionSelected(true);
								players[i].getMinions()[j].setSelected(true);
								break;
							}
						}
					}
				}

				//------------------------------------------------------------------------

				//END TURN BUTTON
				//------------------------------------------------------------------------
				if (!players[turn].getDragging() && que.size() == 0) {		//If the mouse is not being dragged and there are no animations happening.
					//AABB collision detection.
					if ((input->getMouseX() >= endTurnButton.getPosition().x - translate((float)window->getSize().y, 50)) && (input->getMouseX() < endTurnButton.getPosition().x + translate((float)window->getSize().y, 50)) &&
						(input->getMouseY() >= endTurnButton.getPosition().y - translate((float)window->getSize().y, 27)) && (input->getMouseY() < endTurnButton.getPosition().y + translate((float)window->getSize().y, 27))) {
						//Circle collision detection for curved edges.
						if (pow(input->getMouseX() - endTurnButton.getPosition().x, 2) + pow(input->getMouseY() - endTurnButton.getPosition().y - translate((float)window->getSize().y, 88), 2) <= pow((float)translate((float)window->getSize().y, 115), 2) &&
							pow(input->getMouseX() - endTurnButton.getPosition().x, 2) + pow(input->getMouseY() - endTurnButton.getPosition().y + translate((float)window->getSize().y, 88), 2) <= pow((float)translate((float)window->getSize().y, 115), 2)) {
							input->setMouseLeftDown(false);
							endTurn();		//If you click the button, end turn.
						}
					}
				}
				//------------------------------------------------------------------------
			}

			//MOUSE UP
			else if (!input->isMouseLeftDown()) {

				//ATTACKING
				//------------------------------------------------------------------------

				//MINIONS	
				//---------------------------------
				for (unsigned i = 0; i < players[turn].getMinions().size(); i++) {											//Checking all the minions on the player's side who's turn it is.
					if (players[turn].getMinions()[i].getSelected() && players[turn].getMinions()[i].getReady()) {			//If a minion is selected and ready.

						//ENEMY MINIONS																																
						for (unsigned j = 0; j < players[(turn == 0) ? 1 : 0].getMinions().size(); j++) {					//Check all the minions on the other player's side.
							if (players[(turn == 0) ? 1 : 0].getMinions()[j].getTargeted() && players[(turn == 0) ? 1 : 0].getMinions()[j].getAlive()) {		//If a minion is targeted and it is alive.
								players[turn].getMinions()[i].setTarget(&players[(turn == 0) ? 1 : 0].getMinions()[j]);		//Setting a pointer to the enemy minion as it's "target".
								players[turn].getMinions()[i].fight();														//Calling fight() function to edit hit points of each minion.
								players[turn].getMinions()[i].setReady(false);							//Setting this minion's "ready" boolean to false.
								interaction.x = i;
								interaction.y = j;					//Setting a Vector2i equal to the attacking minion's index, the defending minion's index and who's turn it is.
								que.push_back(interaction);			//Adding this "interaction" to the "que" (This is a deque which is like a vector in that it is an array of dynamic size but it is a data structure that handles "first in, first out".)
								break;
							}
						}

						//ENEMY HERO
						if (players[(turn == 0) ? 1 : 0].getHero().getTargeted() && players[(turn == 0) ? 1 : 0].getHero().getAlive()) {				//If the hero is targeted and alive.
							players[turn].getMinions()[i].setTarget(&players[(turn == 0) ? 1 : 0].getHero());		//Doing the same thing here for the hero as for the minions above.
							players[turn].getMinions()[i].fight();
							players[turn].getMinions()[i].setReady(false);
							interaction.x = i;
							interaction.y = 9;					//The number 9 represents the hero. (This is an index that will not be used as there is a maximum of 7 minions allowed on the board.
							que.push_back(interaction);
						}
						break;
					}
				}
				//---------------------------------


				//HERO
				//---------------------------------
				if (players[turn].getHero().getSelected() && players[turn].getHero().getReady()) {				//If the hero is selected and ready.
					//ENEMY HERO
					if (players[(turn == 0) ? 1 : 0].getHero().getTargeted() && players[(turn == 0) ? 1 : 0].getHero().getAlive()) {			//If the enemy hero is targeted and alive.
						players[turn].getHero().setTarget(&players[(turn == 0) ? 1 : 0].getHero());				//Setting a pointer to the enemy hero as it's "target".
						players[turn].getHero().fight();
						players[turn].getHero().setReady(false);
						interaction.x = 9;
						interaction.y = 9;
						que.push_back(interaction);				//Adding the interaction to the que.
					}
					//ENEMY MINIONS
					else {
						for (unsigned i = 0; i < players[(turn == 0) ? 1 : 0].getMinions().size(); i++) {				//Same process as above but for hero attacking minions.
							if (players[(turn == 0) ? 1 : 0].getMinions()[i].getTargeted() && players[(turn == 0) ? 1 : 0].getMinions()[i].getAlive()) {
								players[turn].getHero().setTarget(&players[(turn == 0) ? 1 : 0].getMinions()[i]);
								players[turn].getHero().fight();
								players[turn].getHero().setReady(false);
								interaction.x = 9;
								interaction.y = i;
								que.push_back(interaction);
								break;
							}
						}
					}
				}
				//---------------------------------
				//------------------------------------------------------------------------

				//RESET
				//------------------------------------------------------------------------
				for (int i = 0; i < 2; i++) {						//Reseting the "selected" values of the hero and minions to false.
					players[i].getHero().setSelected(false);
					for (unsigned j = 0; j < players[i].getMinions().size(); j++) {
						if (players[i].getMinions()[j].getSelected()) {
							players[i].getMinions()[j].setSelected(false);
							break;
						}
					}
					players[turn].setMinionSelected(false);			//Reseting the general boolean for "any minion selected" to false.
				}
				//------------------------------------------------------------------------
			}
			//CARD SELECTION					(handled in player class for some reason...)
			//------------------------------------------------------------------------
			//if (!animationState) {			//ONLY ALLOW CARD SELECTION WHEN THERE IS NOT AN ANIMATION HAPPENING. (Avoiding bugs...)
			players[turn].handleInput();		//Calling the player's handleInput() function
												//}
		}	//End pause.
	}	//End started.
}

void Game::update(float dt)
{
	//Checking for end game.
	if (!players[0].getHero().getRenderAlive()) {
		paused = true;
		defeat = true;
	}
	if (!players[1].getHero().getRenderAlive()) {
		paused = true;
		victory = true;
	}

	//Only update if the game has started and it is not paused.
	if (started && !paused) {
		turnTimer += dt;		//Incrementing the turn timer.
		if (turnTimer >= 30) {	//If the timer ends, end turn.
			turnTimer = 0;
			endTurn();
		}

		if (repositioningState || hoveringState) {
			if (!repositioning(dt)) {					//If finished repositioning. 
				repositioningState = false;
				animationState = true;
			}
		}

		//If any of the cards are selected, update the variable used for splitting the minions in the correct place.
		for (unsigned j = 0; j < players[turn].getHand().size(); j++) {				
			if (players[turn].getHand()[j].getSelected()) {
				players[turn].checkHoveringIndex();
				hoveringState = true;
				break;
			}
			//If none of the cards are selected then call update function on the player's cards.
			else {
				players[turn].getHand()[j].update(dt);			//Looking at the cards is handled here.
				hoveringState = false;
			}
		}
		

		//(This next bit got very confusing for me and I got a bit disheartened by it so it is not the best code.)

		//ANIMATIONS						//Setting the target position for the animation.
		if (animationState) {
			repositioningState = false;
			if (que.size() > 0) {				//If there is something in the que.
				//HERO
				//------------------------------------------------------------------------
				if (que[0].x == 9) {			//9 means it is a hero.	 que[0] is accessing the first interaction in the que.			//que[0].x is the index of the attacking minion.
					if (!players[turn].getHero().getAnimating()) {			//If the hero is not animating.								//que[0].y is the index of the defending minion.				
						players[turn].getHero().setAnimating(true);

						//ENEMY HERO							
						if (que[0].y == 9) {
							//Set the target position of the hero to the other player's hero position.
							players[turn].getHero().setTargetPos(players[(turn == 0) ? 1 : 0].getHero().getPos().x, players[(turn == 0) ? 1 : 0].getHero().getPos().y + ((turn == 0) ? translate((float)window->getSize().y, 60) : translate((float)window->getSize().y, -60)));
							players[turn].getHero().setTarget(&players[(turn == 0) ? 1 : 0].getHero());
						}
						//ENEMY MINIONS
						else {
							//Set the target position of the hero to the other player's minion position.
							players[turn].getHero().setTargetPos(players[(turn == 0) ? 1 : 0].getMinions()[que[0].y].getPos().x, players[(turn == 0) ? 1 : 0].getMinions()[que[0].y].getPos().y + ((turn == 0) ? translate((float)window->getSize().y, 0) : translate((float)window->getSize().y, -120)));
							players[turn].getHero().setTarget(&players[(turn == 0) ? 1 : 0].getMinions()[que[0].y]);
						}
						players[turn].getHero().setTargetVector();			//Setting the vector used for animation.
					}

					if (!players[turn].getHero().animation(dt)) {				//If the animation is finished.

						players[turn].getHero().setAnimating(false);
						if (players[(turn == 0) ? 1 : 0].getMinions().size() > 0 && que[0].y != 9) {	//If the enemy has minions on the board and the target is not the hero.
							if (!players[(turn == 0) ? 1 : 0].getMinions()[que[0].y].getAlive()) {		//if the minion is dead.
								int deadIndex = que[0].y;
								players[(turn == 0) ? 1 : 0].getMinions().erase(players[(turn == 0) ? 1 : 0].getMinions().begin() + que[0].y);		//Erase this minion from the array.
								players[(turn == 0) ? 1 : 0].calculateMinionPositions();		//Calculate the new positions of the minions.

								repositioningState = true;
								animationState = false;
								for (unsigned i = 0; i < que.size(); i++) {			//Shifting the values of the defending minion's index to point to its new position
									if (que[i].y != 9 && que[i].y >= deadIndex) {		//If the value is greater than the dead minion's index, and it is not targeting the hero, then shift its position to the left. (decrement the value by one.)
										que[i].y--;						//I have to do this because if i don't, then the interaction value will not point to the correct position in the minions array and could be out of bounds.
									}
								}
							}
						}
						que.erase(que.begin());		//Erase this interaction from the que.
					}
				}
				//------------------------------------------------------------------------

				//MINIONS
				//------------------------------------------------------------------------
				else {
					if (!players[turn].getMinions()[que[0].x].getAnimating()) {		//If the minion is not animating.
						players[turn].getMinions()[que[0].x].setAnimating(true);
						//ENEMY HERO
						if (que[0].y == 9) {
							players[turn].getMinions()[que[0].x].setTargetPos(players[(turn == 0) ? 1 : 0].getHero().getPos().x, players[(turn == 0) ? 1 : 0].getHero().getPos().y + ((turn == 0) ? translate((float)window->getSize().y, 120) : translate((float)window->getSize().y, 0)));
							players[turn].getMinions()[que[0].x].setTarget(&players[(turn == 0) ? 1 : 0].getHero());
						}
						//ENEMY MINION
						else {
							players[turn].getMinions()[que[0].x].setTargetPos(players[(turn == 0) ? 1 : 0].getMinions()[que[0].y].getPos().x, players[(turn == 0) ? 1 : 0].getMinions()[que[0].y].getPos().y + ((turn == 0) ? translate((float)window->getSize().y, 60) : translate((float)window->getSize().y, -60)));
							players[turn].getMinions()[que[0].x].setTarget(&players[(turn == 0) ? 1 : 0].getMinions()[que[0].y]);
						}
						players[turn].getMinions()[que[0].x].setTargetVector();
					}


					if (!players[turn].getMinions()[que[0].x].animation(dt)) {										//If it's animation has finished.

						if (!players[turn].getMinions()[que[0].x].getRenderAlive()) {								//if the attacking minion is dead.
							int deadIndex = que[0].x;
							players[turn].getMinions().erase(players[turn].getMinions().begin() + que[0].x);		//Erase the minion from the array.



							players[turn].calculateMinionPositions();												//Calculate the new positions of the attacking minions.
							repositioningState = true;
							animationState = false;
							for (unsigned i = 0; i < que.size(); i++) {
								if (que[i].x != 9 && que[i].x >= deadIndex) {		//If the value is greater than the dead minion's index, and it is not targeting the hero, then shift its position to the left. (decrement the value by one.)
									que[i].x--;						//I have to do this because if i don't, then the interaction value will not point to the correct position in the minions array and could be out of bounds.
								}
							}
						}
						if (players[(turn == 0) ? 1 : 0].getMinions().size() > 0 && que[0].y != 9) {			//If the enemy has minions on the board and the target is not the hero.
							if (!players[(turn == 0) ? 1 : 0].getMinions()[que[0].y].getRenderAlive()) {		//if the defending minion is dead.
								int deadIndex = que[0].y;
								players[(turn == 0) ? 1 : 0].getMinions().erase(players[(turn == 0) ? 1 : 0].getMinions().begin() + que[0].y);
								players[(turn == 0) ? 1 : 0].calculateMinionPositions();
								repositioningState = true;
								animationState = false;
								for (unsigned i = 0; i < que.size(); i++) {
									if (que[i].y != 9 && que[i].y >= deadIndex) {		//If the value is greater than the dead minion's index, and it is not targeting the hero, then shift its position to the left. (decrement the value by one.)
										que[i].y--;						//I have to do this because if i don't, then the interaction value will not point to the correct position in the minions array and could be out of bounds.
									}
								}
							}
						}

						que.erase(que.begin());		//Delete this attack from the que so it can go on to the next one.
					}

				}
			}
			//------------------------------------------------------------------------
		}

		players[0].update(dt);
		players[1].update(dt);			//inefficient...

		//FPS							//Some maths calculating the amount of frames passed in a second. I used this for testing efficiency.
		sum += dt;
		if (frameCount++ == 30) {
			frameCount = 0;
			int fps = (int)(1 / (sum / 30));
			sum = 0;
			fpsText.setString(to_string(fps));
		}

		//Checking if you are targetting minions.
		if (!players[0].getCardSelected() && !players[1].getCardSelected()) {										//If no card is selected.
			cardSelected = false;
			for (unsigned i = 0; i < players[0].getMinions().size(); i++) {
				if (players[0].getMinions()[i].getSelected() && !players[0].getMinions()[i].getTargeted()) {		//If the minion is selected and it is not targeted.
					cardSelected = true;
				}
			}
			if (!cardSelected) {
				players[0].minionCollisions();		//check for mouse collisions with minions.
			}

			//Doing the same for player 2.	(Duplicate code - this could be optimized.)
			cardSelected = false;			
			for (unsigned i = 0; i < players[1].getMinions().size(); i++) {
				if (players[1].getMinions()[i].getSelected() && !players[1].getMinions()[i].getTargeted()) {
					cardSelected = true;
				}
			}
			if (!cardSelected) {
				players[1].minionCollisions();
			}
		}

		//HERO		Checking if your are targeting the hero.
		if (!players[0].getCardSelected() && !players[1].getCardSelected()) {	//only check if player is not holding a card.
			players[0].getHero().checkTargeted((float)input->getMouseX(), (float)input->getMouseY());		//not optimised.
			players[1].getHero().checkTargeted((float)input->getMouseX(), (float)input->getMouseY());		//not optimised.
		}

	} //End pause.
}

void Game::render()		//Displaying everything.
{
	beginDraw();

	if (tutorial) {
		window->draw(tutorialSprite);
	}
	else if (!started) {
		window->draw(titleSprite);
		window->draw(playButton);
		window->draw(playText);
		window->draw(rulesButton);
		window->draw(rulesText);
	}
	else {
		//window->draw(fpsText);

		displayBackground();
		
		if (que.size() == 0 && players[turn].checkEndTurn()) {		//If it is the players turn and they cant play any cards.			//checkEndTurn() could only be called when you play a minion. (minor optimisation)
			endTurnButton.setOutlineThickness(6);
			endTurnButton.setOutlineColor(Color::Green);
			window->draw(endTurnButton);
		}
		endTurnButton.setOutlineThickness(2);
		endTurnButton.setOutlineColor(Color::Black);
		window->draw(endTurnButton);

		players[(turn == 0) ? 1 : 0].render();
		players[(turn == 0) ? 0 : 1].render();

		displayArrow();

		if (paused && !victory && !defeat) {
			window->draw(pauseSprite);
		}
		if (victory) {
			window->draw(victorySprite);
		}
		if (defeat) {
			window->draw(defeatSprite);
		}
	}

	endDraw();
}

void Game::displayBackground()
{

	float percentageTimePassed = turnTimer / 30 * 100;
	float ropePercentage = percentageTimePassed / 100 * 800;

	rope[0].position.x = (float)window->getSize().x / 2 - translate((float)window->getSize().y, 400) + translate((float)window->getSize().y, ropePercentage);
	rope[0].position.y = (float)window->getSize().y / 2;
	rope[1].position.x = (float)window->getSize().x / 2 + translate((float)window->getSize().y, 400);
	rope[1].position.y = (float)window->getSize().y / 2;

	window->draw(line, 2, Lines);
	window->draw(rope, 2, Lines);

}

void Game::displayArrow()	//Displaying arrow from which minion is selected to it's target. For user feedback.
{
	for (unsigned j = 0; j < players[turn].getMinions().size(); j++) {
		if (players[turn].getMinions()[j].getSelected() && players[turn].getMinions()[j].getReady()) {			
			arrow[0].position.x = players[turn].getMinions()[j].getPos().x;
			arrow[0].position.y = players[turn].getMinions()[j].getPos().y;
			arrow[1].position.x = (float)input->getMouseX();
			arrow[1].position.y = (float)input->getMouseY();
			window->draw(arrow, 2, Lines);
			break;
		}
	}
	if (players[turn].getHero().getSelected() && players[turn].getHero().getReady()) {			
		arrow[0].position.x = players[turn].getHero().getPos().x;
		arrow[0].position.y = players[turn].getHero().getPos().y + translate((float)window->getSize().y, 60);
		arrow[1].position.x = (float)input->getMouseX();
		arrow[1].position.y = (float)input->getMouseY();
		window->draw(arrow, 2, Lines);
	}
}

void Game::beginDraw()
{
	window->clear(sf::Color::White);
}

void Game::endDraw()
{
	window->display();
}

bool Game::repositioning(float dt)
{
	bool player0StillAnimating = true;
	players[0].setMinionsTargetPos();
	if (players[0].getMinions().size() == 0) {		
		player0StillAnimating = false;				//If the player has no minions then it cannot be still repositioning.
	}
	for (unsigned i = 0; i < players[0].getMinions().size(); i++) {
		if (!players[0].getMinions()[i].repositioning(dt)) {		//Checking each of the minions to se if they are still repositioning.
			player0StillAnimating = false;
		}
		else {
			player0StillAnimating = true;
		}
	}

	bool player1StillAnimating = true;				//Duplicate code.... (getting complicated.)
	if (players[1].getMinions().size() == 0) {
		player1StillAnimating = false;
	}
	players[1].setMinionsTargetPos();
	for (unsigned i = 0; i < players[1].getMinions().size(); i++) {
		if (!players[1].getMinions()[i].repositioning(dt)) {
			player1StillAnimating = false;
		}
		else {
			player1StillAnimating = true;
		}
	}
	return (player0StillAnimating || player1StillAnimating);	//Return if either player's minions is still repositioning.
}
