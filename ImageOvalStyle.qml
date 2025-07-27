import QtQuick
import QtQuick.Effects
import com.resource.playlist
Item {
    property string resource
    property int image_size: 200
    property color borderColor: "#E0C3FC"
    property int borderWidth: 15
    width: 300
    height: 300
    Rectangle {
        id: borderCircle
        width: image_size + borderWidth
        height: image_size + borderWidth
        radius: width / 2
        color: "transparent"
        border.color: borderColor
        border.width: borderWidth
        antialiasing: true
        anchors.centerIn: parent
    }

    Image {
        id: sourceItem
        source: resource
        width: image_size
        height: image_size
        visible: false
        smooth: true
    }

    Item {
        id: rotatedImage
        width: image_size
        height: image_size
        anchors.centerIn: parent
        rotation: ( Playlist.degree / 50 ) % 360
        transformOrigin: Item.Center
        layer.enabled: true
        layer.smooth: true

        MultiEffect {
            anchors.fill: parent
            source: sourceItem
            maskEnabled: true
            maskSource: mask
        }

        Item {
            id: mask
            width: image_size
            height: image_size
            visible: false
            layer.enabled: true
            layer.smooth: true

            Rectangle {
                width: parent.width
                height: parent.height
                radius: width / 2
                color: "black"
                antialiasing: true
            }
        }
    }
}
