
// *******************************************************************************************
/// <summary>
/// Fragment.qml
/// Entity
/// created by Mehrdad Solimanimajd on 12.10.2019
/// </summary>
/// <created>ʆϒʅ, 12.10.2019</created>
/// <changed>ʆϒʅ, 27.02.2023</changed>
// *******************************************************************************************

import QtQuick 2.15
//import QtGraphicalEffects 1.15


// a game item container
Item {
  id: item

  property int type: 1

  // property guide:
  // first digit: smart> 1: normal, 2: persuasive
  // second digit: x> 1: positive, 2: negative
  // third digit: y> 1: positive, 2: negative
  property int objData: 000

  // collision property
  property bool dirty: false

  // fragment base container (fragment's body)
  Rectangle {
    id: content
    anchors.fill: parent
    radius: 3
    scale: 1
    color: {
      switch(type)
      {
      case 1:
        return "red"
      case 2:
        return "white"
      case 3:
        return "brown"
      case 4:
        return "black"
      case 5:
        return "green"
      case 6:
        return "purple"
      case 7:
        return "blue"
      case 8:
        return "yellow"
      }
    }

    // collision animations (animations on fragments shadow and scale)
    layer.enabled: true
    layer.effect: ColorAnimation {
        id: collision
        from: "white"
        to: "black"
        duration: 100
      }
    //      DropShadow {
    //        id: collision
    //        verticalOffset: 0
    //        color: "darkorange"
    //        samples: 0
    //        spread: 0.7
    //      }
      PropertyAnimation on color {
        id: collisionAnimation
        from: 0
        to: 90
        duration: 100
        running: dirty
        onStopped: scaleAnimation.start()
      }
    }
    PropertyAnimation on scale {
      id: scaleAnimation
      from: 1
      to: 0
      duration: 500
      running: false
      onStopped: { content.visible = false; content.layer.enabled = false }
    }

  // Todo: persuasive ones
}
