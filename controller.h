#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "controller.h"

class Controller
{
public:
    Controller() : speed(200), key(1), score(0) {}	// Constructor
    void Start();
    void Select();
    void DrawGame();
    int PlayGame();
    void UpdateScore(const int&);
	void UpdateaiScore(const int&);
    void RewriteScore();
	void RewriteaiScore();
    int Menu();
    void Game();
    int GameOver();
private:
    int speed;
    int key;
    int score;
	int aiscore;
};
#endif // CONTROLLER_H
