#include "figure.h"
#include "game.h"
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
bool Figure::check(){
    return false;
}
void Figure::step(int x, int y){
    if(can_go(x,y)){
        this->x = x;
        this->y = y;
        for(int i = 0; i < Game::figures.size();++i){
            if(Game::figures[i]->getX() == x && Game::figures[i]->getY() == y){
                if(Game::figures[i]->getCol() != this->colour) Game::figures.erase(Game::figures.begin()+i);
            }
        }
        Game::check_over();
        Game::turn =!Game::turn;
    }
}
bool Figure::can_go(){
    std::vector<std::pair<int, int>> available = this->probableAttack();
    for(int i = 0; i < available.size();++i)if(can_go(available[i].first, available[i].second)) return true;
    return false;
}
bool Figure::can_go(int x, int y){
    if(this->x == x && this->y == y)return false;
    int prevX = this->x, prevY = this->y;
    Figure * eaten;
    bool found = false, eaten_f=false;
    std::vector<std::pair<int, int>> probableSt = this->probableAttack();
    for(int i = 0; i < probableSt.size();++i){
        if(probableSt[i].first == x && probableSt[i].second == y){
            if(check_for_collision(x,y)){
                found = true;
                break;
            }
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
        if(!check_for_check()){
                this->x = prevX;
                this->y = prevY;
                if(eaten_f)Game::figures.push_back(eaten);
                return false;
        }
        this->x = prevX;
        this->y = prevY;
        if(eaten_f)Game::figures.push_back(eaten);
        return true;
    }
    else  return false;
}
bool Figure::check_for_collision(int x, int y){
    for(int i = 0; i < Game::figures.size();++i){
        if(Game::figures[i]->getX() == x && Game::figures[i]->getY() == y && Game::figures[i]->getCol() == this->colour){
            return false;
        }
    }
    return true;
}
bool Figure::check_for_check(){
    for(int i = 0; i < Game::figures.size();++i){
          if(Game::figures[i]->check() && Game::figures[i]->getCol() == this->colour){
                return false;
          }
    }
    return true;
}
bool Figure::fig_on_field(int x, int y){
    return (x>=0)&&(x<8)&&(y>=0)&& (y<8);
}

