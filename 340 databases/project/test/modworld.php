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
	<h2>Modify World</h2>
</div>
<div>
	<h3>Add/Update World</h3>
	<form method="post" action="modworld.php"> 

		<fieldset>
			<legend>Name</legend>
			<input type="text" name="Name" />
		</fieldset>
		<fieldset>
			<legend>Climate</legend>
			<select name="Climate">
				<option value="dry">Dry</option>
				<option value="wet">Wet</option>
				<option value="cold">Cold</option>
				<option value="hot">Hot</option>
				<option value="moderate">Moderate</option>
				<option value="varies">Varies</option>
			</select>
		</fieldset>
		<input type="submit" name="add" value="Add World" />
		<input type="submit" name="update" value="Update World" />
	</form>
</div>
<div>
	<h3>Delete World</h3>
	<form method="post" action="modworld.php"> 

		<fieldset>
			<legend>Name</legend>
			<input type="text" name="Name" />
		</fieldset>
		<input type="submit" name="delete" value="Delete World" />
	</form>
</div>
<?php
//Code to add world to table
if($_POST['add']){
	if(!($stmt = $mysqli->prepare("INSERT INTO world(name, climate) VALUES (?,?)"))){
		echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
	}
	
	if(!($stmt->bind_param("ss",$_POST['Name'],$_POST['Climate']))){
		echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
	}
	if(!$stmt->execute()){
		echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
	} else {
		echo "Added " . $stmt->affected_rows . " rows to world.";
	}
}
//Code to update table
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
	//if a name is given, update the table
	if($valid != 0){
		if(!($stmt = $mysqli->prepare("UPDATE world 
					SET climate = ? WHERE name = ?"))){
			echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
		}
		if(!($stmt->bind_param("ss",$_POST['Climate'],$_POST['Name']))){
			echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
		}
		if(!$stmt->execute()){
			echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
		} else {
			echo "Updated " . $stmt->affected_rows . " rows to world.";
		}
		$stmt->close();
	}
}
//Code to delete from the table
else if($_POST['delete']){
	$name = $_POST['Name'];
	
	//make sure a name is given
	if(empty($name)){ 
		echo "No name given for delete";
		$valid = 0;
	}
	else{
		$valid = 1;
	}
	//If a name was given, delete that world
	if($valid != 0){	
		if(!($stmt = $mysqli->prepare("DELETE FROM world WHERE name=?"))){
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
?>
</body>
</html>