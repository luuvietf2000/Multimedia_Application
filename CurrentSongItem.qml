import QtQuick
import QtQuick.Layouts
import com.resource.playlist
Item {
    id: item
    property int width_size
    property int height_size
    property int size_image: 70
    width: width_size
    height: height_size
    RowLayout{
        id: row
        anchors.centerIn: parent
        width: parent.width
        height: parent.height
        spacing: 5
        TitleItem{
            id: titleMusic
            Layout.alignment: Qt.AlignTop
            Layout.preferredWidth: item.width_size * 1 / 2
            width_size: item.width_size * 1 / 2
            height_size: parent.height
            image_size: 50
            title: Playlist.nameSong
            description: Playlist.nameAuthor
            resource: Playlist.Image
        }
        Item{
            Layout.fillWidth: true
        }
        ButtonStyle{
            Layout.alignment: Qt.AlignTop
            Layout.preferredWidth: 60
            height_button: size_image
            width_button: size_image
            height_icon: size_image * 1 / 2
            width_icon: size_image * 1 / 2
            resource: Playlist.mediaState ? "qrc:/image/play-button-arrowhead.png" : "qrc:/image/pause.png"
            onButton_clicked:  Playlist.mediaState = !Playlist.mediaState
        }
        ButtonStyle{
            Layout.alignment: Qt.AlignTop
            Layout.preferredWidth: 60
            resource: "qrc:/image/next.png"
            height_button: size_image
            width_button: size_image
            height_icon: size_image * 1 / 2
            width_icon: size_image * 1 / 2
            onButton_clicked: Playlist.requestNextSong()
        }
        Item{
            Layout.fillWidth: true
        }
    }
    MouseArea{
        z: -1
        anchors.fill: parent
        onClicked: Playlist.changedMusicContent()
    }
}
