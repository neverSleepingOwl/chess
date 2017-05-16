#ifndef SLON_H
#define SLON_H
#include <vector>
#include<figure.h>
class Slon : public Figure
{
public:
    Slon(int, int, int);
    std::vector<std::pair<int, int>> probableAttack();
    void step(int, int);
    bool can_go();
    bool check();
};

#endif // SLON_H
