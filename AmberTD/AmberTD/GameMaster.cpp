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
			window.draw(*towerList[j]->DrawPlacementAssist(window));
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
		ManageDamage();
		ManageShooting();
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
		Enemy* enemyPtr = enemyList[i];
		if (enemyPtr->isDestinationreached == true)
		{
			if (!enemyPtr->currentPath)
			{
				enemyPtr->nextPath = map[47];
			}
			else
			{
				GroundTile* lastTile = enemyPtr->previousPath;
				GroundTile* currentTile = enemyPtr->currentPath;
				int currentIndex = GetTileIndex(currentTile);
				GroundTile* left = nullptr;
				GroundTile* right = nullptr;
				GroundTile* up = nullptr;
				GroundTile* down = nullptr;

				if (!(currentIndex%BOARD_WIDTH == 0))
				{
					left = map[currentIndex - 1];
				}
				if (!((currentIndex + 1) % BOARD_WIDTH == 0))
				{
					right = map[currentIndex + 1];
				}
				if (!(currentIndex < BOARD_WIDTH))
				{
					up = map[currentIndex - BOARD_WIDTH];
				}
				if (!(currentIndex > (BOARD_HEIGHT*BOARD_WIDTH - BOARD_WIDTH)))
				{
					down = map[currentIndex + BOARD_WIDTH];
				}

				if (left && (left->GetTiletype()==GroundType::path) && (left!=lastTile))
				{
					enemyPtr->nextPath = left;
					enemyPtr->isDestinationreached = false;
				}
				if (right && (right->GetTiletype() == GroundType::path) && (right != lastTile))
				{
					enemyPtr->nextPath = right;
					enemyPtr->isDestinationreached = false;
				}
				if (up && (up->GetTiletype() == GroundType::path) && (up != lastTile))
				{
					enemyPtr->nextPath = up;
					enemyPtr->isDestinationreached = false;
				}
				if (down && (down->GetTiletype() == GroundType::path) && (down != lastTile))
				{
					enemyPtr->nextPath = down;
					enemyPtr->isDestinationreached = false;
				}

			}
		}
		enemyList[i]->Update();
	}
}

int GameMaster::GetTileIndex(GroundTile* tile)
{
	for (int i = 0; i < map.size();i++)
	{
		if (map[i] == tile)
		{
			return i;
		}
	}
	return -1;
}





void GameMaster::UpdateBullets()
{
	for (int i = 0;i < bulletList.size();i++)
	{
		bulletList[i]->Update();
	}
}


void GameMaster::WaveMaker(int difficulty)
{
	enemyList.clear();

	for (int i = 1; i < BOARD_HEIGHT;i++)
	{
		if (map[i*BOARD_WIDTH - 1]->GetTiletype() == GroundType::path)
		{
			for (int j = 0; j < 1; j++)
			{
				enemyList.push_back(new Enemy(map[i*BOARD_WIDTH - 1]->getPosition().x + +100 +TILE_SIZE*j, map[i*BOARD_WIDTH - 1]->getPosition().y, EnemyType::normal));
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
			WaveMaker(level);
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
/*sf::CircleShape GameMaster::DrawTowerRange(sf::Vector2f coordinates)
{
	//sf::CircleShape range(SearchInTowers(coordinates)->GetRange());
	//range.setFillColor(sf::Color::Transparent);
	//range.setOutlineColor(SearchInTowers(coordinates)->getFillColor());
//range.setOrigin(sf::Vector2f(SearchInTowers(coordinates)->GetRange(), SearchInTowers(coordinates)->GetRange()));
	//.range.setPosition(SearchInTowers(coordinates)->getPosition().x, SearchInTowers(coordinates)->getPosition().y);

	//return range;
	return true;
}*/

void GameMaster::ManageShooting()
{
	for (int i = 0; i < towerList.size(); i++)
	{
		if (towerList[i]->GetIsBuilt() && towerList[i]->GetIsReadyToFire())
		{
			for (int j = 0;j < enemyList.size();j++)
			{
				if (towerList[i]->GetRange()->getGlobalBounds().contains(enemyList[j]->getPosition()))
				{
					bulletList.push_back(new Bullet(towerList[i],enemyList[j]));
					towerList[i]->SetIsReadyToFire(false);
					break;
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

				if (enemyList[i]->getGlobalBounds().contains(bulletList[j]->getPosition()))// crash
				{
					enemyList[i]->GiveDamage(bulletList[j]->GetDamage());
					bulletList.erase(bulletList.begin() + j);
				}
		}
		if (enemyList[i]->GetHP() <= 0)
		{
			GiveMoney(enemyList[i]->GetValue());
			enemyList.erase(enemyList.begin() + i);

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
