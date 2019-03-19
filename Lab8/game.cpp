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
/// Session 7 Start: 23:00 End: 23:45
/// Session 8 Start: 09:10 End: 09:45
/// Session 9 Start: 16:20 End: 17:10
/// Session 10 Start: 16:00 End: 16:50
/// Session 11 Start: 17:40 End: 18:00 TOTAL TIME: 7 hours 45 minutes
/// </summary>
/// 
/// KNOWN BUGS: I can't get the 'highlight' vertex lines to draw around the entire shape, only all but one.
/// 
/// MUSIC: Cottages Kevin MacLeod (incompetech.com)
///	Licensed under Creative Commons : By Attribution 3.0 License
///	http ://creativecommons.org/licenses/by/3.0/

#include "Game.h"
#include <iostream>


Game::Game() :
	m_window{ sf::VideoMode{ 1000, 600 }, "SMFL Game" },
	m_triangle{ sf::Triangles },
	m_quad{ sf::Quads },
	m_highlight{ sf::Lines },
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
	// initialise all vertex points
	for (size_t i = 0; i < NO_POINTS; i++)
	{
		if (i >= 19)
		{
			m_renderPoints[i] = sf::Vertex{ sf::Vector2f(m_shapePoints[i]),sf::Color::White };
		}
		else if ( i >= 15 )
		{
			m_renderPoints[i] = sf::Vertex{ sf::Vector2f(m_shapePoints[i]),sf::Color::White };
		}
		else if (i >= 12)
		{
			m_renderPoints[i] = sf::Vertex{ sf::Vector2f(m_shapePoints[i]),sf::Color::White };
		}
		else if (i >= 9)
		{
			m_renderPoints[i] = sf::Vertex{ sf::Vector2f(m_shapePoints[i]),sf::Color::White };
		}
		else if (i >= 6)
		{
			m_renderPoints[i] = sf::Vertex{ sf::Vector2f(m_shapePoints[i]),sf::Color::White };
		}
		else if (i >= 3)
		{
			m_renderPoints[i] = sf::Vertex{ sf::Vector2f(m_shapePoints[i]),sf::Color::White };
		}
		else
		{
			m_renderPoints[i] = sf::Vertex{ sf::Vector2f(m_shapePoints[i]),sf::Color::White };
		}
	}

	// set up vertex points for our white 'highlight'
	for (int i = 0; i < 8; i++)
	{
		m_highlightRenderPoints[i].color = sf::Color::White;
	}

	resetShapes();
	setupFontAndText();
	setupSprites();
	setupObjects();
	setupSounds();
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
	m_numberText.setFillColor(sf::Color::Black);
	m_numberText.setCharacterSize(18U);

	m_UItext.setFont(m_arialBlackFont);
	m_UItext.setFillColor(sf::Color(255,255,255,220));
	m_UItext.setPosition({ 10.0f,10.0f });
	m_UItext.setCharacterSize(20U);

	m_UItext.setString("Hold [I] to see instructions.");

}

