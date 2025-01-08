#pragma once
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <map>

#include "SFMLHeaders.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"

class Entity
{
public:
	Entity();
	virtual ~Entity();

	void SetUpSprite(sf::Texture& texture);

	virtual void Update (const float& dt);
	virtual void Render(sf::RenderTarget* target = nullptr);

	virtual void Move(const sf::Vector2f& dir, const float& dt);
	virtual void SetPosition(const sf::Vector2f& pos);
	virtual void SetIdle();

	void CreateMovementComponent(const float maxVelocity, const float acceleration,
		const float deceleration);
	void CreateAnimationComponent(sf::Texture& textureSheet);

protected:
	sf::Sprite* Sprite = nullptr;

	MovementComponent* Movement = nullptr;
	AnimationComponent* Animation = nullptr;

private:
	void InitVariables();

};

