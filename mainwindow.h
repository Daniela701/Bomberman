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
    bool colisionparedes();
    ~MainWindow();
protected:
    void keyPressEvent(QKeyEvent *e);
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    int aleatorio,aleatorio2,cont=0,posx=0,posy=0,posx2=0,posy2=0;
    list<QGraphicsRectItem *> bloques;
    list<QGraphicsRectItem *> ladrillos;
    list<QGraphicsRectItem *> destruir;
    list<QGraphicsRectItem *>::iterator elemento;
    QGraphicsRectItem *rect,*bomba,*explotar1,*explotar2;
private slots:
    void explosion();
    void explotar();
    void colisionexplosion();
};
#endif // MAINWINDOW_H
