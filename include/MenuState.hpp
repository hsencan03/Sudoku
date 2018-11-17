#pragma once

#include "State.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>


class MenuState : public State {
public:
	MenuState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);

	void pause() override;
	void resume() override;

	void update() override;
	void draw() override;

private:
	sf::Texture m_mainbgText;
	sf::Sprite m_mainbgSprite;

	sf::Texture m_playText;
	sf::Sprite m_playSprite;

	sf::Font m_menuFont;

	sf::RectangleShape m_exitButton;
	sf::Text m_exitText;
};
