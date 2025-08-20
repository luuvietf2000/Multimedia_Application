import QtQuick
import com.resource.caro

Item {
    id: root
    property int width_size
    property int height_size
    width: width_size
    height: height_size
    signal exitGame()

    ListModel{
        id: listMode
        ListElement{
            name: "Player Vs Cpu"
        }
        ListElement{
            name: "Player Vs Player"
        }
        ListElement{
            name: "Exit"
        }
    }
    readonly property int exitMode: 0
    readonly property var indexStackPage: {
        "Player Vs Cpu": 1,
        "Player Vs Player": 1,
        "Exit": exitMode
    }

    readonly property var modeObject: {
        "Player Vs Cpu": 0,
        "Player Vs Player" : 1,
        "Exit": 2
    }

    StackViewStyle{
        id: stack
        width_size: parent.width
        height_size: parent.height
        componentList: [gameMode, main]
    }
    Component{
        id: gameMode
        CaroGameMode{
            width_size: root.width_size
            height_size: root.height_size
            listModel: listMode
            onSelectionMode: (mode) =>{
                Caro.modeGame = modeObject[mode]
                if(exitMode !== indexStackPage[mode])
                    stack.handleItemChanged(indexStackPage[mode])
                else
                    exitGame()
            }
        }
    }
    Component{
        id: main
        CaroGameMain{
            width_size: root.width_size
            height_size: root.height_size
            onSelectionExitGame: {
                stack.handleItemChanged(0)
                Caro.modeGame = modeObject["Exit"]
                exitGame()
            }
        }
    }
}
