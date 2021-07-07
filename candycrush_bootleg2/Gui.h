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

    void drawCircle( QPainter* painter, std::string col, int offsetX, int offsetY);
    void onaddWidget(void* bub[12][12]);

    void onRemoveWidget();
    void updateView(void* bubs[12][12]);
private slots:
  //  void drawCircle();
    

private:
    Ui::GuiClass ui;
    
    void paintEvent(QPaintEvent* e);
    //void drawCircle(QPainter* painter, std::string col, int offsetX, int offsetY);

    
};
