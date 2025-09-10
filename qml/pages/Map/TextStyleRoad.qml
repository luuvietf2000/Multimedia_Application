import QtQuick

Item{
    property string content
    property int textSize
    implicitHeight: text.contentHeight
    implicitWidth: text.contentWidth
    Text{
        id: text
        wrapMode: Text.Wrap
        text: content
        font.bold: true
        font.italic: false
        font.pixelSize: textSize
    }
}
