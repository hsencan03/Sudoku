#include "MenuState.hpp"
#include "StateMachine.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>

MenuState::MenuState(StateMachine& machine, sf::RenderWindow& window, bool replace)
	: State(machine, window, replace)
{
	if (!m_mainbgText.loadFromFile("assets/mainbg.png"))
	{
		std::cout << "\"assets/mainbg.png\" is not exsist\n";
	}
	else
	{
		m_mainbgSprite.setTexture(m_mainbgText);
	}

	if (!m_playText.loadFromFile("assets/playbutton.png"))
	{
		std::cout << "\"assets/playbutton.png\" is not exsist\n";
	}
	else
	{
		m_playSprite.setTexture(m_playText);
		m_playSprite.setOrigin(m_playText.getSize().x / 2, m_playText.getSize().y / 2);
		m_playSprite.setScale(0.1, 0.1);
		m_playSprite.setPosition(50.f, 50.f);
	}
}

void MenuState::pause()
{
	
}

void MenuState::resume()
{
	
}

void MenuState::update()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if(event.type == sf::Event::Closed)
			m_machine.quit();
		else if (event.type == sf::Event::MouseButtonPressed)
		{
			sf::Vector2i pixelPos = sf::Mouse::getPosition(m_window);
			sf::Vector2f worldPos = m_window.mapPixelToCoords(pixelPos);

			if (m_playSprite.getGlobalBounds().contains(worldPos))
				m_machine.lastState();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				m_machine.lastState();
				break;
			}
		}
	}
}

void MenuState::draw()
{
	m_window.clear();

	m_window.draw(m_mainbgSprite);

	m_window.draw(m_playSprite);

	m_window.display();
}


