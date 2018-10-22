#pragma once

#include "State.hpp"
#include "PlayState.hpp"

#include <SFML/Graphics/Sprite.hpp>


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
};
