#include "Gui.h"
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <qevent.h>
#include <qmimedata.h>
#include <qdrag.h>

Gui::Gui(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    
    

    //QObject::connect(ui.pushButton, &QPushButton::clicked, this, &Gui::onaddWidget);
    
    
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
    
}



void Gui::drawCircle(QPainter *painter,std::string col ,int offsetX, int offsetY)
{
   // QPainter painter(this);
    
    painter->setPen(Qt::white);
    painter->setBrush(Qt::white);
    painter->drawEllipse(1*offsetX,1*offsetY,50,50);
    painter->setBackgroundMode(Qt::BGMode::TransparentMode);
    ui.pushButton->setText("Button");
}


void Gui::onaddWidget(void* bub, int x , int y)
{
    /*
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(ui.frame->layout());

    QPixmap pixmap;
    
    
    for (int x = 0; x<12; x++)
    {
        QHBoxLayout* hLayout = new QHBoxLayout(ui.centralWidget);

        for (int y = 0;y<12;y++)
        {
            //QString buttonText = tr(static_cast<Bubble*>(bub[x-1][y-1])->getcol().c_str());
            std::string col;
            
            col = static_cast<Bubble*>(bub[x][y])->getcol();
            

            QPushButton* button = new QPushButton("", ui.frame);
            
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
            button->setStyleSheet("border:5px solid #ffffff;");
          
            button->setIconSize(pixmap.rect().size());

            //layout->addWidget(button, x, y, 1, 1);
            hLayout->addWidget(button);
            
            
            //QObject::connect(button, &QPushButton::clicked,this, &Gui::onRemoveWidget);
        }
        layout->insertLayout(0, hLayout);
        
    }
    */
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
    button->show();

    QObject::connect(button, &QPushButton::clicked, this, &Gui::onRemoveWidget);

}


void Gui::onRemoveWidget()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    

    QLabel* label = ui.label;
   
    
    QFrame* frame = ui.frame;

    int kek = frame->frameGeometry().x();
    label->setText(QString::fromStdString("Click Next Bubble!"));
    //label->setText(QString::number(button->size().width()));
    //label2->setText(QString::number(button->size().height()));



}


void Gui::updateView(void* bubs[12][12])
{
    QObjectList list = ui.frame->children();

    ui.label->setText(QString::number(list.count()));
}

