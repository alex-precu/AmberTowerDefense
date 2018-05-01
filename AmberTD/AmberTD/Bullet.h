#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <vector>
class Bullet : public sf::ConvexShape
{
	float damage;
	std::string element;
	float elementalDamage;

public:
	void Update();
	Bullet(float damage);
	Bullet(float damage,std::string element, float elementalDamage);
	~Bullet();
	void SetDamage(float damage);
	float GetDamage();
	void SetElement(std::string& element);
	std::string GetElement();
	void SetElementalDamage(float damage);
	float GetElementalDamage();
	bool CollisionDetect();
};

