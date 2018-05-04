#include "GameMaster.h"

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
	DrawText(window);
}

void GameMaster::RenderGameOver(sf::RenderWindow &window)
{
	gameOverTxt.setString("game over /n press space to start again? ");
	gameOverTxt.setFont(font);
	gameOverTxt.setPosition(FullHdresolution::x/2, FullHdresolution::y / 2);
	gameOverTxt.setFillColor(sf::Color::Red);
	window.draw(gameOverTxt);

}


int GameMaster::GetMoney()
{
	return money;
}

void GameMaster::DrawText(sf::RenderWindow &window)
{
	window.draw(moneyTxt);
	window.draw(livesTxt);
	window.draw(towerPrice1txt);
	window.draw(towerPrice2txt);
	window.draw(towerPrice3txt);
}

void GameMaster::MakeGUI() 
{ 
	gui.push_back(new Tower(50, 89,TowerType::basic));
	gui.push_back(new Tower(50, 251, TowerType::fire));
	gui.push_back(new Tower(50, 413, TowerType::ice));
}

void GameMaster::UpdateGUI()
{
	towerPrice1txt.setString(std::to_string(gui[0]->GetPrice()));
	towerPrice2txt.setString(std::to_string(gui[1]->GetPrice()));
	towerPrice3txt.setString(std::to_string(gui[2]->GetPrice()));
	livesTxt.setString(std::to_string(GetLives()));
	moneyTxt.setString(std::to_string(GetMoney()));
	towerPrice1txt.setFont(font);
	towerPrice2txt.setFont(font);
	towerPrice3txt.setFont(font);
	livesTxt.setFont(font);
	moneyTxt.setFont(font);
	towerPrice1txt.setPosition(gui[0]->getPosition().x + 100, gui[0]->getPosition().y);
	towerPrice2txt.setPosition(gui[1]->getPosition().x + 100, gui[1]->getPosition().y);
	towerPrice3txt.setPosition(gui[2]->getPosition().x + 100, gui[2]->getPosition().y);
	livesTxt.setPosition(1674,100);
	moneyTxt.setPosition(1674,6);
	towerPrice1txt.setFillColor(sf::Color::Red);
	towerPrice2txt.setFillColor(sf::Color::Red);
	towerPrice3txt.setFillColor(sf::Color::Red);
	livesTxt.setFillColor(sf::Color::Red);
	moneyTxt.setFillColor(sf::Color::Red);
}

int GameMaster::GetLives()
{
	return playerLives;
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

bool GameMaster::GetIsGameOver()
{
	return isGameOver;
}
void GameMaster::SpendMoney(int amount)
{
	money -= amount;

}
void GameMaster::GameCycle(sf::RenderWindow &window,Flags flag)
{
	if (flag == Flags::restartGame)
	{
		RestartGame();
		GameManager(Flags::gameInProgress);
	}

	if (GameManager(flag) != Flags::waiting)
	{
		if (GameManager(flag) == Flags::gameWon)
		{
			
		}
		else if (GameManager(flag) == Flags::gameOver)
		{

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

void GameMaster::UpdateEnemies()
{
	for (int i = 0;i < enemyList.size();i++)
	{
		Enemy* enemyPtr = enemyList[i];
		if (enemyPtr->GetHasWon())
		{
			playerLives--;
			enemyList.erase(enemyList.begin() + i);
		}
		if (enemyPtr->isDestinationreached == true)
		{
			if (!enemyPtr->currentPath)
			{
				enemyPtr->nextPath = map[ENTRY_POINT_INDEX];
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
		if (enemyList.size() > 0)
		{
			enemyList[i]->Update();
		}
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

	
		for (int j = 0; j < difficulty*ENEMIES_PER_WAVE; j++)
			{
			if (difficulty % 2 == 0)
			{
				enemyList.push_back(new Enemy(map[ENTRY_POINT_INDEX]->getPosition().x + +100 + TILE_SIZE * j, map[ENTRY_POINT_INDEX]->getPosition().y, EnemyType::normal));
			}
			else 
			{
				if(difficulty==WaveDifficulty::insane)
					{
					enemyList.push_back(new Enemy(map[ENTRY_POINT_INDEX]->getPosition().x + +100 + TILE_SIZE * j, map[ENTRY_POINT_INDEX]->getPosition().y, EnemyType::fat));
					}
				else
				{
					enemyList.push_back(new Enemy(map[ENTRY_POINT_INDEX]->getPosition().x + +100 + TILE_SIZE * j, map[ENTRY_POINT_INDEX]->getPosition().y, EnemyType::fast));
				}
				
			
			
			}
			
		}
		

}

void GameMaster::ResetLevel()
{
	level = 1;
}

void GameMaster::RestartGame() 
{
	towerList.clear();
	enemyList.clear();
	bulletList.clear();
	for (int i = 0;i < map.size();i++)
	{
		if (!map[i]->GetIsEmpty())
		{
			map[i]->SetIsEmpty(true);
		}
	}
	ResetLevel();
	playerLives = 11;
	isGameOver = false;
	money = 300;
}

Flags GameMaster::GameManager(Flags flag)
{
	if (playerLives > 0)
	{
		if (level < WaveDifficulty::insane && enemyList.empty())
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
	else
	{
		isGameOver = true;
		return Flags::gameOver;
	}
}

void GameMaster::ManageShooting()
{
	for (int i = 0; i < towerList.size(); i++)
	{
		if (towerList[i]->GetIsBuilt() && towerList[i]->GetIsReadyToFire())
		{
			for (int j = 0;j < enemyList.size();j++)
			{
				if (towerList[i]->GetRange()->getGlobalBounds().contains(enemyList[j]->getPosition()) && towerList[i]->GetIsReadyToFire())
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

				if (enemyList[i]->getGlobalBounds().contains(bulletList[j]->getPosition()))// crash
				{
					enemyList[i]->GiveDamage(bulletList[j]);
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


GameMaster::GameMaster(std::vector<GroundTile*> Worldmap) : map{Worldmap}, money{700}, playerLives{11}, isGameOver{false}, level{1}
{
	loadFont();
	MakeGUI();

}


GameMaster::~GameMaster()
{
}
