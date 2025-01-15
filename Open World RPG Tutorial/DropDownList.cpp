#include "DropDownList.h"

DropDownList::DropDownList(sf::Vector2f position, sf::Vector2f size,
	sf::Font& font, std::string list[], unsigned numberOfElements,
	unsigned default_index)
	: Font(font)
{

	for (size_t i = 0; i < numberOfElements; i++)
	{
		float y = position.y + (i + 1) * size.y;

		List.push_back(new Button(sf::Vector2f(position.x, y), size,
			&Font, list[i], 12,
			sf::Color(255, 255, 255, 1500), sf::Color(250, 250, 250, 250),
			sf::Color(20, 20, 20, 50), sf::Color(70, 70, 70, 200),
			sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200)));
	}

	ActiveElement = new Button(*List[default_index]);
	ActiveElement->SetPosition(position);

	KeyTime = KeyTimeMax;
}

DropDownList::~DropDownList()
{
	for (int i = 0; i < List.size(); i++) delete List[i];

	if (ActiveElement) delete ActiveElement;
}

void DropDownList::UpdateKeytime(const float& dt)
{
	KeyTime += dt;
}

void DropDownList::Update(const sf::Vector2f& mousePos, const float& dt)
{
	UpdateKeytime(dt);

	if (ActiveElement->IsPressed()) if (GetKeyTime()) ShowList = !ShowList;

	if (ShowList)
	{
		for (const auto& button : List)
		{
			button->Update(mousePos);

			if (button->IsPressed())
			{
				sf::Vector2f position = ActiveElement->GetPosition();
				delete ActiveElement;
				ActiveElement = new Button(*button);
				ActiveElement->SetPosition(position);
				ShowList = false;
			}
		}
	}

	ActiveElement->Update(mousePos);
}

void DropDownList::Render(sf::RenderTarget& target)
{
	if (ShowList) for (const auto& button : List) button->Render(target);

	ActiveElement->Render(target);
}

const Button* DropDownList::GetActiveElement() const
{
	return ActiveElement;
}

const bool DropDownList::GetKeyTime()
{
	if (KeyTime > KeyTimeMax)
	{
		KeyTime = 0.0f;
		return true;
	}

	return false;
}
