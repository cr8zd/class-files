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
<head>
	<title>Jennifer's Game</title>
</head>
<body>
<h2><a href="home.html">HOME</a></h2>
<div>
	<h2>View Players By</h2>
</div>
<div>
	<form method="post" action="viewplayer.php">
		<fieldset>
			<legend>Filter By World</legend>
				<select name="World">
					<option value="0"> </option>
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
		<input type="submit" name = "selectWorld" value="View by World" />
	</form>
	<form method="post" action="viewplayer.php">
		<fieldset>
			<legend>Filter By Job</legend>
				<select name="Job">
					<option value="0"> </option>
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
		<input type="submit" name = "selectJob" value="View by Job" />
	</form>
</div>
<div>
	<h3>Players</h3>
	<table>
		<tr>
			<th>First Name</th>
			<th>Last Name</th>
			<th>Job</th>
			<th>World</th>
			<th>Species</th>
		</tr>
		<?php
			if($_POST['selectWorld']){
				if($_POST['World'] == 0){
					if(!($stmt = $mysqli->prepare("SELECT player.first_name, player.last_name, job.title, world.name, player.species 
													FROM player 
													INNER JOIN world ON player.wid = world.id
													INNER JOIN job ON player.jid = job.id"))){
						echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
					}
				}else{
					if(!($stmt = $mysqli->prepare("SELECT player.first_name, player.last_name, job.title, world.name, player.species 
													FROM player 
													INNER JOIN world ON player.wid = world.id
													INNER JOIN job ON player.jid = job.id
													WHERE world.id = ?"))){
						echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
					}
					if(!($stmt->bind_param("i",$_POST['World']))){
						echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
					}
				}
			}
			else if($_POST['selectJob']){
				if($_POST['Job'] == 0){
					if(!($stmt = $mysqli->prepare("SELECT player.first_name, player.last_name, job.title, world.name, player.species 
													FROM player 
													INNER JOIN world ON player.wid = world.id
													INNER JOIN job ON player.jid = job.id"))){
						echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
					}
				}
				else{
					if(!($stmt = $mysqli->prepare("SELECT player.first_name, player.last_name, job.title, world.name, player.species 
													FROM player 
													INNER JOIN world ON player.wid = world.id
													INNER JOIN job ON player.jid = job.id
													WHERE job.id = ?"))){
						echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
					}
					if(!($stmt->bind_param("i",$_POST['Job']))){
						echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
					}
				}
			}
			
			if(!$stmt->execute()){
				echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
			}
			if(!$stmt->bind_result($firstName, $lastName, $job, $world, $species)){
				echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
			}
			while($stmt->fetch()){
			 echo "<tr>\n<td>\n" . $firstName . "\n</td>\n<td>\n" . $lastName . "\n</td>\n<td>\n" . 
				  $job . "\n</td>\n<td>\n" . $world . "\n</td>\n<td>\n" . $species . "\n</td>\n</tr>";
			}
			$stmt->close();
		?>
	</table>
</div>
</body>
</html>