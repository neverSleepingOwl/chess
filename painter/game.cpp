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
    for(int i = 0; i < Game::figures.size();++i){
        if(Game::figures[i]->check() && Game::figures[i]->probableAttack().empty()){
            Game::gameOver = Game::figures[i]->getCol()+1;
            return;
        }
    }
    bool flag = true;
    for(int  i = 0; i < Game::figures.size();++i){
        if(!(Game::figures[i]->getCol() != Game::turn && Game::figures[i]->probableAttack().empty())){
            flag = false;
        }
    }
    if(flag){
        Game::gameOver = 5;
        return;
    }
}
