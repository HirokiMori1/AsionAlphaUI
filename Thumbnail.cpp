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

void Thumbnail::setPathMethod(std::function<void(QString)> cb){
    qDebug() << "[Thumbnail::setPathMethod]";
    this->pathcb = cb;
}

void Thumbnail::setupThumbnail(QString path){
    qDebug() << "[Thumbnail::setupThumbnail]" << path;

    QPalette pal(palette());
//    pal.setColor(QPalette::Background, COLOR);
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    QFileInfo info(path);
    QPixmap pix(path);

    QPushButton *button = new QPushButton(this);
    button->setIcon(QIcon(pix));
    button->setIconSize(QSize(IMAGE_SIZE, IMAGE_SIZE));
    button->setFixedSize(IMAGE_SIZE+10, IMAGE_SIZE+10);
    button->setObjectName(info.baseName());
    button->setCheckable(true);

    QButtonGroup *grp = singleton->getInstance()->buttonGroup;
    grp->addButton(button, (grp->buttons()).count());
    /*
    if ((grp->buttons()).count() == 1) {
        button->setChecked(true);
    } else {
        button->setChecked(false);
    }
*/
    connect(button, SIGNAL(clicked(bool)),
            singleton->getInstance()->_MainWindow, SLOT(selectedMapNameChanged()));

    QLabel *title = new QLabel(this);
    title->setWordWrap(true);
    title->setAlignment(Qt::AlignCenter);
    title->setText(info.baseName());

    this->layout()->setAlignment(Qt::AlignCenter);
    this->layout()->addWidget(button);
    this->layout()->addWidget(title);
}

void Thumbnail::mousePressEvent(QMouseEvent *event){
    Q_UNUSED(event)
    qDebug() << "[Thumbnail::mousePressEvent]";

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
    qDebug() << "[Thumbnail::mouseReleaseEvent]";

    QPalette pal(palette());
    pal.setColor(QPalette::Background, COLOR);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

Thumbnail::~Thumbnail(){
    qDebug() << "[Thumbnail::~Thumbnail]";

    delete ui;
}
