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
    static bool turn,gameOver, clicked;
    static int temporaryFig;
};

#endif // GAME_H
