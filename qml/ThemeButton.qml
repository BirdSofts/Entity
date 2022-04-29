// *******************************************************************************************
/// <summary>
///
/// </summary>
/// <created>ʆϒʅ,20.10.2019</created>
/// <changed>ʆϒʅ,29.04.2022</changed>
// *******************************************************************************************

import QtQuick 2.15
//import QtGraphicalEffects 1.15


Rectangle {
  anchors.fill: parent
  color: Qt.rgba (0.0, 0.0, 0.0, 0.3)
  radius: 10
  antialiasing: true
  layer.enabled: parent.hovered
//  layer.effect:  {
//    verticalOffset: 1
//    color: "#330066ff"
//    samples: 5
//    spread: 0.9
//    antialiasing: true
//  }
}
