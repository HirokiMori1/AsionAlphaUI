#ifndef SINGLETON_H
#define SINGLETON_H

#include <QObject>
#include <QMainWindow>
#include <QButtonGroup>

class Singleton : public QObject
{    
public:
    static Singleton *getInstance();
    static void Create();
    static void Destroy();

    QMainWindow *_MainWindow;
    QButtonGroup *buttonGroup;

    QString selectFilepath;
    QString windowName = "Asion操作パネル";

protected:
    static Singleton *s_pInstance;
//    Singleton();
};

#endif // SINGLETON_H
