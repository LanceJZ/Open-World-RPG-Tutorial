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
	float DTime = {};

	sf::Clock DTClock = {};
	sf::Font Font = {};
	sf::RenderWindow* Window = {};

	std::stack<State*> States = {};
	std::map<std::string, int> SupportedKeys = {};
	std::vector<sf::VideoMode> VideoModes = {};

	void InitVariables();
	void InitWindow();
	void InitStates();
	void InitKeys();
	void InitFonts();
	void EndGame();
};