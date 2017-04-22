<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","frasej-db","z3pwe8QXqGNrAxBu","frasej-db");
if($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
?>


<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN"
"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html>
<body>
<h2><a href="home.html">HOME</a></h2>
<div>
	<h2>Modify Item</h2>
</div>
<div>
	<h3>Add/Update Item</h3>
	<form method="post" action="moditem.php"> 

		<fieldset>
			<legend>Name *required</legend>
			<input type="text" name="Name" />
		</fieldset>
		<fieldset>
			<legend>Class</legend>
			<input type="text" name="Class" /></p>
		</fieldset>
		<fieldset>
			<legend>Level</legend>
			<input type="number" name="Level" /></p>
		</fieldset>
		<fieldset>
			<legend>Job</legend>
			<select name="Job">
<?php
//Code to provide a list of jobs
if(!($stmt = $mysqli->prepare("SELECT id, title FROM job"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($id, $title)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
	echo '<option value=" '. $id . ' "> ' . $title . '</option>\n';
}
$stmt->close();
?>
			</select>
		</fieldset>
		<input type="submit" name="add" value="Add Item" />
		<input type="submit" name="update" value="Update Item" />
	</form>
</div>
<div>
	<h3>Add/Delete Item for World</h3>
	<form method="post" action="moditem.php"> 

		<fieldset>
			<legend>Item</legend>
			<select name="Item">
<?php
//Code to provide a list of items
if(!($stmt = $mysqli->prepare("SELECT id, name FROM item"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($iid, $iname)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
	echo '<option value=" '. $iid . ' "> ' . $iname . '</option>\n';
}
$stmt->close();
?>
			</select>
		</fieldset>	
		<fieldset>
			<legend>World</legend>
			<select name="World">
<?php
//Code to provide a list of worlds
if(!($stmt = $mysqli->prepare("SELECT id, name FROM world"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($wid, $wname)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
	echo '<option value=" '. $wid . ' "> ' . $wname . '</option>\n';
}
$stmt->close();
?>
			</select>
		</fieldset>
		<input type="submit" name="addWorld" value="Add Item to World" />
		<input type="submit" name="deleteWorld" value="Delete Item From World" />
	</form>
</div>
<div>
	<h3>Delete Item</h3>
	<form method="post" action="moditem.php"> 

		<fieldset>
			<legend>Name</legend>
			<input type="text" name="Name" />
		</fieldset>
		<input type="submit" name="delete" value="Delete Item" />
	</form>
</div>
<?php
//Code to add an item to the table
if($_POST['add']){
	if(!($stmt = $mysqli->prepare("INSERT INTO item(name, class, level, jid) VALUES (?,?,?, ?)"))){
		echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
	}
	
	//If level, class, or Job was not specified make it null
	if(!empty($_POST['Level'])){
		$level = $_POST['Levels'];
	}
	else{
		$level = 1;
	}
	if(!empty($_POST['Class'])){
		$class = $_POST['Class'];
	}
	else{
		$class = NULL;
	}
	
	if(!($stmt->bind_param("ssii",$_POST['Name'], $class ,$level, $_POST['Job']))){
		echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
	}
	if(!$stmt->execute()){
		echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
	} else {
		echo "Added " . $stmt->affected_rows . " rows to item.";
	}
}
//Code to update the table
else if($_POST['update']){
	$name = $_POST['Name'];
	
	//make sure a name was given
	if(empty($name)){ 
		echo "No name given for update";
		$valid = 0;
	}
	else{
		$valid = 1;
	}
	//If a name was given update that item
	if($valid != 0){
		
		//get 
		if(!($stmt = $mysqli->prepare("SELECT class, level, jid FROM item WHERE name=?"))){
			echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
		}
		if(!($stmt->bind_param("s",$_POST['Name']))){
			echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
		}
		if(!$stmt->execute()){
			echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
		if(!$stmt->bind_result($class, $level, $jid)){
			echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
		$stmt->fetch();
		$stmt->close();
		
		//If a class, level or job was specified, change the returned value to it
		if(!empty($_POST['Class'])){
			$skills = $_POST['Class'];
		}
		if(!empty($_POST['Level'])){
			$levels = $_POST['Level'];
		}
		
		//Update the item
		if(!($stmt = $mysqli->prepare("UPDATE item 
					SET class = ?, level = ?, jid = ? WHERE name = ?"))){
			echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
		}
		if(!($stmt->bind_param("siis",$skills,$levels,$_POST['Job'], $_POST['Name']))){
			echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
		}
		if(!$stmt->execute()){
			echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
		} else {
			echo "Updated " . $stmt->affected_rows . " rows to item.";
		}
		$stmt->close();
	}
}else if($_POST['delete']){
	$name = $_POST['Name'];
	//make sure a name is given
	if(empty($name)){ 
		echo "No name given for delete";
		$valid = 0;
	}
	else{
		$valid = 1;
	}
	
	//if a name is given delete the item from the table
	if($valid != 0){
		if(!($stmt = $mysqli->prepare("DELETE FROM item WHERE name=?"))){
			echo "Prepare failed: (" . $mysqli->errno . ") " . $mysqli->error;
		}
		if(!($stmt->bind_param("s",$_POST['Name']))){
			echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
		}
		if(!$stmt->execute()){
			echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
		} 
		
		$stmt->close();
	}
}
//Code to add an item to a world
else if($_POST['addWorld']){

	if(!($stmt = $mysqli->prepare("INSERT INTO world_item(wid, iid) VALUES (?,?)"))){
		echo "Prepare failed: (" . $mysqli->errno . ") " . $mysqli->error;
	}
	if(!($stmt->bind_param("ii",$_POST['World'],$_POST['Item']))){
		echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
	}
	if(!$stmt->execute()){
		echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
	} 
	
	$stmt->close();
}
//Code to delete an item from a world
else if($_POST['deleteWorld']){

	if(!($stmt = $mysqli->prepare("DELETE FROM world_item WHERE wid=? AND iid=?"))){
		echo "Prepare failed: (" . $mysqli->errno . ") " . $mysqli->error;
	}
	if(!($stmt->bind_param("ii",$_POST['World'],$_POST['Item']))){
		echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
	}
	if(!$stmt->execute()){
		echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
	} 
	
	$stmt->close();
}
?>
</body>
</html>