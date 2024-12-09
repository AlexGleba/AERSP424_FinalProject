ALEX CHECK 

#ifndef ASTEROID_H
#define ASTEROID_H

#include <cmath>
#include <atomic>

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

class Asteroid 
{
private:
    std::atomic<float> positionX_asteroid;
    std::atomic<float> positionY_asteroid;
    static constexpr float squareSize = 50.0;
    float Xa_position;
    float Ya_position;

public:
    // Asteroid constructor to set initial position to 0
    Asteroid() : Xa_position(0.0), Ya_position(0.0) {}

    void draw(float Xposition, float Yposition);

    float getXaPosition() const { return positionX_asteroid.load(); }
    float getYaPosition() const { return positionY_asteroid.load(); }

};

#endif // ASTEROID_H
