
//  Won't accept PI without this
#define _USE_MATH_DEFINES
// Include Header Files
#include "Spacecraft.h"
#include "Asteroid.h"
#include "game.h"
#include "ErrorLog.h"
// Include OpenGL headers
#include <windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
// Include neccessary libraries
#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <memory>
#include <cmath>
#include <chrono>
// define keys
#define LEFT_ARROW 37
#define RIGHT_ARROW 39
#define UP_ARROW 41
#define DOWN_ARROW 43
using namespace std;

const int window_width = 750;  // define window width
const int window_height = 750; // define window height

// create class to draw the objects
class DrawObjects
{
    // public members
public:
    // Virtual destructor
    virtual ~DrawObjects() {}

    // Pure virtual function for drawing
    virtual void draw() const = 0;
};

// **  DRAW SPACECRAFT **
void Spacecraft::draw()
{
    // call in the position coordinates of the spacecraft
    draw(positionX, positionY);
}

void Spacecraft::draw(float posX, float posY)
{
    // Draw the Spacecraft
    float bodyWidth = 4 * square_size;     // Width of the spacecraft body
    float bodyHeight = 12.0 * square_size; // Height of the spacecraft body
    float finWidth = 8.0 * square_size;    // Width of the fins
    float finHeight = 4.0 * square_size;   // Height of the fins

    // Draw main body of Spacecraft through use of ellipse
    // set color
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON); // Begin drawing the body as a polygon
    for (int i = 0; i < 360; i++)
    {
        float angle = i * M_PI / 180.0;          // Convert to radians
        float x = bodyWidth * 0.5 * cos(angle);  // X coordinate of the ellipse
        float y = bodyHeight * 0.5 * sin(angle); // Y coordinate of the ellipse
        glVertex2f(x + posX, y + posY);          // Drawing the vertex at the spacecraft position
    }
    glEnd();

    // Draw cockpit as small ellipse at the top of the Spacecraft
    float axis1 = 1.0 * square_size; // minor axis
    float axis2 = 2.0 * square_size; // major axis
    // set color
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON); // Begin drawing the cockpit
    for (int i = 0; i < 360; i++)
    {
        float angle = i * M_PI / 180.0;                    // convert to radians
        float x = axis1 * cos(angle);                      // x pos of the cockpit
        float y = axis2 * sin(angle);                      // y pos of the cockpit
        glVertex2f(x + posX, y + posY + bodyHeight * 0.3); // Position it on top of the Spacecraft
    }
    glEnd();

    // Draw the smoke as triangles at the bottom of the spacecraft
    // set the color
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLES); // Begin drawing the smoke
    // Drawing the left triangle
    glVertex2f(posX - bodyWidth * 0.25, posY - bodyHeight * 0.5); // Bottom left
    glVertex2f(posX - bodyWidth * 0.5, posY - bodyHeight * 0.75); // Bottom left point of the triangle
    glVertex2f(posX - bodyWidth * 0.75, posY - bodyHeight * 0.5); // Bottom right

    // Drawing the right triangle
    glVertex2f(posX + bodyWidth * 0.25, posY - bodyHeight * 0.5); // Bottom left
    glVertex2f(posX + bodyWidth * 0.5, posY - bodyHeight * 0.75); // Bottom left point of the triangle
    glVertex2f(posX + bodyWidth * 0.75, posY - bodyHeight * 0.5); // Bottom right
    glEnd();

    // draw the fire in the middle
    // set the orange color
    glColor3f(1.0, 0.647, 0.0);
    glBegin(GL_TRIANGLES);
    // Bottom of the new fin (horizontal alignment between the two other fins)
    glVertex2f(posX - bodyWidth * 0.25, posY - bodyHeight * 0.5); // bottom left
    glVertex2f(posX, posY - bodyHeight * 0.75);                   // bottom left point of the triangle
    glVertex2f(posX + bodyWidth * 0.25, posY - bodyHeight * 0.5); // bottom right
    glEnd();
}

