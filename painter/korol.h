#ifndef KOROL_H
#define KOROL_H

#include <vector>
#include <figure.h>
class korol : public Figure
{
public:
    korol(int, int, int);
    std::vector<std::pair<int, int>> probableAttack();
    bool check();
};

#endif // KOROL_H
