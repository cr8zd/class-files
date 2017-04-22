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
	<h2>Modify Player</h2>
</div>
<div>
	<h3>Add/Update Player</h3>
	<form method="post" action="modplayer.php"> 

		<fieldset>
			<legend>Name *required</legend>
			<p>First Name: <input type="text" name="FirstName" /></p>
			<p>Last Name: <input type="text" name="LastName" /></p>
		</fieldset>

		<fieldset>
			<legend>Job</legend>
			<select name="Job">
<?php
//get job options
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
		
		<fieldset>
			<legend>World</legend>
			<select name="World">
<?php
//get world options
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
		<fieldset>
			<legend>Species</legend>
			<input type="text" name="Species" /></p>
		</fieldset>
		<input type="submit" name="add" value="Add Person" />
		<input type="submit" name="update" value="Update Person" />
	</form>
</div>
<div>
	<h3>Add/Delete Item to Player</h3>
	<form method="post" action="modplayer.php"> 

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
			<legend>Player</legend>
			<select name="Player">
<?php
//Code to provide a list of players
if(!($stmt = $mysqli->prepare("SELECT id, first_name, last_name FROM player"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
if(!$stmt->bind_result($pid, $fname, $lname)){
	echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
}
while($stmt->fetch()){
	echo '<option value=" '. $pid . ' "> ' . $fname . " " . $lname . '</option>\n';
}
$stmt->close();
?>
			</select>
		</fieldset>
		<input type="submit" name="addItem" value="Add Item to Player" />
		<input type="submit" name="deleteItem" value="Delete Item From Player" />
	</form>
</div>
<div>
	<h3>Delete Player</h3>
	<form method="post" action="modplayer.php"> 

		<fieldset>
			<legend>Name</legend>
			<p>First Name: <input type="text" name="FirstName" /></p>
			<p>Last Name: <input type="text" name="LastName" /></p>
		</fieldset>
		<input type="submit" name="delete" value="Delete Person" />
	</form>
</div>
<?php
//Code for adding player into table
if($_POST['add']){
	if(!($stmt = $mysqli->prepare("INSERT INTO player(first_name, last_name, jid, wid, species) VALUES (?,?,?,?, ?)"))){
		echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
	}
		
	//if species was left blank, make it null
	if(!empty($_POST['Species'])){
		$species = $_POST['Species'];
	}
	else{
		$species = NULL;
	}
	
	if(!($stmt->bind_param("ssiis",$_POST['FirstName'],$_POST['LastName'],$_POST['Job'],$_POST['World'],$species))){
		echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
	}
	if(!$stmt->execute()){
		echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
	} else {
		echo "Added " . $stmt->affected_rows . " rows to player.";
	}
}
//Code to update a player
else if($_POST['update']){
	$firstName = $_POST['FirstName'];
	$lastName = $_POST['LastName'];
	
	//Check that the first and last name are not empty
	if(empty($firstName)){ 
		echo "No first name given for update";
		$valid = 0;
	}
	else if(empty($lastName)){ 
		echo "No last name given for update";
		$valid = 0;
	}
	else{
		$valid = 1;
	}
	
	//if first and last name are not empty procede to process the update
	if($valid != 0){
		//get the id and non required information from the table
		if(!($stmt = $mysqli->prepare("SELECT player.id, player.jid, player.wid, player.species FROM player WHERE first_name=? AND last_name=? "))){
			echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
		}
		if(!($stmt->bind_param("ss",$_POST['FirstName'],$_POST['LastName']))){
			echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
		}
		if(!$stmt->execute()){
			echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
		if(!$stmt->bind_result($pid, $jid, $wid, $species)){
			echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
		$stmt->fetch();
		$stmt->close();
		
		//if a job, world and/or species was specified change the returned value from above
		//to the updated information
		if($_POST['Job'] != 0){
			$jid = $_POST['Job'];
		}
		if($_POST['World'] != 0){
			$wid = $_POST['World'];
		}
		if(!empty($_POST['Species'])){
			$species = $_POST['Species'];
		}
		
		//update the player
		if(!($stmt = $mysqli->prepare("UPDATE player 
					SET jid = ?, wid = ?, species = ? WHERE id = ?"))){
			echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
		}
		if(!($stmt->bind_param("iisi",$jid,$wid,$species,$pid ))){
			echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
		}
		if(!$stmt->execute()){
			echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
		} else {
			echo "Updated " . $stmt->affected_rows . " rows to player.";
		}
		$stmt->close();
	}
}
//Code to delete a player from table
else if($_POST['delete']){
	$firstName = $_POST['FirstName'];
	$lastName = $_POST['LastName'];
	
	//make sure first and last name are not empty
	if(empty($firstName)){ 
		echo "No first name given for delete";
		$valid = 0;
	}
	else if(empty($lastName)){ 
		echo "No last name given for delete";
		$valid = 0;
	}
	else{
		$valid = 1;
	}
	//if first and last name are not empty procede to delete
	if($valid != 0){
		if(!($stmt = $mysqli->prepare("DELETE FROM player WHERE first_name=? AND last_name=?"))){
			echo "Prepare failed: (" . $mysqli->errno . ") " . $mysqli->error;
		}
		if(!($stmt->bind_param("ss",$_POST['FirstName'],$_POST['LastName']))){
			echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
		}
		if(!$stmt->execute()){
			echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
		} 
		
		$stmt->close();
	}
}
//Code to add an item to a world
else if($_POST['addItem']){
	
	if(!($stmt = $mysqli->prepare("INSERT INTO player_item(pid, iid) VALUES (?,?)"))){
		echo "Prepare failed: (" . $mysqli->errno . ") " . $mysqli->error;
	}
	if(!($stmt->bind_param("ii",$_POST['Player'],$_POST['Item']))){
		echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
	}
	if(!$stmt->execute()){
		echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
	} 
	
	$stmt->close();
}
//Code to delete an item from a world
else if($_POST['deleteItem']){
	//Code to provide a list of items
	if(!($stmt = $mysqli->prepare("SELECT id FROM player_item WHERE pid=? AND iid=?"))){	
		echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
	}
	if(!($stmt->bind_param("ii",$_POST['Player'],$_POST['Item']))){
		echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
	}
	if(!$stmt->execute()){
		echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	if(!$stmt->bind_result($piid)){
		echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	$stmt->fetch(); //get first occurance
	$stmt->close();

	if(!($stmt = $mysqli->prepare("DELETE FROM player_item WHERE id=?"))){
		echo "Prepare failed: (" . $mysqli->errno . ") " . $mysqli->error;
	}
	if(!($stmt->bind_param("i",$piid))){
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