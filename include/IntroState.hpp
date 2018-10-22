#pragma once

#include "State.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>


class IntroState : public State {
public:
	IntroState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);

	void pause() override;
	void resume() override;

	void update() override;
	void draw() override;

private:
	sf::Texture m_backgroundTex;
	sf::Sprite m_backgroundSprite;

	sf::Clock m_clock;
};
