#include <QApplication>
#include <QQmlApplicationEngine>
#include "board.h"

using namespace Board;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

