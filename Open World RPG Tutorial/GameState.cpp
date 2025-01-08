#include "GameState.h"

GameState::GameState(sf::RenderWindow* window,
	std::map<std::string, int>* supportedKeys,
	std::stack<State*>* states) : State(window, supportedKeys, states)
{
	InitKeyBindings();
	InitTextures();
	InitPlayer();
}

GameState::~GameState()
{
	delete Player;
}

void GameState::UpdateInput(const float& dt)
{
	CheckForClose();
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
	UpdateInput(dt);

	Player->Update(dt);
}

void GameState::Render(sf::RenderTarget* target)
{
	if (!target) target = Window;

	Player->Render(target);
}

void GameState::EndState()
{
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