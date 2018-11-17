#pragma once

#include <utility>

enum
{
	UNASSIGNED = 0,
	ROW = 9,
	COL = 9
};

class SudokuSolver {
public:
	SudokuSolver();

	bool Solve();
	
	void set(int row, int column, int num);

	int get(int row, int column) const;

	void print();

private:
	bool solve();

	bool isSafe(int row, int column, int num);

	std::pair<int,int> FindUnassignedCell();
private:
	int grid[ROW * COL];
	int m_temp[ROW * COL];

	//TODO FIND BETTER SOLUTION
	int m_solveCount;
};