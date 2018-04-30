#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include "enums.h"

class Enemy : public sf::CircleShape
{
	int hp;
	float speed;
	std::string element;

public:
	Enemy(int xPos,int yPos);
	~Enemy();
	Enemy();
	int GetHP();
	float GetSpeed();
	void CollisionDetect();
};

