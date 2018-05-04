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
	for (int j = 42; j < FullHdresolution::y; j += TILE_SIZE)
	{
		for (int i = GUI_OFFSET; i < FullHdresolution::x - GUI_OFFSET; i += TILE_SIZE)
		{
			map.push_back(new GroundTile(i, j, GroundType::hill));
			i += TILE_OFFSET;
		}
		j += TILE_OFFSET;
	}
	LoadLevel();

}


void WorldBuilder::LoadLevel()
{



	for (int y = 0;y < lvlHeight; y++)
	{
		for (int x = 0; x < lvlWidth;x++)
		{
			int index = y * lvlWidth + x;
			if (level2[y][x] == 1)
			{
				map[index]->SetType(GroundType::path);
			}
		}
	}

}



std::vector<GroundTile*>WorldBuilder::GetMap()
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