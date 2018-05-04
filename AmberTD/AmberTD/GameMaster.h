#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Tower.h"
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
	int playerLives;
	int level;
	sf::Font font;
	void loadFont();
	void MakeGUI();
	sf::Text livesTxt;
	sf::Text moneyTxt;
	sf::Text gameOverTxt;
	sf::Text towerPrice1txt;
	sf::Text towerPrice2txt;
	sf::Text towerPrice3txt;
	bool isGameOver;
	void UpdateTowers(sf::RenderWindow &window);
	void UpdateEnemies();
	void UpdateBullets();
	
public:
	void RenderGameOver(sf::RenderWindow &window);
	void ResetLevel();
	int GetLives();
	void RestartGame();
	std::vector<GroundTile*> map;
	bool CheckMoney();
	bool GetIsGameOver();
	bool ContainsMouse(sf::Vector2i &position);
	bool Construction(sf::Vector2i pos);
	Tower* SearchInTowers(sf::Vector2f pos);
	bool CheckPlacement(sf::Vector2i placement);
	void Render(sf::RenderWindow &window, Flags flag);
	void UpdateGUI();
	void CancelTower();
	void WaveMaker(int difficulty);
	int GetMoney();
	void GiveMoney(int amount);
	void SpendMoney(int amount);
	void ActivateTowerBuilder();
	Flags GameManager(Flags flag);
	void GameCycle(sf::RenderWindow &window,Flags flag);
	//void UpgradeTower();
	void UpdateAllStates(sf::RenderWindow &window);
	void ManageShooting();
	void ManageDamage();
	int GetTileIndex(GroundTile* tile);
	void DrawText(sf::RenderWindow &window);


	GameMaster(std::vector<GroundTile*> Worldmap);
	~GameMaster();
};

