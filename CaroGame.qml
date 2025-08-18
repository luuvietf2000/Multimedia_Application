import QtQuick

Item {
    id: root
    property int width_size
    property int height_size
    width: width_size
    height: height_size
    StackViewStyle{
        width_size: parent.width
        height_size: parent.height
        componentList: [gameMode]
    }
    Component{
        id: gameMode
        CaroGameMode{
            width_size: root.width_size
            height_size: root.height_size
        }
    }
}
