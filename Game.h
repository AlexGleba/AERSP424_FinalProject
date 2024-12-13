#ifndef GAME_H
#define GAME_H
#include <vector>
#include <deque>
#include <string>
#include <windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include "Asteroid.h"

// Forward declaration of Spacecraft and Asteroid classes
class Spacecraft;
class Asteroid;
class DrawObjects;

class Game
{
private:
    // static Game * instancePtr;
    //  Game(){};

    Spacecraft &spacecraft;
    std::vector<Asteroid> asteroids;
    bool replay;
    bool over = false;
    float square_size;
    float xincrements;
    float yincrements;
    float xincrementa;
    float yincrementa;
    std::vector<std::vector<bool>> bitmap1;
    int time_interval = 0;
    std::vector<DrawObjects *> drawobjects;
    bool moveLeft;
    bool moveRight;
    float x_s;
    float y_s;
   // float x_a;
   // float y_a;
    
    // std::vector<float> asteroid positions; (not sure if needed)

public:
    const int window_width = 750;
    const int window_height = 750;
    Game(Spacecraft &s);

    // initialize the game and spawn the first asteroid
    void initialize()
    {
        asteroids.push_back(Asteroid(rand() % window_width, window_height, 20, 1.5));
    }

    void updateAsteroids()
    {
        for (auto &asteroid : asteroids)
        {
            // asteroid.updateAsteroidspeed(); // moves each asteroid down the screen
            asteroid.y -= asteroid.speed;
            if (asteroid.y < 0) // if asteroid off the screen
            {
                asteroid.y = window_height;         // resets the asteroid to the top of the screen
                asteroid.x = rand() % window_width; // randomly select a x-position to reset the asteroid
            }
        }

        // Spawn new asteroids
        float probability = 100 * (float)rand() / RAND_MAX;
        if (probability < 0.1) // spawn frequency (increases speed proportionally)
        {
            asteroids.push_back(Asteroid(rand() % window_width, window_height, 20, 1.5));
        }
    }

    virtual ~Game();
    void init();
    //void keyPressed(unsigned char key, int x, int y);
    //void keyUp(unsigned char key, int x, int y);
    void gameover();
    void resetGame();
    void keyOperations();
    void resultsdisplay();
    void Instructionscreen();
    void display();
    void reshape(int width, int height);


    std::vector<bool> keyStates;
};
// Game *Game::instancePtr = new Game();
#endif // GAME_H
