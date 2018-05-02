#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Tower.h"
#include "FireTower.h"
#include "IceTower.h"
#include <iostream>
#include <string>
#include "Enemy.h"
#include "GroundTile.h"
#include "Bullet.h"

class GameMaster
	
{
	std::vector<Tower*> towerList;
	std::vector<Enemy*> enemyList;
	std::vector<Bullet*> bulletList;
	std::vector<Tower*> gui;
	Tower* underContruction;
	int money;
	int playerLifes;
	sf::Font font;
	void loadFont();
	void MakeGUI();
	sf::Text moneyTxt;
	
public:
	std::vector<GroundTile*> map;
	bool CheckMoney();
	bool ContainsMouse(sf::Vector2i &position);
	bool Construction(sf::Vector2i pos);
	sf::ConvexShape* SearchInTowers(sf::Vector2i pos);
	bool CheckPlacement(sf::Vector2i placement);
	void SearchInMap();
	void Render(sf::RenderWindow &window, Flags flag);
	void UpdateGUI();
	void CancelTower();
	void WaveMaker(WaveDifficulty difficulty);
	void MakeEnemies();
	int GetMoney();
	void SpendMoney(int amount);
	void ActivateTowerBuilder();
	void GameManager();
	void UpgradeTower();
	void UpdateAllStates();
	void StartALevel();
	void EndALevel();
	void EndGame();

	GameMaster(std::vector<GroundTile*> Worldmap);
	~GameMaster();
};

