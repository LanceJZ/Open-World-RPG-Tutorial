#pragma once
#include "Entity.h"

class State
{
public:
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,
		std::stack<State*>* states);
	virtual ~State();

	const bool& GetQuit() const;

	virtual void UpdateMousePosition();
	virtual void UpdateInput(const float& dt) = 0;
	virtual void Update(const float& dt) = 0;
	virtual void Render(sf::RenderTarget* target = nullptr) = 0;
	virtual void EndState() = 0;

	virtual void CheckForClose();
	virtual void EndStateUpdate();

protected:
	sf::RenderWindow* Window = nullptr;

	sf::Vector2i MousePosScreen = {};
	sf::Vector2i MousePosWindow = {};
	sf::Vector2f MousePosView = {};

	std::map<std::string, int>* SupportedKeys = {};
	std::map<std::string, int> KeyBindings;
	std::map<std::string, sf::Texture> Textures	= {};

	std::stack<State*>* States = nullptr;

	virtual void InitKeyBindings() = 0;
private:
	bool WantsEnd = false;
};