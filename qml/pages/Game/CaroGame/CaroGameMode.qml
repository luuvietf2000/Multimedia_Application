import QtQuick
import QtQuick.Layouts

Item {
    id: root
    property int width_size
    property int height_size
    property var listModel
    width: width_size
    height: height_size
    signal selectionMode(string mode)

    Rectangle{
        anchors.fill: parent
        radius: 5
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#7F00FF" }
            GradientStop { position: 1.0; color: "#E100FF" }
        }
    }

    ColumnLayout{
        width: parent.width / 2
        anchors.centerIn: parent
        spacing: 20
        Image {
            Layout.preferredHeight: 60
            Layout.preferredWidth: 60
            Layout.alignment: Qt.AlignCenter
            source: "qrc:/image/caro.png"
        }
        Repeater{
            Layout.preferredWidth: parent
            Layout.preferredHeight: 200
            model: listMode
            delegate: rect
        }

    }

    Component{
        id: rect
        Item{
            width: width_size / 2
            height: 70
            Rectangle{
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#FF416C" }
                    GradientStop { position: 1.0; color: "#FF9966" }
                }
                width: parent.width - 10
                height: parent.height - 10
                radius: parent.height / 2
                anchors.centerIn: parent
                FontLoader {
                    id: fontGame
                    source: "qrc:/font/PressStart2P-Regular.ttf"
                }
                Text{
                    text: model.name
                    font.pixelSize: 14
                    anchors.centerIn: parent
                    color: "white"
                    font.family: fontGame.name
                }
            }
            MouseArea{
                anchors.fill: parent
                onClicked: selectionMode(model.name)
            }
        }
    }
}
