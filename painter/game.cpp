#include "game.h"
Game::Game()
{

}
bool Game::turn = true;//true for white figures
std::vector<Figure *> Game::figures;
bool Game::gameOver = false;
bool Game::clicked = false;
int  Game::temporaryFig = -1;
