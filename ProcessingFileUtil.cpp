#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QtWidgets>
#include <QListWidgetItem>
#include <QImage>
#include <QList>
#include <QFile>
#include <QFileInfo>
#include <QFileInfoList>
#include <QDir>
#include <QUndoCommand>

#include "Define.h"
#include "Singleton.h"
#include "ProcessingFileUtil.h"

void FileUtil::fileSet(){
    qDebug() << "fileset";

    info.setFile(singleton->getInstance()->selectFilepath);
    directoryname = info.absolutePath();
    filename = info.baseName();
    pgmdir = QString("%1/%2/modified")
            .arg(MAPS_FILEPATH)
            .arg(filename.toLocal8Bit().constData());
    yamldir = QString("%1/%2/routes")
            .arg(MAPS_FILEPATH)
            .arg(filename.toLocal8Bit().constData());
    Filter.append("*.pgm");

//    qDebug() << info;
    qDebug() << directoryname;
    qDebug() << filename;
    qDebug() << pgmdir;
    qDebug() << yamldir;

}

QDir FileUtil::patternList(){
    fileSet();

    QDir dir(pgmdir);

    dir.setSorting(QDir::Name);
    dir.setFilter(QDir::Filters());

    return dir;
}

