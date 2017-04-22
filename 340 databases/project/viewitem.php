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
	<h2>View Items By</h2>
</div>
<div>
	<form method="post" action="viewitem.php">
		<fieldset>
			<legend>Filter By World</legend>
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
		<input type="submit" name = "selectWorld" value="View by World" />
	</form>
	<form method="post" action="viewitem.php">
		<fieldset>
			<legend>Filter By Job</legend>
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
		<input type="submit" name = "selectJob" value="View by Job" />
	</form>
	<form method="post" action="viewitem.php">
		<fieldset>
			<legend>Filter By Player</legend>
				<select name="Player">
<?php
//Code to provide a list of worlds
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
		<input type="submit" name = "selectPlayer" value="View by Player" />
	</form>
</div>
<div>
	<h3>Items</h3>
	<table>
		<tr>
			<th>Name</th>
			<th>Class</th>
			<th>Level</th>
			<th>Job</th>
		<?php
			if($_POST['selectWorld']){
				echo "\n<th>World</th></tr>\n";
				if($_POST['World'] == 1){
					if(!($stmt = $mysqli->prepare("SELECT item.name, item.class, item.level, job.title, world.name 
												FROM item
												INNER JOIN world_item ON item.id = world_item.iid
												INNER JOIN world ON world_item.wid = world.id
												INNER JOIN job ON job.id = item.jid"))){
					echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
					}
				}
				else{
					if(!($stmt = $mysqli->prepare("SELECT item.name, item.class, item.level, job.title, world.name 
													FROM item
													INNER JOIN world_item ON item.id = world_item.iid
													INNER JOIN world ON world_item.wid = world.id
													INNER JOIN job ON job.id = item.jid
													WHERE world.id = ?"))){
						echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
					}
					if(!($stmt->bind_param("i",$_POST['World']))){
						echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
					}
				}
				if(!$stmt->execute()){
					echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}
				if(!$stmt->bind_result($name, $class, $level, $title, $world)){
					echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}
				while($stmt->fetch()){
				 echo "<tr>\n<td>\n" . $name . "\n</td>\n<td>\n" . $class . "\n</td>\n<td>\n" . 
					  $level . "\n</td>\n<td>\n" . $title . "\n</td>\n<td>\n" . $world . "\n</td>\n</tr>";
				}
			}
			else if($_POST['selectJob']){
				if($_POST['Job'] == 1){
					if(!($stmt = $mysqli->prepare("SELECT item.name, item.class, item.level, job.title
												FROM item
												INNER JOIN job ON item.jid = job.id"))){
					echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
					}	
				}
				else{
					if(!($stmt = $mysqli->prepare("SELECT item.name, item.class, item.level, job.title
													FROM item
													INNER JOIN job ON item.jid = job.id
													WHERE job.id = ?"))){
						echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
					}
					if(!($stmt->bind_param("i",$_POST['Job']))){
						echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
					}
				}
				if(!$stmt->execute()){
					echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}
				if(!$stmt->bind_result($name, $class, $level, $title)){
					echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}
				while($stmt->fetch()){
				 echo "<tr>\n<td>\n" . $name . "\n</td>\n<td>\n" . $class . "\n</td>\n<td>\n" . 
					  $level . "\n</td>\n<td>\n" . $title . "\n</td>\n</tr>";
				}
			}
			else if($_POST['selectPlayer']){
				echo "\n<th>Player</th></tr>\n";
				if(!($stmt = $mysqli->prepare("SELECT item.name, item.class, item.level, job.title, player.first_name, player.last_name
												FROM item
												INNER JOIN job ON job.id = item.jid
												INNER JOIN player_item ON item.jid = player_item.iid
												INNER JOIN player ON player_item.pid = player.id
												WHERE player.id = ?"))){
					echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
				}
				if(!($stmt->bind_param("i",$_POST['Player']))){
					echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
				}
				if(!$stmt->execute()){
					echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}
				if(!$stmt->bind_result($name, $class, $level, $title, $fname, $lname)){
					echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
				}
				while($stmt->fetch()){
				 echo "<tr>\n<td>\n" . $name . "\n</td>\n<td>\n" . $class . "\n</td>\n<td>\n" . 
					  $level . "\n</td>\n<td>\n" . $title . "\n</td>\n<td>\n" . $fname . " " . $lname . "\n</td>\n</tr>";
				}
			}
			$stmt->close();
		?>
	</table>
</div>
</body>
</html>