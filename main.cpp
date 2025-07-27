#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QWindow>
#include "model_playlist.h"
#include "parameter.h"
#include "model_map.h"
#include "api_osmmap.h"
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Material");

    QQmlApplicationEngine engine;
    ModelPlayList *playlist =  new ModelPlayList();
    qmlRegisterSingletonInstance("com.resource.playlist", 1, 0, "Playlist", playlist);

    Parameter *parameter = new Parameter();
    qmlRegisterSingletonInstance("com.resource.parameter", 1, 0, "Parameter", parameter);

    Model_Map *map = new Model_Map();
    qmlRegisterSingletonInstance("com.resource.map", 1, 0, "ModelMap", map);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Display_Application", "Main");

    int quit = app.exec();
    playlist->deleteLater();
    parameter->deleteLater();
    map->deleteLater();
    return quit;
}
