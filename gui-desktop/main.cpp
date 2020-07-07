#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQuickStyle>

#include "backend.h"

#include "datagridViewModel.h"
#include "comboBoxNamesModel.h"

int main(int argc, char *argv[]) {
    // Force a certain style
    //QQuickStyle::setStyle("Imagine");
    // QQuickStyle::setStyle("Material");

    // Enable high DPI scaling
    //QCoreApplication::setAttribute(Qt::AA_DisableHighDpiScaling );
    // Create the GUI application and set settings
    QGuiApplication app(argc, argv);
    app.setOrganizationName("THOPOP technological inventions");
    app.setOrganizationDomain("home.com");
    app.setApplicationName("NeverForgetHydra");
    app.setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Floor);
    // Register types (connect qml <> c++)
    // -- Backend on GUI
    qmlRegisterType<BackEnd>("io.home.essentials", 1, 0, "BackEnd");

    // -- Models that provide data to GUI
    // ---- Comboboxes
    qmlRegisterType<ComboBoxNamesModel>("io.home.essentials", 1, 0, "ComboBoxNamesModel");
    // ---- DataGrid
    qmlRegisterType<DatagridViewModel>("io.home.essentials", 1, 0, "DatagridViewModel");


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
