import QtQuick

Item {
    property int width_navigationBar
    property int height_navigationBar: 50
    property int width_icon: 45
    property int height_icon: 45
    property string hightlight_color: "#cc47f97f"
    property int spacing_item: 0
    property string color_default: "transparent"
    property string color_highlinght: "#e33dc0eb"
    signal item_changed(int index)

    Component{
        id: component_item
        Item{
            width: width_icon
            height: height_icon
            required property string resource
            required property int index
            Row{
                Rectangle{
                    id: background
                    width: width_icon
                    height: height_icon
                    radius: 5
                    property bool hovered: false
                    color: hovered && listview.currentIndex != index ? color_highlinght : color_default
                    Image{
                        anchors.centerIn: parent
                        width: parent.width - 15
                        height: parent.height - 15
                        source: resource
                    }
                    MouseArea{
                        anchors.fill: parent
                        id: mouse
                        hoverEnabled: true
                        onEntered: background.hovered = true
                        onExited: background.hovered = false
                        onClicked: set_index(index)
                    }
                }
            }
        }
    }

    ListModel{
        id: listmodel
        ListElement{
            resource: "qrc:/image/mp3.png"
        }
        ListElement{
            resource: "qrc:/image/map.png"
        }
        ListElement{
            resource: "qrc:/image/remote.png"
        }
        ListElement{
            resource: "qrc:/image/video-player.png"
        }
        ListElement{
            resource: "qrc:/image/setting.png"
        }
    }

    function set_index(index){
        if(listview.currentIndex !== index){
            listview.currentIndex = index
            item_changed(index)
        }
    }
    function get_offsethorizontal(){
        var result = width_navigationBar - (listview.count * width_icon + (listview.count - 1) * (spacing_item))
        return result / 2
    }
    function get_offsetvertical(){
        var result = height_navigationBar - (height_icon)
        return result / 2
    }
    Rectangle{
        width: width_navigationBar
        height: height_navigationBar
        color: "Transparent"
        ListView{
            id: listview
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenterOffset: get_offsethorizontal()
            anchors.verticalCenterOffset: 10
            spacing: spacing_item
            width: width_navigationBar
            height: height_navigationBar
            orientation: ListView.Horizontal
            model: listmodel
            delegate: component_item
            highlight: Rectangle{
                width: width_icon
                height: height_icon
                radius: 5
                border.width: 2
                border.color: hightlight_color
            }
        }
    }
}
