
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include "Game.h"
#include "Input.h"				

using namespace std;

void main()
{
	//RenderWindow window(sf::VideoMode(1366, 768), "Hearthstone", sf::Style::Fullscreen); //, sf::Style::Fullscreen
	RenderWindow window(sf::VideoMode(1024, 576), "Hearthstone"); 
	Clock clock;
	Input input;
	Line mouse;			//Creating an object that calculates the equation of a line between two points. ((0, 0) and mouse co-ordinates.)
	Game game(&window, &input, &mouse);		//Initializing the game object, passing it the memory adress of the window, the input object and the Line object.
	//window.setFramerateLimit(40);
	float deltaTime;					
	srand(time(NULL));	

	while (window.isOpen())
	{
		deltaTime = clock.getElapsedTime().asSeconds();	//Getting time since last frame.
		clock.restart().asSeconds();				//Restarting the clock.
		mouse.setX2((float)sf::Mouse::getPosition(window).x);	//Setting the "mouse" Line's second point to the mouse co-ordinates.
		mouse.setY2((float)sf::Mouse::getPosition(window).y);
		Event event;							
		while (window.pollEvent(event))						//Event handling.
		{
			switch (event.type)		//Switch statement for which event is detected.
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(0.f, 0.f, (float)event.size.width, (float)event.size.height)));
				game.resizeWindow();
				break;
			case sf::Event::KeyPressed:
				input.setKeyDown(event.key.code);
				break;
			case sf::Event::KeyReleased:
				input.setKeyUp(event.key.code);
				break;
			case sf::Event::MouseMoved:
				input.setMousePosition(event.mouseMove.x, event.mouseMove.y);
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					input.setMouseLeftDown(true);
				}
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					input.setMouseRightDown(true);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					input.setMouseLeftDown(false);
				}
				if (event.mouseButton.button == sf::Mouse::Right)
				{
					input.setMouseRightDown(false);
				}
				break;
			default:
				break;
			}
		}
		game.handleInput();						
		game.update(deltaTime);
		game.render();
	}
}

