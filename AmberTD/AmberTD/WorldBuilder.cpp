#include "WorldBuilder.h"



WorldBuilder::WorldBuilder()
{
	
}


WorldBuilder::~WorldBuilder()
{
}
void WorldBuilder::CreateWorld()
{
	int path = 0;
	for (int i = GUI_OFFSET; i < FullHdresolution::x - GUI_OFFSET; i += TILE_SIZE)
	{
		for (int j = 5; j < FullHdresolution::y - 70; j += TILE_SIZE)
		{
			if (j == 497)
			{
				path = GroundType::path;
			}
			else
			{
				path = GroundType::hill;
			}
			GroundTile ground(i, j, path);
			map.push_back(ground);
			j += TILE_OFFSET;
		}
		i += TILE_OFFSET;
	}
}

void WorldBuilder::LoadLevel()
{
	
}



std::vector<sf::RectangleShape>& WorldBuilder::GetMap()
{
	return map;
}



/*for (int i = TILE_SIZE * 4;i < RESOLUTION_X - TILE_SIZE * 4;i += TILE_SIZE)
{
	for (int j = 0; j < RESOLUTION_Y; j += TILE_SIZE)
	{

		sf::RectangleShape shape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
		shape.setPosition(sf::Vector2f(i, j));
		shape.setFillColor(sf::Color(102, 255, 102));
		//shape.setOutlineThickness(2);
		//shape.setOutlineColor(sf::Color(0, 0, 0));
		list.push_back(shape);
		j += TILE_OFFSET;
	}
	i += TILE_OFFSET;
}*/