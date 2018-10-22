#include "IntroState.hpp"
#include "StateMachine.hpp"
#include "PlayState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

IntroState::IntroState(StateMachine& machine, sf::RenderWindow& window, bool replace)
	: State(machine, window, replace)
{
	if(!m_backgroundTex.loadFromFile("assets/sencan.png"))
	{
		std::cout << "\"assets/sencan.png\" is not exsist\n";
	}
	else
	{
		m_backgroundSprite.setTexture(m_backgroundTex);
		m_backgroundSprite.setScale(sf::Vector2f(0.3, 0.3));
		m_backgroundSprite.setOrigin(sf::Vector2f(m_backgroundTex.getSize().x / 2, m_backgroundTex.getSize().y / 2));
		m_backgroundSprite.setPosition(m_window.getSize().x / 2, m_window.getSize().y / 2 + m_backgroundTex.getSize().y / 30);
	}
}

void IntroState::pause()
{

}

void IntroState::resume()
{

}

void IntroState::update()
{
	if (m_clock.getElapsedTime().asSeconds() >= 3)
		m_next = StateMachine::build<PlayState>(m_machine, m_window);
}

void IntroState::draw()
{
	m_window.clear(sf::Color::White);

	m_window.draw(m_backgroundSprite);

	m_window.display();
}