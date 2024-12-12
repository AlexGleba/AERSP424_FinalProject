// ALEX CHECK THIS

#ifndef SPACECRAFT_H
#define SPACECRAFT_H

#include <cmath>
#include <atomic>
#include <windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>

class Spacecraft
{
private:
    float positionX;
    float positionY;
    static constexpr float square_size = 10.0;

public:
    // Spacecraft constructor set to initial position
    Spacecraft() : positionX(0.0), positionY(0.0) {}
    void draw(float Xposition, float Yposition);
    void draw();
    void moveLaterally(float x) { positionX += x; }
    void moveVertically(float y) { positionY += y; }
};

#endif // SPACECRAFT_H
