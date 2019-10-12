// *******************************************************************************************
/// <summary>
///
/// </summary>
/// <created>ʆϒʅ,12.10.2019</created>
/// <changed>ʆϒʅ,13.10.2019</changed>
// *******************************************************************************************


import QtQuick 2.13

// a game item container
Item {
  id: item

  property int type: 0

  Rectangle {
    id: content
    anchors.fill: parent
    color: {
      if (type === 0)
        return "red"
      else if (type == 1)
        return "green"
      else
        return "blue"
    }
  }
}
