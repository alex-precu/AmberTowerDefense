#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "enums.h"

class Enemy : public sf::ConvexShape
{
	int hp;
	int speed ;
	int type;

public:
	Enemy(int xPos,int yPos, EnemyType type);
	~Enemy();
	Enemy();
	void Update();
	int GetHP();
	void SetHp(int damage);
	int GetSpeed();
};

