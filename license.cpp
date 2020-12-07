#include "Define.h"
#include "license.h"
#include "ui_licensedialog.h"

#include <QTextStream>
#include <QDebug>
#include <QScrollBar>

licenseDialog::licenseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::licenseDialog)
{
    ui->setupUi(this);

    QFile file(OSSLICFILE);
    if (! file.open(QIODevice::ReadOnly)) {
        QString errmsg;
        errmsg.sprintf("File open error(%s)", OSSLICFILE);
        return;
    }
    QTextStream in(&file);
    ui->plainTextEdit->setPlainText(in.readAll());
    file.close();
}

licenseDialog::~licenseDialog()
{
    delete ui;
}

void licenseDialog::on_pushButton_clicked()
{
    this->close();
}

