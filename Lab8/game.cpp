// author Peter Lowe

#include "Game.h"
#include <iostream>



#include "Game.h"
#include <iostream>



Game::Game() :
	m_window{ sf::VideoMode{ 800, 480 }, "SMFL Game" },
	m_triangle{ sf::Triangles },
	m_shapePoints{
		 { 100.0,150.0, 1.0 },  // initial positions for triangle
		 { 100.0,350.0, 1.0 },
		 { 200.0,350.0, 1.0 },
		 { 300.0,150.0, 1.0 },  // initial positions for second triangle
		 { 300.0,350.0, 1.0 },
		 { 400.0,350.0, 1.0 }
}

{
	for (size_t i = 0; i < 3; i++)
	{
		m_renderPoints[i] = sf::Vertex{ sf::Vector2f(m_shapePoints[i]),CORNFLOWER_BLUE };
	}
	for (size_t i = 3; i < 6; i++)
	{
		m_renderPoints[i] = sf::Vertex{ sf::Vector2f(m_shapePoints[i]),GRAY };
	}
}

/// <summary>
/// Pete's game loop
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);
	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
		}
		render();
	}
}

/// <summary>
/// check for input
/// just quit
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if (newEvent.type == sf::Event::Closed)
		{
			m_window.close();
		}
	}
}

/// <summary>
/// respond to keyinputs and update vertex array to new vector popsitions
/// </summary>
/// <param name="t_deltaTime">frame time</param>
void Game::update(sf::Time t_deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		m_shapePoints[0] += {0.0, 1.2, 0.0};
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
	{
		m_shapePoints[1] += {1.0, 0.0, 0.0};
	}
	m_triangle.clear();
	for (int i = 0; i < NO_POINTS; i++)
	{
		m_renderPoints[i].position = m_shapePoints[i];  // we could go straight from vector + colour
		m_triangle.append(m_renderPoints[i]); // Pete didn't
	}
}


/// <summary>
/// draw the screen just a 
/// </summary>
void Game::render()
{
	m_window.clear();
	m_window.draw(m_triangle);
	m_window.display();
}