import QtQuick
import QtQuick.Layouts
import com.resource.playlist 1.0
import QtQuick.Controls

Item {
    id: item
    property int width_size
    property int height_size
    property int size_image: 70
    property int currentSong_size: 80
    property var object: []
    width: width_size
    height: height_size
    ColumnLayout{
        id: column
        anchors.fill: parent
        spacing: 5
        ScrollView{
            id: control
            width: width_size
            Layout.fillHeight: true
            ScrollBar.vertical: ScrollBar {
                policy: ScrollBar.AlwaysOff
            }

            ScrollBar.horizontal: ScrollBar {
                policy: ScrollBar.AlwaysOff
            }
            MusicListViewPlayList {
                id: playlist
                width_size: item.width_size
                Layout.preferredWidth: width_size
                Layout.fillHeight: true
                resource: "qrc:/image/music-folder.png"
                title: "Danh Sách Phát"
                anchors.horizontalCenter: parent.horizontalCenter
                object: item.object
            }
        }
        Rectangle{
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredWidth: column.width - 20
            Layout.preferredHeight: currentSong_size - 10
            color: "#ccd84bfb"
            radius: 10
            CurrentSongItem{
                anchors.centerIn: parent
                width_size: parent.width
                height: parent.height
            }
        }
    }
}
