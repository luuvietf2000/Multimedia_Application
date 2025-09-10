import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import com.resource.parameter
Popup{
    property int width_size: 300
    property int height_size: 220
    property int icon_size: 25
    property int button_size: 40
    property string title: "Warring"
    property string description: "description"
    property string imageTitle: "qrc:/image/warning.png"
    property string imageButton: "qrc:/image/check.png"
    id: popup
    width: Parameter.width
    height: Parameter.height
    background: Rectangle{
        anchors.fill: parent
        color: "Transparent"
    }
    Rectangle{
        anchors.centerIn: parent
        width: width_size
        height: height_size
        radius: 10
        color: "white"
        border.color: "#9c1f0c16"
        ColumnLayout{
            anchors.fill: parent
            spacing: 0
            Item{
                Layout.fillWidth: true
                Layout.preferredHeight: 70
                Image{
                    anchors.centerIn: parent
                    source: imageTitle
                }
            }
            Item {
                Layout.fillWidth: true
                Layout.preferredHeight: 50
                Text{
                    anchors.centerIn: parent
                    width: parent.width - 10
                    height: parent.height - 10
                    horizontalAlignment: Text.AlignHCenter
                    font.italic: true
                    font.bold: true
                    text: title
                    font.pointSize: 24
                }
            }
            Item{
                Layout.fillWidth: true
                Layout.fillHeight: true
                Text {
                    horizontalAlignment: Text.AlignHCenter
                    anchors.fill: parent
                    id: descriptionItem
                    width: parent.width - 10
                    height: parent.height
                    wrapMode: Text.Wrap
                    text: description
                }
            }
            Item{
                Layout.fillWidth: true
               Layout.preferredHeight: 50
                ButtonStyle{
                    anchors.centerIn: parent
                    Layout.preferredWidth: 30
                    resource: imageButton
                    onButton_clicked: popup.close()
                }
            }
        }
    }
}
