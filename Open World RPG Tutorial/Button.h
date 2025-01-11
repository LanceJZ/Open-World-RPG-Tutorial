#pragma once
#include "SFMLHeaders.h"
#include "CommonHeaders.h"

enum class ButtonState
{
	Idle = 0,
	Hover,
	Active
};

class Button
{
public:
	Button(float x, float y, float width, float height,
		sf::Font* font, std::string text, unsigned int characterSize,
		sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
		sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	virtual ~Button();

	void Update(const sf::Vector2f& mousePos);
	void Render(sf::RenderTarget& target);

	const bool IsPressed() const;

private:
	ButtonState State = ButtonState::Idle;

	sf::RectangleShape Shape = sf::RectangleShape();
	sf::Font* Font = nullptr;
	sf::Text Text;
	sf::Color TextIdleColor = sf::Color::White;
	sf::Color TextHoverColor = sf::Color::Blue;
	sf::Color TextActiveColor = sf::Color::Red;
	sf::Color IdleColor = sf::Color::White;
	sf::Color HoverColor = sf::Color::Blue;
	sf::Color ActiveColor = sf::Color::Red;

};