import QtQuick
import QtQuick.Layouts
import com.resource.caro

Item {
    id: root
    property int width_size
    property int height_size
    property string background_color: "white"
    property var boardCaro: Caro.board
    property var maxLineCaro: Caro.maxLine
    property var playerInfomation: Caro.player
    readonly property string titleTurn: "Turn: "
    signal selectionExitGame()
    property var board
    width: width_size
    height: height_size

    onBoardCaroChanged: {
        console.log(boardCaro)
        canvas.requestPaint()
    }
    FontLoader{
        id: fontGame
        source: "qrc:/font/PressStart2P-Regular.ttf"
    }
    Rectangle{
        anchors.fill: parent
        color: background_color
        RowLayout{
            anchors.fill: parent
            Rectangle{
                Layout.fillHeight: true
                Layout.fillWidth: true
                Canvas{
                    id: canvas
                    property int edge_size: (parent.width < parent.height ? parent.width : parent.height) - 10
                    width: edge_size
                    height: edge_size
                    anchors.centerIn: parent
                    renderStrategy: Canvas.Threaded
                    onPaint: {
                        var ctx = getContext("2d")
                        ctx.beginPath()
                        drawRect(ctx, edge_size)
                        for(var i = 0; i < maxLineCaro + 1; i++){
                            var xline = getCellSize(edge_size) * i
                            var yline = 0
                            drawLine(ctx, xline, yline, xline, edge_size)
                            drawLine(ctx, yline, xline, edge_size, xline)
                        }
                        drawAllCell(ctx)
                    }
                }
                MouseArea{
                    hoverEnabled: true
                    width: canvas.edge_size
                    height: canvas.edge_size
                    anchors.centerIn: parent
                    onClicked: {
                        if(mouseX % canvas.edge_size !== 0 && mouseY % canvas.edge_size){
                            var x = Math.floor(mouseX / getCellSize(canvas.edge_size))
                            var y = Math.floor(mouseY / getCellSize(canvas.edge_size))
                            Caro.setPixelBoard(x, y)
                        }
                    }
                }
            }
            Loader{
                sourceComponent: controller
            }
        }
    }
    function drawAllCell(ctx){
        for(var x = 0; x < maxLineCaro; x++)
            for(var y = 0; y < maxLineCaro; y++)
                drawCell(ctx, x, y, canvas.edge_size)
    }
    function getCellSize(edge){
        return edge / maxLineCaro
    }
    function drawLine(ctx, x1, y1, x2, y2){
        ctx.save()
        ctx.moveTo(x1, y1)
        ctx.lineTo(x2, y2)
        ctx.lineWidth = 1
        ctx.stroke()
        ctx.restore()
    }
    function drawRect(ctx, edge){
        ctx.save()
        ctx.fillStyle = "white"
        ctx.fillRect(0, 0, edge, edge)
        ctx.fill()
        ctx.restore()
    }
    function drawCell(ctx, x, y, edge){
        var range = getCellSize(edge)
        var cx = range * (x + 0.5)
        var cy = range * (y + 0.5)
        switch(boardCaro[x][y]){
            case 1: drawCellX(ctx, cx, cy, range / 2)
                break
            case 2: drawCellO(ctx, cx, cy, range / 2 * 0.7)
                break
            default:
                return
        }

    }
    function drawCellX(ctx, x, y, radius){
        var cx = x - radius / 2
        var cy = y - radius / 2
        ctx.save()
        ctx.strokeStyle = "red"
        ctx.lineWidth = 4
        ctx.beginPath()
        ctx.moveTo(cx, cy)
        ctx.lineTo(cx + radius, cy + radius)
        ctx.stroke()
        ctx.restore()

        cx = x + radius / 2
        cy = y - radius / 2
        ctx.save()
        ctx.strokeStyle = "red"
        ctx.lineWidth = 4
        ctx.beginPath()
        ctx.moveTo(cx, cy)
        ctx.lineTo(cx - radius, cy + radius)
        ctx.stroke()
        ctx.restore()
    }
    function drawCellO(ctx, x, y, radius){
        ctx.save()
        ctx.beginPath()
        ctx.strokeStyle = "blue"
        ctx.lineWidth = 3
        ctx.arc(x, y, radius,0 ,2 * Math.PI, true)
        ctx.stroke()
        ctx.restore()
    }
    Component{
        id: controller
        Rectangle{
            gradient: Gradient {
                GradientStop { position: 0.2; color: "#FF9689" }
                GradientStop { position: 0.4; color: "#FEAEA7" }
                GradientStop { position: 0.6;  color: "#FFC5C1" }
                GradientStop { position: 0.8;  color: "#FFD6BE" }
                GradientStop { position: 1.0;  color: "#FFC6A4" }
            }
            radius: 5
            border.color: "#C7F1FF"
            border.width: 2
            width: layout.width + 20
            height: layout.height + 20
            ColumnLayout{
                anchors.centerIn: parent
                id: layout
                spacing: 20
                RowLayout{
                    Text{
                        id: textTitle
                        Layout.preferredWidth: contentWidth
                        font.pixelSize: 14
                        text: titleTurn
                        font.family: fontGame.name
                    }
                    Image{
                        Layout.preferredHeight: textTitle.contentHeight
                        Layout.preferredWidth:  textTitle.contentHeight
                        fillMode: Image.PreserveAspectCrop
                        source: !Caro.turn ? "qrc:/image/back.png" : "qrc:/image/letter-o.png"
                    }
                    Text{
                        id: titlePlayer
                        text: playerInfomation[Caro.turn].name
                        font.pixelSize: 14
                        font.family: fontGame.name
                    }
                }

                RowLayout{
                    id: row
                    readonly property int pixel_size: 60
                    Item{
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                    }
                    Image{
                        Layout.preferredHeight: row.pixel_size
                        Layout.preferredWidth:  row.pixel_size
                        source: playerInfomation[0].source
                    }
                    Image{
                        Layout.preferredHeight: row.pixel_size
                        Layout.preferredWidth:  row.pixel_size
                        source: "qrc:/image/vs.png"
                    }
                    Image{
                        Layout.preferredHeight: row.pixel_size
                        Layout.preferredWidth:  row.pixel_size
                        source: playerInfomation[1].source
                    }
                    Item{
                        Layout.fillHeight: true
                        Layout.fillWidth: true
                    }
                }

                Rectangle{
                    Layout.alignment: Qt.AlignCenter
                    Layout.preferredWidth: layout.width / 2
                    Layout.preferredHeight: 40
                    color: "red"
                    radius: 20
                    gradient: Gradient {
                        orientation: Gradient.Horizontal
                        GradientStop { position: 0.33; color: "#005FA3" }
                        GradientStop { position: 0.66; color: "#028AE0" }
                        GradientStop { position: 1.0; color: "#00A5F5" }
                    }
                    Text{
                        text: "Retry"
                        anchors.centerIn: parent
                        font.family: fontGame.name
                        font.pixelSize: 14
                        color: "white"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: Caro.requestRetry()
                    }
                }

                Rectangle{
                    Layout.alignment: Qt.AlignCenter
                    Layout.preferredWidth: layout.width / 2
                    Layout.preferredHeight: 40
                    color: "red"
                    radius: 20
                    gradient: Gradient {
                        orientation: Gradient.Horizontal
                        GradientStop { position: 0.33; color: "#E24943" }
                        GradientStop { position: 0.66; color: "#E0312E" }
                        GradientStop { position: 1.0; color: "red" }
                    }
                    Text{
                        text: "Exit"
                        anchors.centerIn: parent
                        font.family: fontGame.name
                        font.pixelSize: 14
                        color: "white"
                    }
                    MouseArea{
                        anchors.fill: parent
                        onClicked: selectionExitGame()
                    }
                }

            }
        }
    }
}
