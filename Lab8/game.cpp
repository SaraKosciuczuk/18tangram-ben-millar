/// <summary>
/// Author: Ben Millar – C00236772
/// Date: 28/02/2019
/// Estimated time to complete: 12 hours
/// Session 1 Start: 22:50 End: 23:10 
/// Session 2 Start: 14:00 End: 15:00
/// Session 3 Start: 09:00 End: 10:20 
/// Session 4 Start: 12:30 End: 13:20 
/// Session 5 Start: 12:20 End: 13:00
/// Session 6 Start: 21:55 End: 22:10
/// Session 7 Start: 23:00 End: 23:45 TOTAL TIME: 5 hours 10 minutes
/// </summary>

#include "Game.h"
#include <iostream>


Game::Game() :
	m_window{ sf::VideoMode{ 1000, 600 }, "SMFL Game" },
	m_triangle{ sf::Triangles },
	m_quad{ sf::Quads },
	M_INITIAL_POSITIONS{
		 { 100.0,150.0, 1.0 }, // triangle 1
		 { 200.0,250.0, 1.0 },
		 { 300.0,150.0, 1.0 },
		 { 300.0,150.0, 1.0 }, // triangle 2
		 { 200.0,250.0, 1.0 },
		 { 300.0,350.0, 1.0 },
		 { 300.0,350.0, 1.0 }, // triangle 3
		 { 200.0,350.0, 1.0 },
		 { 250.0,300.0, 1.0 },
	 	 { 200.0,350.0, 1.0 }, // triangle 4
	 	 { 100.0,350.0, 1.0 },
		 { 100.0,250.0, 1.0 },
		 { 150.0,300.0, 1.0 }, // triangle 5
		 { 200.0,250.0, 1.0 },
		 { 150.0,200.0, 1.0 },
		 { 150.0,200.0, 1.0 }, // quad 1
		 { 100.0,150.0, 1.0 },
		 { 100.0,250.0, 1.0 },
		 { 150.0,300.0, 1.0 },
		 { 150.0,300.0, 1.0 }, // quad 2
		 { 200.0,350.0, 1.0 },
		 { 250.0,300.0, 1.0 },
		 { 200.0,250.0, 1.0 }
}
{
	for (size_t i = 0; i < NO_POINTS; i++)
	{
		if (i >= 19)
		{
			m_renderPoints[i] = sf::Vertex{ sf::Vector2f(m_shapePoints[i]),sf::Color::Blue };
		}
		else if ( i >= 15 )
		{
			m_renderPoints[i] = sf::Vertex{ sf::Vector2f(m_shapePoints[i]),sf::Color::Cyan };
		}
		else if (i >= 12)
		{
			m_renderPoints[i] = sf::Vertex{ sf::Vector2f(m_shapePoints[i]),sf::Color::Magenta };
		}
		else if (i >= 9)
		{
			m_renderPoints[i] = sf::Vertex{ sf::Vector2f(m_shapePoints[i]),sf::Color::Yellow };
		}
		else if (i >= 6)
		{
			m_renderPoints[i] = sf::Vertex{ sf::Vector2f(m_shapePoints[i]),sf::Color::Green };
		}
		else if (i >= 3)
		{
			m_renderPoints[i] = sf::Vertex{ sf::Vector2f(m_shapePoints[i]),CORNFLOWER_BLUE };
		}
		else
		{
			m_renderPoints[i] = sf::Vertex{ sf::Vector2f(m_shapePoints[i]),sf::Color::Red };
		}
	}

	resetShapes();
	setupFontAndText();
	setupSprites();
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
/// Set up font and text for the game
/// </summary>
void Game::setupFontAndText()
{
	if (!m_arialBlackFont.loadFromFile("ASSETS//FONTS//ariblk.ttf"))
	{
		std::cout << "Error loading arial black font, located at ASSETS//FONTS//ariblk.ttf" << std::endl;
	}

	m_numberText.setFont(m_arialBlackFont);
	m_numberText.setFillColor(sf::Color::White);
	m_numberText.setCharacterSize(18U);

}

/// <summary>
/// Set up all sprites for the game
/// </summary>
void Game::setupSprites()
{
	if (!m_puzzleTextures[0].loadFromFile("ASSETS//IMAGES//PUZZLE1.png"))
	{
		std::cout << "Error loading PUZZLE1 texture, located at ASSETS//IMAGES//PUZZLE1.png";
	}

	if (!m_puzzleTextures[1].loadFromFile("ASSETS//IMAGES//PUZZLE2.png"))
	{
		std::cout << "Error loading PUZZLE2 texture, located at ASSETS//IMAGES//PUZZLE2.png";
	}

	if (!m_puzzleTextures[2].loadFromFile("ASSETS//IMAGES//PUZZLE3.png"))
	{
		std::cout << "Error loading PUZZLE3 texture, located at ASSETS//IMAGES//PUZZLE3.png";
	}

	if (!m_puzzleTextures[3].loadFromFile("ASSETS//IMAGES//PUZZLE4.png"))
	{
		std::cout << "Error loading PUZZLE4 texture, located at ASSETS//IMAGES//PUZZLE4.png";
	}

	for (int i = 0; i < NO_PUZZLES; i++)
	{
		m_puzzleSprites[i].setTexture(m_puzzleTextures[i]);
		m_puzzleSprites[i].setPosition({ 500.0f,130.0f });
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

			switch (event.key.code)
			{
			case sf::Keyboard::Num1:
				m_startRange = 0, m_endRange = 3;
				break;
			case sf::Keyboard::Num2:
				m_startRange = 3, m_endRange = 6;
				break;
			case sf::Keyboard::Num3:
				m_startRange = 6, m_endRange = 9;
				break;
			case sf::Keyboard::Num4:
				m_startRange = 9, m_endRange = 12;
				break;
			case sf::Keyboard::Num5:
				m_startRange = 12, m_endRange = 15;
				break;
			case sf::Keyboard::Num6:
				m_startRange = 15, m_endRange = 19;
				break;
			case sf::Keyboard::Num7:
				m_startRange = 19, m_endRange = 23;
				break;
			default:
				break;
			}
		}

		if (event.type == sf::Event::KeyReleased)
		{
			switch(event.key.code)
			{
			case sf::Keyboard::R:
				resetShapes();
				break;
			default:
				break;
			}
		}
	}
}

