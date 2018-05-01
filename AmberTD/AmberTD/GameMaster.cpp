#include "GameMaster.h"
#include <SFML/Graphics.hpp>

void GameMaster::Render(sf::RenderWindow &window)
{
	UpdateGUI();
	for (int i = 0;i < map.size();i++)
	{
		window.draw(map[i]);
	}

	for (int i = 0; i < towerList.size(); i++)
	{
		window.draw(*towerList[i]);
	}
	for (int i = 0;i < enemyList.size();i++)
	{
		window.draw(*enemyList[i]);
	}
	for (int i = 0;i < bulletList.size();i++)
	{
		window.draw(*bulletList[i]);
	}
	for (int i = 0;i < gui.size();i++)
	{
		window.draw(*gui[i]);
	}

	window.draw(moneyTxt);
}
int GameMaster::GetMoney()
{
	return money;
}

void GameMaster::MakeGUI() 
{ 
	gui.push_back(new Tower(50, 89,TowerType::basic));
	gui.push_back(new Tower(50, 251, TowerType::fire));
	gui.push_back(new Tower(50, 413, TowerType::ice));
}

void GameMaster::UpdateGUI()
{
	moneyTxt.setString(std::to_string(GetMoney()));
	moneyTxt.setFont(font);
	moneyTxt.setPosition(1674,6);
	moneyTxt.setFillColor(sf::Color::Red);
}

void GameMaster::loadFont()
{
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "Font loading Error " << std::endl;
	}
}

bool GameMaster::ContainsMouse(sf::Vector2i &position)
{
	if (position.x < map[0].getPosition().x)
	{
		SearchInGUI();
	}
	else
	{
		SearchInMap();
	}
}

void GameMaster::SearchInGUI()
{

}

void ContainsMouse(std::vector<sf::ConvexShape> &list, float x, float y)
{
	for (int i = 0; i < list.size();i++)
	{
		if (list[i].getGlobalBounds().contains(x, y))
		{
			list[i].setFillColor(sf::Color(255, 0, 0, 150));
			std::cout << list[i].getPosition().x << " and " << list[i].getPosition().y << std::endl;
		}
	}
}

GameMaster::GameMaster(std::vector<sf::ConvexShape> &Worldmap) : map{Worldmap}, money{300}, playerLifes{10}
{
	loadFont();
	MakeGUI();

}


GameMaster::~GameMaster()
{
}
