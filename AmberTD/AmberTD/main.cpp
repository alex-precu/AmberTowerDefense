#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "enums.h"
#include "WorldBuilder.h"
#include "GroundTile.h"
#include "Tower.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(FullHdresolution::x, FullHdresolution::y), "Game");
	WorldBuilder world;
	world.CreateWorld();
	GameMaster gameMaster(world.GetMap());

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
					if (sf::Mouse::getPosition(window).x < world.GetMap()[0].getPosition().x)
					{

					}
					//ContainsMouse( world.GetMap() , sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
				}	
			
			}
		}
		window.clear(sf::Color::Black);

		gameMaster.Render(window);
	

		window.display();
	}

	return 0;

	
}
