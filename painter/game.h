#ifndef GAME_H
#define GAME_H
#include "figure.h"
#include <vector>
#include <QString>

class Game
{
public:
    Game();
    static std::vector<Figure *> figures;
    static bool turn, clicked;
    static int temporaryFig, gameOver;
    static void check_over();
};

#endif // GAME_H
