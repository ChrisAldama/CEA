#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <functional>
#include "board.h"
#include "controller.h"
#include "model.h"
#include "graphics.h"

using fun = std::function<void ()>;
using funV = std::function<VVector (int)>;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    Controller ctx;
    Model model;
    fun compute = nullptr;
    funV test = nullptr;


    auto newGame = [&]{
      ctx.stop();
      model.init(100,100);
      compute = model.makeCompute();
      test = model.makeSimu();
      ctx.start();
    };

    ctx.tick = [&]{
        auto state = model.getState();
        if( state == Model::State::Testing){
            auto result = test(10); //steps
            auto image = Graphics::draw(model.data(),
                                        ctx.provider.lastSize);
            ctx.registerImage(image);

        }
        else if(state == Model::State::Evolving){
            //compute();
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

    engine.addImageProvider("IProvider", &ctx.provider);
    engine.rootContext()->setContextProperty("Controller", &ctx);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