/// <summary>
/// Reset the pieces to their initial positions
/// </summary>
void Game::resetShapes()
{
	for (int i = 0; i < NO_POINTS; i++)
	{
		m_shapePoints[i] = M_INITIAL_POSITIONS[i];
	}
}

/// <summary>
/// respond to keyinputs and update vertex array to new vector positions
/// </summary>
/// <param name="t_deltaTime">frame time</param>
void Game::update(sf::Time t_deltaTime)
{
	// ++++++++++ TAKE USER INPUT ++++++++++

	// +++++++ SPEED UP MOVEMENT +++++++
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
	{
		m_moveSpeed = 3.0f;
	}
	else
	{
		m_moveSpeed = 1.0f;
	}

	// +++++++ MOVE PIECE UP +++++++
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		for (unsigned i = m_startRange; i < m_endRange; i++)
		{
			m_shapePoints[i] = MyMatrix3::translation({ 0.0,-m_moveSpeed,0.0 }) * m_shapePoints[i];
		}
	}


	// +++++++ MOVE PIECE DOWN +++++++
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		for (unsigned i = m_startRange; i < m_endRange; i++)
		{
			m_shapePoints[i] = MyMatrix3::translation({ 0.0,m_moveSpeed,0.0 }) * m_shapePoints[i];
		}
	}


	// +++++++ MOVE PIECE LEFT +++++++
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		for (unsigned i = m_startRange; i < m_endRange; i++)
		{
			m_shapePoints[i] = MyMatrix3::translation({ -m_moveSpeed,0.0,0.0 }) * m_shapePoints[i];
		}
	}


	// +++++++ MOVE PIECE RIGHT +++++++
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		for (unsigned i = m_startRange; i < m_endRange; i++)
		{
			m_shapePoints[i] = MyMatrix3::translation({ m_moveSpeed,0.0,0.0 }) * m_shapePoints[i];
		}
	}


	// +++++++ ROTATE PIECE CLOCKWISE +++++++
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		MyVector3 center = Game::findCenter(m_shapePoints, m_startRange, m_endRange);
		MyMatrix3 rotation = Game::rotate(center, counterclockwise);

		for (unsigned i = m_startRange; i < m_endRange; i++)
		{
			m_shapePoints[i] = rotation * m_shapePoints[i];
		}
	}


	// +++++++ ROTATE PIECE ANTICLOCKWISE +++++++
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		MyVector3 center = Game::findCenter(m_shapePoints, m_startRange, m_endRange);
		MyMatrix3 rotation = Game::rotate(center, clockwise);
		
		for (unsigned i = m_startRange; i < m_endRange; i++)
		{
			m_shapePoints[i] = rotation * m_shapePoints[i];
		}
	}

	// ++++++++++ END USER INPUT ++++++++++


	m_triangle.clear();
	m_quad.clear();
	for (unsigned i = 0; i < NO_POINTS; i++)
	{
		if (i >= 15)
		{
			m_renderPoints[i].position = m_shapePoints[i];
			m_quad.append(m_renderPoints[i]);
		}
		else
		{
			m_renderPoints[i].position = m_shapePoints[i];  // we could go straight from vector + colour
			m_triangle.append(m_renderPoints[i]); // Pete didn't
		}
	}
}

