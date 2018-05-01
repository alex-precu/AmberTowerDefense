#pragma once
#include <SFML/Window.hpp>


const int TILE_OFFSET = 3;
const int GUI_OFFSET = 320;
const int TILE_SIZE = 80;
const float ENEMY_SIZE = 30;

enum GroundType {
	hill = 0,
	path
};

enum TowerType {
	basic = 0,
	fire,
	ice
};

enum EnemyType {
	basic=0,
	fast,
	boss
};
enum FullHdresolution {
	x = 1920,
	y = 1080
};



