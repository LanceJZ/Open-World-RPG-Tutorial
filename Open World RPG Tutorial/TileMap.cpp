#include "TileMap.h"

TileMap::TileMap()
{
	Map.reserve(MaxSize.x);

	for (int x = 0; x < MaxSize.x; x++)
	{
		Map.push_back(std::vector<std::vector<Tile>>());
		Map[x].reserve(MaxSize.y);

		for (int y = 0; y < MaxSize.y; y++)
		{
			Map[x].push_back(std::vector<Tile>());
			Map[x][y].reserve(Layers);

			for (int z = 0; z < Layers; z++)
			{
				sf::Vector2f position = sf::Vector2f(x * GridSize, y * GridSize);

				Map[x][y].push_back(Tile(position, (float)GridSize));
			}
		}
	}
}

TileMap::~TileMap()
{
}

void TileMap::Update(float dt)
{
}

void TileMap::Render(sf::RenderTarget& target)
{
	for (int x = 0; x < MaxSize.x; x++)
	{
		for (int y = 0; y < MaxSize.y; y++)
		{
			for (int z = 0; z < Layers; z++)
			{
				Map[x][y][z].Render(target);
			}
		}
	}
}