// Game Constructor with initial arguments
Game::Game(Spacecraft &s) : spacecraft(s), replay(false), over(true), square_size(10.0), xincrements(1.5), yincrements(0)
{
    // Resize the keyStates vector to hold 256 boolean values (for key states)
    keyStates.resize(256);

    // Initialize the bitmap1 with a starting pattern
    bitmap1 = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
               {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
               {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
               {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
               {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
               {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
               {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
               {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
               {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
               {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
               {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
               {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
               {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
               {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
               {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
}
// Change Game constructor to accept unique_ptr

// Destructor for the game
Game::~Game()
{
    // delete all dynamically allocated draw objects
    for (auto drawobject : drawobjects)
    {
        delete drawobject;
    }
};

// initialize the game
void Game::init()
{
    // Reset all keys states to false so the game can start (256 for broad, generic range)
    keyStates.resize(256, false);
    for (int i = 0; i < 256; i++)
    {
        keyStates[i] = false;
    }
}

// reset the game
void Game::resetGame()
{
    // start the game over by resetting over to false
    over = false;

    // reset increments back to original state
    xincrements = 1.5;
    yincrements = 1.5;

    // Reset keys back to original state
    for (int i = 0; i < 256; i++)
    {
        keyStates[i] = false;
    }
}

// handling the key operatoins
void Game::keyOperations()
{
    // Update Spacecraft's movement according to keys pressed

    x_s = (1.5 + xincrements) * square_size; // updating x movement and position based on previous and current increments
    y_s = (1.5 + yincrements) * square_size; // updating y movement and position based on previous and current increments

    // if the left arrow key is pressed, move the spacecraft left 1.5
    if (keyStates[LEFT_ARROW])
    {
        xincrements -= 1.5;
        this->spacecraft.moveLaterally(-1);
    }

    // if the right arrow key is pressed, move the spacecraft right 1.5
    if (keyStates[RIGHT_ARROW])
    {
        xincrements += 1.5;
        this->spacecraft.moveLaterally(1);
    }
    // if the up arrow key is pressed, move the spacecraft up 1.5
    if (keyStates[UP_ARROW])
    {
        yincrements += 1.5;
        this->spacecraft.moveVertically(1);
    }

    // if the down arrow key is pressed, move the spacecraft down 1.5
    if (keyStates[DOWN_ARROW])
    {
        yincrements -= 1.5;
        this->spacecraft.moveVertically(-1);
    }

    // if the space bar is pressed, then replay the game
    if (keyStates[' '])
    {
        // Reset the game if desiring to replay and the game is over
        if (!replay && over)
        {
            resetGame();
            replay = true;
        }
        // if not, don't reset the game
        else if (replay && over)
        {
            replay = false;
        }
    }

    // Reset the game when r is pressed
    if (keyStates['r'])
    {
        resetGame();
        replay = true;
    }
}

// Method to check if the game is over
void Game::gameover()
{
    for (auto &asteroid : asteroids)
    {
        // print statement to debug
        // cout << x_s << ',' << y_s << endl;
        // cout << asteroid.x << ',' << asteroid.y << endl;
        static constexpr float square_size = 10.0; // define the hit box square size
        float bodyWidth = 3 * square_size;         // Width of the spacecraft body
        float bodyHeight = 12.0 * square_size;     // Height of the spacecraft body
        float finWidth = 6.0 * square_size;        // Width of the fins
        float finHeight = 4.0 * square_size;       // Height of the fins

        int number_x = asteroid.x;
        int lowerbound_x = (x_s / 10) - (0.5 * (bodyWidth + finWidth)); // Lower bound of x range
        int upperbound_x = (x_s / 10) + (0.5 * (bodyWidth + finWidth)); // Upper bound of x range

        int number_y = asteroid.y;                                        // Check this number
        int lowerbound_y = (y_s / 10) - (0.5 * (bodyHeight + finHeight)); // Lower bound of y range
        int upperbound_y = (y_s / 10) + (0.5 * (bodyHeight + finHeight)); // Upper bound of y range

        // conditional statements to determine if the spacecraft is too close in range to another asteroid
        // if x values are too close in range
        if (number_x >= lowerbound_x && number_x <= upperbound_x)
        {
            // if the y values are too close in range
            if (number_y >= lowerbound_y && number_y <= upperbound_y)
            {
                // cout << "Game Over: Number is between the bounds." << endl;
                over = true; // game over
                return;
            }
        }
    }

    if (time_interval == 60) // Allow game to go on for a minute
    {
        over = true; // once 60 seconds is up, the game ends the user wins
        return;
    }
}

// Display the results of the game at the end
void Game::resultsdisplay()
{
    // clear the previous screen
    glClear(GL_COLOR_BUFFER_BIT);

    // i.e. if the game is over and the user hasn't hit an asteroid
    if (time_interval == 60)
    {
        // set overall color
        glClearColor(0, 0, 0, 1.0);
        const char *title = "*************************************"; // Display Message when the Game is Won (design for top)
        glRasterPos2f(170, 250);                                     // position
        while (*title)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *title++);

        title = "CONGRATULATIONS YOU WON SPACECRAFT! "; // display message of winning
        glColor3f(0.0, 0.0, 0.0);
        glRasterPos2f(150, 300); // position
        while (*title)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *title++);

        title = "*************************************"; // design for bottom
        glRasterPos2f(170, 350);                         // position
        while (*title)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *title++);

        title = "In order to restart the game, press the letter r on the keyboard."; // restart instruction message
        glRasterPos2f(170, 550);                                                     // position
        while (*title)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *title++);
    }

    else
    {
        // set the overall color
        glColor3f(0.0, 0.0, 0.0);
        // Display Message when the Game is Lost
        const char *title = "******************************************";
        glRasterPos2f(130, 250);
        while (*title)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *title++);

        title = "SORRY, YOU LOST THE GAME SPACECRAFT";
        glRasterPos2f(130, 300);
        while (*title)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *title++);

        title = "******************************************";
        glRasterPos2f(130, 350);
        while (*title)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *title++);

        while (*title)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *title++);

        title = "In order to restart the game, press the letter r on the keyboard.";
        glRasterPos2f(90, 550);
        while (*title)
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *title++);
    }
    // glFlush();
}

// instructions screen messages
void Game::Instructionscreen()
{
    glClearColor(0, 1.0, 1.0, 1.0); // make the screen a cyan color
    glClear(GL_COLOR_BUFFER_BIT);   // clear the screen
    glBegin(GL_LINES);              // create lines for instructions
    for (int i = 0; i < 180; i++)
    {
        float x = 30 * cos(i) - 375;
        float y = 30 * sin(i) - 375;
        glVertex2f(x, y);
    }
    glEnd();

    // Set text color to black
    glColor3f(0.0, 0.0, 0.0);
    // Title Section
    const char *title = "*************************************";
    glRasterPos2f(150, 500);
    while (*title)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *title++);

    title = "Asteroid Avoider";
    glRasterPos2f(270, 550);
    while (*title)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *title++);

    title = "*************************************";
    glRasterPos2f(150, 600);
    while (*title)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *title++);

    // Instruction Text Section
    title = "To move the spacecraft, use the left and right arrow keys";
    glRasterPos2f(100, 450);
    while (*title)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *title++);

    title = "Press the space key to begin!";
    glRasterPos2f(210, 400);
    while (*title)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *title++);

    title = "To reset the game, press the r key.";
    glRasterPos2f(200, 350);
    while (*title)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *title++);

    // glFlush();
}

