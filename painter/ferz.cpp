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
    Ladya l(this->x, this->y, this->colour);
    Slon s(this->x, this->y,this->colour);
    std::vector<std::pair<int, int>> output = l.probableAttack();
    std::vector<std::pair<int, int>> output2 = s.probableAttack();
    for(int  i = 0; i < output2.size();++i){
        output.push_back(output2[i]);
    }
    return output;
}

bool Ferz::check(){
    return false;
}

void Ferz::step(int x, int y){
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
            if(Game::figures[i]->check() && Game::figures[i]->getCol() == this->colour){
                this->x = prevX;
                this->y = prevY;
                if(eaten_f)Game::figures.push_back(eaten);
                return;
            }
        }
        Game::turn =!Game::turn;Game::check_over();
    }
}

