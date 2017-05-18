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
void Peshka::step(int x, int y){
    if(this->x == x && this->y == y)return;
    int prevX = this->x, prevY = this->y;
    Figure * eaten;
    bool eaten_f=false, step_available  = false;
    if(this->x == x){//step of figure
        if(!this->colour){//for white figures colour = 0
            if(this->y== y+1){
                step_available = true;
                for(int i = 0; i < Game::figures.size();++i){
                    if(Game::figures[i]->getX() == x && Game::figures[i]->getY() == y){
                        step_available = false;
                    }
                }
            }
            if(this->y== y+2 && !this->step_done){
                step_available = true;
                for(int i = 0; i < Game::figures.size();++i){
                    if(Game::figures[i]->getX() == x && Game::figures[i]->getY() == y){
                        step_available = false;
                    }
                    if(Game::figures[i]->getX() == x && Game::figures[i]->getY() == y+1){
                        step_available = false;
                    }
                }
            }
            if(step_available){
                this->x = x;
                this->y = y;
            }
        }
        else{
            if(this->y == y-1){
                step_available = true;
                for(int i = 0; i < Game::figures.size();++i){
                    if(Game::figures[i]->getX() == x && Game::figures[i]->getY() == y){//check for collision
                        step_available = false;
                    }
                }
            }
            if(this->y == y-2 && !this->step_done){
                step_available = true;
                for(int i = 0; i < Game::figures.size();++i){
                    if(Game::figures[i]->getX() == x && Game::figures[i]->getY() == y){//check for collision
                        step_available = false;
                    }
                    if(Game::figures[i]->getX() == x && Game::figures[i]->getY() == y-1){
                        step_available = false;
                    }
                }
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
    for(int i = 0; i < Game::figures.size();++i){
        if(Game::figures[i]->check() && Game::figures[i]->getCol() == this->colour){
            this->x = prevX;
            this->y = prevY;
            if(eaten_f)Game::figures.push_back(eaten);
            return;
        }
    }
    if(step_available){
        this->step_done = true;
        Game::check_over();
        Game::turn =! Game::turn;
    }
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
bool Peshka::check(){
    return false;
}

bool Peshka::can_go(){
    int prevX = this->x, prevY = this->y, x1 = this->x,y1 = this->y, x2 = this->x, y2 = this->y;
    Figure * eaten;
    y1+=(this->colour == 0)?(-1):1;
    y2 +=+(this->colour == 0)?(-2):2;
    bool eaten_f=false, step_available  = true;
    for(int i = 0; i < Game::figures.size();++i)
        if(Game::figures[i]->getX() == x1 && Game::figures[i]->getY() == y1){
            step_available = false;
            break;
        }
    if(step_available){
        this->x = x1;
        this->y = y1;
    }
    for(int i = 0; i < Game::figures.size();++i){
          if(Game::figures[i]->check() && Game::figures[i]->getCol() == this->colour){
                this->x = prevX;
                this->y = prevY;
                step_available = false;
                break;
          }
    }
    if(step_available){
        this->x = prevX;
        this->y = prevY;
        return true;
    }
    if(!this->step_done){
        for(int i = 0; i < Game::figures.size();++i){
            if(Game::figures[i]->getX() == x2 && Game::figures[i]->getY() == y2){
                step_available = false;
                break;
            }
            if(Game::figures[i]->getX() == x2 && Game::figures[i]->getY() == (y2+(this->colour)?(-1):(1))){
                    step_available = false;
                    break;
            }
        }
        if(step_available){
            this->x = x2;
            this->y = y2;
        }
        for(int i = 0; i < Game::figures.size();++i){
              if(Game::figures[i]->check() && Game::figures[i]->getCol() == this->colour){
                    this->x = prevX;
                    this->y = prevY;
                    step_available = false;
                    break;
              }
        }
        if(step_available){
            this->x = prevX;
            this->y = prevY;
            return true;
        }
    }
    std::vector<std::pair<int, int>> probAttack = this->probableAttack();
    for(int i = 0; i < probAttack.size();++i){
        for(int j = 0; j < Game::figures.size();++j){
            if(Game::figures[j]->getX() == probAttack[i].first && Game::figures[j]->getY() == probAttack[i].second && Game::figures[j]->getCol() != this->colour){
                this->x = probAttack[i].first;
                this->y = probAttack[i].second;
                eaten = Game::figures[j];
                Game::figures.erase(Game::figures.begin()+j);
                eaten_f = true;
                step_available = true;
                break;
            }
        }
        if(eaten_f){
            for(int k = 0; k < Game::figures.size();++k){
                  if(Game::figures[k]->check() && Game::figures[k]->getCol() == this->colour){
                        this->x = prevX;
                        this->y = prevY;
                        if(eaten_f)Game::figures.push_back(eaten);
                        step_available = false;
                        break;
                  }
            }
            if(step_available){
                this->x = prevX;
                this->y = prevY;
                if(eaten_f)Game::figures.push_back(eaten);
                return true;
            }
        }

    }
    return false;
}
