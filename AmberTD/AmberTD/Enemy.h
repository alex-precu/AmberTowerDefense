#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "enums.h"
#include "GroundTile.h"
#include <math.h>
class Bullet;

class Enemy : public sf::ConvexShape
{	
	int hp;
	double speed ;
	int type;
	bool IsPathComplete;
	bool hasWon;
	bool  isAffected;

	float OTdamage;
	int value;
	void DrawEnemy(EnemyType type);

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
	bool GetHasWon();
	void Update();
	int GetHP();
	void GiveDamage(Bullet* bullet);
	int GetSpeed();
};

