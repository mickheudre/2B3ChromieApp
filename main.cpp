#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "colorspacegenerator.h"
#include "imageprovider.h"
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/2B3ChromieApp/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);


    std::shared_ptr<ColorSpaceGenerator> gg = std::make_shared<ColorSpaceGenerator>();
    std::shared_ptr<ImageProvider> imageProvider = std::make_shared<ImageProvider>(gg);
    engine.rootContext()->setContextProperty("yo", gg.get());
    engine.addImageProvider(QLatin1String("renders"), imageProvider.get());

    engine.load(url);

    return app.exec();
}
