#ifndef PESHKA_H
#define PESHKA_H
#include "figure.h"
class Peshka : public Figure
{
public:
    Peshka(int, int, int);
    void step(int,int);
    std::vector<std::pair<int,int> > probableAttack();
    bool check();
 private:
    bool step_done;
};

#endif // PESHKA_H
