/// <summary>
/// Author: Ben Millar – C00236772
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
const unsigned NO_POINTS = 23;
const unsigned NO_SHAPES = 7;

const unsigned NO_PUZZLES = 4;

enum rotationDir
{
	clockwise = 1,
	counterclockwise = -1
};

class Game
{
public:
	Game();
	void run();
private:
	// ++++++++++ METHODS ++++++++++
	
	void setupFontAndText();
	void setupSprites();
	void processEvents();
	void resetShapes();
	void update(sf::Time t_deltaTime);
	static MyVector3 findCenter(MyVector3 t_array[], unsigned t_start, unsigned t_end);
	static MyMatrix3 rotate(MyVector3 t_center, rotationDir t_direction);
	void render();
	void drawNumber(int t_number, int t_start, int t_end);

	// +++++++++++++++++++++++++++++


	// +++++++++ VARIABLES +++++++++

	sf::VertexArray m_triangle; // used to draw triangles
	sf::VertexArray m_quad; // used to draw quads

	const MyVector3 M_INITIAL_POSITIONS[NO_POINTS];

	sf::Vertex m_renderPoints[NO_POINTS]; // used to store vertexs, especailly colour
	MyVector3 m_shapePoints[NO_POINTS]; // used for game logic

	float m_moveSpeed = 1.0f;

	unsigned m_startRange = 0;
	unsigned m_endRange = 3;

	// +++++++++++++++++++++++++++++


	// ++++++++++ OBJECTS ++++++++++

	sf::RenderWindow m_window; 

	sf::Font m_arialBlackFont;
	sf::Text m_numberText;

	sf::Texture m_puzzleTextures[NO_PUZZLES];
	sf::Sprite m_puzzleSprites[NO_PUZZLES];
	
	// +++++++++++++++++++++++++++++

};

#endif // !GAME_H