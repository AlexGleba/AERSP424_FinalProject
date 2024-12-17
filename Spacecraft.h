
// Include headers
#ifndef SPACECRAFT_H
#define SPACECRAFT_H
#include <cmath>
#include <atomic>
#include <windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>

// Create Spacecraft Class
class Spacecraft
{
    // private members are the spacecraft position and square size
private:
    float positionX;
    float positionY;
    static constexpr float square_size = 10.0;

    // public members
public:
    // Spacecraft constructor set to initial position
    Spacecraft() : positionX(0.0), positionY(0.0) {}
    void draw(float Xposition, float Yposition);
    // function for drawing the spacecraft
    void draw();
    // functions to increment the spacecraft's position to move up and down
    void moveLaterally(float x) { positionX += x; }
    void moveVertically(float y) { positionY += y; }
};

#endif // SPACECRAFT_H
