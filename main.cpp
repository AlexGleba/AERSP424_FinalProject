ALEX CHECK THIS

//Include Header Files
#include "Spaceship.h"

//Define arrow key codes
#define LEFT_ARROW 37
#define RIGHT_ARROW 39

//Include OpenGL headers
#include <openGL/gl.h>
#include <GLUT/glut.h>


//Include neccessary libraries
#include <iostream>
#include <vector>
#include <thread>
#include <string>
#include <memory>
#include <cmath>

using namespace std;

//////// PUT IN OTHER CPP BUT JUST TO SEE IF IT RUNS/////////////
static float square_size = 50.0; //size of one square on the game


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