/// <summary>
/// Determines the center of a shape given its points
/// </summary>
/// <param name="t_array">array of points</param>
/// <param name="t_start">start point in array</param>
/// <param name="t_end">end point in array</param>
/// <returns>location of the center as a MyVector3</returns>
MyVector3 Game::findCenter(MyVector3 t_array[], unsigned t_start, unsigned t_end)
{
	MyVector3 sum = { 0.0,0.0,0.0 }, result = { 0.0,0.0,0.0 };
	double range = t_end - t_start;

	for (unsigned i = t_start; i < t_end; i++)
	{
		sum += t_array[i];
	}

	result = sum / range;
	return result;
}

/// <summary>
/// Generates a matrix to translate a point to the origin, rotate it, and return it to its original position with its new rotation
/// </summary>
/// <param name="t_center">center of rotation</param>
/// <param name="t_direction">direction of rotation</param>
/// <returns>transformation matrix</returns>
MyMatrix3 Game::rotate(MyVector3 t_center, rotationDir t_direction)
{
	MyMatrix3 result = MyMatrix3::translation(t_center) * MyMatrix3::rotationZ((3.14159 / 180.0) * t_direction) * MyMatrix3::translation(-t_center);

	return result;
}

/// <summary>
/// draw a frame, and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear();

	m_window.draw(m_puzzleSprites[0]);
	m_window.draw(m_triangle);
	m_window.draw(m_quad);

	// for all shapes
	for (int shape = 1, startRange = 0, endRange = 3; shape < 8; shape++)
	{
		drawNumber(shape, startRange, endRange);

		// if it's a triangle, increment by 3. If it's a quad, increment by 4
		startRange += (shape < 6) ? 3 : 4;
		endRange += (shape < 6) ? 3 : 4;
	}

	m_window.display();
}

/// <summary>
/// Finds the center point of each shape, and draws its number there
/// </summary>
/// <param name="t_number">Number to draw on shape</param>
/// <param name="t_start">Start range of points to find center</param>
/// <param name="t_end">End range of points to find center</param>
void Game::drawNumber(int t_number, int t_start, int t_end)
{
	MyVector3 center = Game::findCenter(m_shapePoints, t_start, t_end);
	MyVector3 offset = { -5.0,-5.0,0.0 };

	m_numberText.setString(std::to_string(t_number));
	m_numberText.setPosition(center + offset);

	m_window.draw(m_numberText);
}
