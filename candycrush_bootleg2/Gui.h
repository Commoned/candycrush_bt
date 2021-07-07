#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Gui.h"
#include <QPainter>
#include "Bubble.h"
#include "Special.h"



class Gui : public QMainWindow
{
    Q_OBJECT

public:
    Gui(QWidget *parent = Q_NULLPTR);
    
    //void update(void* bub[12][12]);

    
    void onaddWidget(void* bub, int x, int y);

    void onRemoveWidget();

    void mainLoop();
    void updateView(void* bubs[12][12]);

    int clickedX=100;
    int clickedY=100;

    
private slots:
  
    

private:
    Ui::GuiClass ui;
    //Steuerung* strg;
    QEventLoop loop;

    
};
