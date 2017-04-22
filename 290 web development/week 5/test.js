function changeColor(){
    var toUpdate = document.getElementById("changeMe");
    if(toUpdate.style.backgroundColor == "blue"){
        toUpdate.style.backgroundColor = "red";
    } else {
        toUpdate.style.backgroundColor = "blue";
    }
}

function unbindButton(){
    document.getElementById("myButton").removeEventListener("click", changeColor);
}

document.getElementById("myButton").addEventListener("click", changeColor);
document.getElementById("grimButton").addEventListener("click", unbindButton);