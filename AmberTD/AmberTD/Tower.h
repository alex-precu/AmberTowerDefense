#pragma once
#include <SFML\Graphics.hpp>
#include "Actor.h"
#include <vector>

class Tower : public Actor 
{
	int level;
	float damage;
	float range;
	float fireRate;
	sf::Vector2f position;
	void SetDamage();
	void SetRange();
	void SetPosition(float dx, float dy);
	void SetFireRate(float rate);

public:
	Tower();
	~Tower();
	void UpgradeLevel();
	int GetLevel();
	float GetDamage(); 
	float GetRange();
	float GetFireRate();
	void Update();
	sf::Vector2f GetPosition();
	Actor* Shoot(); 

};

