/// <summary>
/// Author: Ben Millar – C00236772
/// Date: 28/02/2019
/// Estimated time to complete: 12 hours
/// Session 1 Start: 22:50 End: 23:10 02/03/2019
/// </summary>

#include "Game.h"
#include <iostream>


Game::Game() :
	m_window{ sf::VideoMode{ 800, 480 }, "SMFL Game" },
	m_triangle{ sf::Triangles },
	m_quad{ sf::Quads },
	m_shapePoints{
		 { 100.0,150.0, 1.0 },  // initial positions for triangle
		 { 100.0,350.0, 1.0 },
		 { 300.0,350.0, 1.0 },
		 { 400.0,150.0, 1.0 },  // initial positions for second triangle
		 { 400.0,350.0, 1.0 },
		 { 600.0,350.0, 1.0 }
}

{
	for (size_t i = 0; i < 6; i++)
	{
		if (i >= 3)
		{
			m_renderPoints[i] = sf::Vertex{ sf::Vector2f(m_shapePoints[i]),GRAY };
		}
		else
		{
			m_renderPoints[i] = sf::Vertex{ sf::Vector2f(m_shapePoints[i]),CORNFLOWER_BLUE };
		}
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
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				m_window.close();
			}
		}
	}
}

/// <summary>
/// respond to keyinputs and update vertex array to new vector popsitions
/// </summary>
/// <param name="t_deltaTime">frame time</param>
void Game::update(sf::Time t_deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		for (int i = 0; i < 3; i++)
		{
			m_shapePoints[i] = MyMatrix3::translation({ 0.0,-1.0,0.0 }) * m_shapePoints[i];
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		for (int i = 0; i < 3; i++)
		{
			m_shapePoints[i] = MyMatrix3::translation({ 0.0,1.0,0.0 }) * m_shapePoints[i];
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		for (int i = 0; i < 3; i++)
		{
			m_shapePoints[i] = MyMatrix3::translation({ -1.0,0.0,0.0 }) * m_shapePoints[i];
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		for (int i = 0; i < 3; i++)
		{
			m_shapePoints[i] = MyMatrix3::translation({ 1.0,0.0,0.0 }) * m_shapePoints[i];
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		for (int i = 0; i < 3; i++)
		{
			m_shapePoints[i] = MyMatrix3::rotationZ(3.14159 / 180.0) * m_shapePoints[i];
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		for (int i = 0; i < 3; i++)
		{
			m_shapePoints[i] = MyMatrix3::rotationZ(-3.14159 / 180.0) * m_shapePoints[i];
		}
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