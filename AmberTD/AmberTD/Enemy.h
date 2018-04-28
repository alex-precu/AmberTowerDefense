#pragma once
#include "Actor.h"
#include <string>

class Enemy : public Actor
{
	int hp;
	float speed;
	std::string element;

public:
	Enemy();
	~Enemy();

	int GetHP();
	float GetSpeed();
};

