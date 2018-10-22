#pragma once

#include "StateMachine.hpp"
#include "IntroState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

class Game {
public:
	Game() = default;

	void run(unsigned int width, unsigned int height, unsigned int fps = 30);

private:
	StateMachine m_machine;
	sf::RenderWindow m_window;
};