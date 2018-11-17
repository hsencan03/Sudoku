#pragma once 

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

struct Cell{
	sf::RectangleShape shape;
	sf::Text text;
	sf::Font font;
	int num = 0;

	static bool Serialization(Cell* cell, std::string name);
	static Cell* Deserialization(std::string name);
};
