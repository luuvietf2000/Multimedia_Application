import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import com.resource.playlist

Item {
    id: item
    property int width_scroll
    property int height_scroll
    property int header_size: 80
    property int title_size: 70
    property int item_size: 60
    Connections{
        target: Playlist
        function onPlayListNewRelease(info){
            release.object = info
        }
        function onPlaylistHistory(info){
            history.object = info
        }
        function onPlaylistRecomment(info){
            like.object = info
        }
    }
    ColumnLayout{
        id: column
        width: width_scroll
        height: height_scroll
        spacing: 5
        ScrollView{
            id: control
            width: width_scroll
            Layout.fillHeight: true
            ScrollBar.vertical: ScrollBar {
                policy: ScrollBar.AlwaysOff
            }

            ScrollBar.horizontal: ScrollBar {
                policy: ScrollBar.AlwaysOff
            }
            ColumnLayout{
                width: width_scroll
                spacing: 30
                MusicListViewPlayList {
                    id: history
                    width_size: width_scroll - 20
                    Layout.preferredWidth: width_scroll - 20
                    Layout.preferredHeight: history.height
                    resource: "qrc:/image/history.png"
                    title: "Nghe Gần Đây"
                    Layout.alignment: Qt.AlignHCenter
                    main_parent: "ZingMp3"
                }
                MusicListViewPlayList {
                    width_size: width_scroll - 20
                    id: like
                    Layout.preferredHeight: like.height
                    Layout.preferredWidth: width_scroll - 20
                    resource:  "qrc:/image/like.png"
                    title: "Gợi ý"
                    Layout.alignment: Qt.AlignHCenter
                    main_parent: "ZingMp3"
                }
                MusicListViewPlayList {
                    id: release
                    Layout.preferredHeight: release.height
                    width_size: width_scroll - 20
                    Layout.preferredWidth: width_scroll - 20
                    resource: "qrc:/image/project-launch.png"
                    title: "Mới Phát Hành"
                    Layout.alignment: Qt.AlignHCenter
                    main_parent: "ZingMp3"
                }
            }
        }
        Item{
            Layout.fillHeight: true
        }
        Rectangle{
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            Layout.preferredWidth: column.width - 20
            Layout.preferredHeight: header_size - 10
            width: column.width - 20
            height: header_size - 10
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
