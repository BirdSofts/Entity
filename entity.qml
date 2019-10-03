// *******************************************************************************************
/// <summary>
/// 
/// </summary>
/// <created>ʆϒʅ,03.10.2019</created>
/// <changed>ʆϒʅ,04.10.2019</changed>
// *******************************************************************************************


import QtQuick 2.13
//import QtQuick.Window 2.13 // QML window component
import QtQuick.Controls 2.13

// QML window component
//Window {
//visible: true
//title: qsTr("Hello World")

Item {
  id: main
  //  width: 320
  //  height: 480
  width: 480
  height: 640

  Item {
    width: parent.width
    height: parent.height
    anchors.fill: parent
    anchors.rightMargin: 5
    anchors.bottomMargin: 5
    anchors.leftMargin: 5
    anchors.topMargin: 5

    SwipeView {
      id: view
      currentIndex: 0
      anchors.fill: parent

      // pages to be loaded
      Loader { source: "qml/start.qml" }
      Loader { source: "qml/settings.qml" }

    }

    // swip view need: a good practice, which gives the user some clues about where was what. :)
    PageIndicator {
      id: indicator
      count: view.count
      currentIndex: view.currentIndex
      anchors.bottom: view.bottom
      anchors.horizontalCenter: parent.horizontalCenter
    }
  }
}
