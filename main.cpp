#include <QGuiApplication>
#include <QQuickStyle>

#include "qmlengine.h"
#include "registermodules.h"

// Enable hot-reload or not (hot-reload only works without qrc:)
#define DEVELOPMENT

int main(int argc, char* argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQuickStyle::setStyle("Material");

    auto curDir = QString(PROJECT_SOURCE_DIR);
    auto mainQml = curDir + "/qml/main.qml";
    QmlEngine engine;
#ifdef DEVELOPMENT
    const QUrl url(QUrl::fromLocalFile(mainQml));
#else
    const QUrl url(QStringLiteral("qrc:/main.qml"));
#endif
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject * obj, const QUrl & objUrl)
    {
        if (!obj && url == objUrl)
        {
            QCoreApplication::exit(-1);
        }
    },
    Qt::QueuedConnection);

    // Registering MetaTypes
    registerModules();

    // Adding qmlEngine for application hot-reload
    engine.rootContext()->setContextProperty("_qmlEngine", &engine);

    engine.load(url);

    return app.exec();
}
