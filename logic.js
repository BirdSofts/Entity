
// *******************************************************************************************
/// <summary>
/// logic.js
/// Entity
/// created by Mehrdad Soleimanimajd on 12.10.2019
/// </summary>
/// <created>ʆϒʅ, 12.10.2019</created>
/// <changed>ʆϒʅ, 25.06.2023</changed>
// *******************************************************************************************
var screenWidth = configs.getWidth()
var screenHeight = configs.getHeight()
var debug = configs.setGetDebug()
var healthJS = 20
var items = new Array(20)
var component = Qt.createComponent("./qml/Fragment.qml")

// game's different states initializer
function initializeGame(response) {
    if (response === "NotInitialized") {

        if (debug) {
            sentencesFieldOne.time = 130
            sentencesFieldTwo.time = 130
        }

        quitter = false

        welcomeText.visible = true
        welcomeTextTimer.start()
        smily.scale = 0.5

        sentencesFieldOneTimer.stop()

        sentencesFieldOne.proceed = false
        sentencesFieldOne.feed = [tale.getTitle()]
        sentencesFieldOne.proceed = true
    } else if (response === "Welcomed" && !quitter) {

        gameExitButton.visible = false
        taleArea.height = 500

        sentencesFieldOne.proceed = false
        sentencesFieldOne.feed = tale.getTaleSentences()
        sentencesFieldOne.loop = false
        sentencesFieldOne.proceed = true

        newGameTimer.start()
    } else if (response === "Quitted") {

        // guide: Nerd Snow's saying: a quitter is never going to be the same size as of the past!
        if (!quitter)
            smily.scale = 1.0

        gameExitButton.visible = true

        welcomeText.visible = true

        if (tickTimer.running) {
            tickTimer.stop()
            LogicJs.endGame()
            //          logic.endGame()
        }

        taleArea.height = 100
        gameExitButton.visible = true
        sentencesFieldOne.proceed = false
        sentencesFieldOne.feed = ["This one build itself on its own! :)"]
        sentencesFieldOne.loop = true
        sentencesFieldOne.proceed = true
        sentencesFieldOneTimer.start()
    }
}

function newGame() {
    gameCanvas.health = healthJS
    for (var index = 0; index < healthJS; index++) {
        items[index] = null
        createItem(index)
    }
}

function createItem(index) {
    if (component.status === Component.Ready) {
        var dynamicObj = component.createObject(gameCanvas)
        if (dynamicObj === null) {
            console.log("error creating item")
            console.log(component.errorString())
            return false
        }
        dynamicObj.type = Math.floor(Math.random(
                                         ) * 3) + 1 // Note: for the time being

        dynamicObj.objData = (Math.floor(Math.random() * 2) + 1) * 100

        // randomized creation location (probably somehow out of blue! :))
        var temp = Math.floor(Math.random() * 200)
        if (temp <= 50) {
            dynamicObj.x = -20
            dynamicObj.y = Math.floor(Math.random() * screenHeight)
            dynamicObj.objData += 11 // Note: for the time being
        }
        if (temp > 50 && temp <= 100) {
            dynamicObj.x = Math.floor(Math.random() * screenWidth)
            dynamicObj.y = -20
            dynamicObj.objData += 11 // Note: for the time being
        }
        if (temp > 100 && temp <= 150) {
            dynamicObj.x = screenWidth + 20
            dynamicObj.y = Math.floor(Math.random() * screenHeight)
            dynamicObj.objData += 22 // Note: for the time being
        }
        if (temp > 150 && temp <= 200) {
            dynamicObj.x = Math.floor(Math.random() * screenWidth)
            dynamicObj.y = screenHeight + 20
            dynamicObj.objData += 22 // Note: for the time being
        }

        dynamicObj.width = gameCanvas.itemSize
        dynamicObj.height = gameCanvas.itemSize
        items[index] = dynamicObj
    } else {
        console.log("error loading item component")
        console.log(component.errorString())
        return false
    }
    return true
}

function conflict() {// Todo: show some action
}

function tick() {
    if (items[0]) {
        // Todo: each tick:
        // 1. updates to game's timer
        // 2. updates to game's universe based on the user input

        // Todo: randomized movement based on current entity position
        // Todo: speed based on game level

        // movement direction based on the randomized location (for the time being)
        for (var index = 0; index < healthJS; index++) {
            if (Math.floor(items[index].objData / 100) === 2) {
                if ((items[index].objData % 100) === 11) {
                    items[index].x += 5
                    items[index].y += 5
                } else {
                    items[index].x -= 5
                    items[index].y -= 5
                }
            } else {
                if ((items[index].objData % 100) === 11) {
                    items[index].x += 3
                    items[index].y += 3
                } else {
                    items[index].x -= 3
                    items[index].y -= 3
                }
            }
        }
    }
}

function endGame() {
    gameCanvas.health = 0
    for (var index = 0; index < healthJS; index++) {
        items[index].destroy()
        items[index] = null
    }
}
