// *******************************************************************************************
/// <summary>
///
/// </summary>
/// <created>ʆϒʅ,20.10.2019</created>
/// <changed>ʆϒʅ,22.10.2019</changed>
// *******************************************************************************************

import QtQuick 2.13
import QtGraphicalEffects 1.0


Rectangle {
  anchors.fill: parent
  color: Qt.rgba (0.0, 0.0, 0.0, 0.2)
  radius: 10
  antialiasing: true
  layer.enabled: parent.hovered
  layer.effect: DropShadow {
    verticalOffset: 1
    color: "#330066ff"
    samples: 5
    spread: 0.9
    antialiasing: true
  }
}
