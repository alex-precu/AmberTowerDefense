#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "enums.h"
#include "WorldBuilder.h"
#include "GroundTile.h"
#include "Tower.h"

void ContainsMouse(std::vector<GroundTile*> list, int x, int y)
{
	for (int i = 0; i < list.size();i++)
	{
		if (list[i]->getGlobalBounds().contains(x, y))
		{
			list[i]->setFillColor(sf::Color(255, 0, 0, 150));
			std::cout << list[i]->getPosition().x << " and " << list[i]->getPosition().y << std::endl;
		}
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(FullHdresolution::x, FullHdresolution::y), "Game");
	window.setFramerateLimit(60);
	WorldBuilder world;
	world.CreateWorld();
	GameMaster gameMaster(world.GetMap());
	sf::Event event;
	Flags flag = Flags::noConstruction;

	while (window.isOpen())
	{

		
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			
			if (event.type == sf::Event::MouseButtonReleased)
			{
					//igonre MouseButtonRealease
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{

					//Case: Player Clicker on the GUI
					if (sf::Mouse::getPosition(window).x <  gameMaster.map[0]->getPosition().x)
					{
						if (gameMaster.Construction(sf::Mouse::getPosition(window)) && flag!=Flags::towerUnderConstruction)
						{
							gameMaster.ActivateTowerBuilder();
							flag = Flags::towerUnderConstruction;
						}
					}
					//Case: Player clicked on the map
					else
					{
						if (flag == Flags::towerUnderConstruction)
						{
							if (gameMaster.CheckPlacement(sf::Mouse::getPosition(window)))
							{
								flag = Flags::noConstruction;
							}

						}
						gameMaster.SearchInTowers(sf::Mouse::getPosition());
					}



					//ContainsMouse( gameMaster.map , sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

				}	

		
				
				if (event.mouseButton.button == sf::Mouse::Right && flag == Flags::towerUnderConstruction)
				{
					gameMaster.CancelTower();
					flag = Flags::noConstruction;
				}
			}



			
		}
		window.clear(sf::Color::Black);

		gameMaster.Render(window,flag);
	

		window.display();
	}

	return 0;
	
}
