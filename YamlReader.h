#ifndef YAMLREADER_H
#define YAMLREADER_H

#include "ProcessingFileUtil.h"

#include <QList>

class FileUtil;

class YamlReader
{
public:
    void ReadSettingYaml();
    void ReadRouteYaml();
    void editYamlImage(QString name);

    double xorigin,yorigin;
    QList<double> values;
    QList<QList<double>> points;

private:
    FileUtil *_fileutil;

};

#endif // YAMLREADER_H
