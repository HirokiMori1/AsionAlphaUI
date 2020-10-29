#include "waitmessagedialog.h"
#include "ui_waitmessagedialog.h"

waitMessageDialog::waitMessageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::waitMessageDialog)
{
    ui->setupUi(this);
}

waitMessageDialog::~waitMessageDialog()
{
    delete ui;
}

void waitMessageDialog::update()
{
    ui->progressBar->setValue(ui->progressBar->value() + 1);
}
