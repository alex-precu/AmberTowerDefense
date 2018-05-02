#include "GameMaster.h"
#include <SFML/Graphics.hpp>

void GameMaster::Render(sf::RenderWindow &window, Flags flag)
{
	UpdateGUI();

	for (int i = 0;i < map.size();i++)
	{
		if (flag == Flags::towerUnderConstruction && map[i]->GetIsEmpty())
		{
			if (map[i]->GetTiletype() == GroundType::hill)
			{
				map[i]->setFillColor(sf::Color::Green);
			}
			else
			{
				map[i]->setFillColor(sf::Color::Red);
			}
		}
		else
		{
			if (map[i]->GetTiletype() == GroundType::hill)
			{
				map[i]->setFillColor(sf::Color::Yellow);
			}
			else
			{
				map[i]->setFillColor(sf::Color::White);
			}
		}
		window.draw(*map[i]);
	}

	for (int i = 0; i < towerList.size(); i++)
	{
		if (!towerList[i]->GetIsBuilt())
		{
			window.draw(towerList[i]->DrawRangeF(window));
		}
		towerList[i]->Update(window);
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
	if (position.x < map[0]->getPosition().x)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool GameMaster::CheckMoney()
{
	if (underContruction->GetPrice() <= money)
	{
		return true;
	}
	return false;
}

bool GameMaster::Construction(sf::Vector2i pos)
{
	for (int i = 0; i < gui.size();i++)
	{
		Tower* guiPtr = gui[i];
		if (guiPtr->getGlobalBounds().contains(pos.x, pos.y))
		{
			std::cout << "Entity found at " << guiPtr->getPosition().x << " and " << guiPtr->getPosition().y << std::endl;
			underContruction = guiPtr ;
			if (CheckMoney())
			{
				return true;
			}
		}
	}
	return false;
}

void GameMaster::ActivateTowerBuilder()
{
	towerList.push_back(new Tower(underContruction->GetPosition().x, underContruction->GetPosition().y, underContruction->GetType()));
	underContruction = nullptr;
}

void GameMaster::SearchInMap()
{

}
bool GameMaster::CheckPlacement(sf::Vector2i placement)
{
	for (int i = 0;i < map.size();i++)
	{
		GroundTile* groundPtr = map[i];
		if (groundPtr->getGlobalBounds().contains(placement.x, placement.y) && groundPtr->GetIsEmpty() && groundPtr->GetTiletype()!=GroundType::path)
		{
			Tower* ptr = towerList.back();
			ptr->setPosition(sf::Vector2f(map[i]->getPosition()));
			ptr->setOrigin(sf::Vector2f(TILE_SIZE / 2, TILE_SIZE / 2));
			ptr->SetState();
			groundPtr->SetIsEmpty(false);
			SpendMoney(ptr->GetPrice());
			if (!ptr)
			{
				continue;
			}
			ptr->SetState();

		return true;
		}
	}
	return false;
}

void GameMaster::CancelTower()
{
	if (towerList.size())
	{
		towerList.pop_back();
	}
}

sf::ConvexShape* GameMaster::SearchInTowers(sf::Vector2i pos)
{
	for (int i = 0; i < towerList.size();i++)
	{
		if (towerList[i]->getGlobalBounds().contains(pos.x, pos.y))
		{
			std::cout << "Entity found at " << towerList[i]->getPosition().x << " and " << towerList[i]->getPosition().y << std::endl;
			return towerList[i];
		}
	}
}

void GameMaster::SpendMoney(int amount)
{
	money -= amount;
}

void GameMaster::MakeEnemies()
{
	
}

void GameMaster::WaveMaker(WaveDifficulty difficulty)
{
	for (int i = 0; i < BOARD_HEIGHT - 1;i++)
	{
		if (map[i + BOARD_WIDTH]->GetTiletype() == GroundType::path)
		{
			for (int i = 0; i < difficulty; i++)
			{
				enemyList.push_back(new Enemy(map[i + BOARD_WIDTH]->getPosition().x + TILE_SIZE, map[i + BOARD_WIDTH]->getPosition().y + TILE_SIZE, EnemyType::normal));
			}
		}
	}
}

void GameMaster::GameManager()
{
	while (playerLifes > 0)
	{

	}
}

GameMaster::GameMaster(std::vector<GroundTile*> Worldmap) : map{Worldmap}, money{300}, playerLifes{10}
{
	loadFont();
	MakeGUI();

}


GameMaster::~GameMaster()
{
}
