 import QtQuick
import QtQuick.Controls

Item {
    property var object_map: ({})
    property int index_current: 0
    property var componentList
    property int height_size
    property int width_size
    property bool save: true
    StackView{
        id: stackview
        width: width_size
        height: height_size
        Component.onCompleted: stackview.initialItem = handleItemChanged(0)
    }
    function handleItemChanged(index) {
        var newItem;
        if(object_map[index] === null || object_map[index] === undefined){
            newItem = componentList[index].createObject(stackview);
        } else
            newItem = object_map[index]

        if (newItem){
            if(save === true)
                object_map[index_current] = stackview.currentItem
            index_current = index
            stackview.clear(StackView.Immediate);
            stackview.push(newItem);
        }
    }
}
