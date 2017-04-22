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
	<h2>View Worlds</h2>
</div>
<div>
	<h3>Worlds</h3>
	<table>
		<tr>
			<th>Name</th>
			<th>Climate</th>
		</tr>
		<?php
			if(!($stmt = $mysqli->prepare("SELECT name, climate FROM world"))){
				echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
			}
			
			if(!$stmt->execute()){
				echo "Execute failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
			}
			if(!$stmt->bind_result($name, $climate)){
				echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
			}
			while($stmt->fetch()){
			 echo "<tr>\n<td>\n" . $name . "\n</td>\n<td>\n" . $climate . "\n</td>\n</tr>";
			}
			$stmt->close();
		?>
	</table>
</div>
</body>
</html>