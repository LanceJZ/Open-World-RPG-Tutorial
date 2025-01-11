#pragma once
#include <map>
#include "SFMLHeaders.h"

#include "Button.h"

class PauseMenu
{
public:
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenu();

	void Update();
	void Render(sf::RenderTarget& target);

private:
	sf::RectangleShape Background;
	sf::RectangleShape MenuBox;
	sf::Font& Font;
	sf::Text MenuText;

	std::map<std::string, Button*> Buttons;
};

