// ALEX CHECK 

#ifndef ASTEROID_H
#define ASTEROID_H

#include <cmath>
#include <atomic>
#include <windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>

class Asteroid 
{
private:
    std::atomic<float> positionX_asteroid;
    std::atomic<float> positionY_asteroid;
    static constexpr float square_size = 50.0;
    float Xa_position;
    float Ya_position;

public:

    float x, y;
    float speed, size;
    // Asteroid constructor to set initial position to 0
    Asteroid() : Xa_position(0.0), Ya_position(0.0) {}

    void draw(float Xposition, float Yposition);

    float getXaPosition() const { return positionX_asteroid.load(); }
    float getYaPosition() const { return positionY_asteroid.load(); }

};

#endif // ASTEROID_H
