import QtQuick
import QtQuick.Layouts
import QtQuick.Effects
import com.resource.playlist

Item {
    id: item
    property int width_content
    property int height_content
    width: width_content
    height: height_content
    Rectangle{
        width: width_content - 20
        height: height_content - 20
        color: "white"
        radius: 10
        anchors.centerIn: parent
        ColumnLayout{
            anchors.fill: parent
            spacing: 0
            Text{
                leftPadding: 20
                id: title
                Layout.preferredHeight: 40
                Layout.preferredWidth: width_content - 50
                text: Playlist.nameSong
                width: width_content - 50
                elide: Text.ElideRight
                font.bold: true
                font.italic: true
                font.pointSize: 18
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            }
            ImageOvalStyle{
                Layout.fillWidth: true
                Layout.preferredHeight: 200
                image_size: 200
                resource: Playlist.Image
            }
            SliderControlMusic{
                Layout.preferredHeight: 50
                width_size: width_content - 20
                height_size: 50
                width_slider: 300
                height_slider: 50
                width_item: 40
                height_item: 40
                width_text: 50
            }
            MusicControl{
                Layout.preferredHeight: 60
                width_sizeContent: width_content - 20
                height_size: 60
            }
        }
    }
}
