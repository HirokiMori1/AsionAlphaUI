#ifndef WAITMESSAGEDIALOG_H
#define WAITMESSAGEDIALOG_H

#include <QDialog>

namespace Ui {
class waitMessageDialog;
}

class waitMessageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit waitMessageDialog(QWidget *parent = 0);
    ~waitMessageDialog();

private:
    Ui::waitMessageDialog *ui;

private slots:
    void update();
};

#endif // WAITMESSAGEDIALOG_H
