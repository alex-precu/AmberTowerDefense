#include "Enemy.h"
#include "GameMaster.h"
int Enemy::GetHP()
{
	return hp;
}

int Enemy::GetSpeed()
{
	return speed;
}

Enemy::Enemy(int xPos, int yPos, EnemyType type) : hp{ 100 }, speed{ 2.66 }, value{50}, previousPath{nullptr}, nextPath{nullptr}, 
													isDestinationreached{true}, currentPath{nullptr}, IsPathComplete{false}, hasWon{false}, isAffected{false},OTdamage{0}
{
	DrawEnemy(type);
	this->setPosition(xPos, yPos);
	this->setOrigin(TILE_SIZE/2, TILE_SIZE/2);
	switch (type)
	{
	case fast:
		speed *= 2;
		break;
	case fat:
		hp *= 5;
		break;
	default:
		break;
	}

}

void Enemy::DrawEnemy(EnemyType type)
{
	switch (type)
	{
	case EnemyType::normal :
		{
			this->setPointCount(6);
			this->setPoint(0, sf::Vector2f(TILE_SIZE / 2, 25));
			this->setPoint(1, sf::Vector2f(TILE_SIZE - 30, TILE_SIZE / 4));
			this->setPoint(2, sf::Vector2f(TILE_SIZE - 30, TILE_SIZE*0.75));
			this->setPoint(3, sf::Vector2f(TILE_SIZE / 2, TILE_SIZE - 25));
			this->setPoint(4, sf::Vector2f(15, TILE_SIZE*0.75));
			this->setPoint(5, sf::Vector2f(15, TILE_SIZE / 4));
			this->setFillColor(sf::Color::Cyan);
			break;
		}
	case EnemyType::fast : 
		{

		this->setPointCount(4);
		this->setPoint(0, sf::Vector2f(TILE_SIZE / 4, TILE_SIZE / 4));
		this->setPoint(1, sf::Vector2f(TILE_SIZE*0.75, TILE_SIZE / 4));
		this->setPoint(2, sf::Vector2f(TILE_SIZE*0.75, TILE_SIZE*0.75));
		this->setPoint(3, sf::Vector2f(TILE_SIZE/4, TILE_SIZE*0.75));
		this->setFillColor(sf::Color::Blue);
		break;

		}
	case EnemyType::fat :
	{
		this->setPointCount(4);
		this->setPoint(0, sf::Vector2f(0,0));
		this->setPoint(1, sf::Vector2f(TILE_SIZE, 0));
		this->setPoint(2, sf::Vector2f(TILE_SIZE, TILE_SIZE));
		this->setPoint(3, sf::Vector2f(0, TILE_SIZE*0.75));
		this->setFillColor(sf::Color::Black);

		break;
	}
	}
	

}

void Enemy::Update()
{
	hp -= OTdamage;
	if (nextPath)
	{
		sf::Vector2f dirrection = nextPath->getPosition() - this->getPosition();
		float lenght = (float)sqrt(pow(dirrection.x, 2) + pow(dirrection.y,2));
		if (lenght < 5)
		{
			isDestinationreached = true;
			if (currentPath)
			{
				previousPath = currentPath;
			}

			currentPath = nextPath;
			nextPath = nullptr;
			return;
		}

		dirrection.x /= lenght;
		dirrection.y /= lenght;
		dirrection.x *= GetSpeed();
		dirrection.y *= GetSpeed();
		this->setPosition(this->getPosition()+dirrection);
	}
	else
	{
		this->hasWon = true;
	}
}

bool Enemy::GetHasWon()
{
	return hasWon;
}

void Enemy::GiveDamage(Bullet* bullet)
{
	this->hp -= bullet->GetDamage();

	if (bullet->GetElementalDamage()>0 && !this->isAffected)
	{
		this->hp -= bullet->GetElementalDamage();
		if (bullet->GetElement() == TowerType::fire)
		{
			isAffected = true;
			OTdamage = bullet->GetElementalDamage();
		}
		else
		{
			isAffected = true;
			speed /= 2;
		}
	}
}
int Enemy::GetValue()
{
	return value;
}
Enemy::Enemy()
{

}

Enemy::~Enemy()
{
}
