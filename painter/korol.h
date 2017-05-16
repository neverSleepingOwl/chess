#ifndef KOROL_H
#define KOROL_H

#include <vector>
#include <figure.h>
class korol : public Figure
{
public:
    korol(int, int, int);
    std::vector<std::pair<int, int>> probableAttack();
    void step(int, int);
    bool check();
    bool can_go();
};

#endif // KOROL_H
