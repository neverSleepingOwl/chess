#ifndef KON_H
#define KON_H
#include <figure.h>
#include <vector>

class kon : public Figure
{
public:
    kon(int,int,int);
    void step(int, int);
    std::vector<std::pair<int, int>> probableAttack();
    bool check();
    bool can_go();
};

#endif // KON_H
