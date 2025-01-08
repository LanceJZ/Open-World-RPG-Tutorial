#pragma once

#include <iostream>
#include <ctime>
#include <cstdlib>

#include "MainMenuState.h"

class Game
{
public:
	Game();
	virtual ~Game();

	void UpdateDT();
	void UpdateSFMLEvents();
	void Update();
	void Render();
	void Run();

private:
	sf::Clock DTClock = {};
	float DTime = {};

	sf::RenderWindow* Window = {};

	std::stack<State*> States = {};
	std::map<std::string, int> SupportedKeys = {};
	std::vector<sf::VideoMode> VideoModes = {};

	void InitVariables();
	void InitWindow();
	void InitStates();
	void InitKeys();
	void EndGame();
};