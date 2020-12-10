#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Define.h"
#include "waitmessagedialog.h"
#include "aboutdialog.h"
#include "license.h"

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
#include <QTimer>
#include <QMessageBox>

/*
 * コンストラクタ
 */
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

    // ボタンにIconを付与する
    QPixmap navigationPixmap(LOAD_IMG);
    QIcon navigationIcon(navigationPixmap);
    ui->navigationButton->setIcon(navigationIcon);

    QPixmap startPixmap(START_IMG);
    QIcon startIcon(startPixmap);
    ui->startButton->setIcon(startIcon);

    QPixmap releaseBumperPixmap(RESTART_IMG);
    QIcon releaseBumperIcon(releaseBumperPixmap);
    ui->releaseBumperButton->setIcon(releaseBumperIcon);

    QPixmap goHomePixmap(STOP_IMG);
    QIcon goHomeIcon(goHomePixmap);
    ui->goHomeButton->setIcon(goHomeIcon);

    findMap();

    // 起動時は登録したマップの先頭を選択した状態にする
    if ((singleton->getInstance()->buttonGroup->buttons()).count() > 0) {
        singleton->getInstance()->buttonGroup->button(0)->clicked(true);
        singleton->getInstance()->buttonGroup->button(0)->repaint();
    }
}

/*
 * デストラクタ
 */
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
    qDebug() << path;
}

/*
 * mapディレクトリにpgmとroute999.yamlがあれば表示
 */
