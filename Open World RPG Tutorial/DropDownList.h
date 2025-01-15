#pragma once
#include "SFMLHeaders.h"
#include "Button.h"
#include <vector>

class DropDownList
{
public:
	DropDownList(sf::Vector2f position, sf::Vector2f size, sf::Font& font,
		std::string list[], unsigned numberOfElements,
		unsigned default_index = 0);
	virtual ~DropDownList();

	void UpdateKeytime(const float& dt);
	void Update(const sf::Vector2f& mousePos, const float& dt);
	void Render(sf::RenderTarget& target);

	const Button *GetActiveElement() const;
	const bool GetKeyTime();

private:
	bool ShowList = false;
	float KeyTime = 0.0f;
	float KeyTimeMax = 0.25f;

	sf::Font& Font;
	Button* ActiveElement = nullptr;
	std::vector<Button*> List;
};