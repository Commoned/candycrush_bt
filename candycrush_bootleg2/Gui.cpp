#include "Gui.h"

Gui::Gui(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    
    //QObject::connect(ui.pushButton,SIGNAL(clicked()),this,SLOT(drawCircle()));
}

void Gui::paintEvent(QPaintEvent* e) {
    Q_UNUSED(e);

    
    QPainter painter(this);
    for (int x = 0; x < 12; x++)
    {
        for (int y = 0; y < 12; y++)
        {
            drawCircle(&painter, "t", x*50, y*50);
            
        }
    }
    QMainWindow().update();
}

void Gui::update(void* bub[12][12]) 
{
    QPainter painter(this);
    drawCircle(&painter, "red",1,1);

}

void Gui::drawCircle(QPainter *painter,std::string col ,int offsetX, int offsetY)
{
   // QPainter painter(this);
    
    painter->setPen(Qt::white);
    painter->setBrush(Qt::white);
    painter->drawEllipse(1*offsetX,1*offsetY,50,50);
    painter->setBackgroundMode(Qt::BGMode::TransparentMode);
    ui.pushButton->setText("KekW");
}

