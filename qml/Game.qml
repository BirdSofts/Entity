// *******************************************************************************************
/// <summary>
///
/// </summary>
/// <created>ʆϒʅ,03.10.2019</created>
/// <changed>ʆϒʅ,24.10.2019</changed>
// *******************************************************************************************

import QtQuick 2.13
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0
import "../logic.js" as LogicJs


// page base container
Item {
  id: gameCanvas
  objectName: "gameCanvas"
  width: configs.getWidth()
  height: configs.getHeight()
  anchors.margins: 5
  ThemeItem { color: colour }

  // game logic properties
  property int health: 0
  property int itemSize: 10

  // theme properties
  property int fontSize: 0
  property string fontName: ""
  property string colour: ""

  property int start: 1 // new game state controler

  property int current: 1 // current idle sentence controler

  Item {
    id: draggable
    width: parent.width
    height: parent.height - 100


    // introduction Text (Entity word containing a twin of animations)
    Label {
      id: entityText
      text: qsTr("Entity")
      color: "darkBlue"
      y: parent.y + 10
      anchors.horizontalCenter: parent.horizontalCenter
      font.pointSize: 12
      font.bold: true

      // entity text pair animations
      PropertyAnimation on font.letterSpacing {
        id: textExpandAnimation
        from: 0
        to: 8
        duration: 1000
        onFinished: textShrinkAnimation.start()
      }
      PropertyAnimation on font.letterSpacing {
        id: textShrinkAnimation
        from: 8
        to: 0
        duration: 1000
        onFinished: textExpandAnimation.start()
      }
    }


    // game's start procedure (countdown timer + trigger of new game's timer)
    Label {
      id: startText
      text: "Welcome to the world of entity! :|"
      color: "red"
      y: parent.y + 80
      anchors.horizontalCenter: parent.horizontalCenter
      font.pointSize: 12
      font.bold: true
      scale: 1

      // start text animation
      PropertyAnimation on scale {
        id: startTextAnimation
        from: 1
        to: 3
        duration: 300
        running: false
      }

      // start text timer functionality
      Timer {
        id: startTextTimer
        interval: 500
        running: false
        repeat: true
        onTriggered: startText.startGame()
      }
      function startGame()
      {
        //          startTextAnimation.stop()
        if (start <= 4)
        {
          if (start === 1)
          {
            startText.text = "3"
            start++
          } else
            if (start === 2)
            {
              startText.text = "2"
              start++
            } else
              if (start === 3)
              {
                startText.text = "1"
                start++
              } else
              {
                startText.text = "Survive!"
                start++

                newGameTimer.start()
              }
          startTextAnimation.start()
        } else
        {

          start = 1
          startText.text = ""
          startTextAnimation.stop()
          startTextTimer.stop()

          sentence.text = "\n"

        }
      }
    }


    // game's timers (game's logic)
    Timer {
      id: newGameTimer
      interval: 2000
      running: false
      repeat: false
      onTriggered: {
        //                LogicJs.newGame()
        logic.newGame()
        tickTimer.start()
        sentence.text = "\n"
      }
    }
    Timer {
      id: tickTimer
      interval: 1
      running: false
      repeat: true
      //        onTriggered: LogicJs.tick()
      onTriggered: logic.tick()
    }


    // smily canvas (represents game's main character)
    Canvas {
      id: smily
      objectName: "smily"
      x: parent.width / 2 - 50
      y: parent.height / 2 - 50
      width: 100
      height: 100
      Drag.active: smilyDragArea.drag.active
      scale: 1.0
      antialiasing: true

      // smily scale
      property real currentScale: 1.0

      // drawing properties of smily
      //    property color fillStyle: "#900808FF" // ARGB
      //    property color fillStyle: Qt.rgba(0.0, 0.4, 0.9, 0.9)
      property color fillStyle: "dodgerblue"
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

      // draggable
      MouseArea {
        id: smilyDragArea
        anchors.fill: parent
        drag.target: parent
        drag.smoothed: false
        drag.minimumX: draggable.x
        drag.minimumY: draggable.y
        drag.maximumX: draggable.width - 100
        drag.maximumY: draggable.height - 100
        onPressedChanged: smily.caller()

        onReleased: {
          if (logic.isGaming())
          {
            //          LogicJs.endGame()
            logic.endGame()
          }
        }
      }

      // smily pair animations
      PropertyAnimation on scale {
        id: enterAnimation
        from: 1.0
        to: 0.5
        duration: 500
        running: false
      }
      PropertyAnimation on scale {
        id: exitAnimation
        from: 0.5
        to: 1.0
        duration: 500
        running: false
      }

      // smily animations caller function
      function caller()
      {
        if (currentScale === 1.0)
        {

          enterAnimation.start()
          startTextTimer.start()
          currentScale = 0.3

          sentenceTimer.stop()
          sentence.text = tale.getTitle()

        } else
        {

          start = 1
          startText.text = ""
          startTextTimer.stop()
          newGameTimer.stop()
          tickTimer.stop()

          exitAnimation.start()
          currentScale = 1.0

          sentence.text = "\n"
          sentenceTimer.start()

        }
      }

      onXChanged: {
        logic.update("smily", x, y)
        //      console.log("X changed:", x)
      }
      onYChanged: {
        logic.update("smily", x, y)
        //      console.log("Y changed:", y)
      }
    }
  }


  // tale area (narrator space)
  Rectangle {
    id: taleArea
    width: parent.width
    height: 100
    color: "#00000000"
    antialiasing: true
    opacity: 1
    anchors.bottom: parent.bottom
    border.color: "yellow"
    border.width: 1

    // tale area layout container
    GridLayout {
      id: taleGrid
      anchors.horizontalCenter: parent.horizontalAlignment
      width: parent.width
      height: parent.height
      rows: 2
      columns: 1
      columnSpacing: 0
      rowSpacing: 0

      // idle sentences
      Label {
        id: sentence
        Layout.row: 0
        text: "This one build itself on its own! :)\n"
        font.family: "Candara"
        font.pixelSize: 20
        color: "black"
        Layout.fillWidth: true
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.WordWrap
        leftPadding: 5
        rightPadding: 5

        Timer {
          id: sentenceTimer
          interval: 3000
          running: true
          repeat: true
          onTriggered: sentence.text = tale.getNextIdleSentence()
        }
      }

      // exit button
      Button {
        id: gameExit
        Layout.row: 1
        background: ThemeButton {}
        text: qsTr("Return")
        font.family: "Candara"
        font.pixelSize: 20
        contentItem: Text {
          // adjustments to button text
          text: parent.text
          font: parent.font
          color: "black"
          //            opacity: enabled ? 1.0 : 0.3
          opacity: parent.opacity
          //            color: parent.down ? "#17a81a" : "#21be2b"
          horizontalAlignment: Text.AlignLeft
          verticalAlignment: Text.AlignVCenter
          elide: Text.ElideRight // omit characters from right (dynamic resizing)
        }
        Layout.fillWidth: true
        padding: 5
        onClicked: gameStarted = false
      }
    }
  }

}
