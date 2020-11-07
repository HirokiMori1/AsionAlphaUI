#include "Define.h"
#include "YamlReader.h"

#include <yaml-cpp/yaml.h>
#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <QDebug>

#include <QList>

using namespace std;

void YamlReader::ReadSettingYaml(){
    qDebug() << "[YamlReader::ReadSettingYaml]";

    _fileutil = new FileUtil;
    _fileutil->fileSet();
    values.clear();
    try {
        QString filename = QString::asprintf(MAPS_YAML_FORMAT,
                                             MAPS_FILEPATH,
                                             _fileutil->filename.toLocal8Bit().constData(),
                                             _fileutil->filename.toLocal8Bit().constData(),
                                             ROUTE_EXTENSION);
        qDebug() << "[YamlReader::ReadSettingYaml]" << filename;
        YAML::Node route = YAML::LoadFile(filename.toStdString());

        qDebug() << "[YamlReader::ReadSettingYaml]" << "start read Setting yaml";

            values.append(route["resolution"].as<double>());
            values.append(route["negate"].as<double>());
            values.append(route["occupied_thresh"].as<double>());
            values.append(route["free_thresh"].as<double>());

            xorigin = route["origin"][0].as<double>();
            yorigin = route["origin"][1].as<double>();

    }catch (YAML::Exception& e){
        cerr << e.what() << &endl;
    }
}

void YamlReader::ReadRouteYaml(){
    qDebug() << "[YamlReader::ReadRouteYaml]";

    _fileutil = new FileUtil;
    _fileutil->fileSet();
    points.clear();
    try{
        QString filename = QString::asprintf(MAPS_ROUTE_FORMAT, _fileutil->yamldir.toLocal8Bit().constData(), ROUTE_YAML);
        qDebug() << "[YamlReader::ReadRouteYaml]" << filename;
        YAML::Node route = YAML::LoadFile(filename.toStdString());
        qDebug() << "[YamlReader::ReadRouteYaml]" << "start read yaml ";

        int i=0;
        while(1){
            if(route["way_points"][i][4].as<int>() < 0)
                break;

            QList<double> data;
            data.append(route["way_points"][i][X_LENGTH_NUM].as<double>());
            data.append(route["way_points"][i][Y_LENGTH_NUM].as<double>());
            data.append(route["way_points"][i][X_ANGLE_NUM].as<double>());
            data.append(route["way_points"][i][Y_ANGLE_NUM].as<double>());

            points.append(data);

            i++;
        }
    }
    catch(YAML::Exception& e) {
        qDebug() << "[YamlReader::ReadRouteYaml] Exception" ;
        cerr << e.what() << &endl;
    }
}
