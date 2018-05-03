#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "enums.h"
#include <string>
#include <iostream>


class Tower : public sf::ConvexShape
{
	std::string name = "Basic Tower";
	sf::CircleShape rangeHelper;
	int level;
	float damage;
	float range;
	float fireRate;
	bool isReadyToFire = true;
	bool isSelected = false;
	bool isBuilt = false;
	int price;
	TowerType type;
	sf::Time collector = sf::Time::Zero;
	void SetDamage();
	void SetRange();
	void SetFireRate(float rate);

public:
	TowerType GetType();
	Tower();
	Tower(int xPos, int yPos, TowerType type);
	~Tower();
	std::string GetName();
	sf::CircleShape DrawPlacementAssist(sf::RenderWindow &window);
	bool GetIsReadyToFire();
	void SetIsReadyToFire(bool ready);
	int GetPrice();
	void UpgradeLevel();
	int GetLevel();
	float GetDamage(); 
	float GetRange();
	float GetFireRate();
	void SetState();
	bool GetIsBuilt();
	void Update(sf::RenderWindow &window);
	//virtual void ReadyToFire();
	

};

