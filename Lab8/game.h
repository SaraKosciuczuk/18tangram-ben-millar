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
/// Session 12 Start: 12:10 End: 12:55
/// Session 13 Start: 14:30 End: 14:50
/// Session 14 Start: 18:00 End: 18:20 TOTAL TIME: 9 hours 10 minutes
/// </summary>
/// 
/// KNOWN BUGS: I can't get the 'highlight' vertex lines to draw around the entire shape, only all but one.
/// 
/// MUSIC: Cottages Kevin MacLeod (incompetech.com)
///	Licensed under Creative Commons : By Attribution 3.0 License
///	http ://creativecommons.org/licenses/by/3.0/


#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "MyVector3.h"
#include "MyMatrix3.h"


// global constants

const unsigned NO_POINTS = 23;
const unsigned NO_SHAPES = 7;

struct shapeStruct
{
	unsigned startRange, endRange;
	MyVector3 translation;
	double rotation;
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
	
	void setupFontAndText(); // set up font
	void setupSprites(); // load in and setup sprites
	void setupObjects(); // set up SFML objects
	void setupSounds(); // load in an initialise sounds/music
	void processEvents(); // process user input
	void resetShapes(); // return shapes to their starting position
	void update(sf::Time t_deltaTime); // main update loop for game logic
	void calculateTranslations(); // calculate and apply translations to all shapes
	static MyVector3 findCenter(shapeStruct t_shape, MyVector3 t_array[23]); // finds the geometric center of a shape
	static MyMatrix3 rotate(MyVector3 t_center, double t_angle); // rotates a shape in a given direction by 1 degree
	void render(); // clear frame, render new framebuffer, and flip buffers
	void drawNumber(shapeStruct t_shape, int t_num); // draws number text onto shape
	void drawResetBar(); // draws the reset 'loading' bar when resetting

	// +++++++++++++++++++++++++++++


	// +++++++++ VARIABLES +++++++++

	sf::VertexArray m_triangle; // used to draw triangles
	sf::VertexArray m_quad; // used to draw quads
	sf::VertexArray m_highlight; // used to highlight active shape

	sf::Vertex m_highlightRenderPoints[8]; 
	sf::Vertex m_renderPoints[NO_POINTS]; // used to store vertexs, especailly colour
	MyVector3 m_shapePoints[NO_POINTS]; // used for game logic

	// move speed for translation
	float m_moveSpeed = 1.0f;

	// used for accessing groups of points
	shapeStruct m_shapes[NO_SHAPES];
	unsigned m_currentShape = 0;

	// transformation matrices
	MyMatrix3 m_translationMatrix[NO_SHAPES]; // transformation matrices for each shape
	MyMatrix3 m_rotationMatrix[NO_SHAPES];

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

	// sounds/music
	sf::SoundBuffer m_clickBuffer;
	sf::Sound m_clickSound;

	sf::Music m_backgroundMusic;
	
	// +++++++++++++++++++++++++++++
};

#endif // !GAME_H