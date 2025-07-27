import QtQuick
import QtQuick.Layouts
import com.resource.playlist 1.0
Item {
    property int width_sizeContent
    property int height_size
    property int width_size: 40
    property int icon_size: 25
    property string color_enableBackground: "#e33dc0eb"
    property string color_dislableBackground: "white"
    property bool state_PlayMusic: false

    RowLayout{
        width: width_sizeContent
        height: height_size
        Item{
            Layout.fillWidth: true
        }
        Rectangle {
            height: height_size
            width: row.implicitWidth
            color: "#E5D1FA"
            radius: height_size / 2
            RowLayout {
                id: row
                height: parent.height
                Repeater {
                    id: repeater
                    model: [
                        "qrc:/image/download.png",
                        "qrc:/image/previous.png",
                        "qrc:/image/play-button-arrowhead.png",
                        "qrc:/image/next.png",
                        "qrc:/image/arrows.png"
                    ]

                    delegate: ButtonStyle {
                        Layout.alignment: Qt.AlignTop
                        Layout.preferredWidth: height_size
                        width_icon: icon_size
                        height_icon: icon_size
                        width_button: height_size
                        height_button: height_size
                        resource: setImages(index, modelData)
                        onButton_clicked: handleButtonClick(index)
                    }
                }
            }
        }
        Item{
            Layout.fillWidth: true
        }

    }
    function setImages(index, source){
        switch(index){
            case 0:
                return Playlist.download ? "qrc:/image/download.png" : "qrc:/image/no-download.png"
            case 2:
                return Playlist.mediaState ? "qrc:/image/pause.png" : "qrc:/image/play-button-arrowhead.png"
            case 4:
                switch (Playlist.nextState){
                    case 0: return "qrc:/image/tune.png"
                    case 1: return "qrc:/image/repeat.png"
                    case 2: return "qrc:/image/shuffle.png"
                }
        }
        return source
    }
    function handleButtonClick(index){
        switch(index){
            case 0:
                if(Playlist.download === true)
                    return
                Playlist.download = true
                Playlist.requestDownload()
                break
            case 1:
                Playlist.requestPreviosSong()
                break
            case 2:
                if(Playlist.source === undefined || Playlist.source === null || Playlist.source === "")
                    return
                Playlist.mediaState = !Playlist.mediaState
                break
            case 3:
                Playlist.requestNextSong()
                break
            case 4: Playlist.nextState++
                break
            default: break
        }
    }
}
