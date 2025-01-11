#pragma once
#include "SFMLHeaders.h"
#include <map>

class AnimationComponent
{
	struct Animation
	{
		sf::Vector2i Multiply(const sf::Vector2i& left, const sf::Vector2i& right)
		{
			return sf::Vector2i(left.x * right.x, left.y * right.y);
		} //Figure out how to make this project wide.

		float Timer = 0.0f;
		float FrameTimer = 0.0f; //Ticks per frame.
		bool Done = false;

		sf::Vector2i Size = { 0, 0 };
		sf::IntRect StartFrame;
		sf::IntRect EndFrame;
		sf::IntRect CurrentFrame;
		sf::Texture& TextureSheet;
		sf::Sprite& Sprite;

		Animation(sf::Sprite& sprite, sf::Texture& textureSheet,
			float FrameTimer,
			sf::Vector2i firstFrame, int frames, sf::Vector2i size)
			: Sprite(sprite), TextureSheet(textureSheet), FrameTimer(FrameTimer),
			Size(size)
		{
			StartFrame = sf::IntRect(Multiply(firstFrame, size), size);
			EndFrame = StartFrame;
			EndFrame.position.x = StartFrame.position.x + (size.x * (frames - 1));

			CurrentFrame = StartFrame;
		}

		const bool& Play(const float& dt, const float& modifier = 1.0f,
			const float& modifierMax = 1.0f)
		{
			Done = false;

			if (modifier > 0.0f || modifier < 0.0f)
			{
				if (modifier < 0.0f)
					Timer += ((modifier * -1) / modifierMax) * 60 * dt;
				else Timer += (modifier / modifier) * 60 * dt;
			}
			else Timer += 60 * dt;

			if (Timer >= FrameTimer)
			{
				Timer = 0.0f;

				if (CurrentFrame.position.x < EndFrame.position.x)
				{
					CurrentFrame.position.x += Size.x;
				}
				else
				{
					CurrentFrame.position.x = StartFrame.position.x;
					Done = true;
				}

				Sprite.setTextureRect(CurrentFrame);
			}

			return Done;
		}

		void Reset() { CurrentFrame = StartFrame; Timer = FrameTimer; }

		const bool& IsDone() const { return Done; }
	};

public:
	AnimationComponent(sf::Texture& textureSheet);
	virtual ~AnimationComponent();

	void Play(const std::string& name, const float& dt,
		const float& modifier = 1.0f, const float& modifierMax = 1.0f,
		const bool priority = false);

	void Add(const std::string& name, sf::Sprite& sprite, float FrameTimer,
			sf::Vector2i start, int frames, sf::Vector2i size);
	void Start(std::string name);
	void Reset(std::string name);

	const bool& IsDone(std::string name);

private:
	sf::Texture& TextureSheet;

	std::map<std::string, Animation*> Animations;
	Animation* LastAnimation = nullptr;
	Animation* PriorityAnimation = nullptr;
};

