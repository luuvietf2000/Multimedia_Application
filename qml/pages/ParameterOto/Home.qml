import QtQuick
import QtQuick.Layouts
import com.resource.uart 1.0

Item {
    id: root
    property int width_Content
    property int height_Content
    width: width_Content
    height: height_Content
    Rectangle{
        property int border_size: 30
        width: parent.width - border_size
        height: parent.height - border_size
        radius: border_size
        anchors.centerIn: parent
        color: "black"
        RowLayout{
            anchors.fill: parent
            spacing: 5
            Rectangle{
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: "Transparent"
                WatchSpeedComponent{
                    width: parent.width
                    height: 300
                    anchors.centerIn: parent
                    needleAngle:  convertSpeed(Uart.speed, 200)
                }
            }
            Rectangle{
                color: "Transparent"
                Layout.alignment: Qt.AlignCenter
                Layout.fillHeight: true
                Layout.preferredWidth: parent.width / 8
                PowerComponent{
                    width: 50
                    height: 300
                    anchors.centerIn: parent
                    background_color: "black"
                    currentPower: Uart.power
                    maxPower: 99
                }
            }
        }
    }
    function convertSpeed(value, maxValue){
        var res = value / maxValue * 180
        return res
    }
}
