#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Texture& textureSheet)
	: TextureSheet(textureSheet)
{
}

AnimationComponent::~AnimationComponent()
{
	for (const auto& sheet : Animations) delete sheet.second;
}

void AnimationComponent::Play(const std::string& name, const float& dt)
{
	if (LastAnimation)
	{
		if (Animations[name] != LastAnimation)
		{
			LastAnimation->Reset();
			LastAnimation = Animations[name];
		}
	}

	Animations[name]->Play(dt);
}

void AnimationComponent::Add(const std::string& name, sf::Sprite& Sprite,
 float FrameTimer, sf::Vector2i firstFrame, int frames, sf::Vector2i size)
{
	Animations[name] = new Animation(Sprite, TextureSheet, FrameTimer,
		firstFrame, frames, size);
}

void AnimationComponent::Start(std::string name)
{
}

void AnimationComponent::Reset(std::string name)
{
}