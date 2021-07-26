#include "../headers/ResourceManager.h"

int main()
{   
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Works!");
	sf::Text text;
	sf::Font& font = SFENG::ResourceManager::Get().AddFont("rsc/Fonts/Alex_Bold.ttf", "something");
	text.setFont(font);
	text.setCharacterSize(24);
	text.setPosition(Vec2f(0, 0));
	text.setString("SOMETHING FONT");
	sf::RectangleShape shape(sf::Vector2f(32, 32));
	shape.setFillColor(sf::Color::White);
	shape.setPosition(sf::Vector2f(100, 100));
	sf::Texture& tex = SFENG::ResourceManager::Get().AddTexture("rsc/Textures/test.png", "test");
	shape.setTexture(&tex);
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
			window.draw(text);
			window.draw(shape);
			window.display();
		}
	}
	SFENG::ResourceManager::Get().CleanUp();
	return 0;
}