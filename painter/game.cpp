#include "game.h"
Game::Game()
{

}
bool Game::turn = true;//true for white figures
std::vector<Figure *> Game::figures;
int Game::gameOver = 0;
bool Game::clicked = false;
int  Game::temporaryFig = -1;

void Game::check_over(){
     bool flag = true;
    for(int i = 0; i < Game::figures.size();++i){
        if(Game::figures[i]->check()){
            for(int j = 0; j < Game::figures.size();++j){
                if(Game::figures[i]->getCol() == Game::figures[j]->getCol() && Game::figures[j]->can_go()){
                    flag = false;
                    qDebug()<<j;
                    qDebug()<<Game::figures[j]->getX();
                    qDebug()<<Game::figures[j]->getY();
                }
            }
            if(flag){
                qDebug()<<"a";
                Game::gameOver = (!Game::figures[i]->getCol())+1;
                return;
            }
        }

    }
    for(int  i = 0; i < Game::figures.size();++i){
        if(figures[i]->can_go() && figures[i]->getCol() != turn){
            flag = false;
        }
    }
    if(flag){
        Game::gameOver = 5;
        return;
    }
}
