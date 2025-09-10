import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtLocation
import QtPositioning
import com.resource.map
import com.resource.parameter
Item {
    id: item
    property int width_Content: 800
    property int height_Content: 600
    property int mode: 0
    property var locationStart
    property var locationStop
    property string addressStart
    property string addressStop
    width: width_Content
    height: height_Content
    Connections{
        target: ModelMap
        function onListItemMapByToBoxSearchChanged(model){
            setObjectBoxSearch(searchFrom, model)
        }
        function onListItemMapByFromBoxSearchChanged(model){
            setObjectBoxSearch(searchTo, model)
        }
        function onFinishRequestCheckLocation(address, location){
            map.changedItemLocation(address, location)
        }
        function onListParameterChanged(object){
            map.setRoadListParameter(object)
        }
    }

    Rectangle {
        anchors.centerIn: parent
        width: width_Content - 20
        height: height_Content - 20
        color: "white"
        radius: 10
        SearchMapComponent{
            id: searchFrom
            anchors.leftMargin: 20
            anchors.topMargin: 20
            maximumWidthSizeComponent: 300
            maximumHeightSizeComponent: 400
            widthTextField: 300
            heightTextField: 40
            resource: "qrc:/image/google-maps.png"
            imageSize: 20
            anchors.left: parent.left
            anchors.top: parent.top
            widthItem: 300
            heightItem: 60
            textSize: 14
            z: 1
            onRequestSearch: function(keyword){
                ModelMap.requestSearchItem(0, keyword)
            }
            onSelectionItem: function(address, location, coordinate){
                handleSelectionItem(0, address, location, coordinate)
            }
            onOutSide: (isValid) =>{
                if(isValid)
                    handleOutSide()
            }
        }
        Image{
            id: iconTo
            visible: mode === 1
            width: 30
            height: 30
            source: "qrc:/image/route.png"
            anchors.left: searchFrom.right
            anchors.top: parent.top
            anchors.topMargin: 20 + (40 - height) / 2
            anchors.leftMargin: 10
            z: 1
        }

        SearchMapComponent{
            id: searchTo
            isVisible: item.mode === 1
            anchors.leftMargin: 10
            anchors.topMargin: 20
            maximumWidthSizeComponent: 300
            maximumHeightSizeComponent: 400
            widthTextField: 300
            heightTextField: 40
            resource: "qrc:/image/google-maps.png"
            imageSize: 20
            anchors.left: iconTo.right
            anchors.top: parent.top
            widthItem: 300
            heightItem: 60
            textSize: 14
            z: 1
            onRequestSearch:function(keyword){
                ModelMap.requestSearchItem(1, keyword)
            }
            onSelectionItem: function(address, location, coordinate){
                handleSelectionItem(1, address, location, coordinate)
            }
            onOutSide: (isValid) =>{
                if(isValid)
                    handleOutSide()
            }
        }
        PositionSource{
            id: gps
            active: true
            updateInterval: 1000
            onPositionChanged: ()=>{
                map.setCurrentLocation(position)
                active = fasle
            }
            onSourceErrorChanged: ()=>{
                active = false
            }
        }
        Rectangle{
            id: zoom
            width: 90
            height: 30
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            anchors.margins: 10
            z: 1
            RowLayout{
                anchors.fill: parent
                spacing: 0
                Rectangle{
                    Layout.preferredWidth: 30
                    Layout.fillHeight: true
                    color: "#FFE0B2"
                    ButtonStyle{
                        anchors.centerIn: parent
                        color_hightlinght: "Transparent"
                        resource: "qrc:/image/minus-sign.png"
                        onButton_clicked: map.changedZoomLevel(-1)
                    }
                }
                Text{
                    Layout.preferredWidth: 30
                    Layout.fillHeight: true
                    property double value: map.getZoomLevel()
                    id: zoomValue
                    text: value + "%"
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                }
                Rectangle{
                    Layout.preferredWidth: 30
                    Layout.fillHeight: true
                    color: "#FFE0B2"
                    ButtonStyle{
                        anchors.centerIn: parent
                        color_hightlinght: "Transparent"
                        resource: "qrc:/image/plus-symbol-button.png"
                        onButton_clicked: map.changedZoomLevel(1)
                    }
                }
            }
        }
        ButtonStyle{
            z: 1
            resource: "qrc:/image/gps.png"
            anchors.right: parent.right
            anchors.bottom: buttonRoute.top
            anchors.rightMargin: 10
            width_button: 40
            height_button: 40
            width_icon: 30
            height_icon: 30
            color_default: "transparent"
            onButton_clicked: {
                if(gps.parameters.length === 0){
                    Parameter.activePopupWarning("Error", "qrc:/image/error.png", "Không tìm thấy drive Gps nào khả dụng!", "")
                } else
                    gps.active = true
            }
        }
        ButtonStyle{
            z:1
            id: buttonRoute
            anchors.right: parent.right
            anchors.bottom: zoom.top
            anchors.rightMargin: 10
            anchors.bottomMargin: 10
            width_button: 40
            height_button: 40
            width_icon: 30
            height_icon: 30
            color_hightlinght: "Transparent"
            resource: mode === 0 ? "qrc:/image/route_mode.png" : "qrc:/image/treasure-map.png"
            onButton_clicked: () =>{
                mode = mode + 1 > 1 ? 0 : mode + 1
                map.visibleRoad(mode === 1)
                if(mode === 1){
                    searchTo.setText("Tìm Kiếm Ở Đây")
                }
            }
        }
        MapItem{
            id: map
            widthSize: parent.width
            heightSize: parent.height
        }
    }
    function handleSelectionItem(itemRequest, address, location, coordinate){
        map.setObjectMap(location, coordinate)
        map.replaceLocation(itemRequest, location)
        switch(itemRequest){
            case 0:
                //setLocation(locationStart, addressStart, location, address)
                locationStart = location
                addressStart = address
                break
            case 1:
                locationStop = location
                addressStop = address
                //setLocation(locationStop, addressStop, location, address)
                break
        }
    }
    function setLocation(locationSource, addressSource, location, address){
        locationSource = location
        addressSource = address
    }
    function handleOutSide(){
        map.removeItemMapPolygon(map.objectNameMapPolygon)
        requestRoute()
    }
    function isItemValid(item){
        return item !== null && item !== undefined
    }
    function requestRoute(){
        if(isItemValid(locationStart) && isItemValid(locationStop) && item.mode === 1){
            ModelMap.requestRoutingAllTransportation(locationStart, locationStop)
            map.roadDetailOpen(addressStart, addressStop)
        }
    }
    function setObjectBoxSearch(item, model){
        item.object = model
        item.mode = 1
    }
}
