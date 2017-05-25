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
    bool step_available = true;
    for(int i = this->x - 1;i <= this->x+1;++i){
        for(int j = this->y - 1; j <= this->y+1;++j,step_available = true){
            if(i>=0 && i<8 && j>=0 && j<8 && (this->x != i || this->y != j)){
                for(int k = 0; k < Game::figures.size();++k){
                    if(this->colour == Game::figures[k]->getCol() &&
                       i == Game::figures[k]->getX() && j == Game::figures[k]->getY()){
                        step_available = false;
                        break;
                    }
                }
                if(step_available){
                    tmp.first = i;
                    tmp.second = j;
                    output.push_back(tmp);
                }
            }
        }
    }
    return output;
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
