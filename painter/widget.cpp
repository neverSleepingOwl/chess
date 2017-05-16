#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    Game::figures.push_back(new korol(4,7,0));//white king
    Game::figures.push_back(new korol(4,0,1));//black kin*/
    Game::figures.push_back(new Ferz(3,7,0));//white ferz
    Game::figures.push_back(new Ferz(3,0,1));//black ferz

    Game::figures.push_back(new Ladya(0,7,0));//white ladya 1
    Game::figures.push_back(new Ladya(7,7,0));//white ladya 2
    Game::figures.push_back(new Ladya(0,0,1));//black ladya 1
    Game::figures.push_back(new Ladya(7,0,1));//black ladya 2*/
    Game::figures.push_back(new kon(1,7,0));//white kon 1
    Game::figures.push_back(new kon(6,7,0));//white kon 2
    Game::figures.push_back(new kon(1,0,1));//black kon 1
    Game::figures.push_back(new kon(6,0,1));//black kon 2
    Game::figures.push_back(new Slon(2,7,0));//white slon 1
    Game::figures.push_back(new Slon(5,7,0));//white slon 2
    Game::figures.push_back(new Slon(2,0,1));//black slon 1
    Game::figures.push_back(new Slon(5,0,1));//black slon 2
    for(int i = 0; i < 8;++i){
        Game::figures.push_back(new Peshka(i,6,0));//white peshka
        Game::figures.push_back(new Peshka(i,1,1));//black one
    }
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}
void Widget::paintEvent(QPaintEvent * event){
    Q_UNUSED(event);
    QPainter painter(this);
    if(Game::gameOver == 0){
        QImage background_picture("../resources/bg.png");
        painter.drawImage(0,0,background_picture.scaled(QSize(400,400)));
        for(int i = 0; i < Game::figures.size();++i)
            painter.drawImage(Game::figures[i]->getX()*50, Game::figures[i]->getY()*50, Game::figures[i]->getImg().scaled(QSize(50,50)));
    }
    else if(Game::gameOver == 1){
        QImage white_wins("../resources/win1.png");
        painter.drawImage(0,0,white_wins.scaled(QSize(400,400)));
    }
    else if(Game::gameOver == 2){
        QImage black_wins("../resources/win1.jpg");
        painter.drawImage(0,0,black_wins.scaled(QSize(400,400)));
    }
    else{
        QImage in_draw("../resources/draw.jpg");
        painter.drawImage(0,0,in_draw.scaled(QSize(400,400)));
    }
}
void Widget::mousePressEvent(QMouseEvent *event){
    if(Game::gameOver)return;
    int x1 = event->x(), y1 = event->y();
    int x_f  = x1/50, y_f = y1/50;
   // if(event->button() == Qt::LeftButton){
        if(!Game::clicked){
            for(int i = 0; i < Game::figures.size();++i){
                if(x_f == Game::figures[i]->getX() && y_f == Game::figures[i]->getY())
                    if(Game::turn != Game::figures[i]->getCol()){
                        Game::clicked = true;
                        Game::temporaryFig =  i;
                    }
            }
        }
        else{
            Game::figures[Game::temporaryFig]->step(x_f,y_f);
            Game::clicked = false;
            repaint();
        }
   // }
}

void Widget::on_pushButton_clicked()
{
    Game::figures.clear();
    Game::figures.push_back(new korol(4,7,0));//white king
    Game::figures.push_back(new korol(4,0,1));//black kin*/
    Game::figures.push_back(new Ferz(3,7,0));//white ferz
    Game::figures.push_back(new Ferz(3,0,1));//black ferz

    Game::figures.push_back(new Ladya(0,7,0));//white ladya 1
    Game::figures.push_back(new Ladya(7,7,0));//white ladya 2
    Game::figures.push_back(new Ladya(0,0,1));//black ladya 1
    Game::figures.push_back(new Ladya(7,0,1));//black ladya 2*/
    Game::figures.push_back(new kon(1,7,0));//white kon 1
    Game::figures.push_back(new kon(6,7,0));//white kon 2
    Game::figures.push_back(new kon(1,0,1));//black kon 1
    Game::figures.push_back(new kon(6,0,1));//black kon 2
    Game::figures.push_back(new Slon(2,7,0));//white slon 1
    Game::figures.push_back(new Slon(5,7,0));//white slon 2
    Game::figures.push_back(new Slon(2,0,1));//black slon 1
    Game::figures.push_back(new Slon(5,0,1));//black slon 2
    for(int i = 0; i < 8;++i){
        Game::figures.push_back(new Peshka(i,6,0));//white peshka
        Game::figures.push_back(new Peshka(i,1,1));//black one
    }
    Game::turn = true;
    Game::gameOver = 0;
    Game::clicked = false;
    repaint();
}
