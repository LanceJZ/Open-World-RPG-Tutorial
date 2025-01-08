#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window,
	std::map<std::string, int>* supportedKeys,
	std::stack<State*>* states) : State(window, supportedKeys, states)
{
	InitVariables();
	InitBackground();
	InitFonts();
	InitKeyBindings();
	InitButtons();
}

MainMenuState::~MainMenuState()
{
	auto i = Buttons.begin();

	while (i != Buttons.end())
	{
		delete i->second;
		++i;
	}

	//* Old code that was replaced by the code above.
	// for (i = Buttons.begin(); i != Buttons.end(); ++i) delete i->second;
	//*
}

void MainMenuState::UpdateInput(const float& dt)
{
	CheckForClose();

}

void MainMenuState::UpdateButtons()
{
	for (const auto& button : Buttons) button.second->Update(MousePosView);

	if (Buttons["Exit_Game"]->IsPressed()) EndStateUpdate();

	if (Buttons["New_Game"]->IsPressed())
	{
		States->push(new GameState(Window, SupportedKeys, States));
	}

	if (Buttons["Editor"]->IsPressed())
	{
		States->push(new EditorState(Window, SupportedKeys, States));
	}
}

void MainMenuState::Update(const float& dt)
{
	UpdateMousePosition();
	UpdateInput(dt);
	UpdateButtons();
}

void MainMenuState::RenderButtons(sf::RenderTarget* target)
{
	for (const auto& button : Buttons) button.second->Render(target);

	//Turn on for debug.
	//ViewMouseLocation();
}

void MainMenuState::Render(sf::RenderTarget* target)
{
	target->draw(Background);

	RenderButtons(target);
}

void MainMenuState::EndState()
{
}

void MainMenuState::InitVariables()
{
}

void MainMenuState::InitBackground()
{
	Background.setFillColor(sf::Color::Blue);
	Background.setSize((sf::Vector2f)Window->getSize());

	if (BackgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg1.png"))
	{
		Background.setTexture(&BackgroundTexture);
	}
	else throw std::runtime_error("Could not load background texture!");
}

void MainMenuState::InitButtons()
{
	float x = 1000.0f;
	float y = 300.0f;
	float spacing = 70.0f;

	Buttons["New_Game"] = new Button(x, y, 150, 50, &Font,
		"New Game", 20,
		sf::Color(170, 170, 170, 200),
		sf::Color(255, 255, 255, 255),
		sf::Color(20, 20, 20, 200),
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 100));

	Buttons["Load_Game"] = new Button(x, y + spacing, 150, 50, &Font,
		"Load Game", 20,
		sf::Color(170, 170, 170, 200),
		sf::Color(255, 255, 255, 255),
		sf::Color(20, 20, 20, 200),
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 100));

	Buttons["Editor"] = new Button(x, y + spacing * 2, 150, 50, &Font,
		"Editor", 20,
		sf::Color(170, 170, 170, 200),
		sf::Color(255, 255, 255, 255),
		sf::Color(20, 20, 20, 200),
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 100));

	Buttons["Settings"] = new Button(x, y + spacing * 3, 150, 50, &Font,
		"Settings", 20,
		sf::Color(140, 140, 140, 200),
		sf::Color(255, 255, 255, 255),
		sf::Color(20, 20, 20, 200),
		sf::Color(50, 50, 50, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 100));

	Buttons["Exit_Game"] = new Button(x, y + spacing * 5, 150, 50, &Font,
		"Exit Game", 20,
		sf::Color(140, 140, 140, 200),
		sf::Color(255, 255, 255, 255),
		sf::Color(20, 20, 20, 200),
		sf::Color(100, 40, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 100));
}

void MainMenuState::InitFonts()
{
	if (!Font.openFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw std::runtime_error("Could not load font!");
	}
}

void MainMenuState::InitKeyBindings()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");

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
		KeyBindings["MOVE_LEFT"] = SupportedKeys->at("A");
		KeyBindings["MOVE_RIGHT"] = SupportedKeys->at("D");
		KeyBindings["MOVE_UP"] = SupportedKeys->at("W");
		KeyBindings["MOVE_DOWN"] = SupportedKeys->at("S");
	}
}

void MainMenuState::ViewMouseLocation()
{
	sf::Text mouseText = sf::Text(Font);
	mouseText.setPosition(MousePosView + sf::Vector2f(20, 10));
	mouseText.setCharacterSize(12);
	mouseText.setFillColor(sf::Color::White);
	mouseText.setString("X: " + std::to_string((int)MousePosView.x) +
		" Y: " + std::to_string((int)MousePosView.y));

	Window->draw(mouseText);
}
