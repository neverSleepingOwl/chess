#ifndef SLON_H
#define SLON_H
#include <vector>
#include<figure.h>
class Slon : public Figure
{
public:
    Slon(int, int, int);
    std::vector<std::pair<int, int>> probableAttack();
};

#endif // SLON_H
