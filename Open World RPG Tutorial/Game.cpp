#include "Game.h"

Game::Game()
{
	InitFonts();
	InitWindow();
	InitKeys();
	InitStates();
}

Game::~Game()
{
	delete Window;

	while (!States.empty())
	{
		delete States.top();
		States.pop();
	}
}

void Game::UpdateDT()
{
	DTime = DTClock.restart().asSeconds();

	if (DTime > 0.1f)
		DTime = 0.1f;
}

void Game::UpdateSFMLEvents()
{
	while (const std::optional event = Window->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
			Window->close();
	}
}

void Game::Update()
{
	if (States.top()->GetQuit())
	{
		States.top()->EndState();
		delete States.top();
		States.pop();
	}

	if (!States.empty()) States.top()->Update(DTime);
	else
	{
		EndGame();
		Window->close();
	}
}

void Game::Render()
{
	Window->clear();

	if (!States.empty()) States.top()->Render(Window);

	Window->display();
}

void Game::Run()
{
	while (Window->isOpen())
	{
		UpdateSFMLEvents();
		UpdateDT();
		Update();
		Render();
	}
}

void Game::InitVariables()
{
}

void Game::InitWindow()
{
	std::ifstream ifs("Config/window.ini");

	VideoModes = sf::VideoMode::getFullscreenModes();

	std::string title = "Default";
	sf::VideoMode window_bounds(sf::VideoMode::getDesktopMode());
	unsigned framerate_limit = 60;
	bool vertical_sync_enabled = false;
	bool fullscreen = false;
	unsigned anti_aliasing_level = 0;

	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> window_bounds.size.x >> window_bounds.size.y;
		ifs >> fullscreen;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enabled;
		ifs >> anti_aliasing_level;
	}

	ifs.close();

	sf::ContextSettings window_settings;

	window_settings.antiAliasingLevel = anti_aliasing_level;

	Window = new sf::RenderWindow(window_bounds, title);
	Window->setFramerateLimit(framerate_limit);
	Window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::InitStates()
{
	States.push(new GameState(Window, Font, &SupportedKeys, &States));
	//States.push(new MainMenuState(Window, Font, &SupportedKeys, &States));
}

void Game::InitKeys()
{
	std::ifstream ifs("Config/supported_keys.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		int value = 0;

		while (ifs >> key >> value)
		{
			SupportedKeys[key] = value;
		}

		ifs.close();
	}
	else
	{
		SupportedKeys["Escape"] = (int)sf::Keyboard::Key::Escape;
		SupportedKeys["PAUSE"] = (int)sf::Keyboard::Key::P;
		SupportedKeys["W"] = (int)sf::Keyboard::Key::W;
		SupportedKeys["A"] = (int)sf::Keyboard::Key::A;
		SupportedKeys["S"] = (int)sf::Keyboard::Key::S;
		SupportedKeys["D"] = (int)sf::Keyboard::Key::D;
	}
}

void Game::InitFonts()
{
	if (!Font.openFromFile("Fonts/Dosis-Light.ttf"))
	{
		throw std::runtime_error("Could not load font!");
	}
}

void Game::EndGame()
{
}