// display the game
void Game::display()
{

    this->keyOperations();        // handle key operations
    glClear(GL_COLOR_BUFFER_BIT); // clear the window
    this->gameover();             // check to see if the game is over

    updateAsteroids(); // update the asteroids
    for (auto asteroid : asteroids)
    {
        asteroid.draw(); // display the asteroids that are drawn
    }

    // sleep for a short time to control the frame rate
    std::this_thread::sleep_for(std::chrono::milliseconds(5));

    // If the player is replaying then draw the asteroid and spacecraft again
    if (this->replay)
    {
        if (!this->over)
        {
            // draw the spacecraft at its current position
            this->spacecraft.draw(1.5 + this->xincrements, 1.5 + this->yincrements);
        }
        else
        {
            // display the results of the game
            this->resultsdisplay();
        }
    }
    else
    {
        // if not replaying, display the instruction screen
        this->Instructionscreen();
    }
    // swap the back and front buffers to display the rendered screen
    glutSwapBuffers();
}

// Method to reshape the game if the screen size changes
void Game::reshape(int w_resize, int h_resize)
{

    // Switch to the projection matrix mode
    glMatrixMode(GL_PROJECTION);

    // Reset the projection matrix to the identity matrix
    glLoadIdentity();

    // Set the viewport to match the new window size
    glViewport(0, 0, (GLsizei)w_resize, (GLsizei)h_resize);

    // Define the orthographic projection matrix with new window dimensions
    glOrtho(0, 750, 750, 0, -1.0, 1.0);

    // Switch back to the modelview matrix mode
    glMatrixMode(GL_MODELVIEW);
}

