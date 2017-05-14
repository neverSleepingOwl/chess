#ifndef FERZ_H
#define FERZ_H

#include <figure.h>
#include <game.h>
#include <ladya.h>
#include <slon.h>
#include <vector>

class Ferz : public Figure
{
public:
    Ferz(int ,int, int);
    std::vector<std::pair<int, int>> probableAttack();
    void step(int, int);
    bool check();
};

#endif // FERZ_H
