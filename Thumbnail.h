#ifndef THUMBNAIL_H
#define THUMBNAIL_H

// #include "Singleton.h"

#include <QWidget>
#include <QString>

#include <functional>

namespace Ui {
class Thumbnail;
}

class Thumbnail : public QWidget
{
    Q_OBJECT

public:
    explicit Thumbnail(QString path, QWidget *parent = nullptr);
    ~Thumbnail();

    void setPathMethod(std::function<void(QString)> cb);

    QString _path;

public slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Ui::Thumbnail *ui;
//     Singleton *singleton;
    void setupThumbnail(QString path);

    std::function<void(QString)> pathcb;

};

#endif // THUMBNAIL_H
