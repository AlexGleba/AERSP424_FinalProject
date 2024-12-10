# Game

#ifndef GAME_H
#define GAME_H
#include <vector>
#include <deque>
#include <string>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

// Forward declaration of Pacman and Ghost classes
class Spacecraft;
class Asteroid;
class DrawObjects;

class Game {
private:
    Spacecraft& spacecraft;
    Asteroid& asteroid;
    bool replay;
    bool over;
    float square_size;
    float xincrements;
    float yincrements;
    float xincrementa;
    float yincrementa;
   
    int time_interval;
    std::vector<DrawObjects*> drawobjects;
    bool moveLeft;
    bool moveRight;
    float x_spacecraft;
    float y_spacecraft;
    float x_asteroid;
    float y_asteroid;
    // std::vector<float> asteroid positions; (not sure if needed)

public:
    Game(Spacecraft& s, Asteroid& a);
    virtual ~Game();
    void init();   
    void keyPressed(unsigned char key, int x, int y);
    void keyUp(unsigned char key, int x, int y);
    void resetGame();
    void keyOperations();
    void gameover();
    void resultsdisplay();
    void Instructionscreen();
    void display();
    void reshape(int w_resize, int h_resize);
    std::vector<bool> keyStates;
};

#endif // GAME_H
