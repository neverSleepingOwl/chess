#ifndef LADYA_H
#define LADYA_H
#include <figure.h>
class Ladya : public Figure
{
public:
    Ladya(int, int, int);
    std::vector<std::pair<int, int>> probableAttack();
};

#endif // LADYA_H
