#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Tower.h"
#include "FireTower.h"
#include "IceTower.h"
#include <iostream>
#include <string>

class GameMaster
	
{
	std::vector<sf::ConvexShape*> towerList;
	std::vector<sf::ConvexShape*> enemyList;
	std::vector<sf::ConvexShape*> bulletList;
	std::vector<sf::ConvexShape> &map;
	std::vector<sf::ConvexShape*> gui;
	int money;
	int playerLifes;
	sf::Font font;
	void loadFont();
	void MakeGUI();
	sf::Text moneyTxt;
	
public:
	bool ContainsMouse(sf::Vector2i &position);
	void SearchInGUI();
	void SearchInMap();
	void Render(sf::RenderWindow &window);
	void UpdateGUI();
	void MakeEnemies();
	int GetMoney();
	void SetMoney(int amount);
	void CreateTower();
	void UpgradeTower();
	void CheckTowerPurchase(sf::ConvexShape* tower);
	void UpdateAllStates();
	void StartALevel();
	void EndALevel();
	void EndGame();

	GameMaster(std::vector<sf::ConvexShape> &Worldmap);
	~GameMaster();
};

