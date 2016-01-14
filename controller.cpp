#include "controller.h"

Controller::Controller(QObject *parent):
    QObject(parent)
{
    connect(this, &Controller::newGame,
            this, &Controller::stop);
    connect(&timer, &QTimer::timeout,[this]{
        tick();
    });

    timer.setInterval(1000/60);
}

void Controller::registerImage(const QImage &image)
{
    provider.img = image;

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
