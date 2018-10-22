#include "PlayState.hpp"
#include "StateMachine.hpp"
#include "MenuState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <iostream>
#include <thread>
#include <unordered_map>

PlayState::PlayState(StateMachine& machine, sf::RenderWindow& window, bool replace)
	: State(machine, window, replace)
{
	if(!m_mainbgText.loadFromFile("assets/mainbg.png"))
	{
		std::cout << "\"assets/mainbg.png\" is not exsist\n";
	}
	else
	{
		m_mainbgSprite.setTexture(m_mainbgText);
	}

	if(!m_pauseText.loadFromFile("assets/pausebutton.png"))
	{
		std::cout << "\"assets/pausebutton.png\" is not exsist\n";
	}
	else
	{
		m_pauseSprite.setTexture(m_pauseText);
		m_pauseSprite.setOrigin(m_pauseText.getSize().x / 2, m_pauseText.getSize().y / 2);
		m_pauseSprite.setScale(0.1, 0.1);
		m_pauseSprite.setPosition(50.f, 50.f);
	}

	if (!m_resetText.loadFromFile("assets/resetbutton.png"))
	{
		std::cout << "\"assets / resetebutton.png\" is not exsist\n";
	}
	else
	{
		m_resetSprite.setTexture(m_resetText);
		m_resetSprite.setOrigin(m_resetText.getSize().x / 2, m_resetText.getSize().y / 2);
		m_resetSprite.setScale(0.03, 0.03);
		m_resetSprite.setPosition(m_window.getSize().x - 50.0f, 50.f);
	}

	cells = std::unique_ptr<Cell>(new Cell[ROW * COL]);

	for (int x = 0; x < ROW; x++)
	{
		for (int y = 0; y < COL; y++)
		{
			auto& cell = cells.get()[y * ROW + x];

			cell.shape.setSize(sf::Vector2f(m_window.getSize().x / 15, m_window.getSize().y / 15));
			cell.shape.setOrigin(sf::Vector2f(cell.shape.getSize().x / 2, cell.shape.getSize().y / 2));
			cell.shape.setPosition(sf::Vector2f((m_window.getSize().x / 4) + (cell.shape.getSize().x) * x, (m_window.getSize().y / 4) + (cell.shape.getSize().y) * y));
			
			if (x % 3 == 0)
				cell.shape.setPosition(sf::Vector2f(cell.shape.getPosition().x + 3.f, cell.shape.getPosition().y));
			if (y % 3 == 0)
				cell.shape.setPosition(sf::Vector2f(cell.shape.getPosition().x, cell.shape.getPosition().y + 3.f));

			cell.shape.setOutlineThickness(1.f);
			cell.shape.setOutlineColor(sf::Color::Black);

			cell.font.loadFromFile("assets/arial.ttf");

			cell.text = sf::Text("0", cell.font);
			cell.text.setCharacterSize(15);
			cell.text.setPosition(cell.shape.getPosition());
			cell.text.setOrigin(cell.text.getCharacterSize() / 2, cell.text.getCharacterSize() / 2);
			cell.text.setFillColor(sf::Color::Black);
		}
	}
}

void PlayState::pause()
{

}

void PlayState::resume()
{

}

void PlayState::update()
{
	sf::Event event;
	while(m_window.pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed) 
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				m_next = StateMachine::build<MenuState>(m_machine, m_window, false);
				break;
			default:
				break;
			}
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			sf::Vector2i pixelPos = sf::Mouse::getPosition(m_window);
			sf::Vector2f worldPos = m_window.mapPixelToCoords(pixelPos);

			if (m_pauseSprite.getGlobalBounds().contains(worldPos))
				m_next = StateMachine::build<MenuState>(m_machine, m_window, false);
			else if (m_resetSprite.getGlobalBounds().contains(worldPos))
				reset();
			
			for (int x = 0; x < ROW; x++)
			{
				for (int y = 0; y < COL; y++)
				{
					if (cells.get()[y * ROW + x].shape.getGlobalBounds().contains(worldPos))
					{
						int value = cells.get()[y * ROW + x].num;

						if (++value == 10)
							value = 0;
						cells.get()[y * ROW + x].num = value;
						cells.get()[y * ROW + x].text.setString(std::to_string(value));
						solver.set(x, y, value);

						//THREADING
						std::thread([&]()
						{
							solver.Solve();
						}).detach();


						std::this_thread::sleep_for(std::chrono::milliseconds(50));
						solver.stop();							

						//Print
						solver.print();
						if (solver.getStatus())
						{
							std::cout << "\ntrue";
							for (int i = 0; i < ROW * COL; i++)
								cells.get()[i].text.setFillColor(sf::Color::Black);
						}
						else
						{
							std::cout << "\nfalse";
							setColorOfMistakes(x, y, sf::Color::Red);
						}
					}
				}
			}
		}
	}
}

void PlayState::draw()
{
	m_window.clear();

	m_window.draw(m_mainbgSprite);

	for (int i = 0; i < ROW * COL; i++)
	{
		m_window.draw(cells.get()[i].shape);
		m_window.draw(cells.get()[i].text);
	}

	m_window.draw(m_pauseSprite);

	m_window.draw(m_resetSprite);
	
	m_window.display();
}

void PlayState::reset()
{
	for (int i = 0; i < ROW * COL; i++)
	{
		cells.get()[i].num = 0;
		cells.get()[i].text.setString("0");
		cells.get()[i].text.setFillColor(sf::Color::Black);
	}

	solver = SudokuSolver();
	solver.print();
}


void PlayState::setColorOfMistakes(int row, int column, sf::Color color)
{
	std::unordered_multimap<int, std::pair<int, int>> nums;

	for (int x = 0; x < ROW / 3; x++)
	{
		for (int y = 0; y < COL / 3; y++)
		{
			nums.insert(std::make_pair(cells.get()[(column - column % 3 + y) * ROW + (row - row % 3 + x)].num, std::make_pair((row - row % 3 + x), (column - column % 3 + y))));
		}
	}

	for (int x = 0; x < ROW; x++)
	{
		if (nums.find(cells.get()[column * ROW + x].num) != nums.end() && nums.find(cells.get()[column * ROW + x].num)->second != std::make_pair(x, column))
			nums.insert(std::make_pair(cells.get()[column * ROW + x].num, std::make_pair(x, column)));
	}

	for (int y = 0; y < COL; y++)
	{
		if(nums.find(cells.get()[y * ROW + row].num) != nums.end() && nums.find(cells.get()[y * ROW + row].num)->second != std::make_pair(row, y))
			nums.insert(std::make_pair(cells.get()[y * ROW + row].num, std::make_pair(row, y)));
	}

	for(auto i = nums.begin(); i != nums.end(); i++)
	{
		if (i->first != 0 && nums.count(i->first) > 1)
			cells.get()[i->second.second * ROW + i->second.first].text.setFillColor(color);
		else
			cells.get()[i->second.second * ROW + i->second.first].text.setFillColor(sf::Color::Black);
	} 
}
