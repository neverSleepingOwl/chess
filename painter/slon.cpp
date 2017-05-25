#include "slon.h"
#include <game.h>
Slon::Slon(int x, int y, int colour)
{
    this->x = x;
    this->y = y;
    this->colour = colour;
     this->image.load("../resources/slon"+QString::number(colour)+".png");
}

std::vector<std::pair<int, int>> Slon::probableAttack(){
    std::pair<int, int> tmp;
    std::vector<std::pair<int, int>> output;
    bool flag = false;//flag is a simpliest way to break from outer loops without goto
    for(int i = this->x+1, j = this->y+1;i < 8 && j < 8;++i,++j){
        for(int k = 0; k < Game::figures.size();++k){
            if(Game::figures[k]->getX() == i && Game::figures[k]->getY() == j){
                if(Game::figures[k]->getCol() != this->colour){
                    tmp.first = i;
                    tmp.second = j;
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
        tmp.second = j;
        output.push_back(tmp);
    }
    for(int i = this->x-1, j = this->y-1;i >=0 && j >=0;--i,--j){
        for(int k = 0; k < Game::figures.size();++k){
            if(Game::figures[k]->getX() == i && Game::figures[k]->getY() == j){
                if(Game::figures[k]->getCol() != this->colour){
                    tmp.first = i;
                    tmp.second = j;
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
        tmp.second = j;
        output.push_back(tmp);
    }
    for(int i = this->x-1, j = this->y+1;i >=0 && j < 8;--i,++j){
        for(int k = 0; k < Game::figures.size();++k){
            if(Game::figures[k]->getX() == i && Game::figures[k]->getY() == j){
                if(Game::figures[k]->getCol() != this->colour){
                    tmp.first = i;
                    tmp.second = j;
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
        tmp.second = j;
        output.push_back(tmp);
    }
    for(int i = this->x+1, j = this->y-1;i < 8 && j>=0;++i,--j){
        for(int k = 0; k < Game::figures.size();++k){
            if(Game::figures[k]->getX() == i && Game::figures[k]->getY() == j){
                if(Game::figures[k]->getCol() != this->colour){
                    tmp.first = i;
                    tmp.second = j;
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
        tmp.second = j;
        output.push_back(tmp);
    }
    for(int i = 0; i < output.size();++i)
        if(output[i].first == this->x && output[i].second == this->y) output.erase(output.begin()+i);
    return output;
}
