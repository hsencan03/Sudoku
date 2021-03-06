#pragma once

#include "State.hpp"
#include "SudokuSolver.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <set>

class PlayState : public State {
public:
	PlayState(StateMachine& machine, sf::RenderWindow& window, bool replace = true);

	void pause() override;
	void resume() override;

	void update() override;
	void draw() override;

private:
	void reset();

	void setColorOfMistakes(int row, int col, sf::Color color);

	void solve();

private:
	SudokuSolver solver;

	sf::Texture m_mainbgText;
	sf::Sprite m_mainbgSprite;

	sf::Texture m_pauseText;
	sf::Sprite m_pauseSprite;

	sf::Texture m_resetText;
	sf::Sprite m_resetSprite;

	bool m_loadedFromFile;

	std::set<std::pair<int, int>> m_mistakes;

	bool m_done;
};