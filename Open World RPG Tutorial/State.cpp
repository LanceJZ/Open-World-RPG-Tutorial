#include "State.h"

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,
	std::stack<State*>* states)
{
	Window = window;
	SupportedKeys = supportedKeys;
	States = states;
}

State::~State()
{

}

const bool& State::GetQuit() const
{
	return WantsEnd;
}

void State::UpdateMousePosition()
{
	MousePosScreen = sf::Mouse::getPosition();
	MousePosWindow = sf::Mouse::getPosition(*Window);
	MousePosView = Window->mapPixelToCoords(sf::Mouse::getPosition(*Window));
}

void State::CheckForClose()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(KeyBindings.at("CLOSE"))))
		WantsEnd = true;
}

void State::EndStateUpdate()
{
	WantsEnd = true;
}
