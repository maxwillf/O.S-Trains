#include "trem.h"
#include <QtCore>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool trilho1_livre = true;
bool trilho2_livre = true;
bool trilho3_livre = true;
bool trilho4_livre = true;
bool trilho5_livre = true;
bool trilho6_livre = true;
bool trilho7_livre = true;

//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    velocidade = 100;
}

void Trem::mudarVelocidade(int velocidade){
    this->velocidade = velocidade;
}

//Função a ser executada após executar trem->START
void Trem::run(){
    while(true){
        switch(ID){
        case 1:     //Trem 1
            if (y == 30 && x == 310){
                std::unique_lock<std::mutex> lk(mtx);
                cv.wait(lk, []{return trilho1_livre && trilho3_livre;});
                trilho1_livre = false;
                trilho3_livre = false;
                lk.unlock();
                cv.notify_all();
            }
            else if (y == 150 && x == 320){
                trilho1_livre = true;
                cv.notify_all();
            }
            else if (y == 150 && x == 180){
                trilho3_livre = true;
                cv.notify_all();
            }
            // movimentacao
            if (y == 30 && x <330)
                x+=10;
            else if (x == 330 && y < 150)
                y+=10;
            else if (x > 60 && y == 150)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 2: //Trem 2
            if (y == 30 && x == 580) {
                std::unique_lock<std::mutex> lk(mtx);
                cv.wait(lk, []{return trilho1_livre && trilho2_livre && trilho4_livre && trilho5_livre;});
                trilho1_livre = false;
                trilho2_livre = false;
                trilho4_livre = false;
                trilho5_livre = false;
                lk.unlock();
                cv.notify_all();
            }
            else if (y == 150 && x == 580){
                trilho2_livre = true;
                cv.notify_all();
            }
            else if (x == 440 && y == 150){
                trilho5_livre = true;
                cv.notify_all();
            }
            else if (x == 330 && y == 130){
                trilho4_livre = true;
                cv.notify_all();
            }
            else if (y == 30 && x == 350){
                trilho1_livre = true;
                cv.notify_all();
            }
            // movimentacao
            if (y == 30 && x <600)
                x+=10;
            else if (x == 600 && y < 150)
                y+=10;
            else if (x > 330 && y == 150)
                x-=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 3: //Trem 3
            if (x == 200 && y == 170){
                std::unique_lock<std::mutex> lk(mtx);
                cv.wait(lk, []{return trilho3_livre && trilho4_livre && trilho7_livre;});
                trilho3_livre = false;
                trilho4_livre = false;
                trilho7_livre = false;
                lk.unlock();
                cv.notify_all();
            }
            else if (x == 350 && y == 150){
                trilho3_livre = true;
                cv.notify_all();
            }
            else if (x == 470 && y == 170){
                trilho4_livre = true;
                cv.notify_all();
            }
            else if (x == 450 && y == 290){
                trilho7_livre = true;
                cv.notify_all();
            }
            // movimentacao
            if (y == 290 && x > 200)
                x-=10;
            else if (x < 470 && y == 150)
                x+=10;
            else if (x == 470 && y <= 290)
                y+=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 4: //Trem 4
            if (x == 490 && y == 290){
                std::unique_lock<std::mutex> lk(mtx);
                cv.wait(lk, []{return trilho5_livre && trilho6_livre && trilho7_livre;});
                trilho5_livre = false;
                trilho6_livre = false;
                trilho7_livre = false;
                lk.unlock();
                cv.notify_all();
            }
            else if (x == 490 && y == 150){
                trilho7_livre = true;
                cv.notify_all();
            }
            else if (x == 630 && y == 150){
                trilho5_livre = true;
                cv.notify_all();
            }
            else if (x == 740 && y == 170){
                trilho6_livre = true;
                cv.notify_all();
            }
            // movimentacao
            if (y == 290 && x > 470)
                x-=10;
            else if (x < 740 && y == 150)
                x+=10;
            else if (x == 740 && y < 290)
                y+=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 5: //Trem 5
            if (x == 760 && y == 150){
                std::unique_lock<std::mutex> lk(mtx);
                cv.wait(lk, []{return trilho2_livre && trilho6_livre;});
                trilho2_livre = false;
                trilho6_livre = false;
                lk.unlock();
                cv.notify_all();
            }
            else if(x == 610 && y == 130){
                trilho6_livre = true;
                cv.notify_all();
            }
            else if(x == 630  && y == 30){
                trilho2_livre = true;
                cv.notify_all();
            }
            // movimentacao
            if (y == 150 && x > 610)
                x-=10;
            else if (x < 880 && y == 30)
                x+=10;
            else if (x == 880 && y < 150)
                y+=10;
            else
                y-=10;
            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        default:
            break;
        }
        msleep(velocidade);
    }
}




