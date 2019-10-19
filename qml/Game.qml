// *******************************************************************************************
/// <summary>
///
/// </summary>
/// <created>ʆϒʅ,03.10.2019</created>
/// <changed>ʆϒʅ,19.10.2019</changed>
// *******************************************************************************************

import QtQuick 2.13
//import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import "../logic.js" as LogicJs


// page base container
Item {
  id: gameCanvas
  objectName: "gameCanvas"
  width: configs.getWidth()
  height: configs.getHeight()
  anchors.margins: 5

  property int health: 0
  property int itemSize: 10

  Text {
    id: smilyText
    text: qsTr("Entity")
    color: "darkBlue"
    y: parent.y + 10
    anchors.horizontalCenter: parent.horizontalCenter
    font.pointSize: 12
    font.bold: true

    // text pair animations
    PropertyAnimation on font.letterSpacing {
      id: textExpandAnimation
      from: 0
      to: 5
      duration: 1000
      onFinished: textShrinkAnimation.start()
    }
    PropertyAnimation on font.letterSpacing {
      id: textShrinkAnimation
      from: 5
      to: 0
      duration: 1000
      onFinished: textExpandAnimation.start()
    }
  }

  // drop area at the bottom of page
  DropArea {
    width: parent.width
    height: 150
    anchors.bottom: parent.bottom

    Rectangle {
      anchors.fill: parent
      color: "gray"
      visible: parent.containsDrag
    }
  }

  // smily canvas (draw area)
  Canvas {
    id: smily
    x: parent.width / 2 - 50
    y: parent.height / 2 - 50
    width: 100
    height: 100
    Drag.active: smilyDragArea.drag.active
    scale: 1.0
    antialiasing: true

    // smily scale
    property real currentScale: 1.0

    //      property int radius: 50
    //      Component.onCompleted: radius = 20
    //      onRadiousChanged: { requestPaint() }

    // drawing properties of smily
    property color fillStyle: "#900808FF" // ARGB
    property color strokeStyle: Qt.darker(fillStyle, 0.3)

    // the actual draw process
    onPaint: {
      var context = smily.getContext("2d")
      //        context.save();
      context.clearRect(0, 0, smily.width, smily.height)

      context.lineWidth = 2
      context.fillStyle = fillStyle
      context.strokeStyle = strokeStyle

      context.beginPath()
      context.arc(50, 50, 50, -Math.PI, Math.PI * 3, true) // face

      context.moveTo(40, 40)
      context.arc(35, 40, 5, 0, Math.PI * 2, true) // left eye

      context.moveTo(70, 40)
      context.arc(65, 40, 5, 0, Math.PI * 2, true) // right eye

      // mouth
      context.moveTo(45, 70)
      context.lineTo(55, 70)

      context.closePath()
      context.fill()
      context.stroke()
      context.restore()
    }

    // game's timer
    Timer {
      interval: 1
      running: true
      repeat: true
      onTriggered: LogicJs.tick()
    }

    // draggable
    MouseArea {
      id: smilyDragArea
      anchors.fill: parent
      drag.target: parent
      onPressedChanged: smily.caller()
      onReleased: { LogicJs.endGame(); logic.endGame() }
    }

    // smily pair animations
    PropertyAnimation on scale {
      id: enterAnimation
      from: 1.0
      to: 0.5
      duration: 1000
      running: false
    }
    PropertyAnimation on scale {
      id: exitAnimation
      from: 0.5
      to: 1.0
      duration: 1000
      running: false
    }

    // caller + delay function (radius approach)
    function delay() {
      if (radius != 20) {
        var time = new Date().getTime()
        for (var i = radius; i >= 20; i -= 0.01) {
          for (var j = 0; i < 100000; i++)
            if ((new Date().getTime() - time) > 10)
              break
          radius = i
          requestPaint()
        }
      }
    }

    // animation caller function
    function caller() {
      if (currentScale === 1.0) {
        enterAnimation.start()
        currentScale = 0.5
        LogicJs.newGame()
        logic.newGame()
      } else {
        exitAnimation.start()
        currentScale = 1.0
      }
    }

    //      onXChanged: {
    //        console.log("X changed:", x)
    //      }
    //      onYChanged: {
    //        console.log("Y changed:", y)
    //      }
  }

  Button {
    id: gameExit
    //    background: Rectangle {}
    text: qsTr("Exit")
    anchors.bottom: parent.bottom
    font.pixelSize: 20
    contentItem: Text {
      // adjustments to button text
      text: parent.text
      font: parent.font
      //            opacity: enabled ? 1.0 : 0.3
      opacity: parent.opacity
      //            color: parent.down ? "#17a81a" : "#21be2b"
      horizontalAlignment: Text.AlignLeft
      verticalAlignment: Text.AlignVCenter
      elide: Text.ElideRight // omit characters from right (dynamic resizing)
    }
    padding: 10
    onClicked: gameStarted = false
  }

}
