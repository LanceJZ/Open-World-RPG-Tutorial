#pragma once
#include "Entity.h"

class State
{
public:
	State(sf::RenderWindow* window, sf::Font& font,
		std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~State();

	const bool& GetQuit() const;

	void UpdateTimer(const float& dt);
	virtual void UpdateMousePosition();
	virtual void UpdateInput(const float& dt) = 0;
	virtual void Update(const float& dt) = 0;
	virtual void Render(sf::RenderTarget* target) = 0;
	virtual void EndState();

	virtual void CheckForClose();
	virtual void UpdatePause();

	const bool GetPaused();
	void SetPaused(const bool paused);

protected:
	sf::RenderWindow* Window = nullptr;

	sf::Vector2i MousePosScreen = {};
	sf::Vector2i MousePosWindow = {};
	sf::Vector2f MousePosView = {};
	sf::Font& Font;

	std::map<std::string, int>* SupportedKeys = {};
	std::map<std::string, int> KeyBindings;
	std::map<std::string, sf::Texture> Textures	= {};

	std::stack<State*>* States = nullptr;

	virtual void InitKeyBindings() = 0;

private:
	bool WantsEnd = false;
	bool Paused = false;
	float PauseTimer = 0.0f;
	float TimerAmount = 0.50f;

	void ViewMouseLocation();
};