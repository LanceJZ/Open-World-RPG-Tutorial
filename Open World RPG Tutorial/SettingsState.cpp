#include "SettingsState.h"

SettingsState::SettingsState(sf::RenderWindow* window, sf::Font& font,
	std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	 : State(window, font, supportedKeys, states), Options(font)
{
	InitVariables();
	InitKeyBindings();
	InitBackground();
	InitButtons();
	InitText();
}

SettingsState::~SettingsState()
{
	auto button = Buttons.begin();

	while (button != Buttons.end())
	{
		delete button->second;
		++button;
	}

	auto list = DDList.begin();

	while (list != DDList.end())
	{
		delete list->second;
		++list;
	}
}

void SettingsState::UpdateButtons()
{
	for (const auto& button : Buttons) button.second->Update(MousePosView);

	if (Buttons["BACK"]->IsPressed()) EndState();

	if (Buttons["APPLY"]->IsPressed()) Apply();
}

void SettingsState::UpdateInput(const float& dt)
{
	CheckForClose();

}

void SettingsState::Update(const float& dt)
{
	UpdateMousePosition();
	UpdateInput(dt);
	UpdateButtons();

	for (const auto& list : DDList) list.second->Update(MousePosView, dt);
}

void SettingsState::Render(sf::RenderTarget* target)
{
	if (!target) target = Window;

	target->draw(Background);

	for (const auto& button : Buttons) button.second->Render(*target);

	for (const auto& list : DDList) list.second->Render(*target);

	target->draw(Options);

	//Turn on for debug.
	//ViewMouseLocation();
}

void SettingsState::EndState()
{
	State::EndState();
}

void SettingsState::InitVariables()
{
	VideoModes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::InitBackground()
{
	Background.setFillColor(sf::Color::Blue);
	Background.setSize((sf::Vector2f)Window->getSize());

	if (BackgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg1.png"))
	{
		Background.setTexture(&BackgroundTexture);
	}
	else throw std::runtime_error("Could not load background texture!");
}

void SettingsState::InitButtons()
{
	float spacing = 70.0f;
	sf::Vector2f position = sf::Vector2f(1000.0f, 300.0f);
	sf::Vector2f size = sf::Vector2f(150.0f, 50.0f);

	std::string list[] = {"1800x1200", "1440x1080", "800x600", "640x480"};
	size_t listSize = sizeof(list) / sizeof(list[0]);

	DDList["RESULUTION"] = new DropDownList(position,
		sf::Vector2f(200.0f, 50.0f), Font, list, listSize);

	position.y += spacing * 4;
	Buttons["APPLY"] = new Button(position, size, &Font, "Apply", 20,
		sf::Color(240, 240, 240, 200), sf::Color(255, 255, 255, 255),
		sf::Color(120, 120, 120, 200), sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 100));

	position.y += spacing * 2;
	Buttons["BACK"] = new Button(position, size, &Font,	"Back", 20,
		sf::Color(140, 140, 140, 200), sf::Color(255, 255, 255, 255),
		sf::Color(120, 120, 120, 200),	sf::Color(100, 40, 70, 200),
		sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 100));
}

void SettingsState::InitKeyBindings()
{
	std::ifstream ifs("Config/settingsstate_keybinds.ini");

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

void SettingsState::InitText()
{
	Options.setCharacterSize(20);
	Options.setFillColor(sf::Color::White);
	Options.setPosition(sf::Vector2f(100.0f, 600.0f));

	Options.setString("Resolution \nFullscreen \nVsync \nAntialiasing \n");
}

void SettingsState::Apply()
{
}