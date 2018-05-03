#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "enums.h"

class Enemy : public sf::ConvexShape
{
	int hp;
	double speed ;
	int type;
	sf::Vector2i nextPath;
	bool IsPathComplete = false;
	int value;

public:
	Enemy(int xPos,int yPos, EnemyType type);
	~Enemy();
	Enemy();
	bool GetIsPathComplete();
	void SetIsPathComplete();
	void Draw();
	void Update(int x, int y);
	int GetHP();
	void GiveDamage(int damage);
	int GetSpeed();
};

