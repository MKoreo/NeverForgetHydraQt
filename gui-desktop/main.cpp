#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QQuickWindow>
#include <QQuickStyle>
#include <QQmlContext>

#include "backend.h"

#include "datagridViewModel.h"
#include "comboBoxNamesModel.h"

int main(int argc, char *argv[]) {
    // Force a certain style
    // QQuickStyle::setStyle("Default");
    // QQuickStyle::setStyle("Universal");
    // QQuickStyle::setStyle("Fusion");

    // Enable high DPI scaling
    QApplication::setAttribute(Qt::AA_DisableHighDpiScaling);

    // Create the QGuiAplication and set settings
    // 2020-07-19: Changed to QApplication (include widgets in .pro)
    QApplication app(argc, argv);

    // -- Set app settings
    app.setOrganizationName("THOPOP technological inventions");
    app.setOrganizationDomain("home.com");
    app.setApplicationName("NeverForgetHydra");
    app.setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Floor);

    // Doesn't work, TODO:
    app.setWindowIcon(QIcon("qrc:/images/hourglas.ico"));

    // Register types (connect qml <> c++)
    // -- Backend on GUI
    qmlRegisterType<BackEnd>("home.NeverForgetHydra", 1, 0, "BackEnd");

    // -- Models that provide data to GUI
    // ---- Comboboxes
    qmlRegisterType<ComboBoxNamesModel>("home.NeverForgetHydra", 1, 0, "ComboBoxNamesModel");
    // ---- DataGrid
    qmlRegisterType<DatagridViewModel>("home.NeverForgetHydra", 1, 0, "DatagridViewModel");

    // Start QML app engine
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    // Do some weird stuff
    QObject *topLevel = engine.rootObjects().value(0);
    QQuickWindow *window = qobject_cast<QQuickWindow *>(topLevel);

    // Show Window + eternal loop
    window->show();
    return app.exec();
}
