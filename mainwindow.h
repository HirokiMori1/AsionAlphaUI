#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Thumbnail.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Thumbnail *tn;
    QString path;

private slots:
    void on_action_triggered();

    void on_stopButton_clicked();

private:
    Ui::MainWindow *ui;

    void findMap();
    void setFilePath(QString setpath);
    void runShellscript(QString program);

};

#endif // MAINWINDOW_H
