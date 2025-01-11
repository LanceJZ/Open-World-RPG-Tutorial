#include "Entity.h"

Entity::Entity()
{
	InitVariables();

}

Entity::~Entity()
{
	delete Sprite;
	delete Movement;
	delete Animation;
	delete Hitbox;
}

void Entity::SetUpSprite(sf::Texture& texture)
{
	Sprite = new sf::Sprite(texture);
	Sprite->setTextureRect(sf::IntRect({ 0, 0 }, { 0, 0 }));
}

void Entity::Update(const float& dt)
{
	if (Movement) Movement->Update(dt);
	if (Hitbox) Hitbox->Update(dt);
}

void Entity::Render(sf::RenderTarget& target)
{
	if (Sprite) target.draw(*Sprite);
	if (Hitbox) Hitbox->Render(target);
}

void Entity::Move(const sf::Vector2f& dir, const float& dt)
{
	if (Movement) Movement->Move(dir, dt);
}

void Entity::SetPosition(const sf::Vector2f& pos)
{
	if (Sprite) Sprite->setPosition(pos);
}

void Entity::SetIdle()
{
	if (Movement) Movement->SetIdle();
}

void Entity::SetPaused(const bool& paused)
{
	Paused = paused;
}

void Entity::CreateMovementComponent(const sf::Vector2f maxVelocity,
	const float acceleration, const float deceleration)
{
	if (Sprite) Movement = new MovementComponent(*Sprite, maxVelocity,
		acceleration, deceleration);
}

void Entity::CreateAnimationComponent(sf::Texture& textureSheet)
{
	Animation = new AnimationComponent(textureSheet);
}

void Entity::CreateHitboxComponent(sf::Sprite& sprite, const sf::Vector2f& offset,
	const sf::Vector2f& size)
{
	Hitbox = new HitboxComponent(sprite, offset, size);
}

void Entity::InitVariables()
{

}
