#include "SudokuSolver.hpp"

#include <iostream>
#include <ctime>

SudokuSolver::SudokuSolver()
{
	for (int i = 0; i < ROW * COL; i++)
	{
		grid[i] = UNASSIGNED;
		m_temp[i] = UNASSIGNED;
	}

	std::srand(std::time(nullptr));
}

bool SudokuSolver::Solve()
{
	m_solveCount = 0;
	return solve();
}

void SudokuSolver::set(int row, int column, int num)
{
	grid[column * ROW + row] = num;

	for (int i = 0; i < ROW * COL; i++)
		m_temp[i] = grid[i];
}

int SudokuSolver::get(int row, int column) const
{
	return grid[column * ROW + row];
}

int* SudokuSolver::getSolvedCell()
{
	return m_temp;
}

void SudokuSolver::print()
{
	system("cls");

	for (int y = 0; y < COL; y++)
	{
		if (y % 3 == 0)
			std::cout << "------------------------------\n";

		for (int x = 0; x < ROW; x++)
		{
			if (x % 3 == 0)
				std::cout << "|";

			std::cout << " " << grid[y * ROW + x] << " ";
		}

		std::cout << "|\n";
	}
	std::cout << "------------------------------\n";
}

bool SudokuSolver::solve()
{
	if (++m_solveCount > 10000)
		return false;

	std::pair<int, int> cell = FindUnassignedCell();

	if (cell.first == -1)
		return true;

	for (int i = 0; i < 9; i++)
	{
		int num = std::rand() % 9 + 1;

		if (isSafe(cell.first, cell.second, num))
		{
			m_temp[cell.second * ROW + cell.first] = num;

			if (solve())
				return true;

			m_temp[cell.second * ROW + cell.first] = UNASSIGNED;
		}
	}
	return false;
}


bool SudokuSolver::isSafe(int row, int column, int num)
{
	//Check ROW
	for (int x = 0; x < ROW; x++)
	{
		if (m_temp[column * ROW + x] == num)
			return false;
	}
	//Check COLUMN
	for (int y = 0; y < COL; y++)
	{
		if (m_temp[y * ROW + row] == num)
			return false;
	}
	//Check BOX
	for (int x = 0; x < ROW / 3; x++)
	{
		for (int y = 0; y < COL / 3; y++)
		{
			if (m_temp[(column - column % 3 + y) * ROW + (row - row % 3 + x)] == num)
				return false;
		}
	}

	return true;
}

std::pair<int, int> SudokuSolver::FindUnassignedCell()
{
	for (int x = 0; x < ROW; x++)
	{
		for (int y = 0; y < COL; y++)
		{
			if (m_temp[y * ROW + x] == UNASSIGNED)
				return std::make_pair(x, y);
		}
	}

	return std::make_pair(-1, -1);
}