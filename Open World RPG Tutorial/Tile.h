#pragma once
#include "SFMLHeaders.h"

class Tile
{
public:
	Tile(sf::Vector2f position, float girdSize);
	virtual ~Tile();

	void Update(float dt);
	void Render(sf::RenderTarget& target);

protected:
	sf::RectangleShape Shape;

private:

};

