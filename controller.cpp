#include "controller.h"
#include <QStringList>

Controller::Controller(QObject *parent):
    QObject(parent),
    provider(new IProvider)
{
    connect(this, &Controller::newGame,
            this, [this]{
        stop();
        errorD.clear();
    });
    connect(&timer, &QTimer::timeout,[this]{
        tick();
    });

    timer.setInterval(1000/2);
}

void Controller::addError(const float err)
{
    errorD.push_back(err);
    errorDataChanged();
}

void Controller::registerImage(const QImage &image)
{
    static int id = 0;
    provider->img = image;
    newImage(id++);

}

void Controller::registerStimuli(const Stimuli &st, const VVector &out)
{
    QStringList objs;
    const int size = out.size();
    for(int i = 0; i < size; ++i){
        objs << QString("{\"x\": %1, \"y\": %2, \"z\": %3, \"w\": %4}")
                .arg(st.in[i][0])
                .arg(st.in[i][1])
                .arg(st.out[i][0])
                .arg(out[i][0]);
    }
    this->st = QString("[%1]")
            .arg(objs.join(','));
    stimuliChanged();
}

void Controller::start()
{
    timer.start();
}

void Controller::stop()
{
    timer.stop();
}

void Controller::render()
{
    static int id = 0;
    newImage(id++);
}


int Controller::speed()
{
    return timer.interval();
}

void Controller::setSpeed(int s)
{
    timer.setInterval(s);
}

bool Controller::running()
{
    return timer.isActive();
}

QVector<float> Controller::errorData()
{
    return errorD;
}

QString Controller::stimuli()
{
    return st;
}
