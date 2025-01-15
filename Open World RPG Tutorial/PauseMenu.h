#pragma once
#include <map>
#include "SFMLHeaders.h"

#include "Button.h"

class PauseMenu
{
public:
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenu();

	std::map<std::string, Button*>& GetButtons();

	void Update(const sf::Vector2f& mousePosView);
	void Render(sf::RenderTarget& target);

	void AddButton(const std::string name, sf::Vector2f position,
		const std::string text);
	const bool IsButtonPressed(const std::string key);

private:
	sf::RectangleShape Background;
	sf::RectangleShape MenuBox;
	sf::Font& Font;
	sf::Text MenuText;

	std::map<std::string, Button*> Buttons;

};

