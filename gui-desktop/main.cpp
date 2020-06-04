#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQuickStyle>


#include "backend.h"

int main(int argc, char *argv[]) {
    // Random vars and attributes

    qputenv("SQG_VISUALIZE", "overdraw");    // Should show depth, but doesn't appear to work

    // Force a certain style
    // QQuickStyle::setStyle("Imagine");
    // QQuickStyle::setStyle("Material");

    // Enable high DPI scaling
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    qmlRegisterType<BackEnd>("io.home.essentials.backend", 1, 0, "BackEnd");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    QObject *topLevel = engine.rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);
    window->show();

    return app.exec();
}
