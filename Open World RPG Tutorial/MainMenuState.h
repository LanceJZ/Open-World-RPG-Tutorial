#pragma once
#include "GameState.h"
#include "EditorState.h"
#include "Button.h"

class MainMenuState : public State
{
public:
	MainMenuState(sf::RenderWindow* window,
		std::map<std::string, int>* supportedKeys,
		std::stack<State*>* states);
	virtual ~MainMenuState();

	void UpdateInput(const float& dt);
	void UpdateButtons();
	void Update (const float& dt);
	void RenderButtons(sf::RenderTarget* target = nullptr);
	void Render(sf::RenderTarget* target = nullptr);
	void EndState();

private:
	sf::RectangleShape Background;
	sf::Texture BackgroundTexture = {};
	sf::Font Font = {};

	std::map<std::string, Button*> Buttons;

	void InitVariables();
	void InitBackground();
	void InitButtons();
	void InitFonts();
	void InitKeyBindings();
	void ViewMouseLocation();
};