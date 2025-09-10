import QtQuick
import QtQuick.Layouts
import QtMultimedia
import com.resource.playlist 1.0

Item {
    id: item
    property int height_Content: 300
    property int width_Content
    property int height_ControlBar: 40
    property var object: []
    height: height_Content
    width:  width_Content

    Connections{
        target: Playlist
        function onChangedMusicContent(){
            stack_view.handleItemChanged(0)
        }
        function onPlaylistChanged(info){
            item.object = info
        }
        function onMediaStateChanged(){
            if(Playlist.mediaState === true){
                media.setPosition(0)
                media.play()
            }
            else{
                media.pause()
            }
        }
        function onSetPositionMediaPlay(pos){
            media.setPosition(pos * 1000)
        }
    }
    MediaPlayer{
        id: media
        audioOutput: audio
        source: Playlist.source
        onPositionChanged: function (position) {
            Playlist.degree = position
        }
        Component.onDestruction: function(){
            media.stop()
        }
        autoPlay: true
        onMediaStatusChanged: function(){
            if (media.mediaStatus === MediaPlayer.LoadedMedia) {
                if(Playlist.mediaState === true){
                    media.setPosition(0)
                    media.play()
                } else
                    Playlist.mediaState = true
            }
        }
        onDurationChanged: Playlist.length = media.duration
    }
    AudioOutput{
        id: audio
        volume: 50
    }
    ColumnLayout{
        spacing: 0
        MusicControlBar{
            id: controlbar
            height_size: height_ControlBar
            width_size: width_Content
            width: width_Content
            Layout.preferredHeight: height_ControlBar
            onZingMp3Home: {
                Playlist.visibleSearch = true
                Playlist.requestHomeZingMp3()
                stack_view.handleItemChanged(2)
            }
            onLocalHome: {
                Playlist.requestLocalPlaylist()
                stack_view.handleItemChanged(1)
            }
            onClickSearch: function(keyword){
                stack_view.handleItemChanged(1)
                Playlist.requestSearchZingMp3(keyword)
            }
        }
        StackViewStyle{
            id: stack_view
            Layout.fillHeight: true
            width_size: item.width
            height_size: height_Content - height_ControlBar
            componentList: [music_content, playlist_content , zingmp3_content]
            save: false
        }

    }
    Component{
        id: music_content
        MusicContent{
            id: content
            width_content: width_Content
            height_content: height_Content - height_ControlBar
        }
    }
    Component{
        id: playlist_content
        PlayListMusic{
            id: playlist
            width_size:  width_Content
            height_size:  height_Content - height_ControlBar
            object: item.object
        }
    }
    Component{
        id: zingmp3_content
        ZingMp3Home{
            width_scroll: width_Content
            height_scroll:  height_Content - height_ControlBar
        }
    }
}
