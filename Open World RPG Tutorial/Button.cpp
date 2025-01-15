#include "Button.h"

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Font* font,
	std::string text, unsigned int characterSize, sf::Color textIdleColor,
	sf::Color textHoverColor, sf::Color textActiveColor, sf::Color idleColor,
	sf::Color hoverColor, sf::Color activeColor, short unsigned id)
	: Text(*font)
{
	ID = id;
	Shape.setPosition(position);
	Shape.setSize(size);
	Font = font;
	//Text.setFont(*Font);
	Text.setString(text);
	Text.setFillColor(textIdleColor);
	Text.setCharacterSize(20);

	PositionText();

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

void Button::SetText(const std::string text)
{
	Text.setString(text);
}

void Button::SetPosition(const sf::Vector2f& position)
{
	Shape.setPosition(position);
	PositionText();
}

const bool Button::IsPressed() const
{
	if (State == ButtonState::Active) return true;

	return false;
}

const std::string& Button::GetText() const
{
	return Text.getString();
}

const sf::Vector2f& Button::GetPosition() const
{
	return Shape.getPosition();
}

const short unsigned Button::GetID() const
{
	return ID;
}

void Button::PositionText()
{
	float shapePosX = Shape.getPosition().x;
	float shapePosY = Shape.getPosition().y;
	float shapeWidth = Shape.getSize().x;
	float shapeHeight = Shape.getSize().y;
	float textWidth = Text.getLocalBounds().size.x;
	float textHeight = Text.getLocalBounds().size.y;

	Text.setPosition({ shapePosX + (shapeWidth / 2.0f) - textWidth / 2.0f,
		shapePosY + (shapeHeight / 2.0f) - textHeight / 1.25f });
}
