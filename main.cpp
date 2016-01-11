#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <functional>
#include "board.h"
#include "controller.h"
#include "model.h"

using fun = std::function<void ()>;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    Controller ctx;
    Model model;
    fun compute = nullptr;


    auto newGame = [&]{
      ctx.stop();
      model.init(1000,100);
      compute = model.makeCompute();
      ctx.start();
    };

    ctx.tick = [&]{
        compute();
    };

    QObject::connect(&ctx, &Controller::newGame, newGame);
    QObject::connect(&ctx, &Controller::openFile,
                     [&](const QUrl &f){
        QString filename = f.toLocalFile();
        model.openFile(filename);

    });

    engine.addImageProvider("IProvider", &ctx.provider);
    engine.rootContext()->setContextProperty("Controller", &ctx);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

