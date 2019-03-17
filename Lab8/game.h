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

// global constants

const unsigned NO_POINTS = 23;
const unsigned NO_SHAPES = 7;

/// <summary>
/// enum for rotation direction
/// </summary>
enum class rotationDir
{
	clockwise = 1,
	counterclockwise = -1
};

/// <summary>
/// Game class definition
/// </summary>
class Game
{
public:
	Game();
	void run();
private:

	// ++++++++++ METHODS ++++++++++
	
	void setupFontAndText();
	void setupSprites();
	void setupObjects();
	void processEvents();
	void resetShapes();
	void update(sf::Time t_deltaTime);
	static MyVector3 findCenter(MyVector3 t_array[], unsigned t_start, unsigned t_end);
	static MyMatrix3 rotate(MyVector3 t_center, rotationDir t_direction);
	void render();
	void drawNumber(int t_number, int t_start, int t_end);
	void drawResetBar();

	// +++++++++++++++++++++++++++++


	// +++++++++ VARIABLES +++++++++

	const MyVector3 M_INITIAL_POSITIONS[NO_POINTS];

	sf::VertexArray m_triangle; // used to draw triangles
	sf::VertexArray m_quad; // used to draw quads
	sf::VertexArray m_highlight; // used to highlight active shape

	sf::Vertex m_highlightRenderPoints[8];
	sf::Vertex m_renderPoints[NO_POINTS]; // used to store vertexs, especailly colour
	MyVector3 m_shapePoints[NO_POINTS]; // used for game logic

	// move speed for translation
	float m_moveSpeed = 1.0f;

	// used for accessing groups of points
	unsigned m_startRange = 0;
	unsigned m_endRange = 3;

	unsigned m_chosenTexture; // determines which, of four, wood textures is used

	bool m_resetting = false; // tracks the 'R' keypress for resetting shapes

	bool m_showInstructions = false; // when true, instructions are drawn

	// +++++++++++++++++++++++++++++


	// ++++++++++ OBJECTS ++++++++++

	sf::RenderWindow m_window; 

	// font and text objects
	sf::Font m_arialBlackFont;
	sf::Text m_numberText;
	sf::Text m_UItext;

	// texture/sprite for instructions
	sf::Texture m_instructionsTexture;
	sf::Sprite m_instructionsSprite;

	// texture/sprite for our puzzle and solution
	sf::Texture m_puzzleTextures[2];
	sf::Sprite m_puzzleSprite;

	sf::Texture m_woodTextures[4]; // texture for our shapes

	// clock for timing shape reset delay
	sf::Clock m_resetClock;
	sf::Time m_resetTime = sf::seconds(1.0f);

	sf::RectangleShape m_resetBar;
	
	// +++++++++++++++++++++++++++++

};

#endif // !GAME_H