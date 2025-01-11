#include "Button.h"

Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned int characterSize,
	sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
	: Text(*font)
{
	Shape.setPosition({ x, y });
	Shape.setSize({ width, height });
	Font = font;
	//Text.setFont(*Font);
	Text.setString(text);
	Text.setFillColor(textIdleColor);
	Text.setCharacterSize(20);

	float shapePosX = Shape.getPosition().x;
	float shapePosY = Shape.getPosition().y;
	float shapeWidth = Shape.getSize().x;
	float shapeHeight = Shape.getSize().y;
	float textWidth = Text.getLocalBounds().size.x;
	float textHeight = Text.getLocalBounds().size.y;

	Text.setPosition({ shapePosX + (shapeWidth / 2.0f) - textWidth / 2.0f,
		shapePosY + (shapeHeight / 2.0f) - textHeight / 1.25f });

	TextIdleColor = textIdleColor;
	TextHoverColor = textHoverColor;
	TextActiveColor = textActiveColor;

	IdleColor = idleColor;
	HoverColor = hoverColor;
	ActiveColor = activeColor;
}

Button::~Button()
{
}

void Button::Update(const sf::Vector2f& mousePos)
{
	if (Shape.getGlobalBounds().contains(mousePos))
	{
		Text.setFillColor(TextHoverColor);
		Shape.setFillColor(HoverColor);
		State = ButtonState::Idle;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			Text.setFillColor(TextActiveColor);
			Shape.setFillColor(ActiveColor);
			State = ButtonState::Active;
		}
	}
	else
	{
		Text.setFillColor(TextIdleColor);
		Shape.setFillColor(IdleColor);
		State = ButtonState::Idle;
	}
}

void Button::Render(sf::RenderTarget& target)
{
	target.draw(Shape);
	target.draw(Text);
}

const bool Button::IsPressed() const
{
	if (State == ButtonState::Active) return true;

	return false;
}
