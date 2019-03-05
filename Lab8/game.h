/// <summary>
/// Author: Ben Millar � C00236772
/// Date: 28/02/2019
/// Estimated time to complete: 12 hours
/// Session 1 Start: 22:50 End: 23:10 02/03/2019
/// </summary>
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "MyVector3.h"
#include "MyMatrix3.h"

const sf::Color CORNFLOWER_BLUE{ 154, 206, 235, 255 };
const sf::Color GRAY{ 25,25,25,255 };
const unsigned NO_POINTS = 6;

class Game
{
public:
	Game();
	void run();
private:
	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();

private:
	sf::RenderWindow m_window; 
	sf::VertexArray m_triangle; // used to draw triangles
	sf::VertexArray m_quad; // used to draw quads
	sf::Vertex m_renderPoints[NO_POINTS]; // used to store vertexs, especailly colour
	MyVector3 m_shapePoints[NO_POINTS]; // used for game logic

};

#endif // !GAME_H