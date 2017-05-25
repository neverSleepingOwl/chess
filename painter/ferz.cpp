#include "ferz.h"
#include <game.h>

Ferz::Ferz(int x, int y, int colour)
{
    this->x = x;
    this->y = y;
    this->colour = colour;
     this->image.load("../resources/ferz"+QString::number(colour)+".png");
}

std::vector<std::pair<int , int>> Ferz::probableAttack(){
    qDebug()<<"f";
    Ladya l(this->x, this->y, this->colour);
    Slon s(this->x, this->y,this->colour);
    std::vector<std::pair<int, int>> output = l.probableAttack();
    std::vector<std::pair<int, int>> output2 = s.probableAttack();
    for(int  i = 0; i < output2.size();++i){
        output.push_back(output2[i]);
    }
    return output;
}

