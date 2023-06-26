
// *******************************************************************************************
/// <summary>
/// First.qml
/// Entity
/// created by Mehrdad Soleimanimajd on 05.10.2019
/// </summary>
/// <created>ʆϒʅ, 05.10.2019</created>
/// <changed>ʆϒʅ, 25.06.2023</changed>
// *******************************************************************************************
import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

// page base container
Item {
    id: pageStart
    width: configs.getWidth()
    height: configs.getHeight()
    anchors.margins: 5
    ThemeItem {
        color: colour
    }

    property int fontSize: 0
    property string fontName: ""
    property string colour: ""

    Button {
        id: gameStarter
        text: qsTr("Start")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -50
        font.family: fontName
        font.pixelSize: fontSize
        //    background: Button {}
        //    contentItem: Text { // adjustments to button text
        //      text: parent.text
        //      font: parent.font
        //      //            opacity: enabled ? 1.0 : 0.3
        //      opacity: parent.opacity
        //      //            color: parent.down ? "#17a81a" : "#21be2b"
        //      horizontalAlignment: Text.AlignLeft
        //      verticalAlignment: Text.AlignVCenter
        //      elide: Text.ElideRight // omit characters from right (dynamic resizing)
        //    }
        //    implicitHeight: 80
        //    implicitWidth: 100
        padding: 10
        onClicked: gameStarted = true
    }

    Button {
        id: settingsShower
        background: ThemeButton {}
        text: qsTr("Settings")
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 50
        font.family: fontName
        font.pixelSize: fontSize
        contentItem: Label {
            // adjustments to button text
            text: parent.text
            font: parent.font
            //            opacity: enabled ? 1.0 : 0.3
            opacity: parent.opacity
            //            color: parent.down ? "#17a81a" : "#21be2b"
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            elide: Text.ElideRight // omit characters from right (dynamic resizing)
        }
        padding: 100
        onClicked: settingsShow = true
    }

    // tale area (narrator space)
    Rectangle {
        id: rectangle
        width: parent.width
        height: 100
        color: "#00000000"
        antialiasing: true
        opacity: 1
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 40
        border.color: "yellow"
        border.width: 1

        // tale area layout container
        GridLayout {
            anchors.horizontalCenter: parent.horizontalAlignment
            width: parent.width
            height: parent.height
            rows: 2
            columns: 1
            columnSpacing: 0
            rowSpacing: 0

            RockAndRoll {
                feed: ["All the characters and events of the following game", "are pure inventions."]
                Layout.row: 0
                scaleEnabled: false
                proceed: true
                loop: true
            }
            RockAndRoll {
                feed: [""]
                Layout.row: 1
                scaleEnabled: false
                proceed: false
                loop: false
            }

            Button {
                id: gameExit
                Layout.row: 2
                background: ThemeButton {}
                text: qsTr("Exit")
                font.family: fontName
                font.pixelSize: fontSize
                contentItem: Text {
                    // adjustments to button text
                    text: parent.text
                    font: parent.font
                    color: "black"
                    //            opacity: enabled ? 1.0 : 0.3
                    opacity: parent.opacity
                    //            color: parent.down ? "#17a81a" : "#21be2b"
                    horizontalAlignment: Text.AlignLeft
                    verticalAlignment: Text.AlignVCenter
                    elide: Text.ElideRight // omit characters from right (dynamic resizing)
                }
                Layout.fillWidth: true
                padding: 5
                onClicked: Qt.quit()
            }
        }
    }

    // copyright statement
    Label {
        id: copyright
        background: ThemeItem {
            opacity: 0.0
        }
        text: qsTr("©: ʆϒʅ")
        font.pointSize: 13
        font.family: fontName
        padding: 5
        anchors.bottom: parent.bottom
        anchors.right: parent.right
    }
}
