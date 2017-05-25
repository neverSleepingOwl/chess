#ifndef PESHKA_H
#define PESHKA_H
#include "figure.h"
class Peshka : public Figure
{
public:
    Peshka(int, int, int);
    void step(int,int);
    std::vector<std::pair<int,int> > probableAttack();
    bool can_go(int, int);
    bool can_go();
    bool check_for_collision(int, int);
 private:
    bool step_done;
};

#endif // PESHKA_H
