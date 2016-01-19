#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <functional>
#include <QTimer>
#include <QUrl>
#include <QVector>
#include "iprovider.h"
#include "stimuli.h"
#include "vector"

class Controller : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int speed READ speed WRITE setSpeed )
    Q_PROPERTY(bool running READ running )
    Q_PROPERTY(QVector<float> errorData READ errorData NOTIFY errorDataChanged)
    Q_PROPERTY(QString stimuli READ stimuli NOTIFY stimuliChanged)
public:
    explicit Controller(QObject *parent = 0);
    IProvider *provider;
    std::function<void()> tick;
    void addError(const float err);

    void registerImage(const QImage &image);
    void registerStimuli(const Stimuli &st, const VVector &out);
    void render();

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();
    Q_INVOKABLE int speed();
    Q_INVOKABLE void setSpeed(int s);
    Q_INVOKABLE bool running();
    QVector<float> errorData();
    QString stimuli();

signals:
    void newImage(int id);
    void newGame();
    void openFile(const QUrl&);
    void changeMode(const int m);
    void errorDataChanged();
    void stimuliChanged();

public slots:

private:
    QTimer timer;
    QVector<float> errorD;
    QString st;
};

#endif // CONTROLLER_H
