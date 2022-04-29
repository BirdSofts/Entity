// *******************************************************************************************
/// <summary>
///
/// </summary>
/// <created>ʆϒʅ,03.10.2019</created>
/// <changed>ʆϒʅ,29.04.2022</changed>
// *******************************************************************************************

import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
//import QtGraphicalEffects 1.15
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

  // game play properties
  property int start: 1 // new game welcome text controller
  property bool quitter: false // to break the game play procedure correctly

  // sentences' controller properties
  property int current: sentencesFieldOne.current
  property int count: sentencesFieldOne.count


  Item {
    id: draggableArea
    objectName: "draggableArea"
    width: parent.width
    height: parent.height - 100


    // introduction Text (Entity word containing a twin of animations)
    Label {
      id: gameTitle
      text: qsTr("Entity")
      color: "dodgerblue"
      y: parent.y + 10
      anchors.horizontalCenter: parent.horizontalCenter
      font.pointSize: 12
      font.bold: true

      // game title pair animations
      PropertyAnimation on font.letterSpacing {
        id: gameTitleExpandAnimation
        from: 0
        to: 8
        duration: 1000
        onFinished: gameTitleShrinkAnimation.start()
      }
      PropertyAnimation on font.letterSpacing {
        id: gameTitleShrinkAnimation
        from: 8
        to: 0
        duration: 1000
        onFinished: gameTitleExpandAnimation.start()
      }
    }


    // game's start procedure (countdown timer + trigger of new game's timer)
    Label {
      id: welcomeText
      objectName: "welcomeText"
      text: "Welcome to the world of entity! :|"
      color: "red"
      y: parent.y + 80
      anchors.horizontalCenter: parent.horizontalCenter
      font.pointSize: 12
      font.bold: true
      scale: 1
      visible: true

      // start text animation
      PropertyAnimation on scale {
        id: welcomeTextAnimation
        from: 1
        to: 3
        duration: 300
        running: false
        loops: 1
      }

      // start text timer functionality
      Timer {
        id: welcomeTextTimer
        objectName: "welcomeTextTimer"
        interval: 500
        running: false
        repeat: true
        onTriggered: welcomeText.welcoming()
      }
      function welcoming()
      {
        if (start <= 4)
        {
          if (start === 1)
          {
            welcomeText.text = "3"
            start++
          } else
            if (start === 2)
            {
              welcomeText.text = "2"
              start++
            } else
              if (start === 3)
              {
                welcomeText.text = "1"
                start++
              } else
              {
                welcomeText.text = "Survive!"
                start++
              }
          welcomeTextAnimation.start()
        } else
        {

          start = 1
          welcomeTextTimer.stop()
          welcomeText.visible = false
          welcomeText.scale = 1
          welcomeText.text = "Welcome to the world of entity! :|"

//          LogicJs.initializeGame("Welcomed")
          logic.initializeGame("Welcomed")

        }
      }
    }


    // game's timers (game's logic)
    Timer {
      id: newGameTimer
      objectName: "newGameTimer"
      interval: 3000
      running: false
      repeat: true
      onTriggered: {
        if(!tickTimer.running && current === count && !quitter)
        {
//          LogicJs.newGame()
          logic.newGame()
          tickTimer.start()

          taleArea.height = 70
          gameExitButton.visible = false
          sentencesFieldOne.proceed = false
          sentencesFieldOne.feed = [""]
          sentencesFieldOne.loop = true
          sentencesFieldOne.proceed = true
        }
      }
    }
    Timer {
      id: tickTimer
      objectName: "tickTimer"
      interval: 1
      running: false
      repeat: true
//      onTriggered: LogicJs.tick()
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

      // drag functionality provider
      MouseArea {
        id: smilyDragArea
        anchors.fill: parent
        drag.target: parent
        drag.smoothed: false
        drag.minimumX: draggableArea.x
        drag.minimumY: draggableArea.y
        drag.maximumX: draggableArea.width - 100
        drag.maximumY: draggableArea.height - 140
        //        onDoubleClicked: logic.initializeGame("NotInitialized") // for debug purposes
//        onPressed: LogicJs.initializeGame("NotInitialized")
        onPressed: logic.initializeGame("NotInitialized")
        onReleased: {
          if(!logic.isGaming())
            quitter = true
//          LogicJs.initializeGame("Quitted")
          logic.initializeGame("Quitted")
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

      // smily scale animation
      Behavior on scale {  NumberAnimation {
          duration: 500
          running: false
        }
      }
    }
  }


  // tale area (narrator space)
  Rectangle {
    id: taleArea
    objectName: "taleArea"
    width: parent.width
    height: 100
    color: "#00000000"
    antialiasing: true
    opacity: 1
    anchors.bottom: parent.bottom
    anchors.bottomMargin: 40
    border.color: "yellow"
    border.width: 1

    // tale area layout container
    GridLayout {
      id: taleAreaGrid
      anchors.horizontalCenter: parent.horizontalAlignment
      width: parent.width
      height: parent.height
      rows: 2
      columns: 1
      columnSpacing: 0
      rowSpacing: 0


      RockAndRoll {
        id: sentencesFieldOne
        objectName: "sentencesFieldOne"
        feed: ["This one build itself on its own! :)"]
        Layout.row: 0
        scaleEnabled: true
        proceed: true
        loop: true
        Timer {
          id: sentencesFieldOneTimer
          objectName: "sentencesFieldOneTimer"
          interval: 4000
          running: true
          repeat: true
          onTriggered: {
            sentencesFieldOne.proceed = false
            sentencesFieldOne.feed = [tale.getNextIdleSentence()]
            sentencesFieldOne.proceed = true
          }
        }
      }
      RockAndRoll {
        id: sentencesFieldTwo
        objectName: "sentencesFieldTwo"
        feed: [""]
        Layout.row: 1
        scaleEnabled: true
        proceed: false
        loop: false
      }


      // exit button
      Button {
        id: gameExitButton
        objectName: "gameExitButton"
        Layout.row: 2
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


  // copyright statement
  Label {
    id: copyright
    background: ThemeItem { opacity: 0.0 }
    text: qsTr("©: ʆϒʅ")
    font.pointSize: 13
    font.family: fontName
    padding: 5
    anchors.bottom: parent.bottom
    anchors.right: parent.right
  }
}
