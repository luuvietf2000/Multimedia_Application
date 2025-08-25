import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import QtPositioning
import com.resource.parameter
Item {
    id: item
    property int widthTextField
    property int heightTextField
    property int maximumWidthSizeComponent
    property int maximumHeightSizeComponent
    property int widthItem
    property int heightItem
    property int textSize
    property var object
    property string resource
    property int imageSize
    property int mode: 0
    property string address: "Tìm Kiếm Ở Đây"
    property bool isSelectionLocation: false
    property bool isVisible: true
    visible: isVisible
    implicitWidth: isVisible ? maximumWidthSizeComponent : 0
    implicitHeight: column.implicitHeight > maximumHeightSizeComponent ? maximumHeightSizeComponent: column.implicitHeight

    signal requestSearch(string keyword)
    signal selectionItem(var address, var location, var coordinate)
    signal outSide(bool isValid)
    MouseArea{
        anchors.fill: parent
        hoverEnabled: true
        z: 1
        acceptedButtons: Qt.NoButton
        propagateComposedEvents: true
        onContainsMouseChanged: function(){
            if(!containsMouse){
                mode = 0
                if(!isSelectionLocation){
                    address = "Tìm Kiếm Ở Đây"
                }
                outSide(isSelectionLocation)
                textField.focus = false
            } else
                isSelectionLocation = false
        }
    }
    ColumnLayout{
        id: column
        anchors.fill: parent
        spacing: 0
        Rectangle{
            Layout.preferredHeight: heightTextField
            Layout.fillWidth: true
            width: widthTextField
            height: heightTextField
            radius: heightTextField / 2
            border.color: textField.focus ? "#b50071f3" : "white"
            border.width: textField.focus ? 3 : 0
            Image{
                anchors.left: parent.left
                width: imageSize
                height: imageSize
                anchors.leftMargin: 20
                anchors.rightMargin: 0
                source: resource
                anchors.verticalCenter: parent.verticalCenter
            }
            TextField{
                id: textField
                anchors.right: parent.right
                anchors.rightMargin: heightTextField / 2
                height: parent.height
                width: parent.width - 20 - heightTextField / 2 - imageSize
                font.pointSize: textSize

                background: Rectangle{
                    anchors.fill: parent
                    color: "Transparent"
                }                
                text: address
                hoverEnabled: true
                onFocusChanged: {
                    if(focus){
                        isSelectionLocation = false
                        address = address !== "Tìm Kiếm Ở Đây" ? address : ""
                        mode = 1
                        object = defaultModel
                    }
                }
                onEditingFinished: function(){
                    if(focus){
                        focus = false
                        requestSearch(textField.text)
                    }
                }
            }
        }
        Item{
            Layout.preferredHeight: 5
            Layout.fillWidth: true
        }
        ListView{
            id: listView
            clip: true
            visible: mode !== 0
            Layout.preferredHeight: visible ? implicitHeight : 0
            implicitHeight: (contentHeight > maximumHeightSizeComponent - heightTextField ?  maximumHeightSizeComponent  - heightTextField : contentHeight) - 5
            implicitWidth: parent.width
            model: object
            delegate: componentItemSearch
        }
        PositionSource{
            id: currentLocation
            updateInterval: 1000
            onPositionChanged: ()=>{
                active = false
                handleSelectionItemMap(model[0].address, model[0].location, position)
            }
            onSourceErrorChanged: ()=>{
                active = false
            }
        }
    }
    Component{
        id: componentItemSearch
        Item{
            width: widthItem
            height: heightItem
            Rectangle{
                anchors.fill: parent
                color: "white"
                ColumnLayout{
                    anchors.fill: parent
                    spacing: 0
                    TitleItem{
                        Layout.fillWidth: true
                        Layout.preferredHeight: parent.height - 5
                        width_size: parent.width
                        height_size: parent.height - 5
                        image_size: 30
                        title: model.name
                        description: model.address
                        resource: "qrc:/image/location.png"
                        fontSize: 10
                    }
                    Item{
                        Layout.fillWidth: true
                        Layout.preferredHeight: 5
                        Rectangle{
                            visible: index !== listView.model.count - 1
                            anchors.centerIn: parent
                            width: parent.width / 10 * 8
                            height: 2
                            color: "#F2F2F2"
                        }
                    }
                }
            }
            MouseArea{
                anchors.fill: parent
                onClicked: function(){
                    if(defaultModel !== listView.model){
                        handleSelectionItemMap(model.address, model.location, model.coordinate)
                    }
                    else{
                        mode = 0
                        textField.focus = false
                        textField.text = name
                        isSelectionLocation = true
                        currentLocation.active = true
                        if(currentLocation.parameters.length === 0){
                            Parameter.activePopupWarning("Error", "qrc:/image/error.png", "Không tìm thấy drive Gps nào khả dụng!", "")
                        } else
                            currentLocation.active = true
                    }
                }
            }
        }
    }
    function handleSelectionItemMap(address, location, coordinate){
        textField.text = address
        isSelectionLocation = true
        textField.cursorPosition = 0
        selectionItem(address, location, coordinate)
    }
    ListModel{
        id: defaultModel
        ListElement{
            name: "Vị trí hiện tại"
            address: "Đang cập nhật..."
        }
    }
    function setText(content){
        address = content
    }
}
