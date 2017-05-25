#include "ladya.h"
#include <game.h>
Ladya::Ladya(int x, int y, int colour)
{
    this->x = x;
    this->y = y;
    this->colour = colour;
     this->image.load("../resources/ladya"+QString::number(colour)+".png");
}

std::vector<std::pair<int, int>> Ladya::probableAttack(){
    std::pair<int, int> tmp;
    std::vector<std::pair<int, int>> output;
    qDebug()<<"l";
    bool flag = false;//flag is a simpliest way to break from outer loops without goto
    for(int i = this->x-1;i>=0;--i){//y = const, x from fig.position to 0
        for(int j = 0; j < Game::figures.size();++j){//checking collisions with all figures
            if(i == Game::figures[j]->getX() && this->y == Game::figures[j]->getY()){//collision
                if(Game::figures[j]->getCol() != this->colour){//able to eat figure
                    tmp.first = i;
                    tmp.second = this->y;
                    output.push_back(tmp);
                }
                flag = true;
                break;
            }
        }
        if(flag){
            flag = false;
            break;
        }
        tmp.first = i;
        tmp.second = this->y;
        output.push_back(tmp);
    }
    for(int i = this->x+1;i<8;++i){//y = const, x from fig.position to 8
        for(int j = 0; j < Game::figures.size();++j){//checking collisions with all figures
            if(i == Game::figures[j]->getX() && this->y == Game::figures[j]->getY()){//collision
                if(Game::figures[j]->getCol() != this->colour){//able to eat figure
                    tmp.first = i;
                    tmp.second = this->y;
                    output.push_back(tmp);
                }
                flag = true;
                break;
            }
        }
        if(flag){
            flag = false;
            break;
        }
        tmp.first = i;
        tmp.second = this->y;
        output.push_back(tmp);
    }
    for(int i = this->y-1;i>=0;--i){//x = const, y from fig.position to 0
        for(int j = 0; j < Game::figures.size();++j){//checking collisions with all figures
            if(i == Game::figures[j]->getY() && this->x == Game::figures[j]->getX()){//collision
                if(Game::figures[j]->getCol() != this->colour){//able to eat figure
                    tmp.first = this->x;
                    tmp.second = i;
                    output.push_back(tmp);
                }
                flag = true;
                break;
            }
        }
        if(flag){
            flag = false;
            break;
        }
        tmp.first = this->x;
        tmp.second = i;
        output.push_back(tmp);
    }
    for(int i = this->y+1;i<8;++i){//x = const, y from fig.position to 9
        for(int j = 0; j < Game::figures.size();++j){//checking collisions with all figures
            if(i == Game::figures[j]->getY() && this->x == Game::figures[j]->getX()){//collision
                if(Game::figures[j]->getCol() != this->colour){//able to eat figure
                    tmp.first = this->x;
                    tmp.second = i;
                    output.push_back(tmp);
                }
                flag = true;
                break;
            }
        }
        if(flag){
            flag = false;
            break;
        }
        tmp.first = this->x;
        tmp.second = i;
        output.push_back(tmp);
    }
    for(int i = 0; i < output.size();++i)
        if(output[i].first == this->x && output[i].second == this->y) output.erase(output.begin()+i);
    return output;
}