/// <summary>
/// Set up all sprites for the game
/// </summary>
void Game::setupSprites()
{
	// load puzzle textures
	if (!m_puzzleTextures[0].loadFromFile("ASSETS//IMAGES//PUZZLE2.png"))
	{
		std::cout << "Error loading PUZZLE1 texture, located at ASSETS//IMAGES//PUZZLE2.png" << std::endl;
	}

	if (!m_puzzleTextures[1].loadFromFile("ASSETS//IMAGES//PUZZLE2_Solution.png"))
	{
		std::cout << "Error loading PUZZLE2 texture, located at ASSETS//IMAGES//PUZZLE2_Solution.png" << std::endl;
	}


	// assign puzzles texture
	m_puzzleSprite.setTexture(m_puzzleTextures[0]);
	m_puzzleSprite.setPosition({ 500.0f,130.0f });


	// load wood textures
	if (!m_woodTextures[0].loadFromFile("ASSETS//IMAGES//woodTexture0.png"))
	{
		std::cout << "Error loading woodTexture0 texture, located at ASSETS//IMAGES//woodTexture0.png" << std::endl;
	}
	if (!m_woodTextures[1].loadFromFile("ASSETS//IMAGES//woodTexture1.png"))
	{
		std::cout << "Error loading woodTexture1 texture, located at ASSETS//IMAGES//woodTexture1.png" << std::endl;
	}
	if (!m_woodTextures[2].loadFromFile("ASSETS//IMAGES//woodTexture2.png"))
	{
		std::cout << "Error loading woodTexture2 texture, located at ASSETS//IMAGES//woodTexture2.png" << std::endl;
	}
	if (!m_woodTextures[3].loadFromFile("ASSETS//IMAGES//woodTexture3.png"))
	{
		std::cout << "Error loading woodTexture3 texture, located at ASSETS//IMAGES//woodTexture3.png" << std::endl;
	}

	// load instructions texture
	if (!m_instructionsTexture.loadFromFile("ASSETS//IMAGES//instructions.png"))
	{
		std::cout << "Error loading instructions texture, located at ASSETS//IMAGES//instructions.png" << std::endl;
	}

	m_instructionsSprite.setTexture(m_instructionsTexture);
}

/// <summary>
/// Sets up all SFML objects
/// </summary>
void Game::setupObjects()
{
	m_resetBar.setPosition(10.0f, 570.0f);
	m_resetBar.setFillColor(sf::Color::Red);
	m_resetBar.setSize({ 200.0f,20.0f });

	// initialise start and end range values for shape structs
	m_shapes[0].startRange = 0, m_shapes[0].endRange = 3;
	m_shapes[1].startRange = 3, m_shapes[1].endRange = 6;
	m_shapes[2].startRange = 6, m_shapes[2].endRange = 9;
	m_shapes[3].startRange = 9, m_shapes[3].endRange = 12;
	m_shapes[4].startRange = 12, m_shapes[4].endRange = 15;
	m_shapes[5].startRange = 15, m_shapes[5].endRange = 19;
	m_shapes[6].startRange = 19, m_shapes[6].endRange = 23;
}

/// <summary>
/// Sets up all SFML audio
/// </summary>
void Game::setupSounds()
{
	if (!m_backgroundMusic.openFromFile("ASSETS//AUDIO//cottages.wav"))
	{
		std::cout << "Error loading cottages.wav, located at ASSETS//AUDIO//cottages.wav" << std::endl;
	}

	m_backgroundMusic.setLoop(true);

	if (!m_clickBuffer.loadFromFile("ASSETS//AUDIO//click.wav"))
	{
		std::cout << "Error loading click.wav, located at ASSETS//AUDIO//click.wav" << std::endl;
	}

	m_clickSound.setBuffer(m_clickBuffer);

	m_backgroundMusic.play();
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

			// select the range of points to transform
			switch (event.key.code)
			{
			case sf::Keyboard::Num1:
				m_currentShape = 0;
				m_clickSound.play();
				break;
			case sf::Keyboard::Num2:
				m_currentShape = 1;
				m_clickSound.play();
				break;
			case sf::Keyboard::Num3:
				m_currentShape = 2;
				m_clickSound.play();
				break;
			case sf::Keyboard::Num4:
				m_currentShape = 3;
				m_clickSound.play();
				break;
			case sf::Keyboard::Num5:
				m_currentShape = 4;
				m_clickSound.play();
				break;
			case sf::Keyboard::Num6:
				m_currentShape = 5;
				m_clickSound.play();
				break;
			case sf::Keyboard::Num7:
				m_currentShape = 6;
				m_clickSound.play();
				break;
			case sf::Keyboard::R:
				if (m_resetting == false)
				{
					m_resetting = true;
					m_resetClock.restart();
				}
				break;
			default:
				break;
			}
		}

		// check for key release events
		if (event.type == sf::Event::KeyReleased)
		{
			switch(event.key.code)
			{
			case sf::Keyboard::R:
				if (m_resetting == true)
				{
					m_resetting = false;
				}
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
		// This should now reset translation and rotation matrices
		m_shapePoints[i] = M_INITIAL_POSITIONS[i]; // reset point coords to their original
		m_renderPoints[i].texCoords = m_shapePoints[i]; // setup texture coords
	}

	// cycle through our 4 wood textures
	m_chosenTexture = ++m_chosenTexture % 4;
}


