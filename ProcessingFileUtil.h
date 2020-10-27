#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <QListWidget>
#include <QFileInfo>

#include "Singleton.h"

class FileUtil
{
public:
    Singleton *singleton;

    void fileSet();
/*
    void imageSave(QImage image);
*/
    QDir patternList();
/*
    void changeName(QString oldName,QString newName);
    void deleteFile(QString name);
    bool fileExist(QString filename);
*/
    QFileInfo info;
    QString directoryname,filename,saveName;
    QString pgmdir,yamldir;
    QStringList Filter;

public slots:

private:

};
#endif // FILEUTIL_H
