#include <QtWidgets>
#include <QPalette>
#include <QPushButton>
#include <QIcon>
#include <QSize>

#include "Define.h"
// #include "Singleton.h"
#include "Thumbnail.h"
#include "ui_Thumbnail.h"

Thumbnail::Thumbnail(QString path,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Thumbnail)
{
    ui->setupUi(this);
    setupThumbnail(path);

    _path = QString(path);
}

void Thumbnail::setPathMethod(std::function<void(QString)> cb){
    this->pathcb = cb;
}

void Thumbnail::setupThumbnail(QString path){

    QPalette pal(palette());
//    pal.setColor(QPalette::Background, COLOR);
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    QPixmap pix(path);
    /*
    QLabel *image = new QLabel(this);
    image->setAlignment(Qt::AlignCenter);
    image->setFixedSize(IMAGE_SIZE,IMAGE_SIZE);
    image->setPixmap(pix.scaled(IMAGE_SIZE,IMAGE_SIZE));
*/
    QPushButton *button = new QPushButton(this);
    button->setIcon(QIcon(pix));
    button->setIconSize(QSize(IMAGE_SIZE, IMAGE_SIZE));
    button->setFixedSize(IMAGE_SIZE+10, IMAGE_SIZE+10);

    QFileInfo info(path);
    QLabel *title = new QLabel(this);
    title->setWordWrap(true);
    title->setAlignment(Qt::AlignCenter);
    title->setText(info.baseName());

    this->layout()->setAlignment(Qt::AlignCenter);
//    this->layout()->addWidget(image);
    this->layout()->addWidget(button);
    this->layout()->addWidget(title);
}

void Thumbnail::mousePressEvent(QMouseEvent *event){
    Q_UNUSED(event)
    if(!this->pathcb)
    {
        qDebug() << "中身がない";
    }

    QPalette pal(palette());
    pal.setColor(QPalette::Background, "#AAAAAA");
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    this->pathcb(_path);
}

void Thumbnail::mouseReleaseEvent(QMouseEvent *event){
    Q_UNUSED(event)
    QPalette pal(palette());
    pal.setColor(QPalette::Background, COLOR);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

Thumbnail::~Thumbnail(){
    delete ui;
}
