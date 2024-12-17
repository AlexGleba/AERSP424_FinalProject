// Include headers
#ifndef ASTEROID_H
#define ASTEROID_H
#include <cmath>
#include <atomic>
#include <windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <vector>

// Create Asteroid Class
class Asteroid
{
private:
    // private members are asteroid position and square size
    static constexpr float square_size = 10.0;
    float Xa_position;
    float Ya_position;

public:
    // public members - speed, size, and position of the spacecraft
    float speed, size;
    float x, y;

    // Create asteroid constructor
    Asteroid(int x, int y, int size, float speed)
    {
        // set the asteroid's x and y coordinates, size and speed
        this->x = x;
        this->y = y;
        this->size = size;
        this->speed = speed;
    };

    // virtual function to draw the asteroid
    void draw()
    {
        // set the color
        glColor3f(0.0, 0.0, 1.0);
        // use glBegin to initiate
        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i += 30)
        {
            float angle = i * M_PI / 180;                             // convert to radians
            glVertex2f(x + cos(angle) * size, y + sin(angle) * size); // Draw a circle for the Asteroid
        }
        glEnd();
    }
    // create a function that updates the asteroid's speed
    void updateAsteroidspeed()
    {
        // reference vector of Asteroid objects
        std::vector<Asteroid> asteroids;

        // Updating the positions of the asteroids
        for (auto &asteroid : asteroids)
        {
            asteroid.y -= asteroid.speed; // Moving the asteroid down by subtracting its speed from y
        }
    }
};

#endif // ASTEROID_H
