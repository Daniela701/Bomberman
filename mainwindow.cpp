#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    srand(time(NULL));
    int aleatorio,aleatorio2,cont=0;
    aleatorio = rand()%(249-1+1)+1;

    ui->setupUi(this);
    scene=new QGraphicsScene;
    QImage im1(bloque);
    QImage im2(ladrillo);
    QImage im3(puerta);
    QBrush bloquegris(im1);
    QBrush bloqueladrillo(im2);
    QBrush Puerta(im3);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
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
                    scene->addRect(j*50,i*50,50,50,QPen(),bloquegris);

                }
                else if(a[i][j]==0){
                    cont++;
                    if(cont==aleatorio){
                        scene->addRect(j*50,i*50,50,50,QPen(),Puerta);
                        scene->addRect(j*50,i*50,50,50,QPen(),bloqueladrillo);
                    }
                    aleatorio2= rand()%(3-0+1)+0;
                    if(aleatorio2==2){
                        scene->addRect(j*50,i*50,50,50,QPen(),bloqueladrillo);
                    }

                }
            }
        }
}

MainWindow::~MainWindow()
{
    delete ui;
}

