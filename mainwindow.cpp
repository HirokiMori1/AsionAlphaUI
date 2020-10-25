#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Define.h"

#include <QDir>
#include <QDirIterator>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ウィンドウ下に著作権表示
    ui->statusBar->showMessage("Copyrigth(c) Kufusha Inc., 2020, All Rights Reserved.");
    findMap();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setFilePath(QString setpath){
    qDebug() << "[MainWindow::setFilePath]";

    path = setpath;
//    singleton->getInstance()->selectFilepath = setpath;
//    QFileInfo edit(setpath);
//    ui->editing->setText(QString::asprintf(COMMENT_FORMAT,"選択中：",edit.baseName().toLocal8Bit().constData()));
//    singleton->getInstance()->_MainWindow->setWindowTitle(edit.baseName());
    qDebug() << path;
}


void MainWindow::findMap(){
    qDebug() << "[MainWindow::findMap]";

    QDir dir(MAPS_FILEPATH);
    qDebug() << dir.entryList();
    QStringList extension;
    QStringList imglist;
    QStringList rotlist;

    extension.append(IMAGE_EXTENSION);

    QDirIterator maps(MAPS_FILEPATH, QDir::Files, QDirIterator::Subdirectories);
    while(maps.hasNext()){
        maps.next();

        if (maps.filePath().endsWith(IMAGE_EXTENSION, Qt::CaseInsensitive)){
            if (!maps.filePath().contains("modified", Qt::CaseInsensitive)){
                imglist.append(maps.filePath().remove(IMAGE_EXTENSION));
            }
        } else if(maps.filePath().endsWith(ROUTE_EXTENSION, Qt::CaseInsensitive)){
            if(!maps.filePath().contains("routes", Qt::CaseInsensitive)){
                rotlist.append(maps.filePath().remove(ROUTE_EXTENSION));
            }
        }
    }

    imglist.sort();
    rotlist.sort();
    for (QString image : imglist){
        for(QString route : rotlist){
            if(image==route){
                tn = new Thumbnail(QString::asprintf(PATH_FORMAT,image.toLocal8Bit().constData(),IMAGE_EXTENSION));
                tn->setPathMethod([=](QString str){this->setFilePath(str);});
                //tn -> set~method (ramuda)
                ui->scrollArea->widget()->layout()->addWidget(tn);
            }
        }
    }
}

/*
 * [ファイル]->[終了]
 */
void MainWindow::on_action_triggered()
{
    QApplication::quit();
}

/*
 * 停止ボタンがクリックされたときのコールバック関数
 */
void MainWindow::on_stopButton_clicked()
{
    QString sh;
    sh.asprintf(PATH_FORMAT,SH_FILEPATH,SH_STOP);
    runShellscript(sh.asprintf(PATH_FORMAT,SH_FILEPATH,SH_STOP));
    qDebug() << sh;
}

void MainWindow::runShellscript(QString program){
    QProcess *process = new QProcess(this);
    QStringList options;

    process->startDetached(program);
}
