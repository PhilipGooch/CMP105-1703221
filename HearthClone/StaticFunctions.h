#pragma once
#define PI 3.14159265358979323846f

namespace staticFunctions	//Creating my own namespace that I can access from any class that includes the header file and uses the namespace or types staticFunctions:: before a function call.
{
	static float translate(float windowSizeY, float number)		//This function is used everywhere. It takes the current size of the screen and the number in pixels when fullScreen and outputs the scaled number.
	{
		if (number == 0) {
			return 0;
		}
		else {
			return windowSizeY / (768 / number);
		}
	}

	//This displays a number on to the window given, with the variables given.
	static void displayNumber(RenderWindow* window, Font* font, Text text, float x, float y, int number, int size, float angle)	
	{
		//Indenting the text by a different amount for each number to center it.
		int indent = 0;
		switch (number)
		{
		case 0: indent = (int)translate((float)window->getSize().y, 2); break;
		case 1: indent = (int)translate((float)window->getSize().y, 1); break;		//Need to store these values so i am not calling translate every frame...
		case 2: indent = (int)translate((float)window->getSize().y, 1); break;
		case 3: indent = (int)translate((float)window->getSize().y, 2); break;
		case 4: indent = (int)translate((float)window->getSize().y, 0); break;
		case 5: indent = (int)translate((float)window->getSize().y, 1); break;
		case 6: indent = (int)translate((float)window->getSize().y, 0); break;
		case 7: indent = (int)translate((float)window->getSize().y, 1); break;
		case 8: indent = (int)translate((float)window->getSize().y, 1); break;
		case 9: indent = (int)translate((float)window->getSize().y, 1); break;
		default: indent = (int)translate((float)window->getSize().y, -4); break;
		}
		text.setFont(*font);					
		text.setString(to_string(number));
		text.setCharacterSize(size);
		if (angle != 0) {
			text.setRotation(angle * 180 / PI);
		}
		else {
			text.setRotation(0);
		}
		text.setFillColor(Color::Black);		//To create the illusion of outlined text I am drawing the text in black 4 times, indented by one pixel in each direction.
		text.setPosition(x + indent - 1, y);	//I am then drawing the text again in white over the top!			
		window->draw(text);
		text.setPosition(x + indent + 1, y);
		window->draw(text);
		text.setPosition(x + indent, y - 1);
		window->draw(text);
		text.setPosition(x + indent, y + 1);
		window->draw(text);
		text.setFillColor(sf::Color::White);
		text.setPosition(x + indent, y);
		window->draw(text);
	}
}


