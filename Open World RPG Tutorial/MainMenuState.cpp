#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, sf::Font& font,
	std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	 : State(window, font, supportedKeys, states)
{
	InitVariables();
	InitBackground();
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

	if (Buttons["Exit_Game"]->IsPressed()) EndState();

	if (Buttons["New_Game"]->IsPressed())
	{
		States->push(new GameState(Window, Font, SupportedKeys, States));
	}

	if (Buttons["Editor"]->IsPressed())
	{
		States->push(new EditorState(Window, Font, SupportedKeys, States));
	}

	if (Buttons["Settings"]->IsPressed())
	{
		States->push(new SettingsState(Window, Font, SupportedKeys, States));
	}
}

void MainMenuState::Update(const float& dt)
{
	UpdateMousePosition();
	UpdateInput(dt);
	UpdateButtons();
}

void MainMenuState::RenderButtons(sf::RenderTarget& target)
{
	for (const auto& button : Buttons) button.second->Render(target);

	//Turn on for debug.
	//ViewMouseLocation();
}

void MainMenuState::Render(sf::RenderTarget* target)
{
	if (!target) target = Window;

	target->draw(Background);

	RenderButtons(*target);
}

void MainMenuState::EndState()
{
	State::EndState();
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
	float spacing = 70.0f;
	sf::Vector2f position = sf::Vector2f(1000.0f, 300.0f);
	sf::Vector2f size = sf::Vector2f(150.0f, 50.0f);

	Buttons["New_Game"] = new Button(position, size, &Font,
		"New Game", 20,
		sf::Color(170, 170, 170, 200),
		sf::Color(255, 255, 255, 255),
		sf::Color(20, 20, 20, 200),
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 100));

	position.y += spacing;
	Buttons["Load_Game"] = new Button(position, size, &Font,
		"Load Game", 20,
		sf::Color(170, 170, 170, 200),
		sf::Color(255, 255, 255, 255),
		sf::Color(20, 20, 20, 200),
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 100));

	position.y += spacing;
	Buttons["Editor"] = new Button(position, size, &Font,
		"Editor", 20,
		sf::Color(170, 170, 170, 200),
		sf::Color(255, 255, 255, 255),
		sf::Color(20, 20, 20, 200),
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 100));

	position.y += spacing;
	Buttons["Settings"] = new Button(position, size, &Font,
		"Settings", 20,
		sf::Color(140, 140, 140, 200),
		sf::Color(255, 255, 255, 255),
		sf::Color(20, 20, 20, 200),
		sf::Color(50, 50, 50, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 100));

	position.y += spacing;
	Buttons["Exit_Game"] = new Button(position, size, &Font,
		"Exit Game", 20,
		sf::Color(140, 140, 140, 200),
		sf::Color(255, 255, 255, 255),
		sf::Color(20, 20, 20, 200),
		sf::Color(100, 40, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 100));
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