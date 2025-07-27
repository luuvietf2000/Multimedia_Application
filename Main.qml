import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtQuick.Effects
import com.resource.parameter
Window {
    id: window
    width: 720
    height: 560
    visible: true
    flags: Qt.FramelessWindowHint
    onHeightChanged: Parameter.height = height
    onWidthChanged:  Parameter.width = width
    color: "Transparent"

    Component.onCompleted: function(){
        Parameter.height = height
        Parameter.width = width
    }
    Connections{
        target: Parameter
        function onActivePopupWarning(title, sourceImageTitle, description, sourceButtonAccept){
            popup.description = description
            popup.title = title
            if(sourceImageTitle !== "")
                popup.imageTitle = sourceImageTitle
            popup.open()
        }
    }
    Rectangle{
        anchors.fill: parent
        color: "#F2F2F2"
        radius: 10
        border.color: "#9c1f0c16"
        ColumnLayout{
            spacing: 0
            anchors.fill: parent
            ControlBar{
                id: controlbar
                Layout.preferredHeight: 30
                window: window
                width_controlbar: window.width
                height_controlbar: 30
            }
            Item{
                id: item
                Layout.fillHeight: true
                StackViewStyle{
                    id:stackview
                    width_size:  item.width
                    height_size: item.height
                    componentList: [music, map, remote, live, setting]
                }
            }
            NavigationBar{
                id: navigation
                Layout.preferredHeight: 60
                width_navigationBar: parent.width
                height_navigationBar: 60
                Component.onCompleted: {
                    navigation.item_changed.connect(stackview.handleItemChanged)
                }
            }
        }
    }

    PopupWarring{
        width_size: 300
        height_size: 220
        id: popup
    }

    Component{
        id: music
        Music{
            width_Content: window.width
            height_Content: item.height
        }
    }
    Component{
        id: map
        MapComponent{
            width_Content: window.width
            height_Content: item.height
        }
    }
    Component{
        id: remote
        Remote{}
    }
    Component{
        id: setting
        Setting{}
    }
    Component{
        id: live
        Live{}
    }
}
