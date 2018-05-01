#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "enums.h"

class Enemy : public sf::ConvexShape
{
	int hp;
	float speed;
	std::string element;

public:
	Enemy(int xPos,int yPos, EnemyType type);
	~Enemy();
	Enemy();
	int GetHP();
	float GetSpeed();
	void CollisionDetect();
};

