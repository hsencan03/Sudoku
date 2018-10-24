#pragma once

#include <memory>
#include <stack>
#include <string>

#include "Cell.hpp"

class State;

namespace sf
{
	class RenderWindow;
}

class StateMachine {
public:
	StateMachine();

	void run(std::unique_ptr<State> state);

	void nextState();
	void lastState();

	void update();
	void draw();

	bool running() { return m_running; }
	void quit() { m_running = false; }

	template <typename T>
	static std::unique_ptr<T> build(StateMachine& machine, sf::RenderWindow& window, bool replace = true);

	std::unique_ptr<Cell> m_cells;

private:
	std::stack<std::unique_ptr<State>> m_states;

	bool m_resume;
	bool m_running;
};

template <typename T>
std::unique_ptr<T> StateMachine::build(StateMachine& machine, sf::RenderWindow& window, bool replace)
{
	return std::unique_ptr<T>(new T(machine, window, replace));
}
