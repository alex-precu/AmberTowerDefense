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

	for (int j = 0; j < towerList.size(); j++)
	{
		if (!towerList[j]->GetIsBuilt())
		{
			window.draw(towerList[j]->DrawPlacementAssist(window));
		}
		window.draw(*towerList[j]);
	}
	for (int k = 0;k < enemyList.size();k++)
	{
		window.draw(*enemyList[k]);
	}
	for (int l = 0;l < bulletList.size();l++)
	{
		window.draw(*bulletList[l]);
	}
	for (int m = 0;m < gui.size();m++)
	{
		window.draw(*gui[m]);
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
	towerList.push_back(new Tower(underContruction->getPosition().x, underContruction->getPosition().y, underContruction->GetType()));
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

Tower* GameMaster::SearchInTowers(sf::Vector2f pos)
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

void GameMaster::GameCycle(sf::RenderWindow &window,Flags flag)
{
	if (GameManager(flag) != Flags::waiting)
	{
		if (GameManager(flag) == Flags::gameWon)
		{
			//do win
		}
		else if (GameManager(flag) == Flags::gameOver)
		{
			// doo widnow
		}
	}
	else
	{
		//ManageShooting();
		UpdateAllStates(window);
		Render(window, flag);
	}
	
}

void GameMaster::UpdateAllStates(sf::RenderWindow &window)
{
	UpdateTowers(window);
	UpdateEnemies();
	UpdateBullets();
	UpdateGUI();

}

void GameMaster::UpdateTowers(sf::RenderWindow &window)
{
	for (int i = 0;i < towerList.size();i++)
	{
		towerList[i]->Update(window);
	}
}

void GameMaster::GetPath(GroundTile* lastLocation)
{
	
}

void GameMaster::UpdateEnemies()
{
	for (int i = 0;i < enemyList.size();i++)
	{
		//enemyList[i]->Update(map[50]->getPosition().x,map[50]->getPosition().y);
	}
}

void GameMaster::UpdateBullets()
{
	for (int i = 0;i < bulletList.size();i++)
	{
		//bulletList[i]->Update();
	}
}


void GameMaster::WaveMaker(WaveDifficulty difficulty)
{
	enemyList.clear();

	for (int i = 1; i < BOARD_HEIGHT;i++)
	{
		if (map[i*BOARD_WIDTH - 1]->GetTiletype() == GroundType::path)
		{
			for (int j = 0; j < difficulty*MONSTERS_PER_WAVE; j++)
			{
				enemyList.push_back(new Enemy(map[i*BOARD_WIDTH - 1]->getPosition().x + ENRTY_OFFSET + TILE_SIZE*j, map[i*BOARD_WIDTH - 1]->getPosition().y, EnemyType::normal));
			}
			break;
		}
	}
		

}

Flags GameMaster::GameManager(Flags flag)
{
	static int level = 1;
	if (playerLifes > 0)
	{
		if (level <= WaveDifficulty::insane && enemyList.empty())
		{
			switch (level)
			{
			case WaveDifficulty::easy:
				WaveMaker(WaveDifficulty::easy);
				break;
			case WaveDifficulty::medium:
				WaveMaker(WaveDifficulty::medium);
				break;
			case WaveDifficulty::hard:
				WaveMaker(WaveDifficulty::hard);
				break;
			case WaveDifficulty::veryhard:
				WaveMaker(WaveDifficulty::veryhard);
				break;
			case WaveDifficulty::insane:
				WaveMaker(WaveDifficulty::insane);
				break;
			}
			level++;
			return Flags::gameInProgress;
		}
		else if (level > WaveDifficulty::insane)
		{
			return Flags::gameWon;
		}
		else
			return Flags::waiting;
	}
	else return Flags::gameOver;
}
sf::CircleShape GameMaster::DrawTowerRange(sf::Vector2f coordinates)
{
	sf::CircleShape range(SearchInTowers(coordinates)->GetRange());
	range.setFillColor(sf::Color::Transparent);
	range.setOutlineColor(SearchInTowers(coordinates)->getFillColor());
	range.setOrigin(sf::Vector2f(SearchInTowers(coordinates)->GetRange(), SearchInTowers(coordinates)->GetRange()));
	range.setPosition(SearchInTowers(coordinates)->getPosition().x, SearchInTowers(coordinates)->getPosition().y);

	return range;

}

void GameMaster::ManageShooting()
{
	for (int i = 0; i < towerList.size(); i++)
	{
		if (towerList[i]->GetIsReadyToFire())
		{
			for (int j = 0;j < enemyList.size();j++)
			{
				if (DrawTowerRange(towerList[i]->getPosition()).getGlobalBounds().contains(enemyList[j]->getPosition()))
				{
					bulletList.push_back(new Bullet(towerList[i],enemyList[j]));
					towerList[i]->SetIsReadyToFire(false);
				}
			}
		}
	}
}

void GameMaster::ManageDamage()
{
	for (int i = 0; i < enemyList.size();i++)
	{
		for (int j = 0; j < bulletList.size(); j++)
		{
			if (enemyList[i]->getGlobalBounds().contains(bulletList[j]->getPosition()))
			{
				enemyList[i]->GiveDamage(bulletList[j]->GetDamage());
				bulletList.erase(bulletList.begin() + j);

				if (enemyList[i]->GetHP() <= 0)
				{
					enemyList.erase(enemyList.begin() + i);
					
				}
			}
		}
	}
}

void GameMaster::GiveMoney(int amount)
{
	money += amount;
}


GameMaster::GameMaster(std::vector<GroundTile*> Worldmap) : map{Worldmap}, money{300}, playerLifes{10}
{
	loadFont();
	MakeGUI();

}


GameMaster::~GameMaster()
{
}
