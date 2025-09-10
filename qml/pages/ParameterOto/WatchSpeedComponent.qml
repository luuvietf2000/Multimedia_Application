import QtQuick

Item {
    property real needleAngle: 0
    onNeedleAngleChanged: speedometerCanvas.requestPaint()
    Canvas {
        id: speedometerCanvas
        anchors.fill: parent

        onPaint: {
            var ctx = getContext("2d")
            ctx.reset()
            ctx.clearRect(0, 0, width, height)

            var cx = width / 2
            var cy = height * 0.95
            var radius = width / 2 > height ? height : width / 2
            radius *= 0.9
            ctx.beginPath()
            ctx.arc(cx, cy, radius, Math.PI, 0, false)
            ctx.strokeStyle = "#444"
            ctx.lineWidth = 5
            ctx.lineCap = "round"
            ctx.stroke()
            var majorOffset = radius * 0.05

            var majorAngles = [-90, -72, -54, -36, -18, 0, 18, 36, 54, 72, 90]
            majorAngles.forEach(function(a, i){
                ctx.save()
                ctx.translate(cx, cy)
                ctx.rotate(a * Math.PI / 180)
                ctx.fillStyle = "white"
                ctx.fillRect(-radius*0.015, -radius + majorOffset, radius*0.03, radius*0.15)
                ctx.restore()

                var angle = a * Math.PI / 180
                var textRadius = radius - majorOffset - radius*0.25
                var x = cx + textRadius * Math.sin(angle)
                var y = cy - textRadius * Math.cos(angle)

                ctx.save()
                ctx.fillStyle = "white"
                ctx.font = radius*0.08 + "px Arial"
                ctx.textAlign = "center"
                ctx.textBaseline = "middle"
                ctx.fillText(i*20, x, y)
                ctx.restore()
            })

            var minorAngles = [-81, -63, -45, -27, -9, 9, 27, 45, 63, 81]
            minorAngles.forEach(function(a){
                ctx.save()
                ctx.translate(cx, cy)
                ctx.rotate(a * Math.PI / 180)
                ctx.fillStyle = "#90C577"
                ctx.fillRect(-radius*0.0075, -radius + majorOffset, radius*0.015, radius*0.075)
                ctx.restore()
            })

            ctx.save()
            ctx.translate(cx, cy)
            ctx.rotate(needleAngle * Math.PI / 180)
            ctx.beginPath()
            ctx.moveTo(-radius * 0.85, 0)
            ctx.lineTo(0, -radius*0.05)
            ctx.lineTo(0, radius*0.05)
            ctx.closePath()
            ctx.fillStyle = "red"
            ctx.fill()

            ctx.beginPath()
            ctx.arc(0, 0, radius*0.06, 0, 2 * Math.PI)
            ctx.fillStyle = "white"
            ctx.fill()
            ctx.restore()

            ctx.save()
            ctx.translate(cx, cy)
            ctx.beginPath()
            ctx.arc(0, 0, radius*0.03, 0, 2 * Math.PI)
            ctx.fillStyle = "#444"
            ctx.fill()
            ctx.restore()

        }
    }
}
