import QtQuick
import QtQuick.Layouts

Item {
    id: root
    property string title
    property string titleResource
    property var listModel
    property int height_Content
    property int width_Content
    readonly property int indexMainMenu: 0
    width: parent.width
    height: parent.height
    Rectangle{
        id: rec
        radius: 5
        width: parent.width
        height: parent.height
        anchors.centerIn: parent
        color: "transparent"
        StackViewStyle{
            id: stack
            width_size: parent.width
            height_size: parent.height
            componentList: [gameControler, caroComponent]
        }
    }
    FontLoader {
        id: fontGame
        source: "qrc:/font/PressStart2P-Regular.ttf"
    }
    Component{
        id: caroComponent
        CaroGame{
            width_size: rec.width
            height_size: rec.height
            onExitGame: {
                stack.handleItemChanged(indexMainMenu)
            }
        }
    }
    Component{
        id: gameControler
        Rectangle{
            radius: 5
            color: "white"
            width: rec.width
            height: rec.height
            ListView{
                id: listView
                spacing: 5
                width: parent.width - 10
                height: parent.height - 10
                anchors.centerIn: parent
                clip: true
                header: Loader{
                            id: headerItem
                            sourceComponent: itemMenu
                            onLoaded:{
                                headerItem.item.heightItem = 60
                                headerItem.item.titleItem = title
                                headerItem.item.pathResource = titleResource
                                headerItem.item.fontSize = 40
                                headerItem.item.isBold = true
                                headerItem.item.isItalic = true
                            }
                        }
                model: listModel
                delegate: itemContent
                highlight: null
            }
        }
    }
    Component{
        id: itemContent
        Item{
            width: rec.width - 10
            height: 55
            Rectangle{
                anchors.fill: parent
                radius: 10
                color: "#C7F1FF"
                Loader{
                    width: parent.width - 10
                    height: parent.height - 10
                    anchors.centerIn: parent
                    id: loadItemContent
                    sourceComponent: itemMenu
                    onLoaded: {
                        loadItemContent.item.heightItem = 45
                        loadItemContent.item.titleItem = model.name
                        loadItemContent.item.pathResource = model.path
                    }
                }
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    stack.handleItemChanged(index + 1)
                }
            }
        }
    }
    Component{
        id: itemMenu
        Item{
            property int heightItem
            property string titleItem
            property string pathResource
            property int fontSize: 24
            property bool isBold: false
            property bool isItalic: false
            width: rec.width
            height: heightItem
            Rectangle{
                anchors.fill: parent
                color: "transparent"
                RowLayout{
                    anchors.fill: parent
                    spacing: 10
                    Image {
                        Layout.preferredWidth: parent.height - 10
                        Layout.preferredHeight: parent.height - 10
                        Layout.alignment: Qt.AlignVCenter
                        id: image
                        source: pathResource
                    }
                    Text {
                        verticalAlignment: Text.AlignVCenter
                        Layout.fillWidth: true
                        Layout.preferredHeight: parent.height - 10
                        Layout.alignment: Qt.AlignVCenter
                        wrapMode: Text.Wrap
                        font.pixelSize: fontSize
                        font.italic: isItalic
                        font.bold: isBold
                        font.family: fontGame.name
                        id: textTitle
                        text: titleItem
                    }
                }
            }
        }
    }
}
