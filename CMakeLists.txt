cmake_minimum_required(VERSION 3.16)

project(Display_Application VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)
find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Multimedia)
find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2)
find_package(Qt6 REQUIRED COMPONENTS Location)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appDisplay_Application
    main.cpp
)

qt_add_qml_module(appDisplay_Application
    URI Display_Application
    VERSION 1.0
    QML_FILES
        Main.qml
        QML_FILES ControlBar.qml
        RESOURCES Resource.qrc
        QML_FILES ButtonStyle.qml
        QML_FILES NavigationBar.qml
        QML_FILES Music.qml
        QML_FILES Remote.qml
        QML_FILES Setting.qml
        QML_FILES Live.qml
        QML_FILES MusicContent.qml
        QML_FILES MusicControl.qml
        QML_FILES MusicControlBar.qml
        SOURCES API_ZingMp3.h API_ZingMp3.cpp
        QML_FILES SliderControlMusic.qml
        QML_FILES PlayListMusic.qml
        QML_FILES TitleItem.qml
        QML_FILES StackViewStyle.qml
        QML_FILES ZingMp3Home.qml
        SOURCES model_playlist.h model_playlist.cpp
        QML_FILES ImageOvalStyle.qml
        QML_FILES MusicListViewPlayList.qml
        QML_FILES PopupWarring.qml
        SOURCES parameter.h parameter.cpp
        QML_FILES CurrentSongItem.qml
        QML_FILES MapComponent.qml
        QML_FILES SearchMapComponent.qml
        SOURCES api_osmmap.h api_osmmap.cpp
        SOURCES model_map.h model_map.cpp
        QML_FILES MapItem.qml
        QML_FILES RoadDetail.qml
        QML_FILES TextStyleRoad.qml
        RESOURCES
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
)

include(GNUInstallDirs)
install(TARGETS appDisplay_Application
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
