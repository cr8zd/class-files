//Jennifer Frase CS290 homework DOM and Events

//Adapted from http://eloquentjavascript.net/code/#13.1
/*makes a 4x4 table with the first row being headers and the data cells having their position in the table*/
function buildTable() {
    var table = document.createElement("table");
    table.setAttribute("id", "table");
    
    //create header row
    var headRow = document.createElement("tr");
    for (var i = 1; i <= 4; i++) {
        var headCell = document.createElement("th");
        headCell.textContent = "Header " + i;
        headCell.style.border = "1px solid black";
        headRow.appendChild(headCell);
    }
    table.appendChild(headRow);
	
    //create data cells
    for (i = 1; i <= 3; i++) {
        var row = document.createElement("tr");
        for (var j = 1; j <= 4; j++) {
            var cell = document.createElement("td");
            cell.textContent = j + ", " + i;
            cell.style.border = "1px solid black"
            if (i == 1 && j == 1) {
                cell.setAttribute("id", "current");
                cell.style.border = "3px solid black";
            }
            row.appendChild(cell);
        }
        table.appendChild(row);
    }

    return table;
}

/*changes the border of the current cell to 1px and moves the current cell up, down, left, or right depending on which button was pressed, which then also bolds that cell*/
function changeBorder(button) {
    var i = 0;
    var j = 0;
    var found = false;
    
    //thin the current border and find the current cell coridinates 
    var current = document.getElementById("table").firstElementChild;
    current = current.nextElementSibling;
    while (!found && i < 3) {
        current = current.firstElementChild;
        j = 0;
        while (!found && j < 4) {
            if (current == document.getElementById("current")) {
                found = true;
            } else {
                j++
                if (j < 4) 
                    current = current.nextElementSibling;
            }
        }

        if (!found) {
            current = current.parentNode;
            current = current.nextElementSibling;
            i++;
        }
    }
    current.removeAttribute("id", "current");
    current.style.border = "1px solid black";

    //determine which coridinate needs adjusting and do so
    if (button.target.id == "up" && i > 0) {
        i--;
    } else if (button.target.id == "down" && i < 2) {
        i++;
    } else if (button.target.id == "left" && j > 0) {
        j--;
    } else if (button.target.id == "right" && j < 3) {
        j++;
    }
	
    //thicken the new current cell
    current = document.getElementById("table");
    current = current.firstElementChild;
    current = current.nextElementSibling;
    console.log("i:" + i + " j:" + j);
    for (var s = 0; s < i; s++) {
        current = current.nextElementSibling;
    }
    current = current.firstElementChild;
    for (var t = 0; t < j; t++) {
        current = current.nextElementSibling;
    }
    current.setAttribute("id", "current");
    current.style.border = "3px solid black";
}

//changes the background of a the current cell to yellow
function changetoYellow(){
    var current = document.getElementById("current");
    current.style.backgroundColor = "yellow";
}

//make table
var table = buildTable();
table.style.border = "1px solid black";


//create buttons with text and ids
var up = document.createElement("button");
up.textContent = "up";
up.setAttribute("id", "up");
var down = document.createElement("button");
down.textContent = "down";
down.setAttribute("id", "down");
var left = document.createElement("button");
left.textContent = "left";
left.setAttribute("id", "left");
var right = document.createElement("button");
right.textContent = "right";
right.setAttribute("id", "right");
var mark = document.createElement("button");
mark.textContent = "Mark Cell";
mark.setAttribute("id", "mark");

//append everything to body
document.body.appendChild(table);
document.body.appendChild(up);
document.body.appendChild(down);
document.body.appendChild(left);
document.body.appendChild(right);
document.body.appendChild(mark);

//create the event listeners
document.getElementById("down").addEventListener("click", changeBorder);
document.getElementById("up").addEventListener("click", changeBorder);
document.getElementById("right").addEventListener("click", changeBorder);
document.getElementById("left").addEventListener("click", changeBorder);
document.getElementById("mark").addEventListener("click", changetoYellow);