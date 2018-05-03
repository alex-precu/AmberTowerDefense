#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "enums.h"
#include "GroundTile.h"
#include <math.h>

class Enemy : public sf::ConvexShape
{
	int hp;
	double speed ;
	int type;
	bool IsPathComplete = false;
	int value;

public:
	GroundTile * nextPath;
	GroundTile* previousPath;
	GroundTile* currentPath;
	bool isDestinationreached;
	int GetValue();
	Enemy(int xPos,int yPos, EnemyType type);
	~Enemy();
	Enemy();
	bool GetIsPathComplete();
	void SetIsPathComplete();
	void Draw();
	void Update();
	int GetHP();
	void GiveDamage(int damage);
	int GetSpeed();
};

