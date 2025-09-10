cmake_minimum_required(VERSION 3.16)

project(Display_Application VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)
find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Multimedia)
find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2)
find_package(Qt6 REQUIRED COMPONENTS Location)
find_package(Qt6 REQUIRED COMPONENTS SerialPort)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appDisplay_Application
    main.cpp
)

qt_add_qml_module(appDisplay_Application
    URI Display_Application
    VERSION 1.0
    SOURCES core/CaroGame/caro_computer.cpp core/CaroGame/caro_computer.h   core/CaroGame/caro_winchecker.cpp core/CaroGame/caro_winchecker.h core/Uart/uart.cpp core/Uart/uart.h models/api/api_osmmap.cpp models/api/api_osmmap.h models/api/API_ZingMp3.cpp models/api/API_ZingMp3.h ViewModel/CaroViewModel/caro_viewmodel.cpp ViewModel/CaroViewModel/caro_viewmodel.h ViewModel/MapViewModel/model_map.cpp ViewModel/MapViewModel/model_map.h ViewModel/ParameterViewModel/parameter.cpp ViewModel/ParameterViewModel/parameter.h ViewModel/PlaylistViewModel/model_playlist.cpp ViewModel/PlaylistViewModel/model_playlist.h ViewModel/UartViewModel/uart_viewmodel.cpp ViewModel/UartViewModel/uart_viewmodel.h
    RESOURCES Resource.qrc
    QML_FILES qml/component/ButtonStyle.qml qml/component/ImageOvalStyle.qml qml/component/PopupWarring.qml qml/component/TitleItem.qml qml/pages/Game/CaroGame/CaroGame.qml qml/pages/Game/CaroGame/CaroGameMain.qml qml/pages/Game/CaroGame/CaroGameMode.qml qml/pages/Game/Game.qml qml/pages/Live/Live.qml qml/pages/Map/MapComponent.qml qml/pages/Map/MapItem.qml qml/pages/Map/RoadDetail.qml qml/pages/Map/SearchMapComponent.qml qml/pages/Map/TextStyleRoad.qml qml/pages/ParameterOto/Home.qml qml/pages/ParameterOto/PowerComponent.qml qml/pages/ParameterOto/WatchSpeedComponent.qml qml/pages/PlaylistMusic/ContentItemMusic.qml qml/pages/PlaylistMusic/ControlBar.qml qml/pages/PlaylistMusic/CurrentSongItem.qml qml/pages/PlaylistMusic/Main.qml qml/pages/PlaylistMusic/MapComponent.qml qml/pages/PlaylistMusic/MapItem.qml qml/pages/PlaylistMusic/Music.qml qml/pages/PlaylistMusic/MusicContent.qml qml/pages/PlaylistMusic/MusicControl.qml qml/pages/PlaylistMusic/MusicControlBar.qml qml/pages/PlaylistMusic/MusicListViewPlayList.qml qml/pages/PlaylistMusic/PlayListMusic.qml qml/pages/PlaylistMusic/SliderControlMusic.qml qml/pages/PlaylistMusic/ZingMp3Home.qml qml/pages/Remote/Remote.qml qml/pages/Setting/Setting.qml qml/pages/MenuBarComponent.qml qml/pages/NavigationBar.qml qml/pages/StackViewStyle.qml
)

target_include_directories(appDisplay_Application PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/ViewModel/MapViewModel
    ${CMAKE_CURRENT_SOURCE_DIR}/core/CaroGame
    ${CMAKE_CURRENT_SOURCE_DIR}/core/Uart
    ${CMAKE_CURRENT_SOURCE_DIR}/models/api
    ${CMAKE_CURRENT_SOURCE_DIR}/ViewModel/CaroViewModel
    ${CMAKE_CURRENT_SOURCE_DIR}/ViewModel/ParameterViewModel
    ${CMAKE_CURRENT_SOURCE_DIR}/ViewModel/PlaylistViewModel
    ${CMAKE_CURRENT_SOURCE_DIR}/ViewModel/UartViewModel
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appDisplay_Application PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appDisplay_Application
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appDisplay_Application
    PRIVATE Qt6::Quick
    PRIVATE Qt6::QuickControls2
    PRIVATE Qt6::Multimedia
    PRIVATE Qt6::Location
    PRIVATE Qt6::SerialPort
)

include(GNUInstallDirs)
install(TARGETS appDisplay_Application
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
