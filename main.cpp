//ALEX CHECK THIS
// Won't accept PI without this
#define _USE_MATH_DEFINES

//Include Header Files
#include "Spacecraft.h"
#include "Asteroid.h"
#include "Game.h"
#include "ErrorLog.h"
//#include "CMakeLists.txt"

//Define arrow key codes


//Include OpenGL headers
//#include <openGL/gl.h>
//#include <GLUT/glut.h>

#include <GL/gl.h>
#include <GL/glut.h>



//Include neccessary libraries
#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <memory>
#include <cmath>

using namespace std;


// Create classes in order to run the game
// Requirements: Draw the Spacecraft, Asteroids, and lasers

// update the spaceship, draw asteroids, update asteroids, draw lasers, update lasers, and detect collisions between lasers and asteroids.  

class DrawObjects
{
public:
    // Virtual destructor
    virtual ~DrawObjects() {}

    // Pure virtual function for drawing
    virtual void draw() const = 0;
    // Implemented by derived classes
};


// ** SPACECRAFT **
void Spacecraft::draw(float posX, float posY)
{
    // Draw the Spacecraft 
    float bodyWidth = 40 * square_size; // Width of the spacecraft body
    float bodyHeight = 20.0 * square_size; // Height of the spacecraft body
    float finWidth = 6.0 * square_size;    // Width of the fins
    float finHeight = 10.0 * square_size;  // Height of the fins

    // Draw main body of Spacecraft through use of ellipse
    glBegin(GL_POLYGON); // Begin drawing the body as a polygon
    for (int i = 0; i < 360; i++)
    {
        float angle = i * M_PI / 180.0; // Convert to radians
        float x = bodyWidth * 0.5 * cos(angle); // X coordinate of the ellipse
        float y = bodyHeight * 0.5 * sin(angle); // Y coordinate of the ellipse
        glVertex2f(x + posX, y + posY); // Drawing the vertex at the spacecraft position
    }
    glEnd();

    // Draw cockpit as small circle at the top of the Spacecraft
    float cockpitradius = 5.0 * square_size;
    glBegin(GL_POLYGON); // Begin drawing the cockpit
    for (int i = 0; i < 360; i++)
    {
        float angle = i * M_PI / 180.0; // convert to radians
        float x = cockpitradius * cos(angle);
        float y = cockpitradius * sin(angle);
        glVertex2f(x + posX, y + posY + bodyHeight * 0.25); // Position it on top of the Spacecraft
    }
    glEnd();


    // DON"T KNOW WHERE TO PLACE THIS /////////////////////////////////
        // Set Spacecraft color to white (RGB: 1.0, 1.0, 0.0)
        // All the colors are set to their maximum value 1 to be fully on 
    glColor3f(1.0, 1.0, 1.0);

    // Draw the fins as triangles at the bottom of the spacecraft
    glBegin(GL_TRIANGLES); // Begin drawing the fins
    // Drawing the left fin
    glVertex2f(posX - bodyWidth * 0.25, posY - bodyHeight * 0.5); // Bottom left
    glVertex2f(posX - bodyWidth * 0.5, posY - bodyHeight * 0.75); // Bottom left point of the fin
    glVertex2f(posX - bodyWidth * 0.75, posY - bodyHeight * 0.5); // Bottom right

    // Drawing the right fin
    glVertex2f(posX + bodyWidth * 0.25, posY - bodyHeight * 0.5); // Bottom left
    glVertex2f(posX + bodyWidth * 0.5, posY - bodyHeight * 0.75); // Bottom left point of the fin
    glVertex2f(posX + bodyWidth * 0.75, posY - bodyHeight * 0.5); // Bottom right
    glEnd();
}

// Struct for the Asteroid 
struct Asteroid
{
    float x, y;     // Position of the asteroid
    float size;     // Size of the asteroid
    float speed;    // Speed at which the asteroid falls
};


// Global variable 
std::vector<Asteroid> asteroids;
// List of the asteroids 

// Generate random number between given range
float getRandomFloat(float min, float max)
{
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

// Spawn new asteroid 
void spawnAsteroid()
{
    Asteroid newAsteroid;
    newAsteroid.x = getRandomFloat(0, window_width);  // Asteroid falls starting from random X position
    newAsteroid.y = window_height;                    // Start at the top of the screen
    newAsteroid.size = getRandomFloat(10.0f, 30.0f);  // Asteroid has a random size
    newAsteroid.speed = getRandomFloat(1.0f, 5.0f);   // Asteroid has a random fall speed
    asteroids.push_back(newAsteroid);
}

void updateAsteroids(int value)
{
    // Updating the positions of the asteroids
    for (auto& asteroid : asteroids)
    {
        asteroid.y -= asteroid.speed;  // Moving the asteroid down
    }

    // Removing asteroids that are off the screen
    asteroids.erase(std::remove_if(asteroids.begin(), asteroids.end(),
        [](const Asteroid& asteroid) {
            return asteroid.y + asteroid.size < 0;  // Check if asteroid is out of screen
        }),
        asteroids.end());
    glutPostRedisplay(); // Redraw request
    glutTimerFunc(20, updateAsteroids, 0);  // Call this function again after 20 ms
}

// Drawing the Asteroids 
void renderAsteroids()
{
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen

    // Render each asteroid
    for (const auto& asteroid : asteroids)
    {
        glPushMatrix();
        glTranslatef(asteroid.x, asteroid.y, 0);  // Translate to asteroid's position
        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i += 30)
        {
            float angle = i * M_PI / 180; // convert to radians
            glVertex2f(cos(angle) * asteroid.size, sin(angle) * asteroid.size);  // Draw a circle for the Asteroid
        }
        glEnd();
        glPopMatrix();
    }

    glutSwapBuffers();  // Swap the buffers to display the new frame
}

glEnd();
}

// Game 
Game::Game(Spacecraft& s, Asteroid& a) : spacecraft(s), asteroid(a), replay(false), over(true), square_size(50.0), xincrements(1.5), yincrements(0), xincrementa(0), yincrementa(0) {

    // Destructor for the game
    Game::~Game() {
        for (auto DrawObjects : drawobjects) {
            delete drawobjects;
        }
    }



    int main(int argc, char** argv)
    {
        glutInit(&argc, argv);  // Initialize GLUT
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // Double buffering for smooth rendering
        glutInitWindowSize(750, 750); // Set the window size
        glutCreateWindow("Asteroids Destroyers"); // Create the window

        // Set up OpenGL settings
        glClearColor(0.0, 0.0, 0.0, 1.0); // Set background color (black)
        glOrtho(0, window_width, 0, window_height, -1.0, 1.0); // Set 2D orthogonal projection

        // Register the display function and handle input
        glutDisplayFunc(display); // Display callback for rendering
        glutKeyboardFunc(keyPressed); // Regular key press callback
        glutSpecialFunc(specialKeyPressed); // Special key press callback
        glutTimerFunc(16, update, 0);  // Start the update loop (60 FPS)

        // Spawn the first asteroid
        spawnAsteroid();

        // Start the GLUT main loop
        glutMainLoop();

        return 0;

    }
