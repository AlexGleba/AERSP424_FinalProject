ALEX CHECK THIS 
#define GL_SILENCE_DEPRECATION
#ifndef Spaceship_H
#define Spaceship_H

#include <cmath>
#include <atomic>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

class Spacecraft 
{
private:
    std::atomic<float> positionX;
    std::atomic<float> positionY;
    static constexpr float squareSize = 50.0;

public:
    // Spacecraft constructor set to initial position
    Spacecraft() : positionX(0.0), positionY(0.0) {}
    void draw(float Xposition, float Yposition);
};

#endif // Spacecraft_H
