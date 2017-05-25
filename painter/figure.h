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
    virtual bool can_go(int, int);
protected:
    int x,y,colour;
    bool check_for_collision(int, int);
    bool check_for_check();
    virtual bool fig_on_field(int, int);
    QImage image;
};

#endif // FIGURE_H
