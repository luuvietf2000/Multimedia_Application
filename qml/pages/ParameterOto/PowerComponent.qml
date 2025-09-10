import QtQuick

Item {
    property int width_Content
    property int height_Content
    property int currentPower: 50
    property int maxPower: 99
    property int numbleLine: 9
    property string background_color
    width: width_Content
    height: height_Content
    onCurrentPowerChanged: watchPower.requestPaint()
    Canvas{
        id: watchPower
        anchors.fill: parent
        onPaint: {
            var ctx = getContext("2d")
            ctx.reset()
            ctx.clearRect(0, 0, width, height)

            var cx = 0
            var cy = 0
            var lineWidth = 5

            ctx.save()
            ctx.fillStyle = background_color
            ctx.fillRect(cx, cy, width, height)
            ctx.restore()

            ctx.save()
            ctx.lineWidth = lineWidth
            ctx.strokeStyle = "#444"
            ctx.strokeRect(cx, cy, width, height);
            ctx.restore()

            ctx.save()
            ctx.fillStyle = "red"
            ctx.fillRect(cx + lineWidth / 2, cy + lineWidth / 2, width - lineWidth, (height - lineWidth) / (numbleLine + 1))
            ctx.restore()

            var offsetSpace = 0
            for(var i = 1; i < numbleLine + 1; i++){
                var xLine = width - lineWidth / 2 - offsetSpace * width
                var yLine = (height - lineWidth) / (numbleLine + 1) * i + lineWidth / 2
                ctx.save()
                ctx.fillStyle = "white"
                ctx.fillRect(xLine, yLine, -width * 0.45 , lineWidth)
                ctx.restore()
            }

            var xCurrent = width * 0.8
            var yCurrent = lineWidth / 2 + currentPower / maxPower * (height - 2 * lineWidth)

            ctx.save()
            ctx.beginPath()

            ctx.moveTo(xCurrent, yCurrent + lineWidth / 2)

            ctx.lineTo(lineWidth / 2, yCurrent)

            ctx.lineTo(lineWidth / 2, yCurrent + lineWidth)

            ctx.closePath()
            ctx.fillStyle = "#90C577"
            ctx.fill()
            ctx.restore()
        }
    }

}
