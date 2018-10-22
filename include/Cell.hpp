#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

struct Cell
{
	sf::RectangleShape shape;
	sf::Text text;
	sf::Font font;
	int num = 0;
};