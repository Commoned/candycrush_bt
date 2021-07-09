#include "Gui.h"
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <qevent.h>
#include <qmimedata.h>
#include <qdrag.h>
#include "Steuerung.h"
#include <qtimer.h>
#include <qcursor.h>


Gui::Gui(QWidget *parent)
    : QMainWindow(parent)
{
    
    ui.setupUi(this);
    
    timerTick = new QTimer(this);
    timer = new QTimer(this);

    timerTick->start(1000);

    

    QObject::connect(ui.startButton, &QPushButton::clicked, this, &Gui::mainLoop);
    
    connect(timer, &QTimer::timeout, this, &Gui::endGame);
}


void Gui::updateTimer()
{
    //ui.timeLabel->setText(QString::number(timer->remainingTime() ));
    
    double lcdValue = std::double_t(timer->remainingTime() / 1000);
    static_cast<Steuerung*>(strg)->setremTime(lcdValue);
    ui.lcdNumber->display(lcdValue);
    //updateView(static_cast<Steuerung*>(strg)->bubs);
}

void Gui::endGame()
{
    ui.frame->setDisabled(true);
    timer->stop();
    init = true;
    zug = 0;
    ui.startButton->setDisabled(false);
}

void Gui::mainLoop()
{
    if (init == true)
    {
        strg = new Steuerung(this);
        init = false;
        connect(timerTick, &QTimer::timeout, this, &Gui::updateTimer);
        ui.startButton->setDisabled(true);
        ui.frame->setDisabled(false);
    }
    int x, y;


    bool clean = false;

    
    timerTick->stop();
    timer->stop();
    ui.centralWidget->setCursor(Qt::CursorShape::WaitCursor);
    if(!click)
    {
        clean = false;
        while (clean == false)
        {
            clean = static_cast<Steuerung*>(strg)->update();

        }
        if (zug == 0)
        {
            static_cast<Steuerung*>(strg)->setscore(0);
            static_cast<Steuerung*>(strg)->setremTime(20);
            zug++;
        }
        static_cast<Steuerung*>(strg)->update();
    }

    if (static_cast<Bubble*>(static_cast<Steuerung*>(strg)->bubs[clickedX][clickedY])->getcol() != "purple" && pressed)
    {
        pressed = false;
    }
    
    if (clickedX == clickedXM && clickedY - 1 == clickedYM ) { input = 'U'; }
    if (clickedX == clickedXM && clickedY + 1 == clickedYM) { input = 'D'; }
    if (clickedX - 1 == clickedXM   && clickedY == clickedYM) { input = 'L'; }
    if (clickedX + 1 == clickedXM && clickedY == clickedYM) { input = 'R'; }
    
    if (static_cast<Steuerung*>(strg)->checkValidInput(clickedX, clickedY, input) == 1 && pressedMove || static_cast<Bubble*>(static_cast<Steuerung*>(strg)->bubs[clickedX][clickedY])->getcol() == "purple" && click) {
        static_cast<Steuerung*>(strg)->makemove(clickedX, clickedY, input);
        click = false;
        pressedMove = false;
        
        mainLoop();
    }
    
    input = 'X';
    
    static_cast<Steuerung*>(strg)->analyze();
   
    timer->start(static_cast<Steuerung*>(strg)->getremTime() * 1000);
    timerTick->start(10);
    ui.centralWidget->setCursor(Qt::CursorShape::ArrowCursor);
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

    if (!click)
    {
        clickedX = (button->geometry().x() - 5) / 48;
        clickedY = (button->geometry().y() - 5) / 48;
        click = true;
        pressedMove = false;
    }
    else {
        clickedXM = (button->geometry().x() - 5) / 48;
        clickedYM = (button->geometry().y() - 5) / 48;
        pressedMove = true;
        click = false;
    }

    pressed = true;
    
    
    mainLoop();
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
                int abil;
                abil = static_cast<Special*>(bubs[x][y])->getability();
                switch (abil)
                {
                case 1:pixmap.load("special.jpg");
                    break;
                case 2:pixmap.load("specialHbomb.jpg");
                    break;
                case 3:pixmap.load("specialVbomb.jpg");
                    break;
                case 4:pixmap.load("special.jpg");
                    break;

                default:pixmap.load("special.jpg");
                    break;
                }
                
            }
            QIcon ButtonIcon(pixmap);

            button->setIcon(ButtonIcon);
            button->setStyleSheet("border:2px solid #ffffff;");
            button->setFixedSize(QSize(48, 48));
            button->setIconSize(pixmap.rect().size());
            button->setCursor(Qt::CursorShape::PointingHandCursor);

            button->move(QPoint((x * 48)+5, (y * 48)+5));

            QObject::connect(button, &QPushButton::clicked, this, &Gui::onRemoveWidget);

            button->show();

            ui.scoreLabel->setText(QString::number(static_cast<Steuerung*>(strg)->getScore())); 
            
            QCoreApplication::processEvents();
        }
    }
}

