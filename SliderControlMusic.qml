import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import com.resource.playlist
Item {
    property int width_size
    property int height_size
    property int width_slider
    property int height_slider
    property int width_item
    property int height_item
    property int width_text
    RowLayout{
        width: width_size
        height: height_size
        spacing: 30
        Item{
            Layout.fillWidth: true
        }
        Item{
            width: width_text
            height: height_size
            Text{
                width: width_text
                height: height_size
                horizontalAlignment: Text.AlignRight
                id: value_start
                text: convertPosition(Playlist.degree / 1000)
                Layout.preferredWidth: width_text
                font.family: "Arial"
                font.bold: false
                font.pointSize: 14
                verticalAlignment: Text.AlignVCenter
            }
        }
        Slider{
            Layout.preferredWidth: width_slider
            id: control
            to: Playlist.length / 1000
            from: 0
            value: pressed ? value : Playlist.degree / 1000
            onMoved: function(){
                Playlist.setPositionMediaPlay(value)
            }
            background: Rectangle {
                x: control.leftPadding
                y: control.topPadding + control.availableHeight / 2 - height / 2
                implicitWidth: 200
                implicitHeight: 8
                height: 4
                width: width_slider
                radius: 2
                color: "#bdbebf"
                Rectangle {
                    width: control.leftPadding + control.visualPosition * parent.width -  oval.width / 2
                    height: parent.height
                    color: "#21be2b"
                    radius: 2
                }
            }
            handle: Rectangle {
                id: oval
                x: control.leftPadding + control.visualPosition * parent.width - width / 2
                y: control.topPadding + control.availableHeight / 2 - height / 2
                implicitWidth: 26
                implicitHeight: 26
                radius: 13
                color: control.pressed ? "#f0f0f0" : "#f6f6f6"
                border.color: "#bdbebf"
            }
        }
        Item{
            width: width_text
            height: height_size
            Text{
                width: width_text
                height: height_size
                horizontalAlignment: Text.AlignLeft
                anchors.centerIn: parent
                id: value_end
                text: convertPosition(Playlist.length / 1000)
                Layout.preferredWidth: width_text
                font.family: "Arial"
                font.bold: false
                font.pointSize: 14
                verticalAlignment: Text.AlignVCenter
            }
        }
        Item {
            Layout.fillWidth: true
        }
    }
    function insert(value){
        var result
        if(value > 9) return value
        else return "0" + value
    }
    function convertPosition(value){
        var result = value < 3600 ? insert(parseInt(value / 60)) + ":" + insert(parseInt(value % 60)) : insert(parseInt(value / 3600)) + ":" + insert(parseInt(value / 60)) + ":" + insert(parseInt(value % 60))
        return result
    }
}
