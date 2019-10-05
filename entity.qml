﻿// *******************************************************************************************
/// <summary>
/// 
/// </summary>
/// <created>ʆϒʅ,03.10.2019</created>
/// <changed>ʆϒʅ,06.10.2019</changed>
// *******************************************************************************************


import QtQuick 2.13
//import QtQuick.Window 2.13 // QML window component
import QtQuick.Controls 2.13
import "qml"

// QML window component
//Window {
//visible: true
//title: qsTr("Hello World")

Item {
  id: view
  width: configs.getWidth()
  height: configs.getHeight()
  anchors.margins: 5

  x: -(width - width) // -width for settings page
  y: -(height - height) // -height for game page

  property bool gameStarted: false
  property bool settingsShow: false

  Column {
    x: -(width - width)
    y: -(height - height)

    Row {
      //      visible: false // first aproach (without slide ability)
      First {}
    }
    Row {
      //      visible: false
      Game {}
    }
  }

  Column {
    x: width
    y: -(height - height)
    Row {
      //      visible: false
      Configs {}
    }
  }


  states: [
    State {
      name: "gaming"
      when: gameStarted === true && settingsShow === false
      PropertyChanges {
        target: view
        y: -height
      }
    },
    State {
      name: "gamingExit"
      when: gameStarted === false && settingsShow === false
      PropertyChanges {
        target: view
        y: -(height - height)
      }
    },
    State {
      name: "configuring"
      when: gameStarted === false && settingsShow === true
      PropertyChanges {
        target: view
        x: -width
      }
    },
    State {
      name: "configuringExit"
      when: gameStarted === false && settingsShow === false
      PropertyChanges {
        target: view
        x: -(width - width)
      }
    }
  ]

  transitions: Transition {
    NumberAnimation {
      properties: "x,y"
      duration: 2000
      easing.type: Easing.bezierCurve
    }
  }

  //    SwipeView {
  //      id: view
  //      currentIndex: 0
  //      anchors.fill: parent

  //      // pages to be loaded
  //      Loader { source: "qml/Game.qml" }
  //      Loader { source: "qml/Configs.qml" }

  //    }

  // swip view need: a good practice, which gives the user some clues about where was what. :)
  //    PageIndicator {
  //      id: indicator
  //      count: view.count
  //      currentIndex: view.currentIndex
  //      anchors.bottom: view.bottom
  //      anchors.horizontalCenter: parent.horizontalCenter
  //    }
}