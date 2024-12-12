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
    static constexpr float square_size = 50.0;
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
        glColor3f(0.0, 1.0, 1.0);
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

    /* float x, y;
     int sizevalue;
     AsteroidSize size;

     // Asteroid constructor to set initial position to 0
     Asteroid() : Xa_position(0.0), Ya_position(0.0) {}


     explicit Asteroid(AsteroidSize size) : size(size)
     {
         switch(size)
         {
             case AsteroidSize::BIG: sizevalue = 4;
             break;
             case AsteroidSize::SMALL: sizevalue = 6;
             break;
         }
     }


     //void draw(float Xposition, float Yposition);
     //void updateAsteroids(int value);
     //void renderAsteroids();

 static std::vector<std::unique_ptr<Asteroid>> initAsteroids(int numberasteroids)
 {
     // vector of Asteroids
     std::vector<std::unique_ptr<Asteroid>> asteroids;
     // int number_asteroids = 0;
     int numberasteroids;
     if (numberasteroids<=20)
     {
         numberasteroids += 1;
     }

     for(int i =0; i < numberasteroids; i++)
     {
           auto size = static_cast<AsteroidSize>(std::rand() % 2);
           auto asteroid = std::make_unique<Asteroid>(size);
           asteroids.push_back(std::move(asteroid));
     }
     return asteroids;
 }

     void initShapeAsteroid()
     {
         float speed;
         float base;

         switch(size)
         {
             case AsteroidSize::BIG: speed = 20.0f;
             base = 20.0f;
             break;
             case AsteroidSize::SMALL: speed = 30.0f;
             base = 10.0f;
             break;
         }

         glColor3f(1.0,1.0,1.0);
         glBegin(GL_POLYGON);
         for (int i = 0; i < 360; i += 30)
         {
             float angle = i * M_PI / 180; // convert to radians
             glVertex2f(cos(angle) * base, sin(angle) * base); // Draw a circle for the Asteroid
         }
         glEnd();
     //shape.setPosition(std::rand() % x, y)

    // float getXaPosition() const { return positionX_asteroid.load(); }
    // float getYaPosition() const { return positionY_asteroid.load(); } */
};

#endif // ASTEROID_H
