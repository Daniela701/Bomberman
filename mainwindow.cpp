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
    QImage im3("../Bomberman/images/Puerta.png"),im4("../Bomberman/images/Jugador.png"),im5("../Bomberman/images/enemy1.png");
    QBrush bloquegris(im1),bloqueladrillo(im2),Puerta(im3),Jugador(im4),Bomberenemy(im5);

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
                        rect=scene->addRect(j*50+2,i*50+2,42,42,QPen(QColor(255,255,255,0)),Jugador);
                    }
                    else if(cont>3){
                        if(cont==aleatorio){
                            puerta=scene->addRect(j*50,i*50,50,50,QPen(),Puerta);
                            ladrillos.push_back(scene->addRect(j*50,i*50,50,50,QPen(QColor(255,255,255,0)),bloqueladrillo));
                        }
                        aleatorio2= rand()%(3-0+1)+0;
                        if(aleatorio2==2){
                            ladrillos.push_back(scene->addRect(j*50,i*50,50,50,QPen(QColor(255,255,255,0)),bloqueladrillo));
                        }
                        else if (aleatorio2==0){
                            cont2++;
                            if (cont2%5==0){
                                Enemies.push_back(scene->addRect(j*50+2,i*50+2,45,45,QPen(QColor(255,255,255,0)),Bomberenemy));
                            }
                        }
                    }
                }
            }
         }
        num=Enemies.size();
        for(int i=0;i<num;i++){
            pos.push_back(1);
            posicionx.push_back(0);
        }
        timerenemy=new QTimer(this);
        connect(timerenemy,SIGNAL(timeout()),this,SLOT(moveEnemy()));
        timerenemy->start(100);
        ui->textBrowser->setText("PUNTAJE:0");
        ui->textBrowser_2->setText("TIEMPO:300");
        ui->textBrowser_3->setText("VIDAS:3");
        ui->graphicsView->setScene(scene);
        ui->graphicsView->show();
}
void MainWindow::juegoterminado(){
    QImage over("../Bomberman/images/gameover.jpg");
    QBrush game(over);
    if(Vidas==0 or Tiempo==0){
        ui->graphicsView->resize(800,450);
        ui->graphicsView->setForegroundBrush(game);
        QTimer::singleShot(3000,this,SLOT(cerrarjuego()));
    }
}
void MainWindow::juegoganado(){
    QImage win("../Bomberman/images/YouWin.jpg");
    QBrush game(win);
    ui->graphicsView->resize(600,600);
    ui->graphicsView->setForegroundBrush(game);
    QTimer::singleShot(3000,this,SLOT(cerrarjuego()));

}
void MainWindow::keyPressEvent(QKeyEvent *e){

    QImage im1("../Bomberman/images/Abajo.png"),im2("../Bomberman/images/LadoI.png");
    QImage im3("../Bomberman/images/Arriba.png"),im4("../Bomberman/images/LadoD.png"),im5("../Bomberman/images/Bomba.png");
    QBrush ab(im1),li(im2),arr(im3),ld(im4),bom(im5);
    switch (e->key()) {
    case Qt::Key_A:
      {
        posx-=5;
        rect->setBrush(li);
        if(colisionpersonaje()){
            posx+=10;
        }
      }
        break;
    case Qt::Key_W:
      {
        posy-=5;
        rect->setBrush(arr);
        if(colisionpersonaje()){
            posy+=10;
        }
      }
        break;
    case Qt::Key_D:
      {
        posx+=5;
        rect->setBrush(ld);
        if(colisionpersonaje()){
            posx-=10;
        }
      }
        break;
    case Qt::Key_S:
      {
        posy+=5;
        rect->setBrush(ab);
        if(colisionpersonaje()){
            posy-=10;
        }
      }
        break;
    case Qt::Key_Space:
      {
        posx2=posx+50;
        posy2=posy+50;
        bomba=scene->addRect(posx+50,posy+50,50,50,QPen(QColor(255,255,255,0)),bom);
        QTimer::singleShot(2000,this,SLOT(explosion()));
      }
        break;
   }
    rect->setPos(posx,posy);
    ui->graphicsView->setSceneRect(posx-100,posy-100,300,300);
}

