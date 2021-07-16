#include "Gui.h"
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <qevent.h>
#include <qmimedata.h>
#include <qdrag.h>
#include "Controller.h"
#include <qtimer.h>
#include <qcursor.h>
#include <qstring.h>


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

/// <summary>
/// Tick timer to update actual game Timer
/// </summary>
void Gui::updateTimer()
{
    //ui.timeLabel->setText(QString::number(timer->remainingTime() ));
    
    double lcdValue = std::double_t(timer->remainingTime() / 1000);
    static_cast<Controller*>(strg)->setremTime(lcdValue);
    ui.lcdNumber->display(lcdValue);
    //updateView(static_cast<Controller*>(strg)->bubs);
}

/// <summary>
/// Function to end and restart the game
/// </summary>
void Gui::endGame()
{
    ui.frame->setDisabled(true);
    timer->stop();
    init = true;
    zug = 0;
    int hiScroe = ui.highScore->text().toInt();
    if (ui.highScore->text().toInt() < ui.scoreLabel->text().toInt())
    {
        ui.highScore->setText(ui.scoreLabel->text());
    }
    ui.startButton->setDisabled(false);
    delete static_cast<Controller*>(strg);
}

/// <summary>
/// Main loop which was originally in main.cpp
/// </summary>
void Gui::mainLoop()
{
    if (init == true)
    {
        strg = new Controller(this);
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
            clean = static_cast<Controller*>(strg)->update();
            
        }
        if (zug == 0)
        {
            static_cast<Controller*>(strg)->setscore(0);
            static_cast<Controller*>(strg)->setremTime(20);
            zug++;
        }
        static_cast<Controller*>(strg)->update();
    }

    if (static_cast<Bubble*>(static_cast<Controller*>(strg)->bubs[clickedX][clickedY])->getcol() != "purple" && pressed)
    {
        pressed = false;
    }
    
    if (clickedX == clickedXM && clickedY - 1 == clickedYM ) { input = 'U'; }
    if (clickedX == clickedXM && clickedY + 1 == clickedYM)  { input = 'D'; }
    if (clickedX - 1 == clickedXM   && clickedY == clickedYM){ input = 'L'; }
    if (clickedX + 1 == clickedXM && clickedY == clickedYM)  { input = 'R'; }
    
    if (static_cast<Controller*>(strg)->checkValidInput(clickedX, clickedY, input) == 1 && pressedMove || static_cast<Bubble*>(static_cast<Controller*>(strg)->bubs[clickedX][clickedY])->getcol() == "purple" && click) {
        static_cast<Controller*>(strg)->makemove(clickedX, clickedY, input);
        click = false;
        pressedMove = false;
        
        mainLoop();
    }
    
    input = 'X';
    static_cast<Controller*>(strg)->update();
    static_cast<Controller*>(strg)->analyze();
   
    timer->start(static_cast<Controller*>(strg)->getremTime() * 1000);
    timerTick->start(10);
    ui.centralWidget->setCursor(Qt::CursorShape::ArrowCursor);
}


/// <summary>
/// Function creates Bubbles on Press of game start
/// </summary>
/// <param name="bub"></param>
/// <param name="x"></param>
/// <param name="y"></param>
void Gui::onaddWidget(void* bub, int x , int y)
{
  
    QPushButton* button = new QPushButton("",ui.frame);
    QPixmap pixmap;
    std::string col;

    col = static_cast<Bubble*>(bub)->getcol();

    if (col == "green")
    {
        pixmap.load("creeper.png");
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

    QObject::connect(button, &QPushButton::clicked, this, &Gui::onClickedWidget);
    

    button->show();

}

/// <summary>
/// Saves which bubble(s) were pressed
/// </summary>
void Gui::onClickedWidget()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());

    if (!click)
    {
        _beep(400,100);
        clickedX = (button->geometry().x() - 5) / 48;
        clickedY = (button->geometry().y() - 5) / 48;
        click = true;
        pressedMove = false;
    }
    else {
        _beep(800, 100);
        clickedXM = (button->geometry().x() - 5) / 48;
        clickedYM = (button->geometry().y() - 5) / 48;
        pressedMove = true;
        click = false;
    }

    pressed = true;
    
    
    mainLoop();
}


/// <summary>
/// updates Field
/// </summary>
/// <param name="bubs"></param>
void Gui::updateView(void* bubs[12][12])
{
    QObjectList list = ui.frame->children(); // gets all Bubbles currently in frame

    for (auto it = list.begin(); it != list.end(); it++)
    {
        delete* it; // deletes all bubbles
    }
 
    for (int x = 0; x < 12; x++) // creates all bubbles again // this causes flickering
    {
        for (int y = 0; y < 12; y++)
        {
            
            QPushButton* button = new QPushButton("", ui.frame);
            QPixmap pixmap;
            std::string col;

            col = static_cast<Bubble*>(bubs[x][y])->getcol();
            //Setting of icons based on bubble color
            if (col == "green") 
            {
                pixmap.load("emerald.png");
            }
            if (col == "yellow")
            {
                pixmap.load("gold.png");
            }
            if (col == "red")
            {
                pixmap.load("redstone.png");
            }
            if (col == "blue")
            {
                pixmap.load("lapislazuli.png");
            }
            if (col == "purple")
            {
                int abil;
                abil = static_cast<Special*>(bubs[x][y])->getability();
                switch (abil)
                {
                case 1:pixmap.load("creeper.png");
                    break;
                case 2:pixmap.load("enderman.png");
                    break;
                case 3:pixmap.load("chicken.png");
                    break;
                case 4:pixmap.load("special_bomb.jpg");
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

            QObject::connect(button, &QPushButton::clicked, this, &Gui::onClickedWidget); // connects new bubbles to the removewidget function

            button->show();

            ui.scoreLabel->setText(QString::number(static_cast<Controller*>(strg)->getScore())); 
            
            QCoreApplication::processEvents();
        }
    }
}

