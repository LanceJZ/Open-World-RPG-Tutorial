#pragma once
#include "GameState.h"
#include "EditorState.h"
#include "SettingsState.h"
#include "Button.h"

class MainMenuState : public State
{
public:
	MainMenuState(sf::RenderWindow* window, sf::Font& font,
		std::map<std::string, int>* supportedKeys,
		std::stack<State*>* states);
	virtual ~MainMenuState();

	void UpdateInput(const float& dt);
	void UpdateButtons();
	void Update (const float& dt);
	void RenderButtons(sf::RenderTarget& target);
	void Render(sf::RenderTarget* target = nullptr);
	void EndState();

private:
	sf::RectangleShape Background;
	sf::Texture BackgroundTexture = {};


	std::map<std::string, Button*> Buttons;

	void InitVariables();
	void InitBackground();
	void InitButtons();
	void InitKeyBindings();
};