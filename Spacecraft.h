//ALEX CHECK THIS 

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
    std::atomic<float> positionX;
    std::atomic<float> positionY;
    static constexpr float square_size = 50.0;

public:
    // Spacecraft constructor set to initial position
    Spacecraft() : positionX(0.0), positionY(0.0) {}
    void draw(float Xposition, float Yposition);
};

#endif // SPACECRAFT_H
