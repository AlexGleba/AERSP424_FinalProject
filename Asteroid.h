// ALEX CHECK

#ifndef ASTEROID_H
#define ASTEROID_H

#include <cmath>
#include <atomic>
#include <windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <vector>

// enum class AsteroidSize
//{
//    BIG,
//    SMALL
//};

class Asteroid
{
private:
    // std::atomic<float> positionX_asteroid;
    // std::atomic<float> positionY_asteroid;
    static constexpr float square_size = 10.0;
    float Xa_position;
    float Ya_position;

public:
    // Asteroid() {};
    // Asteroid(const Asteroid &) = delete;

    float speed, size;
    float x, y;

    Asteroid(int x, int y, int size, float speed)
    {
        this->x = x;
        this->y = y;
        this->size = size;
        this->speed = speed;
    };

    void draw()
    {
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i += 30)
        {
            float angle = i * M_PI / 180;                     // convert to radians
            glVertex2f(x + cos(angle) * size, y + sin(angle) * size); // Draw a circle for the Asteroid
        }
        glEnd();
    }
    void updateAsteroidspeed()
    {
        std::vector<Asteroid> asteroids;
        // List of the asteroids

        // Updating the positions of the asteroids
        for (auto &asteroid : asteroids)
        {
            asteroid.y -= asteroid.speed; // Moving the asteroid down
        }
    }

};

#endif // ASTEROID_H
