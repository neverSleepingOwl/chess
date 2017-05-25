#include "kon.h"
#include <game.h>
kon::kon(int x, int y, int colour)
{
    this->x = x;
    this->y = y;
    this->colour = colour;
    this->image.load("../resources/kon"+QString::number(colour)+".png");
}

std::vector<std::pair<int, int>> kon::probableAttack(){
    int tX,tY;
    qDebug()<<"K";
    std::vector<std::pair<int, int>> output,temp = {{1,-2},{2,-1},{2,1},{1,2},
                                               {-1,2},{-2,1},{-2,-1},{-1,-2}};
    for(int i = 0; i < temp.size();++i){
        tX = temp[i].first + this->x;
        tY = temp[i].second + this->y;
        if(fig_on_field(tX,tY) && check_for_collision(tX,tY)){
            output.push_back(std::pair<int,int>(tX, tY));
        }
    }
    return output;
}
