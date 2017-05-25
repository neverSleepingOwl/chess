#include "peshka.h"
#include <game.h>
Peshka::Peshka(int x, int y, int colour)
{
    this->x = x;
    this->y = y;
    this->colour = colour;
    this->image.load("../resources/peshka"+QString::number(colour)+".png");
    this->step_done = false;
}

std::vector<std::pair<int, int>> Peshka::probableAttack(){
    std::pair<int, int> temp;
    std::vector<std::pair<int, int>> output;
    if(!this->colour){
        if(this->x>=1){
            temp.first = this->x-1;
            temp.second = this->y - 1;
            output.push_back(temp);
        }
        if (this->x<=7){
            temp.first = this->x+1;
            temp.second = this->y-1;
            output.push_back(temp);
        }
    }
    else{
        if(this->x>=1){
            temp.first = this->x-1;
            temp.second = this->y+1;
            output.push_back(temp);
        }
        if (this->x<=7){
            temp.first = this->x+1;
            temp.second = this->y+1;
            output.push_back(temp);
        }
    }
    for(int i = 0; i < output.size();++i)
        if(output[i].first == this->x && output[i].second == this->y){
            output.erase(output.begin()+i);
            break;
        }
    return output;
}


void Peshka::step(int x, int y){
    if(this->x == x && this->y == y)return;
    int prevX = this->x, prevY = this->y;
    Figure * eaten;
    bool eaten_f=false, step_available  = false;
    if(this->x == x){//step of figure
        if(!this->colour){//for white figures colour = 0
            if(this->y== y+1){
                step_available = check_for_collision(x,y);
            }
            if(this->y== y+2 && !this->step_done){
                step_available = check_for_collision(x,y) && check_for_collision(x,y+1);
            }
            if(step_available){
                this->x = x;
                this->y = y;
            }
        }
        else{
            if(this->y == y-1){
                step_available = check_for_collision(x,y);
            }
            if(this->y == y-2 && !this->step_done){
                step_available = check_for_collision(x,y) && check_for_collision(x,y-1);
            }
            if(step_available){
                this->x = x;
                this->y = y;
            }
        }
    }
    else{//attack
        std::vector<std::pair<int, int>> probAttack = this->probableAttack();
        for(int i = 0; i < probAttack.size();++i){
            if(probAttack[i].first == x && probAttack[i].second == y){
                for(int j = 0; j < Game::figures.size();++j){
                    if(Game::figures[j]->getX() == x && Game::figures[j]->getY() == y && Game::figures[j]->getCol() != this->colour){
                        this->x = x;
                        this->y = y;
                        eaten = Game::figures[j];
                        Game::figures.erase(Game::figures.begin()+j);
                        eaten_f = true;
                        step_available = true;
                        break;
                    }
                }
            }
        }
    }
    if(!check_for_check()){
            this->x = prevX;
            this->y = prevY;
            if(eaten_f)Game::figures.push_back(eaten);
            return;
    }
    if(step_available){
        Game::check_over();
        Game::turn =!Game::turn;
        this->step_done = true;
    }
}

bool Peshka::can_go(int, int){
    if(this->x == x && this->y == y)return false;
    int prevX = this->x, prevY = this->y;
    Figure * eaten;
    bool eaten_f=false, step_available  = false;
    if(this->x == x){//step of figure
        if(!this->colour){//for white figures colour = 0
            step_available = true;
            if(this->y== y+1){
                step_available = check_for_collision(x,y);
            }
            if(this->y== y+2 && !this->step_done){
                step_available = check_for_collision(x,y) && check_for_collision(x,y+1);
            }
            if(step_available){
                return true;
            }
        }
        else{
            if(this->y == y-1){
                step_available = check_for_collision(x,y);
            }
            if(this->y == y-2 && !this->step_done){
                step_available = check_for_collision(x,y) && check_for_collision(x,y-1);
            }
            if(step_available){
                return true;
            }
        }
    }
    else{//attack
        std::vector<std::pair<int, int>> probAttack = this->probableAttack();
        for(int i = 0; i < probAttack.size();++i){
            if(probAttack[i].first == x && probAttack[i].second == y){
                for(int j = 0; j < Game::figures.size();++j){
                    if(Game::figures[j]->getX() == x && Game::figures[j]->getY() == y && Game::figures[j]->getCol() != this->colour){
                        this->x = x;
                        this->y = y;
                        eaten = Game::figures[j];
                        Game::figures.erase(Game::figures.begin()+j);
                        eaten_f = true;
                        step_available = true;
                        break;
                    }
                }
            }
        }
    }
    if(!check_for_check()){
            this->x = prevX;
            this->y = prevY;
            if(eaten_f)Game::figures.push_back(eaten);
            return false;
    }
    if(step_available){
        this->x = prevX;
        this->y = prevY;
        if(eaten_f)Game::figures.push_back(eaten);
        return true;
    }
    else return false;
}

bool Peshka::check_for_collision(int x, int y){
    for(int i = 0; i < Game::figures.size();++i){
        if(Game::figures[i]->getX() == x && Game::figures[i]->getY() == y){
            return false;
        }
    }
    return true;
}

bool Peshka::can_go(){
    bool out = Figure::can_go();
    int x1 = this->x,x2 = this->x,y1 = this->y+(this->colour > 0)?1:(-1), y2 = this->y+(this->colour > 0)?2:(-2);
    out = out || can_go(x1,y1) || can_go(x2,y2);
    return out;
}
