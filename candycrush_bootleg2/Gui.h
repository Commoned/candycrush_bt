#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Gui.h"
#include <QPainter>
#include "Bubble.h"
#include "Special.h"
#include <qtimer.h>



class Gui : public QMainWindow
{
    Q_OBJECT

public:
    Gui(QWidget* parent = Q_NULLPTR);
    
    
    void onaddWidget(void* bub, int x, int y);

    void onRemoveWidget();
    
    void updateTimer();
    void endGame();
    void mainLoop();
    void updateView(void* bubs[12][12]);

    int clickedX=0;
    int clickedY = 0;
    int clickedXM = 0;
    int clickedYM = 0;
    bool click= false;
    bool pressed = false;
    bool pressedMove = false;
    bool clean = false;
    char input = 'X';
    int zug = 0;
    bool init = true;
    void* strg;
    
    QTimer* timerTick;
    QTimer* timer;

private slots:
    
    

private:
    Ui::GuiClass ui;
    //Steuerung* strg;
    QEventLoop loop;
    
};
