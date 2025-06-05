#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QStringListModel>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQmlComponent>
#include "mymodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    MyModel model;

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty(QStringLiteral("_myModel"), &model);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("qt-quick-model-example", "Main");

    return app.exec();
}
