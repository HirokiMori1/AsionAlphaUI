#ifndef LICENSE_H
#define LICENSE_H

#include <QDialog>

namespace Ui {
class licenseDialog;
}

class licenseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit licenseDialog(QWidget *parent = 0);
    ~licenseDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::licenseDialog *ui;
};

#endif // LICENSE_H
