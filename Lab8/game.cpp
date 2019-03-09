/// <summary>
/// Author: Ben Millar – C00236772
/// Date: 28/02/2019
/// Estimated time to complete: 12 hours
/// Session 1 Start: 22:50 End: 23:10 02/03/2019
/// </summary>

#include "Game.h"
#include <iostream>


Game::Game() :
	m_window{ sf::VideoMode{ 1000, 600 }, "SMFL Game" },
	m_triangle{ sf::Triangles },
	m_quad{ sf::Quads }
	{
		setupShapes();
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
/// 
/// </summary>
void Game::setupShapes()
{
	m_triangleShape[0].init_A = { 100.0,150.0, 1.0 }, // triangle 1
	m_triangleShape[0].init_B = { 200.0,250.0, 1.0 },
	m_triangleShape[0].init_C = { 300.0,150.0, 1.0 },
	m_triangleShape[0].color = sf::Color::Cyan;

	m_triangleShape[1].init_A = { 300.0,150.0, 1.0 }, // triangle 2
	m_triangleShape[1].init_B = { 200.0,250.0, 1.0 },
	m_triangleShape[1].init_C = { 300.0,350.0, 1.0 },
	m_triangleShape[1].color = sf::Color::Yellow;

	m_triangleShape[2].init_A = { 300.0,350.0, 1.0 }, // triangle 3
	m_triangleShape[2].init_B = { 200.0,350.0, 1.0 },
	m_triangleShape[2].init_C = { 250.0,300.0, 1.0 },
	m_triangleShape[2].color = sf::Color::Red;

	m_triangleShape[3].init_A = { 200.0,350.0, 1.0 }, // triangle 4
	m_triangleShape[3].init_B = { 100.0,350.0, 1.0 },
	m_triangleShape[3].init_C = { 100.0,250.0, 1.0 },
	m_triangleShape[3].color = sf::Color::Magenta;

	m_triangleShape[4].init_A = { 150.0,300.0, 1.0 }, // triangle 5
	m_triangleShape[4].init_B = { 200.0,250.0, 1.0 },
	m_triangleShape[4].init_C = { 150.0,200.0, 1.0 },
	m_triangleShape[4].color = sf::Color::Green;

	m_quadShape[0].init_A = { 150.0,200.0, 1.0 }, // quad 1
	m_quadShape[0].init_B = { 100.0,150.0, 1.0 },
	m_quadShape[0].init_C = { 100.0,250.0, 1.0 },
	m_quadShape[0].init_D = { 150.0,300.0, 1.0 },
	m_quadShape[0].color = sf::Color::Blue;

	m_quadShape[1].init_A = { 150.0,300.0, 1.0 }, // quad 2
	m_quadShape[1].init_B = { 200.0,350.0, 1.0 },
	m_quadShape[1].init_C = { 250.0,300.0, 1.0 },
	m_quadShape[1].init_D = { 200.0,250.0, 1.0 },
	m_quadShape[1].color = CORNFLOWER_BLUE;
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
			MyVector3 originalPos = m_shapePoints[i];
			MyMatrix3 transformation = MyMatrix3::translation(-originalPos);
			m_shapePoints[i] = transformation * m_shapePoints[i];

			// I'm moving each point to the origin
			std::cout << "Original: " << originalPos.toString() << std::endl;
			std::cout << "Transformation: " << transformation.toString() << std::endl;
			std::cout << "New pos: " << m_shapePoints[i].toString() << std::endl;
			//MyMatrix3::rotationZ(3.14159 / 180.0)
			//m_shapePoints[i] = MyMatrix3::translation(originalPos) * originalPos;
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
	m_quad.clear();
	for (int i = 0, j = 0; i < 5; i++)
	{
		m_renderPoints[j] = { m_triangleShape[i].current_A, m_triangleShape[i].color };
		m_triangle.append(m_renderPoints[j]);
		j++;
		m_renderPoints[j] = { m_triangleShape[i].current_B, m_triangleShape[i].color };
		m_triangle.append(m_renderPoints[j]);
		j++;
		m_renderPoints[j] = { m_triangleShape[i].current_C, m_triangleShape[i].color };
		m_triangle.append(m_renderPoints[j]);
		j++;
	}
	//for (int i = 0; i < NO_POINTS; i++)
	//{
	//	if (i >= 15)
	//	{
	//		m_renderPoints[i] = { m_triangleShape[i].current_A, m_triangleShape[i].color };
	//		m_quad.append(m_renderPoints[i]);
	//	}
	//	else
	//	{
	//		m_renderPoints[i].position = m_shapePoints[i];  // we could go straight from vector + colour
	//		m_triangle.append(m_renderPoints[i]); // Pete didn't
	//	}
	//}
}


/// <summary>
/// draw the screen just a 
/// </summary>
void Game::render()
{
	m_window.clear();
	m_window.draw(m_triangle);
	m_window.draw(m_quad);
	m_window.display();
}