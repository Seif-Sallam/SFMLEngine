#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "SFML/System.hpp"


int main()
{   
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Works!");
	sf::CircleShape shape(8.f);
	shape.setPosition(sf::Vector2f(window.getSize() / 2u));
	shape.setFillColor(sf::Color::Blue);
	bool inFocus = true;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				window.close();
			else if (event.type == sf::Event::LostFocus)
				inFocus = false;
			else if (event.type == sf::Event::GainedFocus)
				inFocus = true;

		}
		if (inFocus)
		{



			window.clear(sf::Color(192,168,128));
			window.draw(shape);
			window.display();
		}
	}
	return 0;
}