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

bool Slon::check(){
    return false;
}

void Slon::step(int x, int y){
    if(this->x == x && this->y == y)return;
    int prevX = this->x, prevY = this->y;
    Figure * eaten;
    bool found = false, eaten_f=false;
    std::vector<std::pair<int, int>> probableSt = this->probableAttack();
    for(int i = 0; i < probableSt.size();++i){
        if(probableSt[i].first == x && probableSt[i].second == y){
            found = true;
            break;
        }
    }
    if(found){
        for(int i = 0; i < Game::figures.size();++i){
            if(Game::figures[i]->getX() == x && Game::figures[i]->getY() == y && Game::figures[i]->getCol() != this->colour){//for eating
                eaten = Game::figures[i];
                Game::figures.erase(Game::figures.begin()+i);
                eaten_f = true;
            }
        }
        this->x = x;
        this->y = y;
        for(int i = 0; i < Game::figures.size();++i){
            if(Game::figures[i]->check() && Game::figures[i]->getCol() != this->colour){
                this->x = prevX;
                this->y = prevY;
                if(eaten_f)Game::figures.push_back(eaten);
                return;
            }
        }
        Game::turn =!Game::turn;
    }
}
