#pragma once
#include <SFML\Graphics.hpp>
#include "Actor.h"

class Tower : public Actor 
{
	int level;
	float damage;
	float range;
	sf::Vector2f position;
	void SetDamage();
	void SetRange();
	void SetPosition(float dx, float dy);

public:
	Tower();
	~Tower();
	void UpgradeLevel();
	int GetLevel();
	float GetDamage(); 
	float GetRange();
	sf::Vector2f GetPosition();
	Actor* Shoot();

};

