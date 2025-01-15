#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, sf::Font& font,
	std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	 : State(window, font, supportedKeys, states), ThePauseMenu(*window, font)
{
	InitKeyBindings();
	InitTextures();
	InitPlayer();
	InitPauseMenu();

	Map = new TileMap();
}

GameState::~GameState()
{
	delete Player;
	delete Map;
}

void GameState::UpdatePauseMenuButtons()
{
	if (ThePauseMenu.IsButtonPressed("Quit"))
	{
		EndState();
	}
}

void GameState::UpdatePauseInput()
{
	UpdatePause();
	CheckForClose();
	Player->SetPaused(GetPaused());
}

void GameState::UpdateInput(const float& dt)
{
	UpdatePauseInput();
	Player->SetIdle();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(KeyBindings.at("MOVE_LEFT"))))
		Player->Move(sf::Vector2f(-1.f, 0.f), dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(KeyBindings.at("MOVE_RIGHT"))))
		Player->Move(sf::Vector2f(1.f, 0.f), dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(KeyBindings.at("MOVE_UP"))))
		Player->Move(sf::Vector2f(0.f, -1.f), dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(KeyBindings.at("MOVE_DOWN"))))
		Player->Move(sf::Vector2f(0.f, 1.f), dt);
}

void GameState::Update(const float& dt)
{
	UpdateMousePosition();
	UpdatePauseInput();
	UpdateTimer(dt);

	if (GetPaused())
	{
		ThePauseMenu.Update(MousePosView);
		UpdatePauseMenuButtons();
		return;
	}

	UpdateInput(dt);
	Player->Update(dt);
	Map->Update(dt);
}

void GameState::Render(sf::RenderTarget* target)
{
	if (!target) target = Window;

	Map->Render(*target);
	Player->Render(*target);

	if (GetPaused()) ThePauseMenu.Render(*target);
}

void GameState::EndState()
{
	State::EndState();
}

void GameState::EndStateUpdate()
{
}

void GameState::InitKeyBindings()
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
		KeyBindings["PAUSE"] = SupportedKeys->at("P");
		KeyBindings["MOVE_LEFT"] = SupportedKeys->at("A");
		KeyBindings["MOVE_RIGHT"] = SupportedKeys->at("D");
		KeyBindings["MOVE_UP"] = SupportedKeys->at("W");
		KeyBindings["MOVE_DOWN"] = SupportedKeys->at("S");
	}
}

void GameState::InitTextures()
{
	Textures["PLAYER_SHEET"].loadFromFile(
		"Resources/Images/Sprites/Player/PLAYER_SHEET2.png");

	//if (!Textures["PLAYER"].loadFromFile(
	//	"Resources/Images/Sprites/Player/Girl Knight.png"));
	//{
	//	throw "ERROR::GAMESTATE::INITTEXTURES::FAILED_TO_LOAD_PLAYER_TEXTURE";
	//	Window->close();
	//}
}

void GameState::InitPlayer()
{
	Player = new ThePlayer(sf::Vector2f(900.0f, 500.0f),
		Textures.at("PLAYER_SHEET"));
}

void GameState::InitPauseMenu()
{
	float center = Window->getSize().x / 2.0f;
	float hieght = 400.0f;
	float spacing = 70.0f;

	sf::Vector2f position = sf::Vector2f(center, 750.0f);

	ThePauseMenu.AddButton("Quit", position, "Quit");
}
