#include "EditorState.h"

EditorState::EditorState(sf::RenderWindow* window, std::map<std::string,
	int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	InitKeyBindings();
	InitVariables();
	InitFonts();
	InitKeyBindings();
	InitButtons();
}

EditorState::~EditorState()
{
	auto i = Buttons.begin();

	while (i != Buttons.end())
	{
		delete i->second;
		++i;
	}
}

void EditorState::UpdateButtons()
{
	for (const auto& button : Buttons) button.second->Update(MousePosView);

}

void EditorState::UpdateInput(const float& dt)
{
	CheckForClose();

}

void EditorState::Update(const float& dt)
{
	UpdateMousePosition();
	UpdateInput(dt);
	UpdateButtons();
}

void EditorState::RenderButtons(sf::RenderTarget& target)
{
	for (const auto& button : Buttons) button.second->Render(target);

}

void EditorState::Render(sf::RenderTarget* target)
{
	if (!target) target = Window;

	RenderButtons(*target);
}

void EditorState::EndState()
{

}

void EditorState::InitVariables()
{
}

void EditorState::InitButtons()
{
}

void EditorState::InitFonts()
{
	if (!Font.openFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw std::runtime_error("Could not load font!");
	}
}

void EditorState::InitKeyBindings()
{
	std::ifstream ifs("Config/editorstate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string value = "";

		while (ifs >> key >> value)
		{
			KeyBindings[key] = SupportedKeys->at(value);
		}

		ifs.close();
	}
	else
	{
		KeyBindings["CLOSE"] = SupportedKeys->at("Escape");
	}
}

void EditorState::ViewMouseLocation()
{
	sf::Text mouseText = sf::Text(Font);
	mouseText.setPosition(MousePosView + sf::Vector2f(20, 10));
	mouseText.setCharacterSize(12);
	mouseText.setFillColor(sf::Color::White);
	mouseText.setString("X: " + std::to_string((int)MousePosView.x) +
		" Y: " + std::to_string((int)MousePosView.y));

	Window->draw(mouseText);
}
