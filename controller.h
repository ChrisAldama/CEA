#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <functional>
#include <QTimer>
#include <QUrl>
#include "iprovider.h"

class Controller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int speed READ speed WRITE setSpeed )
    Q_PROPERTY(bool running READ running )
public:
    explicit Controller(QObject *parent = 0);
    IProvider provider;
    std::function<void()> tick;

    void registerImage(const QImage &image);
    void render();

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();
    Q_INVOKABLE int speed();
    Q_INVOKABLE void setSpeed(int s);
    Q_INVOKABLE bool running();



signals:
    void newImage(int id);
    void newGame();
    void openFile(const QUrl&);
    void changeMode(const int m);

public slots:

private:
    QTimer timer;
};

#endif // CONTROLLER_H
