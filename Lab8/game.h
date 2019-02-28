#ifndef GAME_H
#define GAME_H
// must write comments for Pete's sake


#include <SFML/Graphics.hpp>
#include "MyVector3.h"


const sf::Color CORNFLOWER_BLUE{ 154, 206, 235, 255 };
const sf::Color GRAY{ 25,25,25,255 };
const unsigned NO_POINTS = 6;

class Game
{
public:
	Game();
	void run();
private:
	void             processEvents();
	void             update(sf::Time t_deltaTime);
	void             render();

private:
	sf::RenderWindow m_window; 
	sf::VertexArray m_triangle;  // used to draw triangles
	sf::Vertex m_renderPoints[NO_POINTS]; // used to store vertexs, especailly colour
	MyVector3 m_shapePoints[NO_POINTS]; // used for game logic

};

#endif // !GAME_H