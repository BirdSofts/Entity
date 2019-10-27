// *******************************************************************************************
/// <summary>
///
/// </summary>
/// <created>ʆϒʅ,05.10.2019</created>
/// <changed>ʆϒʅ,27.10.2019</changed>
// *******************************************************************************************

import QtQuick 2.13
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5


// page base container
Item {
  id: pageStart
  width: configs.getWidth()
  height: configs.getHeight()
  anchors.margins: 5
  ThemeItem { color: colour }

  property int fontSize: 0
  property string fontName: ""
  property string colour: ""

  Button {
    id: gameStarter
    text: qsTr("Start")
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter
    anchors.verticalCenterOffset: -50
    font.family: fontName
    font.pixelSize: fontSize
    background: ThemeButton {}
    contentItem: Text { // adjustments to button text
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
    onClicked: gameStarted = true
  }

  Button {
    id: settingsShower
    background: ThemeButton {}
    text: qsTr("Settings")
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter
    anchors.verticalCenterOffset: 50
    font.family: fontName
    font.pixelSize: fontSize
    contentItem: Text { // adjustments to button text
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
    onClicked: settingsShow = true
  }

  // tale area (narrator space)
  Rectangle {
    id: rectangle
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
      anchors.horizontalCenter: parent.horizontalAlignment
      width: parent.width
      height: parent.height
      rows: 2
      columns: 1

      RockAndRoll {
        feed: ["All characters and events of the following game are pure inventions.", ""]
        Layout.row: 0
        scaleEnabled: false
        proceed: true
        loop: true
      }
      RockAndRoll {
        feed: [""]
        Layout.row: 1
        scaleEnabled: false
        proceed: false
        loop: false
      }

      Button {
        id: gameExit
        Layout.row: 2
        background: ThemeButton {}
        text: qsTr("Exit")
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
        onClicked: Qt.quit()
      }
    }
  }

}
