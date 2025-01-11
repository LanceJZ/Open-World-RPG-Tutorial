#pragma once
#include "SFMLHeaders.h"

class HitboxComponent
{
public:
	sf::Vector2f Addf(const sf::Vector2f& left, const sf::Vector2f& right)
	{
		return sf::Vector2f(left.x + right.x, left.y + right.y);
	} //Figure out how to make this project wide.

	HitboxComponent(sf::Sprite& sprite, sf::Vector2f offset, sf::Vector2f size);
	virtual ~HitboxComponent();

	sf::Vector2f Offset;
	sf::Vector2f Size;

	void Update(const float& dt);
	void Render(sf::RenderTarget& target);

	const bool CheckIntersct(const sf::FloatRect& fRect);

private:
	sf::RectangleShape Hitbox;
	sf::Sprite& Sprite;
};

