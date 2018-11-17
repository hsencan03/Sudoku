#include "Cell.hpp"

#include <fstream>
#include <direct.h>

bool Cell::Serialization(Cell* cell, std::string name)
{
	std::ofstream file("Saves/" + name + ".txt");

	if (!file.is_open())
	{
		_mkdir("Saves");
		file.open("Saves/" + name + ".txt");
	}

	if (file.is_open())
	{
		for (int x = 0; x < 9; x++)
		{
			for (int y = 0; y < 9; y++)
				file << cell[y * 9 + x].num << " ";

			file << std::endl;
		}

		file.close();

		return true;
	}
	return false;
}

Cell* Cell::Deserialization(std::string name)
{
	std::ifstream file("Saves/" + name + ".txt");

	if (!file.is_open())
	{
		_mkdir("Saves");
		return nullptr;
	}

	Cell* cell = new Cell[9 * 9];

	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			file >> cell[j * 9 + i].num;

	return cell;
}