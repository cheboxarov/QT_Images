#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    img = new QImage(":/main/img/test.jpg");
    resize(img->width()*2, img->height()+50+300);

    up_brith = new QPushButton(this);
    up_brith->setGeometry(20, img->height()+20, 60, 20);
    up_brith->setText("+");
    QObject::connect(up_brith, &QPushButton::clicked, this, &MainWindow::upClick);

    down_brith = new QPushButton(this);
    down_brith->setGeometry(100, img->height()+20, 60, 20);
    down_brith->setText("-");
    QObject::connect(down_brith, &QPushButton::clicked, this, &MainWindow::downClick);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::upClick()
{
    changeBrith(10);
    qDebug() << "up";
}

void MainWindow::downClick()
{
    changeBrith(-10);
}

void MainWindow::changeBrith(int n)
{
    QImage tmp = *img;
    qint32 width = img->width();
    qint32 height = img->height();
    for(qint32 i = 0; i < height; ++i)
    {
        QRgb* tempLine = reinterpret_cast<QRgb*>(img->scanLine(i));
        for(qint32 j = 0; j < width; ++j)
        {
            int r = qRed(*tempLine) + n;
            int g = qGreen(*tempLine) + n;
            int b = qBlue(*tempLine) + n;
            *tempLine++ = qRgba(r > 255 ? 255 : r < 0 ? 0 : r,
                                g > 255 ? 255 : g < 0 ? 0 : g,
                                b > 255 ? 255 : b < 0 ? 0 : b,
                                255 );
        }
    }
    update();
}

void MainWindow::paintEvent(QPaintEvent* ev)
{
    QPainter painter(this);
    painter.drawImage(img->rect(), *img, img->rect());
    QImage inv = *img;
    inv.invertPixels(QImage::InvertRgb);
    painter.drawImage(inv.width(), 0, inv);

    QPixmap map(":/main/img/test2.jpg");
    map.scaled(QSize(300,300));
    painter.drawPixmap(QRect(0,height()-300, 300,300), map);
}
