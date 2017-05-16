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
    std::pair<int, int> tmp;
    std::vector<std::pair<int, int>> output;
    if((this->x+1)<8 && (this->y-2) >= 0){
        tmp.first = this->x+1;
        tmp.second = this->y-2;
        output.push_back(tmp);
    }
    if((this->x+2)<8 && (this->y-1) >= 0){
        tmp.first = this->x+2;
        tmp.second = this->y-1;
        output.push_back(tmp);
    }
    if((this->x+2)<8 && (this->y+1) < 8){
        tmp.first = this->x+2;
        tmp.second = this->y+1;
        output.push_back(tmp);
    }
    if((this->x+1)<8 && (this->y+2) < 8){
        tmp.first = this->x+1;
        tmp.second = this->y+2;
        output.push_back(tmp);
    }
    if((this->x-1)>=0 && (this->y+2) <8){
        tmp.first = this->x-1;
        tmp.second = this->y+2;
        output.push_back(tmp);
    }
    if((this->x-2)>=0 && (this->y+1) < 8){
        tmp.first = this->x-2;
        tmp.second = this->y+1;
        output.push_back(tmp);
    }
    if((this->x-2)>=0 && (this->y-1) >= 0){//
        tmp.first = this->x-2;
        tmp.second = this->y-1;
        output.push_back(tmp);
    }
    if((this->x-1)>=0 && (this->y-2) >= 0){//
        tmp.first =this->x-1;
        tmp.second = this->y-2;
        output.push_back(tmp);
    }
    for(int i = 0; i < output.size();++i)
        for(int j = 0; j < Game::figures.size();++j){
            if(output[i].first == Game::figures[j]->getX() && output[i].second == Game::figures[j]->getY()){
                if(this->colour == Game::figures[j]->getCol())output.erase(output.begin()+i);//remove collisions
            }
        }
    return output;
}

void kon::step(int x, int y){
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
        Game::check_over();
        Game::turn =!Game::turn;
    }
}

bool kon::check(){
    return false;
}

bool kon::can_go(){
    int prevX = this->x, prevY = this->y;
    Figure * eaten;
    bool found = false, eaten_f=false;
    std::vector<std::pair<int, int>> probableSt = this->probableAttack();
    for(int i = 0; i < probableSt.size();++i){
        for(int j = 0; j < Game::figures.size();++j){
            if(Game::figures[j]->getX() == probableSt[i].first && Game::figures[j]->getY() == probableSt[i].second && Game::figures[j]->getCol() != this->colour){//for eating
                eaten = Game::figures[j];
                Game::figures.erase(Game::figures.begin()+j);
                eaten_f = true;
            }
        }
        this->x = probableSt[i].first;
        this->y = probableSt[i].second;
        found = true;
        for(int k = 0; k < Game::figures.size();++k){
            if(Game::figures[k]->check() && Game::figures[k]->getCol() == this->colour){
                this->x = prevX;
                this->y = prevY;
                if(eaten_f)Game::figures.push_back(eaten);
                found = false;
            }
        }
        if(found){
            this->x = prevX;
            this->y = prevY;
             if(eaten_f)Game::figures.push_back(eaten);
            return true;
        }
    }
    return false;
}
