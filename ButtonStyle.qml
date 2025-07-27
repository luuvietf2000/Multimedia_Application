import QtQuick
import QtQuick.Controls

Item {
    property int width_button: 30
    property int height_button: 30
    property int height_icon: 20
    property int width_icon: 20
    property string resource
    property string color_default: "transparent"
    property string color_hightlinght: "#e33dc0eb"
    property string back_groundEnable: "#ccc91a74"
    property bool button_state: false
    signal button_clicked()
    width: width_button
    height: height_button
    Button{
        id: button
        //width: width_button
        //height: height_button
        anchors.fill: parent
        onClicked: button_clicked()
        contentItem: Item{
            id:item
            anchors.fill: parent
            anchors.centerIn: parent
            Image {
                id: image
                width: width_icon
                height: height_icon
                source: resource
                anchors.centerIn: parent
            }
        }
        background: Rectangle{
            id: background_item
            anchors.fill: parent
            radius: button.height / 2
            color: get_color()
        }
    }
    function changedState(){
        button_state =! button_state
    }
    function get_color(){
        if(button.hovered)
            return color_hightlinght;
        else if(button_state)
            return  back_groundEnable;
        return color_default;
    }
}
