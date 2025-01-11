#pragma once
#include "State.h"
#include "Button.h"

class EditorState : public State
{
public:
	EditorState(sf::RenderWindow* window,
	 std::map<std::string, int>* supportedKeys,
		std::stack<State*>* states);
	virtual ~EditorState();

	void UpdateButtons();
	void UpdateInput(const float& dt);
	void Update (const float& dt);
	void RenderButtons(sf::RenderTarget& target);
	void Render(sf::RenderTarget* target = nullptr);
	void EndState();

private:
	std::map<std::string, Button*> Buttons;
	sf::Font Font = {};

	void InitVariables();
	void InitButtons();
	void InitFonts();
	void InitKeyBindings();
	void ViewMouseLocation();
};