#pragma once
#include "State.h"
#include "ThePlayer.h"

class GameState : public State
{
public:
	GameState(sf::RenderWindow* window,
		std::map<std::string, int>* supportedKeys,
		std::stack<State*>* states);
	virtual ~GameState();

	void UpdateInput(const float& dt);
	void Update(const float& dt);
	void Render(sf::RenderTarget* target = nullptr);

	void EndState();
	void EndStateUpdate();

private:
	ThePlayer* Player;

	void InitKeyBindings();
	void InitTextures();
	void InitPlayer();
};