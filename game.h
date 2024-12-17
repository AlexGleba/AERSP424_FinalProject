// include headers
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

// create the game class
class Game
{
    // private members
private:
    Spacecraft &spacecraft;
    std::vector<Asteroid> asteroids;        // vector to store asteroids
    bool replay;                            // used to determine if game is replaying
    bool over = false;                      // used to determine if the game is over
    float square_size;                      // square size of the game
    float xincrements;                      // increment of x for the spacecraft
    float yincrements;                      // increment of y for the spacecraft
    float xincrementa;                      // increment of x for the asteroids
    float yincrementa;                      // increment of y for the asteroids
    std::vector<std::vector<bool>> bitmap1; // bitmap for storing game state
    int time_interval = 0;                  // time interval of the game
    std::vector<DrawObjects *> drawobjects; // vector of drawable objects
    bool moveLeft;                          // determine whether the spacecraft moves left
    bool moveRight;                         // determine whether the spacecraft moves right
    float x_s;                              // x position of the spacecraft
    float y_s;                              // y position of the spacecraft

public:
    // public members
    const int window_width = 750;  // define window width
    const int window_height = 750; // define window height
    Game(Spacecraft &s);           // game constructor

    // initialize the game and spawn the first asteroid
    void initialize()
    {
        // store the asteroids
        asteroids.push_back(Asteroid(rand() % window_width, window_height, 20, 1.5));
    }

    // update the positions of the asteroids
    void updateAsteroids()
    {
        for (auto &asteroid : asteroids)
        {

            asteroid.y -= asteroid.speed; // moves asteroids down the screen
            if (asteroid.y < 0)           // if asteroid off the screen
            {
                asteroid.y = window_height;         // resets the asteroid to the top of the screen
                asteroid.x = rand() % window_width; // randomly select a x-position to reset the asteroid
            }
        }

        // Spawn new asteroids
        float probability = 100 * (float)rand() / RAND_MAX;
        if (probability < 0.1) // spawn frequency (increases speed proportionally)
        {
            // store the asteroids
            asteroids.push_back(Asteroid(rand() % window_width, window_height, 20, 1.5));
        }
    }

    virtual ~Game();                     // destructor
    void init();                         // initialize the game
    void gameover();                     // handle game over circumstance
    void resetGame();                    // handle game reset circumstance
    void keyOperations();                // handle key operations
    void resultsdisplay();               // handle displaying results
    void Instructionscreen();            // display instruction screen
    void display();                      // display the game
    void reshape(int width, int height); // handle reshaping circumstance
    std::vector<bool> keyStates;         // vector for storing the state of the keys
};

#endif // GAME_H