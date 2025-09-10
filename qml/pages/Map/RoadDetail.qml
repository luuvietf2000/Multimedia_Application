import QtQuick
import QtQuick.Layouts
import QtQuick.Controls
import com.resource.map
Item {
    id: item
    readonly property string contentTitle: "Thông tin chi tiết"
    readonly property string contentAddressTitle: "Quãng đường"
    property int heightTitle: 50
    property int heightAddress: 40
    property int heightContent: 30
    property int widthSize: 400
    property int heightSize: 200
    property int indexItemSelectionTitle: 0
    property bool isOpen: false
    property var listParamter
    anchors.fill: parent
    signal selectionItem(var index)
    visible: false
    Rectangle{
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: widthSize
        height: heightSize
        radius: 10
        ScrollView{
            ScrollBar.vertical.policy: ScrollBar.AlwaysOff
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            width: parent.width - 20
            anchors.centerIn: parent
            height: parent.height
            ColumnLayout{
                id: layoutTitle
                width: parent.width
                spacing: 5
                Rectangle{
                    height: heightTitle
                    width: parent.width
                    color: "Transparent"
                    Layout.alignment: Qt.AlignHCenter
                    TextStyleRoad{
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        textSize: 20
                        content: contentTitle
                    }
                    ButtonStyle{
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        resource: "qrc:/image/close.png"
                        onButton_clicked: close()
                    }
                }
                Rectangle{
                    Layout.preferredHeight: 2
                    Layout.preferredWidth: parent.width
                    Layout.alignment: Qt.AlignHCenter
                    radius: 1
                    color: "black"
                }
                Rectangle{
                    Layout.preferredHeight: heightAddress
                    Layout.preferredWidth: parent.width
                    Layout.alignment: Qt.AlignHCenter
                    TextStyleRoad{
                        anchors.left:parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        textSize: 18
                        content: contentAddressTitle
                    }
                }
                RowLayout{
                    id: roadContent
                    Layout.preferredWidth: parent.width
                    Layout.alignment: Qt.AlignHCenter
                    spacing: 5
                    Repeater{
                        id: repeaterRoadContent
                        model: ["start", "--->", "stop"]
                        delegate: Text{
                            Layout.preferredWidth: index === 1 ? 30 : ((roadContent.width - 30 - roadContent.spacing * 2) / 2)
                            text: modelData
                            wrapMode: Text.Wrap
                            font.pixelSize: 14
                        }
                    }
                }
                Rectangle{
                    Layout.preferredHeight: 2
                    Layout.preferredWidth: parent.width
                    Layout.alignment: Qt.AlignHCenter
                    radius: 1
                    color: "black"
                }

                RowLayout{
                    id: roadTitleItem
                    Layout.fillWidth: true
                    Repeater{
                        id: repeater
                        model: itemSelectionModel
                        delegate: Item{
                            Layout.fillWidth: true
                            implicitHeight: itemRoadTitle.implicitHeight
                            property string _content: model.content
                            property string _resource: model.resource
                            Loader{
                                id: itemRoadTitle
                                sourceComponent: itemSelectionComponent
                                width: parent.width
                                onLoaded: {
                                    item.indexItem = index
                                    item.lengthItem = repeater.model.count
                                    item.lableText = _content
                                    item.resource = _resource
                                }
                            }
                        }
                    }
                }
                Repeater{
                    model: handleModel()
                    delegate: Item{
                        property string _key: modelData["key"]
                        property string _value: modelData["value"]
                        Layout.fillWidth: true
                        Layout.preferredHeight: itemRoadDetail.implicitHeight
                        Loader{
                            id: itemRoadDetail
                            sourceComponent: detailRoadComponent
                            Layout.fillWidth: true
                            Layout.preferredHeight: 70
                            onLoaded: {
                                item.titleItem = _key
                                item.content = _value
                            }
                        }
                    }
                }
                Item{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                }
            }
        }
    }
    ListModel{
        id: itemSelectionModel
        ListElement{
            resource: "qrc:/image/car.png"
            content: "Ô tô"
        }
        ListElement{
            resource: "qrc:/image/cycling.png"
            content: "Xe đạp"
        }
        ListElement{
            resource: "qrc:/image/walk.png"
            content: "Đi bộ"
        }
    }
    Component{
        id: itemSelectionComponent
        Item{
            id: itemSelection
            property int indexItem
            property int lengthItem
            property string resource
            property string lableText
            implicitHeight: layout.height + 5 + 2
            RowLayout{
                id: layout
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                width: implicitWidth
                height: 30
                spacing: 5
                Image{
                    id: image
                    Layout.alignment: Qt.AlignVCenter
                    Layout.preferredHeight: 30
                    Layout.preferredWidth: 30
                    source: resource
                }
                Text{
                    Layout.preferredHeight: 30
                    Layout.fillWidth: implicitWidth
                    id: text
                    wrapMode: Text.Wrap
                    text: lableText
                    font.bold: true
                    font.italic: false
                    font.pixelSize: 14
                    verticalAlignment: Text.AlignVCenter
                }
            }
            Rectangle{
                visible: indexItem === indexItemSelectionTitle
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                color: "#028AE0"
                width: layout.width
                radius: 2
                height: 2
            }
            MouseArea{
                id: side
                anchors.fill: parent
                onClicked: handleSelectionItem(indexItem)
               }
        }
    }
    function handleModel(){
        if(isValid(listParamter) || isValid(listParamter[indexItemSelectionTitle]) || isValid(listParamter[indexItemSelectionTitle]["data"]))
            return []
        return listParamter[indexItemSelectionTitle]["data"]
    }
    function isValid(object){
        if(object === null || object !== undefined)
            return false
        return true
    }
    function open(start, stop){
        indexItemSelectionTitle = 0
        repeaterRoadContent.model[0] = start
        repeaterRoadContent.model[repeaterRoadContent.model.length - 1] = stop
        item.visible = true
    }
    function close(){
        selectionItem(listParamter[indexItemSelectionTitle]["coordinate"])
        item.visible = false
    }
    function handleSelectionItem(index){
        indexItemSelectionTitle = indexItemSelectionTitle !== index ? index : indexItemSelectionTitle
    }
    Component{
        id: addressComponent
        Item{
            implicitHeight: 35
            implicitWidth: address.width
            Text{
                id: address
                text: modelData
                font.pixelSize: 14
            }
        }
    }
    ListModel{
        id: roadDetailModel
    }
    Component{
        id: detailRoadComponent
        Item{
            property string titleItem
            property string content
            implicitHeight: layout.height
            ColumnLayout{
                id: layout
                height: 50
                spacing: 5
                Rectangle{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Rectangle{
                        id: icon
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        width: 15
                        height: 15
                        color: "red"
                        rotation: 90
                        transformOrigin: Item.Center
                    }
                    Text{
                        anchors.leftMargin: 10
                        anchors.left: icon.right
                        anchors.verticalCenter: parent.verticalCenter
                        text: titleItem
                        wrapMode: Text.Wrap
                        font.pixelSize: 16
                    }
                }
                Rectangle{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Text{
                        anchors.leftMargin: 25
                        anchors.left: parent.left
                        anchors.verticalCenter: parent.verticalCenter
                        text: content
                        wrapMode: Text.Wrap
                        font.pixelSize: 14
                    }
                }
            }
        }
    }
}
