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
	sf::Event event;
	Flags eventFlag = Flags::gameInProgress;
	sf::Clock clock;
	sf::Time collector = sf::Time::Zero;
	float frameTime = 1.0f / 60.0f;

	while (window.isOpen())
	{

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
				}
				if (gameMaster.GetIsGameOver())
				{
					if (event.type == sf::Event::KeyPressed)
					{
						if (event.key.code == sf::Keyboard::Space)
						{
							gameMaster.RestartGame();
						}
					}
				}

				if (event.type == sf::Event::MouseButtonReleased)
				{
					//igonre MouseButtonRealease
				}
				if (event.type == sf::Event::MouseButtonPressed)
				{
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						//Case: Player Clicker on the GUI
						if (sf::Mouse::getPosition(window).x < gameMaster.map[0]->getPosition().x)
						{
							if (gameMaster.Construction(sf::Mouse::getPosition(window)) && eventFlag != Flags::towerUnderConstruction)
							{
								gameMaster.ActivateTowerBuilder();
								eventFlag = Flags::towerUnderConstruction;
							}
						}
						//Case: Player clicked on the map
						else
						{
							if (eventFlag == Flags::towerUnderConstruction)
							{
								if (gameMaster.CheckPlacement(sf::Mouse::getPosition(window)))
								{
									eventFlag = Flags::gameInProgress;
								}

							}
							gameMaster.SearchInTowers(sf::Vector2f(sf::Mouse::getPosition()));
						}


					}

					if (event.mouseButton.button == sf::Mouse::Right && eventFlag == Flags::towerUnderConstruction)
					{
						gameMaster.CancelTower();
						eventFlag = Flags::gameInProgress;
					}
				}

			}

			while (collector > TIME_PASED)
			{
				if (gameMaster.GetIsGameOver())
				{
					collector -= TIME_PASED;
					window.clear(sf::Color::Black);
					gameMaster.RenderGameOver(window);
					window.display();
				}
				else
				{
					collector -= TIME_PASED;
					window.clear(sf::Color::Black);
					gameMaster.GameCycle(window, eventFlag);
					window.display();
				}
			
			}

			collector += clock.restart();
	}
	

	
		
}
	


	


	

