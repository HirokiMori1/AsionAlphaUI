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
    _fileutil = new FileUtil;
    _fileutil->fileSet();
    values.clear();
    try {
        QString filename = QString::asprintf(MAPS_YAML_FORMAT,
                                             MAPS_FILEPATH,
                                             _fileutil->filename.toLocal8Bit().constData(),
                                             _fileutil->filename.toLocal8Bit().constData(),
                                             ROUTE_EXTENSION);
        qDebug() << filename;
        YAML::Node route = YAML::LoadFile(filename.toStdString());

        qDebug() << "start read Setting yaml";

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
    _fileutil = new FileUtil;
    _fileutil->fileSet();
    points.clear();
    try{
        QString filename = QString::asprintf(MAPS_ROUTE_FORMAT,_fileutil->yamldir.toLocal8Bit().constData(),ROUTE_YAML);
        qDebug() << filename;
        YAML::Node route = YAML::LoadFile(filename.toStdString());
        qDebug() << "start read yaml";

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
        cerr << e.what() << &endl;
    }
}

/*
void YamlReader::editYamlImage(QString name){
    _fileutil = new FileUtil;
    _fileutil->fileSet();
    try{
        YAML::Emitter emitter;
        qDebug() << QString::asprintf("%s/%s%s",_fileutil->directoryname.toLocal8Bit().constData(),_fileutil->filename.toLocal8Bit().constData(),ROUTE_EXTENSION);
        YAML::Node org = YAML::LoadFile(QString::asprintf("%s/%s%s",_fileutil->directoryname.toLocal8Bit().constData(),_fileutil->filename.toLocal8Bit().constData(),ROUTE_EXTENSION).toStdString());

        qDebug() << "start read yaml";

        emitter << YAML::BeginMap;
        emitter << YAML::Key << "image";
        emitter << YAML::Value << QString::asprintf("%s/%s%s",_fileutil->pgmdir.toLocal8Bit().constData(),name.toUtf8().data(),IMAGE_EXTENSION).toStdString();
        emitter << YAML::Key << "resolution";
        emitter << YAML::Value << org["resolution"];
        emitter << YAML::Key << "origin";
        emitter << YAML::Value << org["origin"];
        emitter << YAML::Key << "negate";
        emitter << YAML::Value << org["negate"];
        emitter << YAML::Key << "occupied_thresh";
        emitter << YAML::Value << org["occupied_thresh"];
        emitter << YAML::Key << "free_thresh";
        emitter << YAML::Value << org["free_thresh"];
        emitter << YAML::EndMap;

        std::ofstream fout(QString::asprintf("%s/%s%s",_fileutil->pgmdir.toLocal8Bit().constData(),name.toUtf8().data(),ROUTE_EXTENSION).toStdString());
        fout << emitter.c_str();
    }
    catch(YAML::Exception& e) {
        cerr << e.what() << &endl;
    }
}
*/
