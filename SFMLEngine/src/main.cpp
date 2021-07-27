#include "../headers/ResourceManager.h"
#include "../headers/Animation.h"


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
	sf::Texture& texture = SFENG::ResourceManager::Get().AddTexture("rsc/Textures/SampleSprite.png", "sample");
	sf::Sprite sp;
	sp.setTexture(texture);
	sp.setPosition(Vec2f(300, 250));
	SFENG::Animation anim(32, 32);
	sf::Time delay = sf::seconds(0.15f);
	anim.AddFrame(0, delay);
	anim.AddFrame(1, delay);
	anim.AddFrame(2, delay);
	anim.AddFrame(3, delay);
	anim.AddFrame(2, delay);
	anim.AddFrame(1, delay);
	anim.AddFrame(0, delay);
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
			sp.setTextureRect(anim.GetFrame());

			window.clear(sf::Color(192,168,128));
			window.draw(text);
			//window.draw(shape);
			window.draw(sp);
			window.display();
		}
	}
	SFENG::ResourceManager::Get().CleanUp();
	return 0;
}