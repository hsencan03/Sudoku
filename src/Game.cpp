#include "Game.hpp"

void Game::run(unsigned int width, unsigned int height, unsigned int fps)
{
	m_window.create(sf::VideoMode{ width, height }, "SENCAN GAMES", sf::Style::Titlebar | sf::Style::Close);
	m_window.setFramerateLimit(fps);

	m_machine.run(StateMachine::build<IntroState>(m_machine, m_window, true));

	while (m_machine.running())
	{
		m_machine.nextState();
		m_machine.update();
		m_machine.draw();
	}
}