#include "Tile.h"

Tile::Tile(sf::Vector2f position, float girdSize)
{
	Shape.setSize(sf::Vector2f(girdSize, girdSize));
	Shape.setFillColor(sf::Color::Green);
	Shape.setPosition(position);
}

Tile::~Tile()
{
}

void Tile::Update(float dt)
{
}

void Tile::Render(sf::RenderTarget& target)
{
	target.draw(Shape);
}
