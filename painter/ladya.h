#ifndef LADYA_H
#define LADYA_H
#include <figure.h>
class Ladya : public Figure
{
public:
    Ladya(int, int, int);
    void step(int, int);
    std::vector<std::pair<int, int>> probableAttack();
    bool check();
    bool can_go();
};

#endif // LADYA_H
