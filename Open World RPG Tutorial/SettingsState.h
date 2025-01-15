#pragma once
#include "State.h"
#include "Button.h"
#include "DropDownList.h"

class SettingsState : public State
{
public:
	SettingsState(sf::RenderWindow* window, sf::Font& font,
	 std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~SettingsState();

	void UpdateButtons();
	void UpdateInput(const float& dt);
	void Update (const float& dt);
	void Render(sf::RenderTarget* target = nullptr);
	void EndState();

private:
	sf::Text Options;
	sf::RectangleShape Background;
	sf::Texture BackgroundTexture = {};

	std::map<std::string, Button*> Buttons;
	std::map<std::string, DropDownList*> DDList;

	std::vector<sf::VideoMode> VideoModes;

	void InitVariables();
	void InitBackground();
	void InitButtons();
	void InitKeyBindings();
	void InitText();
	void Apply();
};