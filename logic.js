// *******************************************************************************************
/// <summary>
///
/// </summary>
/// <created>ʆϒʅ,12.10.2019</created>
/// <changed>ʆϒʅ,19.10.2019</changed>
// *******************************************************************************************

var screenWidth = configs.getWidth()
var screenHeight = configs.getHeight()
var healthJS = 20;
var items = new Array(20);
var component = Qt.createComponent("./qml/Fragment.qml");


function newGame()
{
  gameCanvas.health = healthJS;
  for (var index = 0; index < healthJS; index++)
  {
    items[index] = null
    createItem(index)
  }
}


function createItem(index)
{
  if (component.status === Component.Ready)
  {
    var dynamicObj = component.createObject(gameCanvas);
    if (dynamicObj === null)
    {
      console.log("error creating item");
      console.log(component.errorString());
      return false;
    }
    dynamicObj.type = Math.floor(Math.random() * 3) + 1; // Note: for the time being

    dynamicObj.objData = (Math.floor(Math.random() * 2) + 1) * 100;

    // randomized creation location (probably somehow out of blue! :))
    var temp = Math.floor(Math.random() * 200);
    if(temp <= 50)
    {
      dynamicObj.x = -20;
      dynamicObj.y = Math.floor(Math.random() * screenHeight);
      dynamicObj.objData += 11 // Note: for the time being
    }
    if(temp > 50 && temp <= 100)
    {
      dynamicObj.x = Math.floor(Math.random() * screenWidth);
      dynamicObj.y = -20;
      dynamicObj.objData += 11 // Note: for the time being
    }
    if(temp > 100 && temp <= 150)
    {
      dynamicObj.x = screenWidth + 20;
      dynamicObj.y = Math.floor(Math.random() * screenHeight);
      dynamicObj.objData += 22 // Note: for the time being
    }
    if(temp > 150 && temp <= 200)
    {
      dynamicObj.x = Math.floor(Math.random() * screenWidth);
      dynamicObj.y = screenHeight + 20;
      dynamicObj.objData += 22 // Note: for the time being
    }

    dynamicObj.width = gameCanvas.itemSize;
    dynamicObj.height = gameCanvas.itemSize;
    items[index] = dynamicObj;
  } else
  {
    console.log("error loading item component");
    console.log(component.errorString());
    return false;
  }
  return true;
}


function conflict()
{
  // Todo: show some action
}


function tick()
{
  if (items[0])
  {
    // Todo: each tick:
    // 1. updates to game's timer
    // 2. updates to game's universe based on the user input

    // Todo: randomized movement based on current entity position
    // Todo: speed based on game level

    // movement direction based on the randomized location (for the time being)
    for (var index = 0; index < healthJS; index++)
    {
      if(Math.floor(items[index].objData / 100) === 2)
      {
        if ((items[index].objData % 100) === 11)
        {
          items[index].x += 5;
          items[index].y += 5;
        } else
        {
          items[index].x -= 5;
          items[index].y -= 5;
        }
      } else
      {
        if ((items[index].objData % 100) === 11)
        {
          items[index].x += 3;
          items[index].y += 3;
        } else
        {
          items[index].x -= 3;
          items[index].y -= 3;
        }
      }
    }
  }
}


function endGame()
{
  gameCanvas.health = 0;
  for (var index = 0; index < healthJS; index++)
  {
    items[index].destroy();
    items[index] = null;
  }
}
