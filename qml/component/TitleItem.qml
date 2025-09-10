import QtQuick
import QtQuick.Layouts

Item {
    property int width_size
    property int height_size
    property string resource: "qrc:/image/zingmp3.png"
    property int image_size
    property string title
    property string description
    property int padding_left: 20
    property int fontSize: 14
    RowLayout{
        x: padding_left
        id: row
        width: width_size - padding_left
        height: height_size
        spacing: 10
        Image {
            id: image
            Layout.preferredWidth: image_size
            Layout.preferredHeight: image_size
            fillMode: Image.PreserveAspectCrop
            source: resource
            width: image_size
            height: image_size
            Layout.alignment: Qt.AlignVCenter
        }
        ColumnLayout{
            id: column
            Layout.fillWidth: true
            Layout.preferredHeight: image_size
            Layout.alignment: Qt.AlignLeft
            Text{
                text: title
                elide: Text.ElideRight
                wrapMode: Text.NoWrap
                Layout.fillWidth: true
                Layout.preferredHeight: image_size / 2
                font.family: "Arial"
                font.bold: false
                font.pointSize: fontSize
                verticalAlignment: Text.AlignVCenter
            }
            Text{
                verticalAlignment: Text.AlignVCenter
                text: description
                elide: Text.ElideRight
                wrapMode: Text.NoWrap
                Layout.fillWidth: true
                Layout.preferredHeight: image_size /2
                font.family: "Arial"
                font.bold: false
                font.pointSize: fontSize
            }
        }
    }
}
