#include <QtWidgets>
#include <QPalette>
#include <QPushButton>
#include <QIcon>
#include <QSize>
#include <QList>

#include "Define.h"
#include "Singleton.h"
#include "Thumbnail.h"
#include "ui_Thumbnail.h"

Thumbnail::Thumbnail(QString path, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Thumbnail)
{
    qDebug() << "[Thumbnail::Thumbnail]";
    ui->setupUi(this);
    setupThumbnail(path);

    _path = QString(path);
}

Thumbnail::~Thumbnail(){
    qDebug() << "[Thumbnail::~Thumbnail]";

    delete ui;
}

void Thumbnail::setPathMethod(std::function<void(QString)> cb){
    qDebug() << "[Thumbnail::setPathMethod]";
    this->pathcb = cb;
}

void Thumbnail::setupThumbnail(QString path){
    qDebug() << "[Thumbnail::setupThumbnail]" << path;

    QFileInfo info(path);

    QLabel *title = new QLabel(this);
    title->setWordWrap(true);
    title->setAlignment(Qt::AlignCenter);
    title->setText(info.baseName());

    QPushButton *button = new QPushButton(this);
    QPixmap pix(path);
    button->setIcon(QIcon(pix));
    button->setIconSize(QSize(IMAGE_SIZE, IMAGE_SIZE));
    button->setFixedSize(IMAGE_SIZE+10, IMAGE_SIZE+10);
    button->setObjectName(info.baseName());
    button->setCheckable(true);
    button->setStyleSheet("\
                          QPushButton {   \
                              color:white;    \
                          }   \
                          QPushButton:checked{\
                              background-color: rgb(80, 80, 80);\
                              border: none; \
                          }\
                          QPushButton:hover{  \
                              background-color: grey; \
                              border-style: outset;  \
                          }  \
                          ");

    // ボタンをトグル化するためにボタングループに所属させる
    QButtonGroup *grp = singleton->getInstance()->buttonGroup;
    grp->addButton(button, (grp->buttons()).count());

    connect(button, SIGNAL(clicked(bool)),
            singleton->getInstance()->_MainWindow, SLOT(selectedMapNameChanged()));

    this->layout()->setAlignment(Qt::AlignCenter);
    this->layout()->addWidget(button);
    this->layout()->addWidget(title);
}

