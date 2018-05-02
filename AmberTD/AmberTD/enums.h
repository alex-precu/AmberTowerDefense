#pragma once
#include <SFML/Window.hpp>


const int TILE_OFFSET = 3;
const int GUI_OFFSET = 320;
const int TILE_SIZE = 80;
const float ENEMY_SIZE = 30;
const int BOARD_HEIGHT = 13;
const int BOARD_WIDTH = 16;
enum Flags
{
	noConstruction = 0,
	towerUnderConstruction = 1,
	gameOver = 2
	
};
enum GroundType
{
	hill = 0,
	path
};

enum TowerType
{
	basic = 0,
	fire,
	ice
};

enum EnemyType 
{
	normal = 0,
	fast,
	fat
};

enum WaveDifficulty
{
	easy = 5,
	medium = 10,
	hard = 20

};
enum FullHdresolution 
{
	x = 1920,
	y = 1080
};




