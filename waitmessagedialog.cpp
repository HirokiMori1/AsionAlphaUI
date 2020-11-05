#include "waitmessagedialog.h"
#include "ui_waitmessagedialog.h"

waitMessageDialog::waitMessageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::waitMessageDialog)
{
    ui->setupUi(this);

    // Asionのイメージ貼り付け
    QImage *asionImg = new QImage();
    asionImg->load(ASION_IMG);
    QPixmap asionPixmap = QPixmap::fromImage(*asionImg);
    asionPixmap = asionPixmap.scaled(ui->AsionImgLabel->size());
    ui->AsionImgLabel->setPixmap(asionPixmap);
}

waitMessageDialog::~waitMessageDialog()
{
    delete ui;
}

void waitMessageDialog::update()
{
    ui->progressBar->setValue(ui->progressBar->value() + 1);
}
