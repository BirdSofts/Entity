// *******************************************************************************************
/// <summary>
///
/// </summary>
/// <created>ʆϒʅ,12.10.2019</created>
/// <changed>ʆϒʅ,24.10.2019</changed>
// *******************************************************************************************

import QtQuick 2.13
import QtGraphicalEffects 1.0


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
      if (type === 1)
        return "red"
      else if (type === 2)
        return "white"
      else if (type === 3)
        return "brown"
      else if (type === 4)
        return "black"
      else if (type === 5)
        return "green"
      else if (type === 6)
        return "purple"
      else if (type === 7)
        return "blue"
      else if (type === 8)
        return "yellow"
    }

    // collision animations (animations on fragments shadow and scale)
    layer.enabled: true
    layer.effect: DropShadow {
      id: collision
      verticalOffset: 0
      color: "darkorange"
      samples: 0
      spread: 0.7
      PropertyAnimation on samples {
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
  }

  // Todo: persuasive ones
}
