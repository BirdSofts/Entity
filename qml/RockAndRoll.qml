
// *******************************************************************************************
/// <summary>
/// RockAndRoll.qml
/// Entity
/// created by Mehrdad Solimanimajd on 26.10.2019
/// </summary>
/// <created>ʆϒʅ, 26.10.2019</created>
/// <changed>ʆϒʅ, 27.02.2023</changed>
// *******************************************************************************************

import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15


// RockAndRoll container
Item {
  id: rockAndRoll
  width: parent.width
  Layout.minimumHeight: 26
  Layout.alignment: Qt.AlignTop
  antialiasing: true
  opacity: 1

  // modifiable
  property var feed: ["", ""]
  property int time: 1300
  property bool scaleEnabled: false
  property bool proceed: false
  property bool loop: false

  onProceedChanged: current = 0

  property int count: rockAndRollRepeater.count
  property int current: 0

  GridLayout {
    id: rockAndRollGrid
    anchors.horizontalCenter: parent.horizontalAlignment
    width: parent.width
    //    height: parent.height
    columns: 1
    rows: 3

    Repeater {
      id: rockAndRollRepeater
      //      model: 5
      //      model: [ "AAA", "BBB", "CCC", "DDD", "EEE" ]
      model: feed
      Label {
        visible: true
        Layout.row: parseInt(index, 10)
        //        text: "" + Layout.row
        //        text: "" + index
        text: "" + modelData
        font.family: fontName
        font.pixelSize: fontSize
        color: "black"
        Layout.fillWidth: true
        Layout.maximumHeight: 26
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        wrapMode: Text.WordWrap
        padding: 3
        opacity: 0.5
        scale: 1
        Behavior on opacity {  NumberAnimation {
            duration: 300
            running: false
          }
        }
        Behavior on scale {  NumberAnimation {
            duration: 300
            running: false
          }
        }
      }
    }

    Timer {
      id: rockAndRollTimer
      interval: time
      running: proceed
      repeat: true
      onTriggered: {
        for(var i = 0; i < rockAndRollRepeater.count; i++)
        {
          if(i===current)
          {
            rockAndRollRepeater.itemAt(current).opacity = 1
            if (scaleEnabled)
              rockAndRollRepeater.itemAt(current).scale = 1.1
          } else
          {
            rockAndRollRepeater.itemAt(i).opacity = 0.5
            if (scaleEnabled)
              rockAndRollRepeater.itemAt(i).scale = 1
          }
        }
        current++
        if (current === rockAndRollRepeater.count && loop)
          current = 0
        if (current === rockAndRollRepeater.count && !loop)
        {
          proceed = false
          current = rockAndRollRepeater.count
        }
      }

      //      onTriggered: {
      //        switch(current)
      //        {
      //        case 0:
      //          rockAndRollRepeater.itemAt(0).Layout.row += rockAndRollRepeater.count
      //          rockAndRollRepeater.itemAt(1).Layout.row -- // 1 to 0
      //          rockAndRollRepeater.itemAt(2).Layout.row -- // 2 to 1
      //          rockAndRollRepeater.itemAt(0).Layout.row -- // 3 to 2

      //          //                rockAndRollRepeater.itemAt(0).visible = false
      //          //                rockAndRollRepeater.itemAt(1).visible = true
      //          current++
      //          break;
      //        case 1:
      //          rockAndRollRepeater.itemAt(1).Layout.row += rockAndRollRepeater.count
      //          rockAndRollRepeater.itemAt(2).Layout.row -- // 1 to 0
      //          rockAndRollRepeater.itemAt(0).Layout.row -- // 2 to 1
      //          rockAndRollRepeater.itemAt(1).Layout.row -- // 3 to 2

      //          //                rockAndRollRepeater.itemAt(1).visible = false
      //          //                rockAndRollRepeater.itemAt(2).visible = true
      //          current++
      //          break;
      //        case 2:
      //          rockAndRollRepeater.itemAt(2).Layout.row += rockAndRollRepeater.count
      //          rockAndRollRepeater.itemAt(0).Layout.row -- // 1 to 0
      //          rockAndRollRepeater.itemAt(1).Layout.row -- // 2 to 1
      //          rockAndRollRepeater.itemAt(2).Layout.row -- // 3 to 2

      //          //                rockAndRollRepeater.itemAt(2).visible = false
      //          //                rockAndRollRepeater.itemAt(0).visible = true
      //          current = 0
      //          break;
      //        }
      //      }

      //      onTriggered: {
      //        switch(current)
      //        {
      //        case 0:
      //          rockAndRollRepeater.itemAt(2).Layout.row ++ // 2 to 3
      //          rockAndRollRepeater.itemAt(1).Layout.row ++ // 1 to 2
      //          rockAndRollRepeater.itemAt(0).Layout.row ++ // 0 to 1
      //          rockAndRollRepeater.itemAt(2).Layout.row -= rockAndRollRepeater.count

      //          //          rockAndRollRepeater.itemAt(2).visible = false
      //          //          rockAndRollRepeater.itemAt(1).visible = true
      //          current++
      //          break;
      //        case 1:
      //          rockAndRollRepeater.itemAt(1).Layout.row ++ // 2 to 3
      //          rockAndRollRepeater.itemAt(0).Layout.row ++ // 1 to 2
      //          rockAndRollRepeater.itemAt(2).Layout.row ++ // 0 to 1
      //          rockAndRollRepeater.itemAt(1).Layout.row -= rockAndRollRepeater.count

      //          //          rockAndRollRepeater.itemAt(1).visible = false
      //          //          rockAndRollRepeater.itemAt(0).visible = true
      //          current++
      //          break;
      //        case 2:
      //          rockAndRollRepeater.itemAt(0).Layout.row ++ // 2 to 3
      //          rockAndRollRepeater.itemAt(2).Layout.row ++ // 1 to 2
      //          rockAndRollRepeater.itemAt(1).Layout.row ++ // 0 to 1
      //          rockAndRollRepeater.itemAt(0).Layout.row -= rockAndRollRepeater.count

      //          //          rockAndRollRepeater.itemAt(0).visible = false
      //          //          rockAndRollRepeater.itemAt(2).visible = true
      //          current = 0
      //          break;
      //        }
      //      }
    }

  }
}
