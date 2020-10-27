#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Define.h"

#include <QDir>
#include <QDirIterator>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QProcess>
#include <QtMath>
#include <QPainter>
#include <QPen>
#include <QProgressDialog>
#include <QtCore/QThread>

// コンストラクタ
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qDebug() << "[MainWindow::MainWindow]";

    ui->setupUi(this);

    singleton->getInstance()->_MainWindow = this;

    yamlreader = new YamlReader;
    _fileutil = new FileUtil;

    singleton->getInstance()->buttonGroup = new QButtonGroup;

    // ウィンドウ下に著作権表示
    ui->statusBar->showMessage(COPYRIGHT);

    this->setWindowTitle(singleton->getInstance()->windowName);

    findMap();

    // 起動時は登録したマップの先頭を選択した状態にする
    if ((singleton->getInstance()->buttonGroup->buttons()).count() > 0) {
        singleton->getInstance()->buttonGroup->button(0)->clicked(true);
    }

    qDebug() << "[MainWindow::MainWindow]label: " << ui->label->size();
}

// デストラクタ
MainWindow::~MainWindow()
{
    qDebug() << "[MainWindow::~MainWindow]";

    delete ui;
}

/*
 *
 */
void MainWindow::setFilePath(QString setpath){
    qDebug() << "[MainWindow::setFilePath]";

    path = setpath;
    singleton->getInstance()->selectFilepath = setpath;
//    QFileInfo edit(setpath);
//    ui->editing->setText(QString::asprintf(COMMENT_FORMAT,"選択中：",edit.baseName().toLocal8Bit().constData()));
//    singleton->getInstance()->_MainWindow->setWindowTitle(edit.baseName());
    qDebug() << path;
}

/*
 * mapディレクトリから.pgmを見つけ出す
 */
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

    // 左ペインに表示する
    imglist.sort();
    rotlist.sort();
    for (QString image : imglist){
        for (QString route : rotlist){
            if (image==route){
                qDebug() << "[MainWindow::findMap]create Thumbnail";
                tn = new Thumbnail(QString::asprintf(PATH_FORMAT, image.toLocal8Bit().constData(), IMAGE_EXTENSION));
                tn->setPathMethod([=](QString str){this->setFilePath(str);});
                //tn -> set~method (ramuda)
                ui->scrollArea->widget()->layout()->addWidget(tn);
            }
        }
    }
}

/*
 * シェルスクリプトを実行する関数
 */
void MainWindow::runShellscript(QString script){
    qDebug() << "[MainWindow::runShellscript]";

    QProcess *process = new QProcess(this);
    QStringList options;

    process->startDetached(script);
}

/*
 * マップを選択
 */
void MainWindow::selectedMapNameChanged() {
    QString mapName = sender()->objectName();
    qDebug() << "[MainWindow::selectedMapNameChanged]" << mapName;

    ui->selectedMapName->setText(mapName);
    singleton->getInstance()->selectFilepath = QString::asprintf(MAPS_YAML_FORMAT,
                                                                MAPS_FILEPATH,
                                                                mapName.toLocal8Bit().constData(),
                                                                mapName.toLocal8Bit().constData(),
                                                                IMAGE_EXTENSION);
    qDebug() << singleton->getInstance()->selectFilepath;

    drawRoute();

    // 選択しているマップを変更したらデータ読み込みボタンはtrueにする
    ui->dataLoadButton->setEnabled(true);
    // 選択しているマップを変更したらスタート・ストップボタンはtrueにするfalseにする
    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(false);

    qDebug() << "[MainWindow::selectedMapNameChanged]label: " << ui->label->size();

}

/*
 * 真ん中のペインに清掃場所と経路を描画する
 */
