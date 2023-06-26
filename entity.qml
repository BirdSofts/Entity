
// *******************************************************************************************
/// <summary>
/// entity.qml
/// Entity
/// created by Mehrdad Soleimanimajd on 03.10.2019
/// </summary>
/// <created>ʆϒʅ, 03.10.2019</created>
/// <changed>ʆϒʅ, 25.06.2023</changed>
// *******************************************************************************************
import QtQuick 2.15
import QtQuick.Window 2.15
// QML window component
import QtQuick.Controls 2.15
import "./qml"

Item {
    id: view
    objectName: "view"
    width: configs.getWidth()
    height: configs.getHeight()
    anchors.margins: 5

    x: -(width - width) // -width for settings page
    y: -(height - height) // -height for game page

    property bool gameStarted: false
    property bool settingsShow: false

    property int fontSize: configs.getFontSize()
    property string fontName: configs.getFontName()
    property string colour: configs.getColour()

    Column {
        x: -(width - width)
        y: -(height - height)

        Row {
            //      visible: false // first approach (without slide ability)
            First {
                fontSize: view.fontSize
                fontName: view.fontName
                colour: view.colour
            }
        }

        Row {
            //      visible: false
            Game {
                fontSize: view.fontSize
                fontName: view.fontName
                colour: view.colour
            }
        }
    }

    Column {
        x: width
        y: -(height - height)

        Row {
            //      visible: false
            Configs {
                fontSize: view.fontSize
                fontName: view.fontName
                colour: view.colour
            }
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
            duration: 1000
            easing.type: Easing.InOutCirc
        }
    }
}