// unique pointer for Spacecraft object
std::unique_ptr<Spacecraft> spacecraftPtr(new Spacecraft);

// create a game object with spacecraft
Game game(*spacecraftPtr);
// GLUT display callback function
void displaycallback() { game.display(); }
// GLUT reshape callback function
void reshapecallback(int width, int height) { game.reshape(width, height); }
// GLUT key pressed callback function
void keypressedcallback(unsigned char key, int x, int y)
{
    game.keyStates[key] = true;
}

// GLUT key released callback function
void keyUpCallback(unsigned char key, int x, int y) { game.keyStates[key] = false; }

// GLUT special key pressed callback function
void specialKeyPressedCallback(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        game.keyStates[LEFT_ARROW] = true;
        break;

    case GLUT_KEY_RIGHT:
        game.keyStates[RIGHT_ARROW] = true;
        break;
    case GLUT_KEY_UP:
        game.keyStates[UP_ARROW] = true;
        break;
    case GLUT_KEY_DOWN:
        game.keyStates[DOWN_ARROW] = true;
        break;
    }
}

// GLUT special key released callback function
void specialkeyupcallback(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        game.keyStates[LEFT_ARROW] = false;
        break;

    case GLUT_KEY_RIGHT:
        game.keyStates[RIGHT_ARROW] = false;
        break;
    case GLUT_KEY_UP:
        game.keyStates[UP_ARROW] = false;
        break;
    case GLUT_KEY_DOWN:
        game.keyStates[DOWN_ARROW] = false;
        break;
    }
}

// Int main()
int main(int argc, char **argv)
{

    ErrorLog logger("error_log.txt");             // link with the error log
    logger.WriteMessage("Something went wrong!"); // link the error log

    glutInit(&argc, argv);                       // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Double buffering for smooth rendering
    glutInitWindowSize(750, 750);                // Set the window size
    glutCreateWindow("Asteroids Avoiders");      // Create the window
    glewInit();                                  // initialize with glew
    // Set up OpenGL settings
    glClearColor(0.0, 0.0, 0.0, 1.0);                      // Set background color (black)
    glOrtho(0, window_width, 0, window_height, -1.0, 1.0); // Set 2D orthogonal projection

    // Set GLUT callbacks
    glutKeyboardFunc(keypressedcallback);
    glutKeyboardUpFunc(keyUpCallback);
    glutDisplayFunc(displaycallback);
    // glutReshapeFunc(reshapecallback);
    glutIdleFunc(displaycallback);
    glutSpecialFunc(specialKeyPressedCallback);
    glutSpecialUpFunc(specialkeyupcallback);

    // Initialize game
    game.init();
    // GLUT mainloop
    glutMainLoop();

    return 0;
}
