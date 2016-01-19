#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include <functional>
#include "board.h"
#include "controller.h"
#include "model.h"
#include "graphics.h"

using fun = std::function<double ()>;
using funV = std::function<VVector (int)>;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    Controller ctx;
    Model model;
    fun compute = nullptr;
    funV test = nullptr;
    const int steps = 50;
    double fitt = 0;


    auto newGame = [&]{
      ctx.stop();
      fitt = 0;
      model.init(10,10);
      compute = model.makeCompute(steps);
      test = model.makeSimu();
      ctx.start();
    };

    ctx.tick = [&]{
        auto state = model.getState();
        if( state == Model::State::Testing){
            auto result = test(steps); //steps
            auto image = Graphics::draw(model.data(),
                                        ctx.provider->size());
            ctx.registerImage(image);            
        }
        else if(state == Model::State::Evolving){
            if(fitt < 0.95){
                fitt = compute();
                ctx.addError(1.0 - fitt);
            }
            auto result = test(steps);
            auto image = Graphics::draw(model.data(),
                                        ctx.provider->size());
            ctx.registerImage(image);
            ctx.registerStimuli(model.sti, result);
        }
    };

    QObject::connect(&ctx, &Controller::newGame, newGame);
    QObject::connect(&ctx, &Controller::openFile,
                     [&](const QUrl &f){
        QString filename = f.toLocalFile();
        model.openFile(filename);

    });
    QObject::connect(&ctx, &Controller::changeMode,[&](int m){
       auto state = static_cast<Model::State>(m);
       model.state(state);
    });

    engine.addImageProvider("IProvider", ctx.provider);
    engine.rootContext()->setContextProperty("Controller", &ctx);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

