// *******************************************************************************************
/// <summary>
///
/// </summary>
/// <created>ʆϒʅ,03.10.2019</created>
/// <changed>ʆϒʅ,21.10.2019</changed>
// *******************************************************************************************

import QtQuick 2.13
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.6
import QtQml.Models 2.3
import QtQuick.Dialogs 1.3


// page base container
Item {
  id: pageSettings
  width: configs.getWidth()
  height: configs.getHeight()
  anchors.margins: 5
  ThemeItem {}

  property int fontSize: 0

  property string pFontName: configs.getFontName()
  property string pFilePath: configs.getFilePath()
  property string pColour: configs.getColour()

  // page's scroll view control
  ScrollView {
    id: scrollView
    anchors.fill: parent
    padding: 10

    // page's list view feed (page objects container)
    ObjectModel {
      id: items

      // setting 1: font size setting base container (pane control)
      Pane {
        anchors.horizontalCenter: parent.horizontalAlignment
        width: pageSettings.width - 20
        padding: 0
        background: ThemeItem { opacity: 0.0 }

        // layout (container of font size controls)
        RowLayout {
          anchors.fill: parent
          // font size label
          Label {
            id: fontSizeLabel
            text: qsTr("Font size: " + sliderFont.value)
            font.pixelSize: fontSize
            padding: 10
            Layout.fillWidth: true
            Layout.minimumWidth: 90
          }
          // font size slider
          Slider {
            id: sliderFont
            from: 10
            snapMode: Slider.SnapAlways
            stepSize: 1
            to: 30
            value: fontSize
            onMoved: {
              fontSizeLabel.text = qsTr("Font size: " + value)
              fontSize = value
            }
            Layout.fillWidth: true
            Layout.minimumWidth: 150
          }
        }
      }

      // setting 2: font name setting base container (layout control)
      RowLayout {
        anchors.horizontalCenter: parent.horizontalAlignment
        width: pageSettings.width - 20
        // font name button
        Button {
          id: fontType
          background: ThemeButton {}
          Layout.fillWidth: true
          text: qsTr("Font: " + configs.getFontName())
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
          onClicked: fontPopup.open()

          // font name popup (base container)
          Popup {
            id: fontPopup
            background: ThemeItem { color: "white"; opacity: 0.8 }
            width: parent.width - 60
            height: parent.height - 60
            margins: 30
            //              topPadding: 40
            bottomPadding: 40
            dim: true
            parent: Overlay.overlay
            contentItem: Text {
              color: "red"
            }

            BusyIndicator {
              id: indicator
              background: ThemeItem { opacity: 0.0 }
              anchors.right: parent.right
              anchors.rightMargin: 2
              anchors.top: parent.top
              anchors.topMargin: 2
              scale: 1
              running: false
              antialiasing: true
            }

            // font name popup list view
            ListView {
              id: fontList
              model: Qt.fontFamilies()
              y: 60
              width: parent.width
              height: parent.height
              delegate: ItemDelegate {
                text: modelData
                font.pixelSize: fontSize
                width: parent.width
                highlighted: ListView.isCurrentItem
                onClicked: {
                  fontType.text = qsTr("Font: " + modelData)
                  pFontName = modelData
                  //                  highlighted = ListView.isCurrentItem
                  //                    console.log("clicked:", modelData)
                  fontPopup.close()
                }
              }
              // popup scroll functionality
              ScrollIndicator.vertical: ScrollIndicator {}
            }
            onOpened: indicator.running = true
            onClosed: indicator.running = false

          }
        }
      }

      // setting 3: file path setting base container (layout control)
      RowLayout {
        anchors.horizontalCenter: parent.horizontalAlignment
        width: pageSettings.width - 20
        // file path button
        Button {
          id: path
          background: ThemeButton {}
          Layout.fillWidth: true
          text: qsTr("Path: " + configs.getFilePath())
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
          onClicked: pathDialog.open()

          // file path dialog (base container)
          FileDialog {
            id: pathDialog
            title: "Please choose a file"
            folder: shortcuts.desktop
            onAccepted: {
              path.text = qsTr("Path: " + pathDialog.fileUrl)
              pFilePath = pathDialog.fileUrl
              //                Qt.quit() // exit the application
            }
          }
        }
      }

      // setting 4: colour setting
      // colour label container (layout control)
      RowLayout {
        anchors.horizontalCenter: parent.horizontalAlignment
        width: pageSettings.width - 20
        // font size label
        Label {
          id: colourLable
          background: ThemeItem { opacity: 0.0 }
          text: qsTr("Current Colour: " + configs.getColour())
          font.pixelSize: fontSize
          padding: 10
          Layout.fillWidth: true
        }
      }
      // colour base container (layout control)
      RowLayout {
        anchors.horizontalCenter: parent.horizontalAlignment
        width: pageSettings.width - 20
        // colour path view base container
        Rectangle {
          id: pathBase
          ThemeItem {}
          Layout.fillWidth: true
          Layout.preferredWidth: 300
          Layout.minimumHeight: 200
          Layout.maximumHeight: 300
          Component {
            id: component
            Column {
              id: wrapper
              opacity: PathView.isCurrentItem ? 1 : 0.6
              Rectangle {
                id: colourIcon
                anchors.horizontalCenter: nameText.horizontalCenter
                width: 32
                height: 32
                color: colour
              }
              Text {
                id: nameText
                text: name
                font.pixelSize: fontSize
              }
            }
          }
          PathView {
            id: pathView
            model: ColourModel {}
            anchors.fill: parent
            delegate: component
            snapMode: PathView.SnapPosition
            // dynamic path based on the screen size
            path: Path {
              startX: pathBase.width / 2
              startY: 150
              PathQuad {
                x: 200
                y: 50
                controlX: pathBase.width + ( pathBase.width / 2)
                controlY: 50
              }
              PathQuad {
                x: pathBase.width / 2
                y: 150
                controlX: -150
                controlY: 50
              }
            }
            onCurrentIndexChanged: {
              colourLable.text = qsTr("Current Colour: " + currentItem.children[1].text)
              pColour = currentItem.children[1].text
            }
          }
        }
      }

      // setting 5:
      RowLayout {
        anchors.margins: 10
        anchors.horizontalCenter: parent.horizontalAlignment
        Label {
          background: ThemeItem { opacity: 0.0 }
          text: "Item 1"
          font.pixelSize: fontSize
        }
      }

      // setting 6:
      RowLayout {
        anchors.margins: 10
        anchors.horizontalCenter: parent.horizontalAlignment
        Label {
          background: ThemeItem { opacity: 0.0 }
          text: "Item 2"
          font.pixelSize: fontSize
        }
      }

      // Exit button:
      RowLayout {
        anchors.margins: 10
        anchors.horizontalCenter: parent.horizontalAlignment
        Button {
          id: settingsExit
          background: ThemeButton {}
          text: qsTr("Return")
          Layout.fillWidth: true
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
          onClicked: {
            settingsShow = false
            configs.set (fontSize, pFontName, pFilePath, pColour)
          }

        }
      }

    }

    // page's list view control
    ListView {
      id: view
      model: items
      width: parent.width
      height: parent.height
      anchors { fill: parent; bottomMargin: 30 }
      highlightRangeMode: ListView.StrictlyEnforceRange
      snapMode: ListView.SnapOneItem
      //        flickDeceleration: 2000
      //        cacheBuffer: 200
    }
  }
}
