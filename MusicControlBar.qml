import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import com.resource.playlist 1.0

Item {
    property int width_size
    property int height_size
    property int icon_size: 30
    property int width_currentSource: 120
    signal zingMp3Home()
    signal localHome()
    signal clickSearch(string keyword)

    width: width_size
    height: height_size
    RowLayout{
        anchors.centerIn: parent
        id: rowlayout
        width: width_size - 20
        height: height_size
        spacing: 10
        ButtonStyle{
            height_button: 40
            width_button: 40
            height_icon: icon_size
            width_icon: icon_size
            Layout.preferredWidth: 40
            resource: "qrc:/image/folder.png"
            onButton_clicked: localHome()
        }
        ButtonStyle{
            height_button: 40
            width_button: 40
            height_icon: icon_size
            width_icon: icon_size
            Layout.preferredWidth: 40
            resource: "qrc:/image/zingmp3.png"
            onButton_clicked: zingMp3Home()
        }
        ButtonStyle{
            height_button: 40
            width_button: 40
            height_icon: icon_size
            width_icon: icon_size
            visible: Playlist.visibleSearch
            Layout.preferredWidth: 40
            resource: "qrc:/image/search.png"
            onButton_clicked: Playlist.isSearch = true
        }
        ButtonStyle{
            height_button: 40
            width_button: 40
            height_icon: icon_size
            width_icon: icon_size
            visible: Playlist.isSearch
            Layout.preferredWidth: 40
            resource: "qrc:/image/back.png"
            onButton_clicked: Playlist.visibleSearch = false
        }
        TextField{
            id: search
            Layout.fillHeight: true
            Layout.preferredWidth: width_size / 3
            padding: 10
            placeholderText: "Vui lòng nhập keyword"
            visible: Playlist.isSearch
            background: Rectangle{
                height: height_size - 10
                width: width_size / 3
                color: "Transparent"
            }
            onEditingFinished: clickSearch(search.text)
        }
        Item{
            Layout.fillWidth: true
        }
    }
}
