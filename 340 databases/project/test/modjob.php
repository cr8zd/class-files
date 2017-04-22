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
	<h2>Modify Job</h2>
</div>
<div>
	<h3>Add/Update Job</h3>
	<form method="post" action="modjob.php"> 

		<fieldset>
			<legend>Job Title *required</legend>
			<input type="text" name="Title" />
		</fieldset>
		<fieldset>
			<legend>Skills</legend>
			<input type="text" name="Skills" /></p>
		</fieldset>
		<fieldset>
			<legend>Promotes To</legend>
			<input type="text" name="Levels" /></p>
		</fieldset>
		<input type="submit" name="add" value="Add Job" />
		<input type="submit" name="update" value="Update Job" />
	</form>
</div>
<div>
	<h3>Delete Job</h3>
	<form method="post" action="modjob.php"> 

		<fieldset>
			<legend>Title</legend>
			<input type="text" name="Title" />
		</fieldset>
		<input type="submit" name="delete" value="Delete Job" />
	</form>
</div>
<?php
//Code to add job to table
if($_POST['add']){
	if(!($stmt = $mysqli->prepare("INSERT INTO job(title, skills, levels) VALUES (?,?,?)"))){
		echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
	}
	
	//if promotes to and/or skills was left blank make it null 
	if(!empty($_POST['Levels'])){
		$levels = $_POST['Levels'];
	}
	else{
		$levels = NULL;
	}
	if(!empty($_POST['Skills'])){
		$skills = $_POST['Skills'];
	}
	else{
		$skills = NULL;
	}
	
	if(!($stmt->bind_param("sss",$_POST['Title'],$skills,$levels))){
		echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
	}
	if(!$stmt->execute()){
		echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
	} else {
		echo "Added " . $stmt->affected_rows . " rows to job.";
	}
}
//Code to update the table
else if($_POST['update']){
	$title = $_POST['Title'];
	
	//make sure a title was given
	if(empty($title)){ 
		echo "No title given for update";
		$valid = 0;
	}
	else{
		$valid = 1;
	}
	
	//if a title was provided update it
	if($valid != 0){
		//get the current skills and level up for the given title
		if(!($stmt = $mysqli->prepare("SELECT skills, levels FROM job WHERE title=?"))){
			echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
		}
		if(!($stmt->bind_param("s",$_POST['Title']))){
			echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
		}
		if(!$stmt->execute()){
			echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
		if(!$stmt->bind_result($skills, $levels)){
			echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}
		$stmt->fetch();
		$stmt->close();
		
		//if skills or level up are not empty set the returned values to these update values 
		if(!empty($_POST['Skills'])){
			$skills = $_POST['Skills'];
		}
		if(!empty($_POST['Levels'])){
			$levels = $_POST['Levels'];
		}
		//Update the table
		if(!($stmt = $mysqli->prepare("UPDATE job 
					SET skills = ?, levels = ? WHERE title = ?"))){
			echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
		}
		if(!($stmt->bind_param("sss",$skills,$levels,$_POST['Title']))){
			echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
		}
		if(!$stmt->execute()){
			echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
		} else {
			echo "Updated " . $stmt->affected_rows . " rows to job.";
		}
		$stmt->close();
	}
}
//Code to delete from the table
else if($_POST['delete']){
	//check that the title is not empty
	$title = $_POST['Title'];
	
	if(empty($title)){ 
		echo "No title given for delete";
		$valid = 0;
	}
	else{
		$valid = 1;
	}
	//if title is there delete the job
	if($valid != 0){
		if(!($stmt = $mysqli->prepare("DELETE FROM job WHERE title=?"))){
			echo "Prepare failed: (" . $mysqli->errno . ") " . $mysqli->error;
		}
		if(!($stmt->bind_param("s",$_POST['Title']))){
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