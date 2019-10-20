// *******************************************************************************************
/// <summary>
///
/// </summary>
/// <created>ʆϒʅ,12.10.2019</created>
/// <changed>ʆϒʅ,20.10.2019</changed>
// *******************************************************************************************

import QtQuick 2.13


// a game item container
Item {
  id: item

  property int type: 1
  property string colour: "red"

  // property guide:
  // first digit: smart> 1: normal, 2: persuasive
  // second digit: x> 1: positive, 2: negative
  // third digit: y> 1: positive, 2: negative
  property int objData: 000

  Rectangle {
    id: content
    anchors.fill: parent
    //    color: parent.colour
    color: {
      if (type === 1)
        return "red"
      else if (type === 2)
        return "green"
      else if (type === 3)
        return "blue"
    }
  }

  // Todo: each fragment has its own movement animation based on its position


  // Todo: later on the smarter movement based on the player position may be added
}
