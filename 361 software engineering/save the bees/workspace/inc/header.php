<!DOCTYPE HTML>
<?php 
	require_once('db.php');//Connect to database
 	session_start();
?>
<html>

<head>
	<meta charset="UTF-8">
	<link rel="stylesheet" href="./css/style.css">
	<link rel='stylesheet' href='fullcalendar/fullcalendar.css' />
	<script src='fullcalendar/lib/jquery.min.js'></script>
	<script src='fullcalendar/lib/moment.min.js'></script>
	<script src='fullcalendar/fullcalendar.js'></script>
	<title><?php echo $pageTitle; ?></title>
</head>

<body>
	<div id="container">

		<div id="header">
			<h1><a href ="index.php">Save the Bees!</a></h1>
		</div>
		
		<div id="nav">
			<ul>
				<li><a href ="index.php">Home</a></li>
				<li><a href ="beekeeper.php">Bee Keepers</a></li>
				<li><a href ="plants.php">Honeybee Plants</a></li>
				<li><a href ="list_hazmat.php">Hazardous Materials</a></li>
			</ul>
		</div>
