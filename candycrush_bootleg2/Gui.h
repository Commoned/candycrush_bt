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
    
    void update(void* bub[12][12]);

    void drawCircle( QPainter* painter, std::string col, int offsetX, int offsetY);
    
private slots:
  //  void drawCircle();


private:
    Ui::GuiClass ui;
    
    void paintEvent(QPaintEvent* e);
    //void drawCircle(QPainter* painter, std::string col, int offsetX, int offsetY);

    
};
