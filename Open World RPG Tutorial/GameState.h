#pragma once
#include "State.h"
#include "ThePlayer.h"
#include "PauseMenu.h"

class GameState : public State
{
public:
	GameState(sf::RenderWindow* window, sf::Font& font,
		std::map<std::string, int>* supportedKeys,
		std::stack<State*>* states);
	virtual ~GameState();

	void UpdatePauseInput();
	void UpdateInput(const float& dt);
	void Update(const float& dt);
	void Render(sf::RenderTarget* target);

	void EndState();
	void EndStateUpdate();

private:
	ThePlayer* Player;
	PauseMenu ThePauseMenu;

	void InitKeyBindings();
	void InitTextures();
	void InitPlayer();
};