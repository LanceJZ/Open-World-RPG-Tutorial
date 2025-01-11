#pragma once
#include "Entity.h"

class ThePlayer : public Entity
{
public:
	ThePlayer(sf::Vector2f spawnPoint, sf::Texture& textureSheet);
	virtual ~ThePlayer();

	bool Attacking = false;

	void UpdateAttack(const float& dt);
	void UpdateAnimation(const float& dt);
	void Update (const float& dt);
	void Render(sf::RenderTarget& target);

	void Move(const sf::Vector2f& dir, const float& dt);

private:
	void InitVariables();
};