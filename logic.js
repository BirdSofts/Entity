// *******************************************************************************************
/// <summary>
///
/// </summary>
/// <created>ʆϒʅ,12.10.2019</created>
/// <changed>ʆϒʅ,13.10.2019</changed>
// *******************************************************************************************


var healthJS = 20;
var items = new Array(20);
var component = Qt.createComponent("./qml/Fragment.qml");;


function newGame() {
  gameCanvas.health = healthJS;
  for (var index = 0; index < healthJS; index++)
  {
    items[index] = null
    createItem(index)
  }
}


function createItem(index) {
  if (component.status === Component.Ready)
  {
    var dynamicObj = component.createObject(gameCanvas);
    if (dynamicObj === null)
    {
      console.log("error creating item");
      console.log(component.errorString());
      return false;
    }
    dynamicObj.type = Math.floor(Math.random() * 3); // for the time being
    dynamicObj.x = Math.floor(Math.random() * configs.getWidth());
    dynamicObj.y = Math.floor(Math.random() * configs.getHeight());
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
