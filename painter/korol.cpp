#include "korol.h"
#include "game.h"

korol::korol(int x, int y, int colour)
{
    this->x = x;
    this->y = y;
    this->colour = colour;
     this->image.load("../resources/korol"+QString::number(colour)+".png");
}

std::vector<std::pair<int, int>> korol::probableAttack(){
    std::pair<int, int> tmp;
    std::vector<std::pair<int, int>> output;
    for(int i = this->x - 1;i <= this->x+1;++i){
        for(int j = this->y - 1; j <= this->y+1;++j){
            if(i>=0 && i<8 && j>=0 && j<8 && (this->x != i || this->y != j)){
                tmp.first = i;
                tmp.second = j;
                output.push_back(tmp);
            }
        }
    }
    for(int i = 0; i < output.size();++i)
        for(int j = 0; j < Game::figures.size();++j){
            if(output[i].first == Game::figures[j]->getX() && output[i].second == Game::figures[j]->getY()){
                if(this->colour == Game::figures[j]->getCol())output.erase(output.begin()+i);//remove collisions
            }
        }
    return output;
}
void korol::step(int x, int y){//TODO master with chekmate
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

bool korol::check(){
    std::vector<std::pair<int, int>> tmp;
    for(int  i = 0; i < Game::figures.size();++i){
        tmp = Game::figures[i]->probableAttack();
        for(int j = 0; j < tmp.size();++j){
            if(this->colour != Game::figures[i]->getCol()){
                if(this->x == tmp[j].first && this->y == tmp[j].second){
                    return true;
                }
            }
        }
    }
    return false;
}
