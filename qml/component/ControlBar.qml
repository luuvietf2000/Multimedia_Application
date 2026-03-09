import QtQuick
import QtQuick.Layouts

Item {
    property var window
    property int width_controlbar
    property int height_controlbar
    width: width_controlbar
    height: height_controlbar
    RowLayout{
        anchors.centerIn: parent
        width: width_controlbar - 20
        height: height_controlbar
        spacing: 0
        Text{
            Layout.alignment: Qt.AlignVCenter
            id: title
            text: "Control Appliaction"
            Layout.preferredWidth: 100
            font.family: "Arial"
            font.bold: false
            font.pointSize: 10
            verticalAlignment: Text.AlignVCenter
        }
        Item {
            Layout.fillWidth: true
            Layout.fillHeight: true
            MouseArea {
                anchors.fill: parent
                property real clickX
                property real clickY

                onPressed: function(){
                    clickX = mouseX
                    clickY = mouseY
                }

                onPositionChanged: function(mouse) {
                    if (mouse.buttons === Qt.LeftButton) {
                        window.x += mouseX - clickX
                        window.y += mouseY - clickY
                    }
                }
            }
        }
        ButtonStyle{
            id: button_minimum
            Layout.preferredWidth: 30
            resource: "qrc:/image/minimum.png"
            onButton_clicked: window.visibility = Window.Minimized
        }
        ButtonStyle{
            id: button_maximum
            Layout.preferredWidth: 30
            resource: "qrc:/image/maximum.png"
            onButton_clicked: window.visibility = Window.Maximized
        }
        ButtonStyle{
            id:button_close
            height_button: height_controlbar
            Layout.preferredWidth: 30
            resource: "qrc:/image/close.png"
            onButton_clicked: window.close()
        }
    }
}
