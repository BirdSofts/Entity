// *******************************************************************************************
/// <summary>
///
/// </summary>
/// <created>ʆϒʅ,05.10.2019</created>
/// <changed>ʆϒʅ,20.10.2019</changed>
// *******************************************************************************************

import QtQuick 2.13
import QtQuick.Controls 2.5
//import QtQuick.Layouts 1.3


// page base container
Item {
  id: pageStart
  width: configs.getWidth()
  height: configs.getHeight()
  anchors.margins: 5
  ThemeItem {}

  property int fontSize: 0

  Button {
    id: gameStarter
    text: qsTr("Start")
    anchors.verticalCenterOffset: -30
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter
    font.family: configs.getFontName()
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
    anchors.verticalCenterOffset: 30
    anchors.horizontalCenter: parent.horizontalCenter
    anchors.verticalCenter: parent.verticalCenter
    font.family: configs.getFontName()
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


}
