#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <map>

#include "SFMLHeaders.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "HitboxComponent.h"

class Entity
{
public:
	Entity();
	virtual ~Entity();

	void SetUpSprite(sf::Texture& texture);

	virtual void Update (const float& dt);
	virtual void Render(sf::RenderTarget& target);

	virtual void Move(const sf::Vector2f& dir, const float& dt);
	virtual void SetPosition(const sf::Vector2f& pos);
	virtual void SetIdle();
	virtual void SetPaused(const bool& paused);

	void CreateMovementComponent(const sf::Vector2f maxVelocity, const float acceleration,
		const float deceleration);
	void CreateAnimationComponent(sf::Texture& textureSheet);
	void CreateHitboxComponent(sf::Sprite& sprite, const sf::Vector2f& offset,
		const sf::Vector2f& size);

protected:
	bool Paused = false;

	sf::Sprite* Sprite = nullptr;

	MovementComponent* Movement = nullptr;
	AnimationComponent* Animation = nullptr;
	HitboxComponent* Hitbox = nullptr;

private:
	void InitVariables();
};

