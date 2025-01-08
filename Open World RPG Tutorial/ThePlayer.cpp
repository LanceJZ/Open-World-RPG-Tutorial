#include "ThePlayer.h"

ThePlayer::ThePlayer(sf::Vector2f spawnPoint, sf::Texture& textureSheet)
{
	SetUpSprite(textureSheet);
	SetPosition(spawnPoint);
	CreateMovementComponent(200.0f, 40.0f, 15.0f);
	CreateAnimationComponent(textureSheet);

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

void ThePlayer::Update(const float& dt)
{
	Entity::Update(dt);


	if (Movement->IsMovingLeft())
		Animation->Play("WALK_LEFT", dt);
	else if (Movement->IsMovingRight())
		Animation->Play("WALK_RIGHT", dt);
	else if (Movement->IsMovingUp())
		Animation->Play("WALK_UP", dt);
	else if (Movement->IsMovingDown())
		Animation->Play("WALK_DOWN", dt);
	else Animation->Play("IDLE", dt);
}

void ThePlayer::Render(sf::RenderTarget* target)
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