/// <summary>
/// respond to keyinputs and update vertex array to new vector positions
/// </summary>
/// <param name="t_deltaTime">frame time</param>
void Game::update(sf::Time t_deltaTime)
{
	// ++++++++++ RESET SHAPES ++++++++++
	if (m_resetting == true && m_resetClock.getElapsedTime() > m_resetTime)
	{
		resetShapes();
		m_resetting = false;
	}

	// ++++++++ SHOW INSTRUCTIONS ++++++++
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
	{
		m_showInstructions = true;
	}
	else
	{
		m_showInstructions = false;
	}

	// ++++++++++ SHOW SOLUTION ++++++++++
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
	{
		m_puzzleSprite.setTexture(m_puzzleTextures[1]);
	}
	else
	{
		m_puzzleSprite.setTexture(m_puzzleTextures[0]);
	}


	// ++++++++++ TAKE USER INPUT ++++++++++

	// *** START and END are assigned ***
	unsigned start = m_shapes[m_currentShape].startRange, end = m_shapes[m_currentShape].endRange;
	// **********************************

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
		m_translations[m_currentShape] += { 0.0, -m_moveSpeed, 0.0 };
		/*for (unsigned i = start; i < end; i++)
		{
			m_shapePoints[i] = MyMatrix3::translation({ 0.0,-m_moveSpeed,0.0 }) * m_shapePoints[i];
		}*/
	}


	// +++++++ MOVE PIECE DOWN +++++++
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_translations[m_currentShape] += { 0.0, m_moveSpeed, 0.0 };
		/*for (unsigned i = start; i < end; i++)
		{
			m_shapePoints[i] = MyMatrix3::translation({ 0.0,m_moveSpeed,0.0 }) * m_shapePoints[i];
		}*/
	}


	// +++++++ MOVE PIECE LEFT +++++++
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{

		m_translations[m_currentShape] += { -m_moveSpeed, 0.0, 0.0 };
		/*for (unsigned i = start; i < end; i++)
		{
			m_shapePoints[i] = MyMatrix3::translation({ -m_moveSpeed,0.0,0.0 }) * m_shapePoints[i];
		}*/
	}


	// +++++++ MOVE PIECE RIGHT +++++++
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_translations[m_currentShape] += { m_moveSpeed, 0.0, 0.0 };
		/*for (unsigned i = start; i < end; i++)
		{
			m_shapePoints[i] = MyMatrix3::translation({ m_moveSpeed,0.0,0.0 }) * m_shapePoints[i];
		}*/
	}


	// +++++++ ROTATE PIECE CLOCKWISE +++++++
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		MyVector3 center = Game::findCenter(m_shapePoints, start, end);
		MyMatrix3 rotation = Game::rotate(center, rotationDir::counterclockwise);

		for (unsigned i = start; i < end; i++)
		{
			m_shapePoints[i] = rotation * m_shapePoints[i];
		}
	}


	// +++++++ ROTATE PIECE ANTICLOCKWISE +++++++
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		MyVector3 center = Game::findCenter(m_shapePoints, start, end);
		MyMatrix3 rotation = Game::rotate(center, rotationDir::clockwise);
		
		for (unsigned i = start; i < end; i++)
		{
			m_shapePoints[i] = rotation * m_shapePoints[i];
		}
	}

	// ++++++++++ END USER INPUT ++++++++++

	// clear vertex arrays
	m_triangle.clear();
	m_quad.clear();
	m_highlight.clear();

	for (int i = 0; i < NO_SHAPES; i++)
	{
		m_transformations[i] = MyMatrix3::translation(m_translations[i]);
	}

	// for all points
	for (unsigned i = 0, shape = 0; i < NO_POINTS; i++)
	{
		if (i >= 15)
		{
			if (i % 4 == 0) shape++;
			// append points to quads
			m_renderPoints[i].position = m_shapePoints[i];
			m_quad.append(m_renderPoints[i]);
		}
		else
		{
			if (i > 0 && i % 3 == 0) shape++;
			// append points to triangles
			m_renderPoints[i].position = m_transformations[shape] * m_shapePoints[i];
			m_triangle.append(m_renderPoints[i]);
		}
	}


	// Draw our highlight lines around chosen shape
	for (unsigned i = 0, j = start; i < (end-start)*2; i++) // loop for num points * 2
	{
		if (i == 5) // if this is our last point
		{
			// link back to the starting point
			m_highlightRenderPoints[i].position = m_renderPoints[start].position;
		}
		else
		{
			// otherwise set position equal to point[j] and assign to our vertex array
			m_highlightRenderPoints[i].position = m_renderPoints[j].position;
			m_highlight.append(m_highlightRenderPoints[i]);
		}

		// update j only every second point, as consecutive lines share a start/end point
		if (i % 2 == 0) j++;
	}
}

