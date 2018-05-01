#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
class GameMaster
	
{
	std::vector<sf::CircleShape> towerList;
	std::vector<sf::CircleShape> enemyList;
	std::vector<sf::CircleShape> bulletList;
	std::vector<sf::RectangleShape> map;
	std::vector<sf::Shape> gui;
	int money;
	int playerLifes;
	
public:
	int GetMoney();
	void SetMoney(int amount);
	void CreateTower();
	void UpgradeTower();
	void CheckTowerPurchase(sf::CircleShape tower);
	void CreateTower();
	void UpdateAllStates();
	void StartALevel();
	void EndALevel();
	void EndGame();

	GameMaster();
	~GameMaster();
};

