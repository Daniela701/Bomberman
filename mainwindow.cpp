#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    srand(time(NULL));
    aleatorio = rand()%(249-1+1)+1;

    ui->setupUi(this);
    scene=new QGraphicsScene;
    QImage im1("../Bomberman/images/Bloquegris.png"),im2("../Bomberman/images/Bloqueladrillo.png");
    QImage im3("../Bomberman/images/Puerta.png"),im4("../Bomberman/images/Jugador.png");
    QBrush bloquegris(im1),bloqueladrillo(im2),Puerta(im3),Jugador(im4);

    int a[13][31]=
    {
          {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
          {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
          {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
          {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
          {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
          {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
          {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
          {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
          {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
          {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
          {1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1},
          {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
          {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        };
        for(int i=0;i<13;i++){
            for(int j=0;j<31;j++){
                if(a[i][j]==1){
                    bloques.push_back(scene->addRect(j*50,i*50,50,50,QPen(),bloquegris));

                }
                else if(a[i][j]==0){
                    cont++;
                    if(cont==1){
                        rect=scene->addRect(j*52,i*52,40,40,QPen(QColor("#408b2c")),Jugador);
                    }
                    else if(cont>3){
                        if(cont==aleatorio){
                            scene->addRect(j*50,i*50,50,50,QPen(),Puerta);
                            ladrillos.push_back(scene->addRect(j*50,i*50,50,50,QPen(),bloqueladrillo));
                        }
                        aleatorio2= rand()%(3-0+1)+0;
                        if(aleatorio2==2){
                            ladrillos.push_back(scene->addRect(j*50,i*50,50,50,QPen(),bloqueladrillo));
                        }
                    }
                }
            }
         }
        ui->graphicsView->setScene(scene);
        ui->graphicsView->show();
}

void MainWindow::keyPressEvent(QKeyEvent *e){

    switch (e->key()) {
    case Qt::Key_A:
      {
        posx-=5;
        if(colision()){
            posx+=8;
        }
      }
        break;
    case Qt::Key_W:
      {
        posy-=5;
        if(colision()){
            posy+=8;
        }
      }
        break;
    case Qt::Key_D:
      {
        posx+=5;
        if(colision()){
            posx-=8;
        }
      }
        break;
    case Qt::Key_S:
      {
        posy+=5;
        if(colision()){
            posy-=8;
        }
      }
        break;
    }
    rect->setPos(posx,posy);
    ui->graphicsView->setSceneRect(posx-100,posy-100,300,300);
}

bool MainWindow::colision(){
    rect->setPos(posx,posy);
    for(auto item:bloques){
        if(rect->collidesWithItem(item)){
            return true;
        }
    }
    for(auto item:ladrillos){
        if(rect->collidesWithItem(item)){
            return true;
        }
    }
    return false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