/// <summary>
/// Determines the geometric center of a shape given its points
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
	MyMatrix3 result = MyMatrix3::translation(t_center) * MyMatrix3::rotationZ((3.14159 / 180.0) * int(t_direction)) * MyMatrix3::translation(-t_center);

	return result;
}

/// <summary>
/// draw a frame, and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear();

	// draw puzzle
	m_window.draw(m_puzzleSprite);

	// draw shapes with texture
	m_window.draw(m_triangle, &m_woodTextures[m_chosenTexture]);
	m_window.draw(m_quad, &m_woodTextures[m_chosenTexture]);
	m_window.draw(m_highlight);

	// for all shapes
	for (int shape = 1, rangeStart = 0, rangeEnd = 3; shape < 8; shape++)
	{
		// if shape highlighted, draw white text. Otherwise, draw black
		m_numberText.setFillColor((rangeStart == m_shapes[m_currentShape].startRange) ? sf::Color::White : sf::Color::Black);

		// pass off parameters to draw number
		drawNumber(shape, rangeStart, rangeEnd);

		// if it's a triangle, increment by 3. If it's a quad, increment by 4
		rangeStart += (shape < 6) ? 3 : 4;
		rangeEnd += (shape < 6) ? 3 : 4;
	}

	if (m_resetting == true)
	{
		drawResetBar();
	}

	if (m_showInstructions == true)
	{
		m_window.draw(m_instructionsSprite);
	}
	else
	{
		m_window.draw(m_UItext);
	}

	m_window.display();
}

/// <summary>
/// Draws the number of each shape over it's geometric center, plus an offset
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

/// <summary>
/// Draws and animates 'reset' bar on-screen
/// </summary>
void Game::drawResetBar()
{
	m_resetBar.setFillColor(sf::Color(0, 0, 0, 0));
	m_resetBar.setOutlineColor(sf::Color::White);
	m_resetBar.setOutlineThickness(2.0f);
	m_resetBar.setSize({ 204.0f, 24.0f });
	m_resetBar.setPosition({ 8.0f, 568.0f });

	m_window.draw(m_resetBar);

	m_resetBar.setFillColor(sf::Color::Red);
	m_resetBar.setOutlineColor(sf::Color(0, 0, 0, 0));
	m_resetBar.setSize({ (200.0f * m_resetClock.getElapsedTime().asSeconds()) ,20.0f }); // set to be equal to 100
	m_resetBar.setPosition({ 10.0f, 570.0f });

	m_window.draw(m_resetBar);
}
