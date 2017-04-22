function deepEqual(first, second){
  if(first != second){ //if they aren't the same object check them
    if(typeof first == "object" && typeof second == "object"){ //check if both are objects
      if(first == null || second == null){ //at least one null object
        return false;
      }else{
        var count1 = 0;
        var count2 = 0;
        for(var prop1 in first){ //count the number of properties in first
          count1++;
        }
        for(var prop2 in second){ //count the number of properties in second
          count2++;
        }
        if(deepEqual(count1, count2)){ //if same number of properties check them
          for(var prop1 in first){
            var found = false;
            for(var prop2 in second){
              if(deepEqual(first[prop1], second[prop2])){ //check each property
                found = true;
              }
            }
            if(!found){
              return false;
            }
          }
        }
      }
    }else if(first != second){ //both are not object so check if they are equal
      return false;
    }
  }
  return true;
}

var obj = {here: {is: "an"}, object: 2};
console.log(deepEqual(obj, obj));
// true
console.log(deepEqual(obj, {here: 1, object: 2}));
// false
console.log(deepEqual(obj, {here: {is: "an"}, object: 2}));
// true