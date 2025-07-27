import QtQuick
import QtQuick.Layouts
import com.resource.playlist
import com.resource.parameter
Item {
    id: item
    property int width_size
    property int height_size
    property int header_size: 80
    property int title_size: 70
    property int item_size: 60
    property string resource
    property string title
    property var object: []
    property string main_parent
    implicitWidth: width_size
    implicitHeight: listview.implicitHeight + 20
    Rectangle{
        anchors.centerIn: parent
        width: width_size - 10
        height: listview.implicitHeight
        //anchors.centerIn: parent
        color: "white"
        radius: 10
        ListView{
            id: listview
            interactive: false
            width: width_size
            model: object
            implicitHeight: contentHeight
            clip: true
            header: Loader {
                sourceComponent: header_listview
            }
            delegate: component_delegate
        }
    }


    Component{
        id: header_listview
        Item{
            id:item
            width: width_size
            height: header_size
            Rectangle{
                anchors.centerIn: parent
                width: width_size - 20
                height: item_size
                color: "transparent"
                radius: 20
                Row{
                    anchors.fill: parent
                    spacing: 10
                    Image{
                        y: item_size / 4
                        width: item_size / 2
                        height: item_size / 2
                        source: resource
                    }
                    Text{
                        verticalAlignment: Text.AlignVCenter
                        height: item_size
                        text: title
                        font.pointSize: 24
                        font.italic: true
                        font.bold: true
                    }
                }
            }
        }
    }
    Component{
        id: component_delegate
        Item{
            height: header_size + 10
            width: width_size - 10
            Rectangle{
                height: header_size
                width: width_size - 20
                radius: 10
                border.width: 0
                color: mouse.containsMouse ? "#e33dc0eb" : "#f9c8d9"
                anchors.centerIn: parent
                RowLayout{
                    anchors.fill: parent
                    TitleItem{
                        Layout.preferredHeight: header_size
                        Layout.preferredWidth: (item.width_size) * 2 / 3
                        width_size: (item.width_size) * 2 / 3
                        height_size: header_size
                        image_size: item_size
                        title: model.song
                        description: model.author
                        resource: model.resource
                    }
                    Image{
                        Layout.preferredHeight: 30
                        Layout.preferredWidth: 30
                        width: 30
                        height: 30
                        visible: model.streamingStatus === 2
                        source: "qrc:/image/crown.png"
                    }
                    Item{
                        Layout.fillWidth: true
                    }
                }
                MouseArea{
                    id: mouse
                    hoverEnabled: true
                    anchors.fill: parent
                    onClicked: {
                        if(model.streamingStatus === 2)
                            Parameter.activePopupWarning("Cảnh báo!", "", "Bài hát chỉ dành cho tài khoản vip. Vui lòng đăng nhập hoặc nâng cấp lên tài khoản vip!", "")
                        else{
                            Playlist.requestStreamingAudioLink(model.id)
                            Playlist.changedMusicContent()
                            Playlist.setPropertyMusic(model.song, model.author, model.resource, false)
                            Playlist.isSearch = false
                            Playlist.visibleSearch = false
                            Playlist.requestSelectionPlaylist(object)
                        }
                    }
                }
            }
        }
    }
}
