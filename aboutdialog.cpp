#include "aboutdialog.h"
#include "ui_aboutdialog.h"

aboutDialog::aboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutDialog)
{
    ui->setupUi(this);

    // Asionのイメージ貼り付け
    QImage *asionImg = new QImage();
    asionImg->load(ASION_IMG);
    QPixmap asionPixmap = QPixmap::fromImage(*asionImg);
    asionPixmap = asionPixmap.scaled(ui->AsionImgLabel->size());
    ui->AsionImgLabel->setPixmap(asionPixmap);

    // Kufushaのイメージ貼り付け
    QImage *kufushaImg = new QImage();
    kufushaImg->load(KUFUSHA_IMG);
    QPixmap kufushaPixmap = QPixmap::fromImage(*kufushaImg);
    kufushaPixmap = kufushaPixmap.scaled(ui->KufushaImgLabel->size());
    ui->KufushaImgLabel->setPixmap(kufushaPixmap);


}

aboutDialog::~aboutDialog()
{
    delete ui;
}

void aboutDialog::on_pushButton_clicked()
{
    this->close();
}
