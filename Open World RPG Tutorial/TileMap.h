#pragma once

#include "Tile.h"

class TileMap
{
public:
	TileMap();
	virtual ~TileMap();

	void Update(float dt);
	void Render(sf::RenderTarget& target);

private:
	unsigned GridSize = 50;
	unsigned Layers = 1;

	std::vector<std::vector<std::vector<Tile>>> Map;

	sf::Vector2u MaxSize = sf::Vector2u(40, 30);
};

