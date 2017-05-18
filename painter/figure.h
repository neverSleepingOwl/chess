#ifndef FIGURE_H
#define FIGURE_H
#include <QString>
#include <vector>
#include <string>
#include <QImage>
#include <QDebug>
class Figure
{
public:
    Figure();
    int getX();
    int getY();
    int getCol();
    QImage getImg();
    virtual void step(int,int);
    virtual std::vector<std::pair <int, int> > probableAttack();
    virtual bool check();
    virtual bool can_go();
protected:
    int x,y,colour;
    bool check_for_collision();
    QImage image;
};

#endif // FIGURE_H