void MainWindow::findMap(){
    qDebug() << "[MainWindow::findMap]";

    QDir dir(MAPS_FILEPATH);
    qDebug() << "[MainWindow::findMap]entryList(): " << dir.entryList();

    for (int i = 0; i < dir.entryList().size(); i++) {
        if ((dir.entryList().at(i) == ".") || (dir.entryList().at(i) == "..")) {
            continue;
        }

        QString image = MAPS_FILEPATH;
        QString route = MAPS_FILEPATH;
        image.append("/").append(dir.entryList().at(i)).append("/").append(dir.entryList().at(i)).append(IMAGE_EXTENSION);
        route.append("/").append(dir.entryList().at(i)).append("/routes/route999").append(ROUTE_EXTENSION);

        // 左ペインに表示する
        QFileInfo imageFile(image);
        QFileInfo routeFile(route);
        if (imageFile.exists() && routeFile.exists()) {
            qDebug() << "[MainWindow::findMap]create Thumbnail " << image;
            tn = new Thumbnail(image);
            tn->setPathMethod([=](QString str){this->setFilePath(str);});
            //tn -> set~method (ramuda)
            ui->scrollArea->widget()->layout()->addWidget(tn);
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
    qDebug() << "[MainWindow::selectedMapNameChanged]mapName:" << mapName;

    ui->selectedMapName->setText(mapName);
    singleton->getInstance()->selectFilepath = QString::asprintf(MAPS_YAML_FORMAT,
                                                                MAPS_FILEPATH,
                                                                mapName.toLocal8Bit().constData(),
                                                                mapName.toLocal8Bit().constData(),
                                                                IMAGE_EXTENSION);
    qDebug() << singleton->getInstance()->selectFilepath;

    drawRoute();

    ui->navigationButton->setEnabled(true);   // マップが選択されたのでデータ読み込みボタンは押下できる
    ui->startButton->setEnabled(false);     // データ読み込み前なのでstart/goHomeボタンは押下できない
    ui->releaseBumperButton->setEnabled(false);
    ui->goHomeButton->setEnabled(false);
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
        painter.drawLine(line);
//      qDebug() << line;
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
void MainWindow::on_navigationButton_clicked()
{
    int button = QMessageBox::question(this, tr("データ読み込み確認"), tr(NAVIGATION_MSG));
    if (button == QMessageBox::Yes) {


        // 読み込み開始時は操作できないようにする
        ui->navigationButton->setEnabled(false);
        ui->startButton->setEnabled(false);
        ui->releaseBumperButton->setEnabled(false);
        ui->goHomeButton->setEnabled(false);
        ui->scrollArea->setEnabled(false);

        // ラベルから地図番号を取得
        QRegExp r("(\\d+)$");
        r.indexIn(ui->selectedMapName->text());
        QString mapNum = r.cap(0);

        // navigation.sh実行
        QString sh = QString::asprintf("%s%s %s",
                                       SH_FILEPATH,
                                       SH_NAVIGATION,
                                       mapNum.toLocal8Bit().constData());
        qDebug() << "[MainWindow::on_navigationButton_clicked]" << sh;

        runShellscript(sh);

        // 起動待ちダイアログ表示
        waitMessageDialog *dialog = new waitMessageDialog;
        dialog->setModal(true);
        dialog->show();
        QTimer dlg_timer;           // ダイアログ表示時間用のタイマー
        dlg_timer.start(6 * 1000);
        connect(&dlg_timer, SIGNAL(timeout()), dialog, SLOT(close()));
        QTimer update_timer;
        update_timer.start(1000);   // 進捗バー表示用タイマー
        connect(&update_timer, SIGNAL(timeout()), dialog, SLOT(update()));

        dialog->exec();
        dlg_timer.stop();

        ui->startButton->setEnabled(true);
        ui->goHomeButton->setEnabled(true);
    }
}

/*
 * 「清掃開始」ボタンのコールバック関数
 */
void MainWindow::on_startButton_clicked()
{
    int button = QMessageBox::question(this, tr("清掃開始確認"), tr(START_MSG));
    if (button == QMessageBox::Yes) {

        // ステート変更
        ui->navigationButton->setEnabled(false);
        ui->startButton->setEnabled(true);
        ui->releaseBumperButton->setEnabled(true);
        ui->goHomeButton->setEnabled(true);
        ui->scrollArea->setEnabled(false);

        // ラベルから地図番号を取得
        QRegExp r("(\\d+)$");
        r.indexIn(ui->selectedMapName->text());
        QString mapNum = r.cap(0);

        // start.sh実行
        QString startPath = QString::asprintf("%s%s %s",
                                                SH_FILEPATH,
                                                SH_START,
                                                mapNum.toLocal8Bit().constData());
        qDebug() << "[MainWindow::on_startButton_clicked]" << startPath;
        runShellscript(startPath);
    }
}

/*
 * 「スタートに戻る」ボタンのコールバック関数
 */
void MainWindow::on_goHomeButton_clicked()
{
    // ステート変更
    ui->navigationButton->setEnabled(false);
    ui->startButton->setEnabled(true);
    ui->releaseBumperButton->setEnabled(true);
    ui->goHomeButton->setEnabled(true);
    ui->scrollArea->setEnabled(true);

    QString sh = QString::asprintf(PATH_FORMAT,SH_FILEPATH,SH_GOHOME);
    qDebug() << "[MainWindow::on_goHomeButton_clicked]" << sh;
    runShellscript(sh);
}

/*
 * [ファイル]->[終了]
 */
void MainWindow::on_action_triggered()
{
    qDebug() << "[MainWindow::on_action_triggered]";

    QApplication::quit();
}

/*
 * [ヘルプ]->[このツールについて]
 */
void MainWindow::on_action_2_triggered()
{
    aboutDialog *about = new aboutDialog;
    about->show();
}

/*
 * 「バンパーセンサ停止解除」ボタンコールバック
 */
void MainWindow::on_releaseBumperButton_clicked()
{
    // ステート変更なし

    int button = QMessageBox::question(this, tr("バンパーセンサ停止解除確認"), tr(RELEASE_BUMPER_MSG));

    if (button == QMessageBox::Yes) {
        QString sh = QString::asprintf(PATH_FORMAT,SH_FILEPATH,SH_RELEASE_BUMPER);
        qDebug() << "[MainWindow::on_releaseBumperButton_clicked]" << sh;
        runShellscript(sh);
    }
}


void MainWindow::on_action_3_triggered()
{
    licenseDialog *license = new licenseDialog;
    license->show();
}
