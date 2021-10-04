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
                    bloques.push_back(scene->addRect(j*50,i*50,50,50,QPen(QColor(255,255,255,0)),bloquegris));

                }
                else if(a[i][j]==0){
                    cont++;
                    if(cont==1){
                        rect=scene->addRect(j*51,i*51,42,42,QPen(QColor(255,255,255,0)),Jugador);
                    }
                    else if(cont>3){
                        if(cont==aleatorio){
                            scene->addRect(j*50,i*50,50,50,QPen(),Puerta);
                            ladrillos.push_back(scene->addRect(j*50,i*50,50,50,QPen(QColor(255,255,255,0)),bloqueladrillo));
                        }
                        aleatorio2= rand()%(3-0+1)+0;
                        if(aleatorio2==2){
                            ladrillos.push_back(scene->addRect(j*50,i*50,50,50,QPen(QColor(255,255,255,0)),bloqueladrillo));
                        }
                    }
                }
            }
         }
        ui->graphicsView->setScene(scene);
        ui->graphicsView->show();
}

void MainWindow::keyPressEvent(QKeyEvent *e){

    QImage im1("../Bomberman/images/Abajo.png"),im2("../Bomberman/images/Jugador.png"),im3("../Bomberman/images/LadoI.png");
    QImage im4("../Bomberman/images/Arriba.png"),im5("../Bomberman/images/LadoD.png"),im6("../Bomberman/images/Bomba.png");
    QBrush ab1(im1),ab(im2),li(im3),arr(im4),ld(im5),bom(im6);
    switch (e->key()) {
    case Qt::Key_A:
      {
        posx-=5;
        rect->setBrush(li);
        if(colisionparedes()){
            posx+=10;
        }
      }
        break;
    case Qt::Key_W:
      {
        posy-=5;
        rect->setBrush(arr);
        if(colisionparedes()){
            posy+=10;
        }
      }
        break;
    case Qt::Key_D:
      {
        posx+=5;
        rect->setBrush(ld);
        if(colisionparedes()){
            posx-=10;
        }
      }
        break;
    case Qt::Key_S:
      {
        posy+=5;
        rect->setBrush(ab1);
        if(colisionparedes()){
            posy-=10;
        }
      }
        break;
    case Qt::Key_Space:
      {
        posx2=posx+50;
        posy2=posy+50;
        bomba=scene->addRect(posx+50,posy+50,50,50,QPen(QColor(255,255,255,0)),bom);
        //posx2+=20;
        //posy2+=20;
        QTimer::singleShot(2000,this,SLOT(explosion()));
      }
        break;
   }
    rect->setPos(posx,posy);
    ui->graphicsView->setSceneRect(posx-100,posy-100,300,300);
}

bool MainWindow::colisionparedes(){
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
void MainWindow::colisionexplosion(){
    QImage im1("../Bomberman/images/expladrillo.png");
    QBrush ladrillo(im1);
    explotar1->hide();
    explotar2->hide();
    for(auto item:ladrillos){
        if(explotar1->collidesWithItem(item)){
            item->setBrush(ladrillo);
            destruir.push_back(item);
            ladrillos.remove(item);
        }
        if(explotar2->collidesWithItem(item)){
            item->setBrush(ladrillo);
            destruir.push_back(item);
            ladrillos.remove(item);
        }
    }
    QTimer::singleShot(2000,this,SLOT(explotar()));
}
void MainWindow::explosion(){
    QImage im1("../Bomberman/images/Explosion1.png"),im2("../Bomberman/images/Explosion2.png");
    QBrush exp1(im1),exp2(im2);
    explotar1=scene->addRect(posx2+25,posy2-5,20,100,QPen(QColor(255,255,255,0)),exp1);
    explotar2=scene->addRect(posx2-5,posy2+25,100,20,QPen(QColor(255,255,255,0)),exp2);
    bomba->hide();
    QTimer::singleShot(1000,this,SLOT(colisionexplosion()));

}
void MainWindow::explotar(){
    for(auto item:destruir){
        item->hide();
    }

}
MainWindow::~MainWindow()
{
    delete ui;
}

