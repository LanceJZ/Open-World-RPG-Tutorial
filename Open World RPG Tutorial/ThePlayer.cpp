#include "ThePlayer.h"

ThePlayer::ThePlayer(sf::Vector2f spawnPoint, sf::Texture& textureSheet)
{
	SetUpSprite(textureSheet);
	SetPosition(spawnPoint);
	CreateMovementComponent(sf::Vector2f(200.0f, 200.0f), 40.0f, 15.0f);
	CreateAnimationComponent(textureSheet);
	{
		CreateHitboxComponent(*Sprite, { 0, 0 }, { 64, 64 });
	}

	sf::Vector2i size = { 64, 64 };

	Animation->Add("IDLE", *Sprite, 4.0f, { 0, 0 }, 9, size);
	Animation->Add("WALK_DOWN", *Sprite, 4.0f, { 0, 1 }, 4, size);
	Animation->Add("WALK_LEFT", *Sprite, 4.0f, { 4, 1 }, 4, size);
	Animation->Add("WALK_RIGHT", *Sprite, 4.0f, { 8, 1 }, 4, size);
	Animation->Add("WALK_UP", *Sprite, 4.0f, { 12, 1 }, 4, size);
}

ThePlayer::~ThePlayer()
{
}

void ThePlayer::UpdateAttack(const float& dt)
{
	if (Attacking && !Movement->IsMoving())
	{

	}
}

void ThePlayer::UpdateAnimation(const float& dt)
{
	sf::Vector2f velocity = Movement->GetVelocity();
	sf::Vector2f maxVelocity = Movement->GetMaxVelocity();

	if (Movement->IsMovingLeft())
		Animation->Play("WALK_LEFT", dt, velocity.x, maxVelocity.x);
	else if (Movement->IsMovingRight())
		Animation->Play("WALK_RIGHT", dt, velocity.x, maxVelocity.x);
	else if (Movement->IsMovingUp())
		Animation->Play("WALK_UP", dt, velocity.y, maxVelocity.y);
	else if (Movement->IsMovingDown())
		Animation->Play("WALK_DOWN", dt, velocity.y, maxVelocity.y);
	else Animation->Play("IDLE", dt);
}

void ThePlayer::Update(const float& dt)
{
	Entity::Update(dt);

	UpdateAttack(dt);
	UpdateAnimation(dt);
}

void ThePlayer::Render(sf::RenderTarget& target)
{
	Entity::Render(target);

}

void ThePlayer::Move(const sf::Vector2f& dir, const float& dt)
{
	Entity::Move(dir, dt);
}

void ThePlayer::InitVariables()
{
}