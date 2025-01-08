#pragma once
#include "SFMLHeaders.h"

class MovementComponent
{
public:
	MovementComponent(sf::Sprite& sprite, float maxVelocity,
		float acceleration, float deceleration);
	virtual ~MovementComponent();

	void Update(const float& dt);
	void Move(const sf::Vector2f direction, const float dt);

	const sf::Vector2f& GetVelocity() const;
	const bool IsIdle() const;
	const bool IsMovingLeft() const;
	const bool IsMovingRight() const;
	const bool IsMovingUp() const;
	const bool IsMovingDown() const;

	void SetIdle();

private:
	bool Idle = true;
	float MaxVelocity = 0.0f;
	float Acceleration = 0.0f;
	float Deceleration = 0.0f;

	sf::Sprite& Sprite;

	sf::Vector2f Velocity = sf::Vector2f(0.0f, 0.0f);



};

