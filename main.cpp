#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QWindow>
#include "model_playlist.h"
#include "parameter.h"
#include "model_map.h"
#include "api_osmmap.h"
#include "uart_viewmodel.h"
#include "caro_viewmodel.h"
#include "caro_computer.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Material");
    app.setWindowIcon(QIcon(":/icon.ico"));

    QQmlApplicationEngine engine;
    ModelPlayList *playlist =  new ModelPlayList();
    qmlRegisterSingletonInstance("com.resource.playlist", 1, 0, "Playlist", playlist);

    Parameter *parameter = new Parameter();
    qmlRegisterSingletonInstance("com.resource.parameter", 1, 0, "Parameter", parameter);

    Model_Map *map = new Model_Map();
    qmlRegisterSingletonInstance("com.resource.map", 1, 0, "ModelMap", map);

    UartViewModel *uartViewModel = new UartViewModel();
    qmlRegisterSingletonInstance("com.resource.uart", 1, 0, "Uart", uartViewModel);

    CaroViewModel *caroViewModel = new CaroViewModel();
    qmlRegisterSingletonInstance("com.resource.caro", 1, 0, "Caro", caroViewModel);

    CaroComputer computer;
    QList<char> list = { '*', '*', '*', '.', '*', '*', '*', '.', '.', '.'};
    qDebug() << computer.convertListToScore(list, computer.map_attackScore);
    list = { '*', '*', '*', '.', '~', '*', '*', '.', '.', '.'};
    qDebug() << computer.convertListToScore(list, computer.map_defendScore);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Display_Application", "Main");

    int quit = app.exec();
    delete uartViewModel;
    delete playlist;
    delete parameter;
    delete map;
    delete caroViewModel;
    return quit;
}
