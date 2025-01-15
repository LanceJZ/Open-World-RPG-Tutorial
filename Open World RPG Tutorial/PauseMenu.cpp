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

std::map<std::string, Button*>& PauseMenu::GetButtons()
{
	return Buttons;
}

void PauseMenu::Update(const sf::Vector2f& mousePosView)
{

	for (const auto& button : Buttons) button.second->Update(mousePosView);
}

void PauseMenu::Render(sf::RenderTarget& target)
{
	target.draw(Background);
	target.draw(MenuBox);
	target.draw(MenuText);

	for (const auto& button : Buttons) button.second->Render(target);
}

void PauseMenu::AddButton(const std::string name, sf::Vector2f position,
	const std::string text)
{
	sf::Vector2f size = sf::Vector2f(150.0f, 50.0f);

	position.x -= size.x / 2.0f;

	Buttons[name] = new Button(position, size, &Font,
		text, 20,
		sf::Color(140, 140, 140, 200),
		sf::Color(255, 255, 255, 255),
		sf::Color(20, 20, 20, 200),
		sf::Color(50, 50, 50, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 100));
}

const bool PauseMenu::IsButtonPressed(const std::string key)
{
	return Buttons.at(key)->IsPressed();
}