#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QImage>
#include <QTimer>
#include <QDebug>
#include <iostream>
#include <ctime>
#include <QKeyEvent>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <list>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    bool colisionpersonaje();
    bool colisionenemigos();
    void juegoterminado();
    void juegoganado();
    void move();
    ~MainWindow();
protected:
    void keyPressEvent(QKeyEvent *e);
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QString datos;
    int Puntaje=0,Tiempo=300,Vidas=3,conttiempo=0;
    string Puntaje1,Tiempo1,Vidas1;
    int aleatorio,aleatorio2,cont=0,cont2=0,cont3=1,cont4=0,cont5=0,cont6=0,posx=0,posy=0,posx2=0,posy2=0,xenemy=0,yenemy=0,num;
    bool pass;
    list<QGraphicsRectItem *> bloques,ladrillos,Enemies,destruir;
    list<QGraphicsRectItem *>::iterator elemento;
    list<int> pos,auxi,auxi2,posicionx;
    list<int> ::iterator Enemigo,posicion;
    QGraphicsRectItem *rect,*puerta,*bomba,*explotar1,*explotar2,*enemigos;
    QTimer *timerenemy;
private slots:
    void explosion();
    void explotar();
    void colisionexplosion();
    void moveEnemy();
    void cerrarjuego();
};
#endif // MAINWINDOW_H
