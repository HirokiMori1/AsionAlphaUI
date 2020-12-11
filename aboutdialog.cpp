#include <QDebug>
#include <QProcess>

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

    // FDesignのイメージ貼り付け
    QImage *fdesignImg = new QImage();
    fdesignImg->load(FDESIGN_IMG);
    QPixmap fdesignPixmap = QPixmap::fromImage(*fdesignImg);
    fdesignPixmap = fdesignPixmap.scaled(ui->FDesignImgLabel->size());
    ui->FDesignImgLabel->setPixmap(fdesignPixmap);

    // CarrotSystemsのイメージ貼り付け
    QImage *carrotImg = new QImage();
    carrotImg->load(CARROT_IMG);
    QPixmap carrotPixmap = QPixmap::fromImage(*carrotImg);
    carrotPixmap = carrotPixmap.scaled(ui->CarrotImgLabel->size());
    ui->CarrotImgLabel->setPixmap(carrotPixmap);


}

aboutDialog::~aboutDialog()
{
    delete ui;
}

/*
 * 「Close」ボタンコールバック
 */
void aboutDialog::on_closeButton_clicked()
{
    this->close();
}

/*
 * 「OSS Licenses」ボタンコールバック
 */
void aboutDialog::on_ossLicButton_clicked()
{
    QString sh = QString::asprintf(PATH_FORMAT,LICENSES_PATH,SH_COPYRIGHT);
    qDebug() << "[aboutDialog::on_ossLicButton_clicked]" << sh;
    QProcess *process = new QProcess(this);
    process->startDetached(sh);
}
