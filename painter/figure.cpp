#include "figure.h"

Figure::Figure()
{
}

int Figure::getCol(){
    return this->colour;
}
QImage Figure::getImg(){
    return this->image;
}
int Figure::getX(){
    return this->x;
}
int Figure::getY(){
    return this->y;
}
std::vector<std::pair<int, int>> Figure::probableAttack(){}
bool Figure::check(){}
void Figure::step(int x, int y){}
bool Figure::can_go(){}
bool Figure::check_for_collision(){
    return true;//TODO fix this
}
