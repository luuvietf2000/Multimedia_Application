import QtQuick
import QtLocation
import QtPositioning
import QtQuick.Layouts
import com.resource.map
Item {
    property int widthSize
    property int heightSize
    readonly property string objectNameMapPolygon: "polygon"
    readonly property var resourceImageLocation: ["qrc:/image/placeholderLocation.png", "qrc:/image/placeholderStop.png", "qrc:/image/adress.png"]
    readonly property var objectNameItemRequest: ["locationStart", "locationStop", "locationCurernt"]
    property var hashMap: {[]}
    width: widthSize
    height: heightSize
    Plugin {
        id: mapPlugin
        name: "osm"
        PluginParameter {
            name: "osm.mapping.host"
            value: "https://tile.openstreetmap.org"
        }
    }
    RoadDetail{
        z: 1
        id: roadDetail
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 15
        onSelectionItem: (coordinate) =>{
            road.path = coordinate
            map.center = coordinate[0]
        }
    }
    Map {
        property geoCoordinate startCentroid
        anchors.centerIn: parent
        id: map
        width: parent.width - 15
        height: parent.height - 15
        plugin: mapPlugin
        center: QtPositioning.coordinate(59.91, 10.75)
        zoomLevel: 14

        PinchHandler {
            id: pinch
            target: null
            onActiveChanged: if (active) {
                map.startCentroid = map.toCoordinate(pinch.centroid.position, false)
            }
            onScaleChanged: (delta) => {
                map.zoomLevel += Math.log2(delta)
                map.alignCoordinateToPoint(map.startCentroid, pinch.centroid.position)
            }
            onRotationChanged: (delta) => {
                map.bearing -= delta
                map.alignCoordinateToPoint(map.startCentroid, pinch.centroid.position)
            }
            grabPermissions: PointerHandler.TakeOverForbidden
        }
        MapPolyline{
            id: road
            line.color: "blue"
            line.width: 2
        }
        MapQuickItem{
            id: currentLocation
            anchorPoint.x: sourceItem.width / 2
            anchorPoint.y: sourceItem.height
            zoomLevel: map.zoomLevel
            sourceItem: Item{
                width: 50
                height: 50
                Text{
                    width: 18
                    height: 18
                    text: "Current"
                    font.pixelSize: 12
                    anchors.top: parent.top
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                Image{
                    width: 32
                    height: 32
                    anchors.bottom: parent.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    source: "qrc:/image/map-pin.png"
                }
            }
        }
        WheelHandler {
            acceptedDevices: Qt.platform.pluginName === "cocoa" || Qt.platform.pluginName === "wayland"
                             ? PointerDevice.Mouse | PointerDevice.TouchPad
                             : PointerDevice.Mouse
            rotationScale: 1/120
            property: "zoomLevel"
        }

        TapHandler{
            acceptedButtons: Qt.RightButton
            onTapped: (eventPoint) =>{
                const coordinate = map.toCoordinate(eventPoint.position)
                ModelMap.requestCheckLocation(coordinate)
                addLocation(2, coordinate)
            }
        }
        DragHandler {
            target: null
            onTranslationChanged: (delta) => map.pan(-delta.x, -delta.y)
        }

        Shortcut {
            enabled: map.zoomLevel < map.maximumZoomLevel
            sequence: StandardKey.ZoomIn
            onActivated: map.zoomLevel = Math.round(map.zoomLevel + 1)
        }

        Shortcut {
            enabled: map.zoomLevel > map.minimumZoomLevel
            sequence: StandardKey.ZoomOut
            onActivated: map.zoomLevel = Math.round(map.zoomLevel - 1)
        }
    }
    function visibleRoad(visible){
        road.visible = visible
    }
    function setCurrentLocation(coordinate){
        currentLocation.coordinate = coordinate
        setCurrentLocation(coordinate)
    }
    function setCenter(coordinate){
        map.center = coordinate
    }
    function roadDetailOpen(start, stop){
        roadDetail.open(start, stop)
    }
    function setRoadListParameter(object){
        roadDetail.listParamter = object
    }
    function roadDetailClose(){
        roadDetail.close()
    }
    function changedItemLocation(address, coordinate){
        var itemRequest = 2
        var nameObject = objectNameItemRequest[itemRequest] + coordinate.latitude + "," + coordinate.longitude
        removeItemMapPolygon(nameObject)
        var newItem = infoLocation.createObject(map, {
            "address": address,
            "location": coordinate,
            "objectName": nameObject
        })
        hashMap[nameObject] = newItem
        map.addMapItem(newItem)
    }
    function replaceLocation(itemRequest, location){
        removeLocation(itemRequest)
        addLocation(itemRequest, location)
    }
    function removeLocation(itemRequest){
        removeItemMapPolygon(objectNameItemRequest[itemRequest])
    }
    function addLocation(itemRequest, location){
        var resource = resourceImageLocation[itemRequest]
        var objectName = objectNameItemRequest[itemRequest] + (itemRequest === 2 ? location.latitude + "," + location.longitude : "")
        var newItem = locationQuickItemComponent.createObject(map)
        newItem.resource = resource
        newItem.coordinate = location
        newItem.objectName = objectName
        hashMap[objectName] = newItem
        map.addMapItem(newItem)
    }
    function getZoomLevel(){
        return Math.round(100 / (map.maximumZoomLevel - map.minimumZoomLevel) * map.zoomLevel)
    }
    function setObjectMap(location, coordinate){
        map.center = location
        replacePolygonMap(coordinate)
    }
    function changedZoomLevel(changed){
        var value = map.zoomLevel
        if(changed === 1)
            value = value + 1 > map.maximumZoomLevel ? value : value + 1
        else
            value = value - 1 < map.minimumZoomLevel ? value : value - 1
        map.zoomLevel = value
    }
    function replacePolygonMap(listCoordinate){
        removeItemMapPolygon(objectNameMapPolygon)
        addNewMapPolygon(listCoordinate)
    }
    function removeItemMapPolygon(objectNameItem){
        if(hashMap[objectNameItem] !== undefined){
            var object = hashMap[objectNameItem]
            if(Array.isArray(object))
                for(var item in object)
                    map.removeMapItem(item)

            else
                map.removeMapItem(hashMap[objectNameItem])
            delete hashMap[objectNameItem]
        }
    }
    function addNewMapPolygon(listCoordinate){
        var listNameObject = []
        for(var i = 0; i < listCoordinate.length; i++){
            var newItem = borderComponent.createObject(map)
            newItem.path = listCoordinate[i]
            newItem.objectName = objectNameMapPolygon
            map.addMapItem(newItem)
            listNameObject.push(newItem)
        }
        var objectName = objectNameMapPolygon
        hashMap[objectName] = newItem
    }
    Component{
        id: locationQuickItemComponent
        MapQuickItem{
            property string resource
            anchorPoint.x: 16
            anchorPoint.y: 32
            zoomLevel: map.zoomLevel
            sourceItem: Image{
                width: 32
                height: 32
                source: resource
            }
        }
    }
    Component{
        id: borderComponent
        MapPolygon{
            border.color: "red"
            border.width: 2
        }
    }
    Component{
        id: infoLocation
        MapQuickItem{
            property string address
            property var location
            anchorPoint.x: sourceItem.width / 2
            anchorPoint.y: sourceItem.height
            coordinate: location
            zoomLevel: map.zoomLevel
            sourceItem: Item{
                width: 200
                height: 150
                ColumnLayout{
                    spacing: 0
                    anchors.fill: parent
                    anchors.centerIn: parent
                    Rectangle{
                        Layout.fillWidth: true
                        Layout.preferredHeight: 30
                        ButtonStyle{
                            id: buttonClose
                            height_icon: 10
                            width_icon: 10
                            anchors.right: parent.right
                            anchors.verticalCenter: parent.verticalCenter
                            resource: "qrc:/image/close.png"
                            onButton_clicked: {
                                var nameObject = objectNameItemRequest[2] + coordinate.latitude + "," + coordinate.longitude
                                removeItemMapPolygon(nameObject)
                            }
                        }
                        Text{
                            anchors.centerIn: parent
                            font.pixelSize: 16
                            text: "Thông tin"
                            font.bold: true
                            font.underline: true
                        }
                    }
                    Rectangle{
                        Layout.preferredHeight: 20
                        Layout.preferredWidth: parent.width
                        Layout.alignment: Qt.AlignCenter
                        RowLayout{
                            width: parent.width - 10
                            height: parent.height
                            anchors.centerIn: parent
                            spacing: 0
                            Text{
                                Layout.fillHeight: true
                                Layout.preferredWidth: implicitWidth
                                font.pixelSize: 8
                                text: "Địa Chỉ: "
                            }
                            Text{
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                font.pixelSize: 8
                                text: address
                                color: "blue"
                                elide: Text.ElideRight
                            }
                        }
                    }
                    Rectangle{
                        Layout.preferredHeight: 20
                        Layout.preferredWidth: parent.width
                        Layout.alignment: Qt.AlignCenter
                        RowLayout{
                            width: parent.width - 10
                            height: parent.height
                            anchors.centerIn: parent
                            spacing: 0
                            Text{
                                Layout.fillHeight: true
                                Layout.preferredWidth: implicitWidth
                                font.pixelSize: 8
                                text: "Coordinate: "
                            }
                            Text{
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                font.pixelSize: 8
                                text: location.latitude + "," + location.longitude
                                color: "blue"
                                elide: Text.ElideRight
                            }
                        }
                    }
                    Item {
                        id: triangle
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                        Canvas {
                            anchors.fill: parent
                            onPaint: {
                                var ctx = getContext("2d")
                                ctx.clearRect(0, 0, width, height)
                                ctx.moveTo(0, 0)
                                ctx.lineTo(width, 0)
                                ctx.lineTo(width / 2, height)
                                ctx.closePath()
                                ctx.fillStyle = "white"
                                ctx.fill()
                            }
                        }
                    }
                }
            }
        }
    }
}
