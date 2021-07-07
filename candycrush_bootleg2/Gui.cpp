#include "Gui.h"
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <qevent.h>
#include <qmimedata.h>
#include <qdrag.h>
#include "Steuerung.h"



Gui::Gui(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
   
    QObject::connect(ui.startButton, &QPushButton::clicked, this, &Gui::mainLoop);
   
}

void Gui::mainLoop()
{
    Steuerung strg(this);
   
    updateView(strg.bubs);
    
    
    int x, y;
    char input;

    bool clean = false;
    
    int zug = 0; // temporary

    clean = false;
    while (clean == false)
    {
        clean = strg.update();
            
    }
    if (zug == 0)
    {
        strg.setscore(0);
        strg.update();
        zug++;
    }

    
    
        
    if (static_cast<Bubble*>(strg.bubs[clickedX][clickedY])->getcol() != "purple" && clickedX<12 && clickedY <12)
    {
        qDebug("KWK");
    }

    /*
    if (static_cast<Bubble*>(strg.bubs[clickedX][clickedY])->getcol() != "purple")
    {
            
    }
        

    if (strg.checkValidInput(x, y, input) == 1 || static_cast<Bubble*>(strg.bubs[x][y])->getcol() == "purple") {
        strg.makemove(x, y, input);
    }
    */
    strg.analyze();
   
}




void Gui::onaddWidget(void* bub, int x , int y)
{
  
    QPushButton* button = new QPushButton("",ui.frame);
    QPixmap pixmap;
    std::string col;

    col = static_cast<Bubble*>(bub)->getcol();

    if (col == "green")
    {
        pixmap.load("green.jpg");
    }
    if (col == "yellow")
    {
        pixmap.load("yellow.jpg");
    }
    if (col == "red")
    {
        pixmap.load("red.jpg");
    }
    if (col == "blue")
    {
        pixmap.load("blue.jpg");
    }
    if (col == "purple")
    {
        pixmap.load("special.jpg");
    }
    QIcon ButtonIcon(pixmap);

    button->setIcon(ButtonIcon);
    button->setStyleSheet("border:2px solid #ffffff;");
    button->setFixedSize(QSize(48, 48));
    button->setIconSize(pixmap.rect().size());

    button->move(QPoint(x*48,y*48));

    QObject::connect(button, &QPushButton::clicked, this, &Gui::onRemoveWidget);
    

    button->show();

    

}


void Gui::onRemoveWidget()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    

    QLabel* label = ui.label;
   
    
    QFrame* frame = ui.frame;

    int kek = frame->frameGeometry().x();
    label->setText(QString::number((button->geometry().x()-5)/48)+QString::fromStdString("")+ QString::number((button->geometry().y()-5)/48));
    //label->setText(QString::number(button->size().width()));
    //label2->setText(QString::number(button->size().height()));
    
    clickedX = (button->geometry().x() - 5) / 48;
    clickedY = (button->geometry().y() - 5) / 48;
    
    
    
    
}



void Gui::updateView(void* bubs[12][12])
{
    QObjectList list = ui.frame->children();
    
    for (auto it = list.begin(); it != list.end(); it++)
    {
        delete *it;
    }

    for (int x = 0; x < 12; x++)
    {
        for (int y = 0; y < 12; y++)
        {
            QPushButton* button = new QPushButton("", ui.frame);
            QPixmap pixmap;
            std::string col;

            col = static_cast<Bubble*>(bubs[x][y])->getcol();

            if (col == "green")
            {
                pixmap.load("green.jpg");
            }
            if (col == "yellow")
            {
                pixmap.load("yellow.jpg");
            }
            if (col == "red")
            {
                pixmap.load("red.jpg");
            }
            if (col == "blue")
            {
                pixmap.load("blue.jpg");
            }
            if (col == "purple")
            {
                pixmap.load("special.jpg");
            }
            QIcon ButtonIcon(pixmap);

            button->setIcon(ButtonIcon);
            button->setStyleSheet("border:2px solid #ffffff;");
            button->setFixedSize(QSize(48, 48));
            button->setIconSize(pixmap.rect().size());

            button->move(QPoint((x * 48)+5, (y * 48)+5));

            QObject::connect(button, &QPushButton::clicked, this, &Gui::onRemoveWidget);

            button->show();
            
            QCoreApplication::processEvents();
        }
    }
}

