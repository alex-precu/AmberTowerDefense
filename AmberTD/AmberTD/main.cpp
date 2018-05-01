#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "enums.h"
#include "WorldBuilder.h"
#include "GroundTile.h"
#include "Tower.h"

void Draw(std::vector<sf::RectangleShape> world, sf::RenderWindow &window)
{
	for (int i = 0; i < world.size(); i++)
	{
		window.draw(world[i]);
	}
}
void ContainsMouse(std::vector<sf::RectangleShape> &list, float x, float y)
{
	for (int i = 0; i < list.size();i++)
	{
		if (list[i].getGlobalBounds().contains(x, y))
		{
			list[i].setFillColor(sf::Color(255, 0, 0));
			std::cout << list[i].getPosition().x << " and " << list[i].getPosition().y << std::endl;
		}
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(FullHdresolution::x, FullHdresolution::y), "Game");
	WorldBuilder world;
	world.CreateWorld();

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			
			if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					ContainsMouse( world.GetMap() , sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
				}	
			
			}
		}
		window.clear(sf::Color::Black);

		Draw(world.GetMap(), window);
	

		window.display();
	}

	return 0;

	
}
