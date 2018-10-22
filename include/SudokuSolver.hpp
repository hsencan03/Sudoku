#pragma once

#include <utility>
#include <future>
enum
{
	UNASSIGNED = 0,
	ROW = 9,
	COL = 9
};

class SudokuSolver {
public:
	SudokuSolver();

	void Solve();

	void stop();
	
	void set(int row, int column, int num);

	int get(int row, int column) const;

	bool getStatus() const;

	void print();

private:
	bool solve();

	bool isSafe(int row, int column, int num);

	std::pair<int,int> FindUnassignedCell();
private:
	int grid[ROW * COL];
	int m_temp[ROW * COL];

	bool m_status;

	std::promise<void> m_exit;
	std::future<void> m_future;
};