#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font)
	: Font(font), MenuText(font)
{
	Background.setSize(sf::Vector2f(window.getSize()));
	Background.setFillColor(sf::Color(20, 20, 20, 100));

	MenuBox.setSize(sf::Vector2f(window.getSize().x / 4.0f,
		window.getSize().y - 60.0f));
	MenuBox.setFillColor(sf::Color(20, 20, 20, 200));
	MenuBox.setPosition(sf::Vector2f(window.getSize().x / 2.0f -
		MenuBox.getSize().x / 2.0f,	30.0f));

	MenuText.setFillColor(sf::Color(200, 200, 200, 200));
	MenuText.setCharacterSize(64);
	MenuText.setString("PAUSED");
	MenuText.setPosition(sf::Vector2f(MenuBox.getPosition().x +
		MenuBox.getSize().x / 2.0f - MenuText.getGlobalBounds().size.x / 2.0f,
		MenuBox.getPosition().y + 20.0f));
}

PauseMenu::~PauseMenu()
{
	auto i = Buttons.begin();

	while (i != Buttons.end())
	{
		delete i->second;
		++i;
	}
}

void PauseMenu::Update()
{
}

void PauseMenu::Render(sf::RenderTarget& target)
{
	target.draw(Background);
	target.draw(MenuBox);
	target.draw(MenuText);

	for (const auto& button : Buttons) button.second->Render(target);
}