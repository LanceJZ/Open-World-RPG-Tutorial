#include "State.h"

State::State(sf::RenderWindow* window, sf::Font& font,
	std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: Font(font), Window(window), SupportedKeys(supportedKeys), States(states)
{
}

State::~State()
{

}

const bool& State::GetQuit() const
{
	return WantsEnd;
}

void State::UpdateTimer(const float& dt)
{
	PauseTimer += dt;
}

void State::UpdateMousePosition()
{
	MousePosScreen = sf::Mouse::getPosition();
	MousePosWindow = sf::Mouse::getPosition(*Window);
	MousePosView = Window->mapPixelToCoords(sf::Mouse::getPosition(*Window));
}

void State::EndState()
{
	WantsEnd = true;
}

void State::CheckForClose()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(KeyBindings.at("CLOSE"))))
		WantsEnd = true;
}

void State::UpdatePause()
{
	if (PauseTimer > TimerAmount)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(KeyBindings.at("PAUSE"))))
		{
			Paused = !Paused;
			PauseTimer = 0.0f;
		}
	}
}

const bool State::GetPaused()
{
	return Paused;
}

void State::SetPaused(const bool paused)
{
}

void State::ViewMouseLocation()
{
	sf::Text mouseText = sf::Text(Font);
	mouseText.setPosition(MousePosView + sf::Vector2f(20, 10));
	mouseText.setCharacterSize(12);
	mouseText.setFillColor(sf::Color::White);
	mouseText.setString("X: " + std::to_string((int)MousePosView.x) +
		" Y: " + std::to_string((int)MousePosView.y));

	Window->draw(mouseText);
}
