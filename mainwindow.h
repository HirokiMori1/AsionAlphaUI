#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Thumbnail.h"
#include "Singleton.h"
#include "YamlReader.h"

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
    Singleton *singleton;
    YamlReader *yamlreader;
    FileUtil *_fileutil;

private slots:
    void on_action_triggered();

    void on_goHomeButton_clicked();

    void selectedMapNameChanged();

    void on_startButton_clicked();

    void on_action_2_triggered();

    void on_releaseBumperButton_clicked();

    void on_navigationButton_clicked();

    void on_action_3_triggered();

private:
    Ui::MainWindow *ui;

    void findMap();
    void setFilePath(QString setpath);
    void runShellscript(QString program);
    void drawRoute();

};

#endif // MAINWINDOW_H