void MainWindow::drawRoute(){
    qDebug() << "[MainWindow::drawRoute]";

    yamlreader->ReadSettingYaml();
    yamlreader->ReadRouteYaml();
    QImage ima(singleton->getInstance()->selectFilepath);

    double x = qFabs(yamlreader->xorigin / yamlreader->values[RESOLUTION_NUM]);
    double y = ima.height() - qFabs(yamlreader->yorigin / yamlreader->values[RESOLUTION_NUM]);

    QLineF line;
    QPainter painter;

    painter.begin(&ima);
    QPen penSolid(QColor("#FF0000"), 3, Qt::SolidLine ,Qt::SquareCap, Qt::MiterJoin);
    painter.setPen(penSolid);
    painter.setBrush(Qt::SolidPattern);

//  数値をファイルから読めるようにする

    int i=0;

    double x1 = x + (yamlreader->points[i][X_LENGTH_NUM] / yamlreader->values[RESOLUTION_NUM]);
    double y1 = y - (yamlreader->points[i][Y_LENGTH_NUM] / yamlreader->values[RESOLUTION_NUM]);

    i++;

    for (;i<yamlreader->points.size();i++) {
        double x2 = x + (yamlreader->points[i][X_LENGTH_NUM] / yamlreader->values[RESOLUTION_NUM]);
        double y2 = y - (yamlreader->points[i][Y_LENGTH_NUM] / yamlreader->values[RESOLUTION_NUM]);

        line.setLine(x1, y1, x2, y2);
        qDebug() << line;
        painter.drawLine(line);
        x1 = x2;
        y1 = y2;
    }

    painter.end();

    QPixmap pix;
    pix = QPixmap::fromImage(ima);
    ui->label->setAlignment(Qt::AlignCenter);
    ui->label->setPixmap(pix.scaled(ui->label->size()));
}

/*
 * 「データ読み込み」ボタンのコールバック関数
 */
void MainWindow::on_dataLoadButton_clicked()
{
    // ラベルから地図番号を取得
    QRegExp r("(\\d+)$");
    r.indexIn(ui->selectedMapName->text());
    QString mapNum = r.cap(0);

    // load.sh実行
    QString sh = QString::asprintf("%s%s %s",
                                   SH_FILEPATH,
                                   SH_LOADMAP,
                                   mapNum.toLocal8Bit().constData());
    qDebug() << "[MainWindow::on_dataLoadButton_clicked]" << sh;

    runShellscript(sh);

    // 起動待ち
    QProgressDialog progress(
                tr("しばらくお待ちください・・・"),
                tr("キャンセル"),
                0,
                10,
                this
                );
    progress.setWindowModality(Qt::WindowModal);
    progress.setWindowTitle(tr("処理中"));
    progress.show();

    for (int cnt=0; cnt<10; cnt++) {
        QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
        progress.setValue(cnt);
        if (progress.wasCanceled()) {
            break;
        }
        QThread::sleep(1);
    }
    progress.setValue(10);

    ui->dataLoadButton->setEnabled(false);
    ui->startButton->setEnabled(true);
    ui->stopButton->setEnabled(true);
}

/*
 * 「清掃開始」ボタンのコールバック関数
 */
void MainWindow::on_startButton_clicked()
{
    // ラベルから地図番号を取得
    QRegExp r("(\\d+)$");
    r.indexIn(ui->selectedMapName->text());
    QString mapNum = r.cap(0);

    // power_on.sh実行
    QString powerOnPath = QString::asprintf("%s%s %s",
                                            SH_FILEPATH,
                                            SH_POWER_ON,
                                            mapNum.toLocal8Bit().constData());
    qDebug() << "[MainWindow::on_startButton_clicked]" << powerOnPath;
    runShellscript(powerOnPath);

    // routes.sh実行
    QString routePath = QString::asprintf("%s%s %s %s",
                                            SH_FILEPATH,
                                            SH_ROUTES,
                                            mapNum.toLocal8Bit().constData(),
                                            "999");
    qDebug() << "[MainWindow::on_startButton_clicked]" << routePath;
    runShellscript(routePath);

}

/*
 * 「停止ボタン」のコールバック関数
 */
void MainWindow::on_stopButton_clicked()
{
    QString sh;
    sh.asprintf(PATH_FORMAT,SH_FILEPATH,SH_STOP);
    runShellscript(sh.asprintf(PATH_FORMAT,SH_FILEPATH,SH_STOP));
    qDebug() << "[MainWindow::on_stopButton_clicked]" << sh;
}

/*
 * [ファイル]->[終了]
 */
void MainWindow::on_action_triggered()
{
    qDebug() << "[MainWindow::on_action_triggered]";

    QApplication::quit();
}
