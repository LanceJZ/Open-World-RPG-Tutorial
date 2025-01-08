#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity,
	float acceleration, float deceleration) : Sprite(sprite),
	MaxVelocity(maxVelocity), Acceleration(acceleration), Deceleration(deceleration)
{
}

MovementComponent::~MovementComponent()
{
}

const bool MovementComponent::IsIdle() const
{
	return (Idle);
}

const bool MovementComponent::IsMovingLeft() const
{
	return (Velocity.x < 0.0f);
}

const bool MovementComponent::IsMovingRight() const
{
	return (Velocity.x > 0.0f);
}

const bool MovementComponent::IsMovingUp() const
{
	return (Velocity.y < 0.0f);
}

const bool MovementComponent::IsMovingDown() const
{
	return (Velocity.y > 0.0f);
}

void MovementComponent::SetIdle()
{
	Idle = true;
}

void MovementComponent::Update(const float& dt)
{
	if (Velocity.x > 0.0f)
	{
		Velocity.x -= Deceleration;

		if (Velocity.x < 0.0f) Velocity.x = 0.0f;
	}
	else
	{
		Velocity.x += Deceleration;

		if (Velocity.x > 0.0f) Velocity.x = 0.0f;
	}

	if (Velocity.y > 0.0f)
	{
		Velocity.y -= Deceleration;

		if (Velocity.y < 0.0f) Velocity.y = 0.0f;
	}
	else
	{
		Velocity.y += Deceleration;

		if (Velocity.y > 0.0f) Velocity.y = 0.0f;
	}

	Sprite.move(Velocity * dt);
}

void MovementComponent::Move(const sf::Vector2f direction, const float dt)
{
	Velocity.x += Acceleration * direction.x;
	Velocity.y += Acceleration * direction.y;

	Idle = false;

	if (Velocity.x > 0.0f)
	{
		if (Velocity.x > MaxVelocity) Velocity.x = MaxVelocity;
	}
	else
	{
		if (Velocity.x < -MaxVelocity) Velocity.x = -MaxVelocity;
	}

	if (Velocity.y > 0.0f)
	{
		if (Velocity.y > MaxVelocity) Velocity.y = MaxVelocity;
	}
	else
	{
		if (Velocity.y < -MaxVelocity)	Velocity.y = -MaxVelocity;
	}
}

const sf::Vector2f& MovementComponent::GetVelocity() const
{
	return Velocity;
}