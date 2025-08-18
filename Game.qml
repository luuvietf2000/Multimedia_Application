import QtQuick

Item {
    id: item
    property int width_Content
    property int height_Content
    width: width_Content
    height: height_Content
    Rectangle{
        width:  parent.width - 20
        height: parent.height - 20
        anchors.centerIn: parent
        color: "transparent"
        StackViewStyle{
            width_size: parent.width
            height_size: parent.height
            save: false
            componentList: [menuGame]
        }
    }
    Component{
        id: menuGame
        MenuBarComponent{
            listModel: listModelMenu
            width_Content: item.width_Content
            height_Content: item.height_Content
            title: "Game Playlist"
            titleResource: "qrc:/image/gamePlaylist.png"
        }
    }
    ListModel{
        id: listModelMenu
        ListElement{
            name: "Caro"
            path: "qrc:/image/caro.png"
        }
        ListElement{
            name: "test"
            path: "qrc:/image/caro.png"
        }
    }
}
