#pragma once 

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include <fstream>
#include <direct.h>

struct Cell{
	sf::RectangleShape shape;
	sf::Text text;
	sf::Font font;
	int num = 0;

	static bool Serialization(Cell* cell, std::string name);
	static Cell* Deserialization(std::string name);
};

inline bool Cell::Serialization(Cell* cell, std::string name)
{
	std::ofstream file("Saves/" + name, std::ios::binary);

	if (!file.is_open())
	{
		mkdir("Saves");
		file.open("Saves/" + name, std::ios::binary);
	}

	if(file.is_open())
	{
		file.write(reinterpret_cast<char*>(&cell), sizeof(cell));
		file.close();

		return true;
	}

	return false;
}

inline Cell* Cell::Deserialization(std::string name)
{
	if (_chdir("Saves") == -1)
	{
		_mkdir("Saves");
		_chdir("Saves");
	}

	std::ifstream file(name, std::ios::binary);
	Cell temp;

	if(file.is_open())
	{
		file.read(reinterpret_cast<char*>(&temp), sizeof(temp));
		file.close();
		_chdir("..");

		return &temp;
	}

	return nullptr;
}

