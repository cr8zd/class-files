/*Jennifer Frase CS-290 Automobile assignment*/
function Automobile( year, make, model, type ){
    this.year = year; //integer (ex. 2001, 1995)
    this.make = make; //string (ex. Honda, Ford)
    this.model = model; //string (ex. Accord, Focus)
    this.type = type; //string (ex. Pickup, SUV)
}

var automobiles = [ 
    new Automobile(1995, "Honda", "Accord", "Sedan"),
    new Automobile(1990, "Ford", "F-150", "Pickup"),
    new Automobile(2000, "GMC", "Tahoe", "SUV"),
    new Automobile(2010, "Toyota", "Tacoma", "Pickup"),
    new Automobile(2005, "Lotus", "Elise", "Roadster"),
    new Automobile(2008, "Subaru", "Outback", "Wagon")
    ];

/*This function sorts arrays using an arbitrary comparator. You pass it a comparator and an array of objects appropriate for that comparator and it will return a new array which is sorted with the largest object in index 0 and the smallest in the last index*/
function sortArr( comparator, array ){
    var newArr = array.slice();
	for(var i = 1; i < newArr.length; i++){
        var j = i;
        while(j > 0 && comparator(newArr[j], newArr[j - 1])){
            var temp = newArr[j - 1];
            newArr[j - 1] = newArr[j];
            newArr[j] = temp;
            j--;
        }
    }
    return newArr;
}

/*A comparator takes two arguments and uses some algorithm to compare them. If the first argument is larger or greater than the 2nd it returns true, otherwise it returns false. Here is an example that works on integers*/
function exComparator( int1, int2){
    if (int1 > int2){
        return true;
    } else {
        return false;
    }
}

/*For all comparators if cars are 'tied' according to the comparison rules then the order of those 'tied' cars is not specified and either can come first*/

/*This compares two automobiles based on their year. Newer cars are "greater" than older cars.*/
function yearComparator( auto1, auto2){
    if (auto1.year > auto2.year){
        return true;
    } else {
        return false;
    }
}

/*This compares two automobiles based on their make. It should be case insensitive and makes which are alphabetically earlier in the alphabet are "greater" than ones that come later.*/
function makeComparator( auto1, auto2){
    var make1 = auto1.make.toLowerCase();
    var make2 = auto2.make.toLowerCase();
    for(i = 0; i < make1.length; i++){
        if (make1[i] < make2[i]){
        	return true; /*a character in auto1 comes before the character with the same index in auto2, with all preceeding charaters = */
    	} else if (make1[i] > make2[i]){
        	return false; /*a character in auto2 comes before the character with the same index in auto1, with all preceeding charaters = */
    	}
        if(i == make2.length - 1) /*auto2.length <= auto1.length, with all the same characters ex. if auto1 = HONDAI and auto2 = HONDA, it will return false; makes sure that the for loop doesn't try to access a nonexistent index in auto2.make since the for loop only knows the length of auto1.make */
     		return false;
    }
    return true; //auto2.length > auto1.length, with all the same characters ex. if auto1 = HONDA and auto2 = HONDAI, it will return true 
}

/*This compares two automobiles based on their type. The ordering from "greatest" to "least" is as follows: roadster, pickup, suv, wagon, (types not otherwise listed). It should be case insensitive. If two cars are of equal type then the newest one by model year should be considered "greater".*/
function typeComparator( auto1, auto2){
    var type1 = auto1.type.toLowerCase();
    var type2 = auto2.type.toLowerCase();
    if (type1 != type2){ //check that they are not the same type, so that each inner if only has to check one or the other auto at a time
        //check if either the first or second has the highest ranked type
    	if( type1 == "roadster")
            return true;
        else if (type2 == "roadster")
            return false;
        //since neither are a roadster, check if either is 2nd ranked type
        else if (type1 == "pickup")
            return true;
        else if (type2 == "pickup")
            return false;
        //since neither are the first two highest ranked types, check if one is the 3rd
        else if (type1 == "suv")
            return true;
        else if (type2 == "suv")
            return false;
        //since neither are the first 3 highest ranked types, check if one is the 4th
        else if (type1 == "wagon")
            return true;
        else if (type2 == "wagon")
            return false;
    }
    //the autos have the same type rank, so compare their years
    return yearComparator(auto1, auto2);
}

/*Accepts a boolean arguments; if it is false then it prints the car's year, make, and model; if it is true then the car's type is added to the end printed line from false*/
Automobile.prototype.logMe = function(showType){
    if(showType == true)
        console.log(this.year + " " + this.make + " " + this.model + " " + this.type);
    else if (showType == false)
        console.log(this.year + " " + this.make + " " + this.model + " ");
}


/*OUTPUT*/

console.log("*****");
console.log("The cars sorted by year are:");
var copyArr = sortArr(yearComparator, automobiles);
for(var i = 0; i < copyArr.length; i++){
    var autoPrint = copyArr[i];
    autoPrint.logMe(false);
}

console.log("");
console.log("The cars sorted by make are:");
copyArr = sortArr(makeComparator, automobiles);
for(i = 0; i < copyArr.length; i++){
    autoPrint = copyArr[i];
    autoPrint.logMe(false);
}

console.log("");
console.log("The cars sorted by type are:");
copyArr = sortArr(typeComparator, automobiles);
for(i = 0; i < copyArr.length; i++){
    autoPrint = copyArr[i];
    autoPrint.logMe(true);
}
console.log("*****");