bool MainWindow::colisionpersonaje(){
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
    for(auto item:Enemies){
        if(item->collidesWithItem(rect)){
            juegoterminado();
            Vidas-=1;
            Vidas1= to_string(Vidas);
            Vidas1="VIDAS:"+Vidas1;
            datos = QString::fromStdString(Vidas1);
            ui->textBrowser_3->setText(datos);
        }
    }
    if(rect->collidesWithItem(puerta)){
        juegoganado();
    }
    return false;
}
void MainWindow::colisionexplosion(){
    QImage im1("../Bomberman/images/expladrillo.png"),im2("../Bomberman/images/KillEnemy.png");
    QBrush ladrillo(im1),Kill(im2);
    explotar1->hide();
    explotar2->hide();
    for(auto item:ladrillos){
        if(explotar1->collidesWithItem(item)){
            item->setBrush(ladrillo);
            destruir.push_back(item);
            ladrillos.remove(item);
            Puntaje+=50;
            Puntaje1= to_string(Puntaje);
            Puntaje1="PUNTAJE:"+Puntaje1;
            datos = QString::fromStdString(Puntaje1);
            ui->textBrowser->setText(datos);
        }
        if(explotar2->collidesWithItem(item)){
            item->setBrush(ladrillo);
            destruir.push_back(item);
            ladrillos.remove(item);
            Puntaje+=50;
            Puntaje1= to_string(Puntaje);
            Puntaje1="PUNTAJE:"+Puntaje1;
            datos = QString::fromStdString(Puntaje1);
            ui->textBrowser->setText(datos);
        }
    }
    for(auto item:Enemies){
        if(explotar1->collidesWithItem(item)){
            item->setBrush(Kill);
            destruir.push_back(item);
            Enemies.remove(item);
            Puntaje+=50;
            Puntaje1= to_string(Puntaje);
            Puntaje1="PUNTAJE:"+Puntaje1;
            datos = QString::fromStdString(Puntaje1);
            ui->textBrowser->setText(datos);
        }
        if(explotar2->collidesWithItem(item)){
            item->setBrush(Kill);
            destruir.push_back(item);
            Enemies.remove(item);
            Puntaje+=50;
            Puntaje1= to_string(Puntaje);
            Puntaje1="PUNTAJE:"+Puntaje1;
            datos = QString::fromStdString(Puntaje1);
            ui->textBrowser->setText(datos);
        }
    }
    if(explotar1->collidesWithItem(rect)){
        juegoterminado();
        Vidas-=1;
        Vidas1= to_string(Vidas);
        Vidas1="VIDAS:"+Vidas1;
        datos = QString::fromStdString(Vidas1);
        ui->textBrowser_3->setText(datos);
    }
    if(explotar2->collidesWithItem(rect)){
        juegoterminado();
        Vidas-=1;
        Vidas1= to_string(Vidas);
        Vidas1="VIDAS:"+Vidas1;
        datos = QString::fromStdString(Vidas1);
        ui->textBrowser_3->setText(datos);
    }
    QTimer::singleShot(2000,this,SLOT(explotar()));
}
bool MainWindow::colisionenemigos(){
    for(auto bloque:bloques){
         if(enemigos->collidesWithItem(bloque)){
              return true;
          }
      }
    for(auto ladrillo:ladrillos){
         if(enemigos->collidesWithItem(ladrillo)){
              return true;
          }
        }
    return false;
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
void MainWindow::move(){
    QImage im1("../Bomberman/images/enemy1.png"),im2("../Bomberman/images/enemy2.png");
    QBrush dere(im1),izquie(im2);

    if(colisionenemigos()){
        cont3*=-1;
    }
    auxi.push_back(cont3);
    if(cont3>0){
        enemigos->setBrush(dere);
    }
    else{
        enemigos->setBrush(izquie);
    }
    xenemy+=5*cont3;
    auxi2.push_back(xenemy);
    enemigos->setPos(xenemy,yenemy);
}
void MainWindow::moveEnemy(){
    conttiempo++;
    if(conttiempo>=10){
        juegoterminado();
        Tiempo-=1;
        Tiempo1= to_string(Tiempo);
        Tiempo1="TIEMPO:"+Tiempo1;
        datos = QString::fromStdString(Tiempo1);
        ui->textBrowser_2->setText(datos);
        conttiempo=0;
    }
    cont4=0;
    elemento=Enemies.begin();
    while(elemento!=Enemies.end()){
        enemigos= *elemento;
        cont4++;
        cont5=0;
        cont6=0;
        Enemigo=pos.begin();
        while(Enemigo!=pos.end()){
            cont5++;
            if(cont5==cont4){
              cont3= *Enemigo;
              break;
            }
            Enemigo++;
        }
        posicion=posicionx.begin();
        while(posicion!=posicionx.end()){
            cont6++;
            if(cont6==cont4){
                xenemy= *posicion;
                break;
            }
            posicion++;
        }
        move();
        elemento++;
    }
    pos=auxi;
    posicionx=auxi2;
    auxi.clear();
    auxi2.clear();
}
void MainWindow::cerrarjuego(){
    exit(1);
}
MainWindow::~MainWindow()
{
    delete ui;
}

