#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite& sprite,
	sf::Vector2f offset, sf::Vector2f size) : Sprite(sprite), Offset(offset)
{
	Hitbox.setPosition(Addf(sprite.getPosition(), offset));
	Hitbox.setSize(size);
	Hitbox.setFillColor(sf::Color::Transparent);
	Hitbox.setOutlineThickness(1.0f);
	Hitbox.setOutlineColor(sf::Color::Blue);
}

HitboxComponent::~HitboxComponent()
{
}

void HitboxComponent::Update(const float& dt)
{
	Hitbox.setPosition(Addf(Sprite.getPosition(), Offset));
}

void HitboxComponent::Render(sf::RenderTarget& target)
{
	target.draw(Hitbox);
}

const bool HitboxComponent::CheckIntersct(const sf::FloatRect& fRect)
{
	if (Hitbox.getPosition().x + Hitbox.getSize().x > fRect.size.x &&
		Hitbox.getPosition().x + Hitbox.getSize().x < fRect.position.x &&
		Hitbox.getPosition().y + Hitbox.getSize().y > fRect.size.y &&
		Hitbox.getPosition().y + Hitbox.getSize().y < fRect.position.y)
		return true;

	return false;
}
