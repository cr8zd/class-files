<?php 
	$pageTitle = "Bee Keepers";
	include('inc/header.php'); 

	//Add beekeeper to Beekeeper table
	if(isset($_POST['record_beekeeper'])) {
		$firstName = $_POST['firstName'];
		$lastName = $_POST['lastName'];
		$street = $_POST['street'];
		$city = $_POST['city'];
		$state = $_POST['state'];
		$zipcode = $_POST['zipcode'];
		$phone = $_POST['phone'];
		$email = $_POST['email'];
		
		//Unit testing on form input.
		if(!empty($firstName)) {
			$error_msg1 = "PASS first name not empty.<br>";
		}
		else{
			$error_msg1 = "FAIL first name empty.<br>";
		}
	    if(!empty($lastName)) {
			$error_msg2 = "PASS last name not empty.<br>";
		}
		else{
			$error_msg2 = "FAIL last name empty.<br>";
		}
		if(!empty($street)) {
			$error_msg3 = "PASS street address not empty.<br>";
		}
		else{
			$error_msg3 = "FAIL street address empty.<br>";
		}
		if(!empty($city)) {
			$error_msg4 = "PASS city not empty.<br>";
		}
		else{
			$error_msg4 = "FAIL city empty.<br>";
		}
		if(!empty($state)) {
			$error_msg5 = "PASS state not empty.<br>";
		}
		else{
			$error_msg5 = "FAIL state empty.<br>";
		}
		if(!empty($zipcode)) {
			$error_msg6 = "PASS zipcode not empty.<br>";
		}
		else{
			$error_msg6 = "FAIL zipcode empty.<br>";
		}
		if(!empty($phone)){
			$error_msg7 = "PASS phone number not empty.<br>";
		}
		else{
			$error_msg7 = "FAIL phone number empty.<br>";
		}
		if(!empty($email)) {
			$error_msg8 = "PASS email address not empty.<br>";
		}
		else{
			$error_msg8 = "FAIL email address empty.<br>";
		}
		
		//Checks if record_beekeeper form inputs are empty.
		if(empty($firstName)) {
			$error_msg = "A first name is required.<br>";
			$valid = 0;
		}
		else if(empty($lastName)) {
			$error_msg = "A last name is required.<br>";
			$valid = 0;
		}
		else if(empty($street)) {
			$error_msg = "A street address is required.<br>";
			$valid = 0;
		}
		else if(empty($city)) {
			$error_msg = "A city is required.<br>";
			$valid = 0;
		}
		else if(empty($state)) {
			$error_msg = "A state is required.<br>";
			$valid = 0;
		}
		else if(empty($zipcode)) {
			$error_msg = "A zipcode is required.<br>";
			$valid = 0;
		}
		else if(empty($phone)){
			$error_msg = "A phone number is required.<br>";
			$valid = 0;
		}
		else if(empty($email)) {
			$error_msg = "A email address is required.<br>";
			$valid = 0;
		}
		else {
			$valid=1;
		}
		
		//If no errors, add the record_beekeeper to database in Beekeeper table.
		if($valid != 0 ) {
			$stmt = $mysqli->prepare
				("INSERT INTO Beekeeper (firstName, lastName, street, city, state, zipcode, phone, email) 
					VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
			$stmt->bind_param('sssssiss', $firstName, $lastName, $street, $city, $state, $zipcode, $phone, $email);
			$stmt->execute();
			if(!$stmt->execute()){
				$error_msgD = "PASS added row.";
			}
			else{
				$error_msgD = "FAIL could not add.";
			}
			$stmt->close();
		}
	}
	

	//Update beekeeper in Beekeeper table
	if(isset($_POST['update_beekeeper'])) {
		$firstName = $_POST['firstName'];
		$lastName = $_POST['lastName'];
		$street = $_POST['street'];
		$city = $_POST['city'];
		$state = $_POST['state'];
		$zipcode = $_POST['zipcode'];
		$phone = $_POST['phone'];
		$email = $_POST['email'];
		$beekeeper_id = $_POST['id'];
		
		//Unit testing on form input.
		if(!empty($firstName)) {
			$error_msg9 = "PASS first name not empty.<br>";
		}
		else{
			$error_msg9 = "FAIL first name empty.<br>";
		}
	    if(!empty($lastName)) {
			$error_msg10 = "PASS last name not empty.<br>";
		}
		else{
			$error_msg10 = "FAIL last name empty.<br>";
		}
		if(!empty($street)) {
			$error_msg11 = "PASS street address not empty.<br>";
		}
		else{
			$error_msg11 = "FAIL street address empty.<br>";
		}
		if(!empty($city)) {
			$error_msg12 = "PASS city not empty.<br>";
		}
		else{
			$error_msg12 = "FAIL city empty.<br>";
		}
		if(!empty($state)) {
			$error_msg13 = "PASS state not empty.<br>";
		}
		else{
			$error_msg13 = "FAIL state empty.<br>";
		}
		if(!empty($zipcode)) {
			$error_msg14 = "PASS zipcode not empty.<br>";
		}
		else{
			$error_msg14 = "FAIL zipcode empty.<br>";
		}
		if(!empty($phone)){
			$error_msg15 = "PASS phone number not empty.<br>";
		}
		else{
			$error_msg15 = "FAIL phone number empty.<br>";
		}
		if(!empty($email)) {
			$error_msg16 = "PASS email address not empty.<br>";
		}
		else{
			$error_msg16 = "FAIL email address empty.<br>";
		}
		
		//Checks if update_beekeeper form inputs are empty.
		if(empty($firstName)) {
			$error_msg = "A first name is required.<br>";
			$valid = 0;
		}
		else if(empty($lastName)) {
			$error_msg = "A last name is required.<br>";
			$valid = 0;
		}
		else if(empty($street)) {
			$error_msg = "A street address is required.<br>";
			$valid = 0;
		}
		else if(empty($city)) {
			$error_msg = "A city is required.<br>";
			$valid = 0;
		}
		else if(empty($state)) {
			$error_msg = "A state is required.<br>";
			$valid = 0;
		}
		else if(empty($zipcode)) {
			$error_msg = "A zipcode is required.<br>";
			$valid = 0;
		}
		else if(empty($phone)){
			$error_msg = "A phone number is required.<br>";
			$valid = 0;
		}
		else if(empty($email)) {
			$error_msg = "A email address is required.<br>";
			$valid = 0;
		}
		else {
			$valid=1;
		}
		//If no errors, Update the beekeeper in Beekeeper table.
		if($valid != 0 ) {
			$stmt = $mysqli->prepare
				("UPDATE Beekeeper 
					SET firstName = ?, lastName = ?, street = ?, city = ?, state = ?, zipcode = ?,
					phone =?, email = ?
					WHERE id = $beekeeper_id");
			$stmt->bind_param('sssssiss', $firstName, $lastName, $street, $city, $state, $zipcode, $phone, $email);
			$stmt->execute();
			if(!$stmt->execute()){
				$error_msgD = "FAIL could not update.";
			}
			else{
				$error_msgD = "PASS updated row.";
			}
			$stmt->close();
		}
	}
	
	//Delete a beekeeper from database in Beekeeper table
	if(isset($_POST['deleteRecord'])){
		$beekeeper_id = $_POST['id'];
		if(!($stmt = $mysqli->prepare("DELETE FROM Beekeeper WHERE id = '$beekeeper_id'"))){
			echo "Prepare failed: (" . $mysqli->errno . ") " . $mysqli->error;
		}
		if(!$stmt->execute()){
			$error_msgD = "FAIL could not delete.";
		}
		else{
			$error_msgD = "PASS deleted row.";
		}
	}
	
	//get all beekeepers from Beekeeper table
	$query = "SELECT id, firstName, lastName, street, city, state, zipcode, phone, email
			  FROM Beekeeper ORDER BY lastName ASC";
	$beekeepers = $mysqli->query($query);

?>
<div id="intro">
	<h2>The Bee Keepers</h2>
	<p>Add a bee keeper here.</p>
</div>

<!-- ADD Beekeeper to Beekeeper table-->

<div>
	<h2>Add a new Bee Keeper</h2>
	<form action="beekeeper.php" method="post">
		<table>
			<tr>
				<th>
					<label for"firstName">First Name</label>
				</th>
				<td>
					<input type="text" name="firstName">
				</td>
			</tr>
			<tr>
				<th>
					<label for"lastName">Last Name</label>
				</th>
				<td>
					<input type="text" name="lastName">
				</td>
			</tr>
			<tr>
				<th>
					<label for"street">Street Address</label>
				</th>
				<td>
					<input type="text" name="street">
				</td>
			</tr>
			<tr>
				<th>
					<label for"city">City</label>
				</th>
				<td>
					<input type="text" name="city">
				</td>
			</tr>
			<tr>
				<th>
					<label for"state">State</label>
				</th>
				<td>
					<input type="text" name="state">
				</td>
			</tr>
			<tr>
				<th>
					<label for"zipcode">Zipcode</label>
				</th>
				<td>
					<input type="text" name="zipcode">
				</td>
			</tr>
			<tr>
				<th>
					<label for"phone">Phone Number</label>
				</th>
				<td>
					<input type="text" name="phone">
				</td>
			</tr>
			<tr>
				<th>
					<label for"email">Email Address</label>
				</th>
				<td>
					<input type="text" name="email">
				</td>
			</tr>
		</table>
		<div id="record_btn">
			<input type="submit" name="record_beekeeper" value="ADD">
		</div>
		<div id="err">
			<?php
				if(!empty($error_msg))
				{
					echo $error_msg;
				}
				if(!empty($error_msg1))
				{
					echo $error_msg1;
				}
				if(!empty($error_msg2))
				{
					echo $error_msg2;
				}
				if(!empty($error_msg3))
				{
					echo $error_msg3;
				}
				if(!empty($error_msg4))
				{
					echo $error_msg4;
				}
				if(!empty($error_msg5))
				{
					echo $error_msg5;
				}
				if(!empty($error_msg6))
				{
					echo $error_msg6;
				}
				if(!empty($error_msg7))
				{
					echo $error_msg7;
				}
				if(!empty($error_msg8))
				{
					echo $error_msg8;
				}
			?>
		</div>
	</form>
	
	<!-- UPDATE beekeeper in Beekeeper table-->
	<form action="beekeeper.php" method="post">
		<table>
			<tr>
				<th>
					<label for"id">Who do you want to edit?</label>
				</th>
				<td>
					<select name="id">
						<?php foreach ($beekeepers as $beekeeper) :
							echo '<option value="'. $beekeeper['id']. '">'.
							$beekeeper['firstName']. ' '. $beekeeper['lastName']. '</option>';
							endforeach; 
						?>
					</select>
				</td>
			</tr>
			<tr>
				<th>
					<label for"firstName">First Name</label>
				</th>
				<td>
					<input type="text" name="firstName">
				</td>
			</tr>
			<tr>
				<th>
					<label for"lastName">Last Name</label>
				</th>
				<td>
					<input type="text" name="lastName">
				</td>
			</tr>
			<tr>
				<th>
					<label for"street">Street Address</label>
				</th>
				<td>
					<input type="text" name="street">
				</td>
			</tr>
			<tr>
				<th>
					<label for"city">City</label>
				</th>
				<td>
					<input type="text" name="city">
				</td>
			</tr>
			<tr>
				<th>
					<label for"state">State</label>
				</th>
				<td>
					<input type="text" name="state">
				</td>
			</tr>
			<tr>
				<th>
					<label for"zipcode">Zipcode</label>
				</th>
				<td>
					<input type="text" name="zipcode">
				</td>
			</tr>
			<tr>
				<th>
					<label for"phone">Phone Number</label>
				</th>
				<td>
					<input type="text" name="phone">
				</td>
			</tr>
			<tr>
				<th>
					<label for"email">Email Address</label>
				</th>
				<td>
					<input type="text" name="email">
				</td>
			</tr>
		</table>
		<div id="record_btn">
			<input type="submit" name="update_beekeeper" value="UPDATE">
		</div>
		<div id="err">
			<?php
				if(!empty($error_msg))
				{
					echo $error_msg;
				}
				if(!empty($error_msg9))
				{
					echo $error_msg9;
				}
				if(!empty($error_msg10))
				{
					echo $error_msg10;
				}
				if(!empty($error_msg11))
				{
					echo $error_msg11;
				}
				if(!empty($error_msg12))
				{
					echo $error_msg12;
				}
				if(!empty($error_msg13))
				{
					echo $error_msg13;
				}
				if(!empty($error_msg14))
				{
					echo $error_msg14;
				}
				if(!empty($error_msg15))
				{
					echo $error_msg15;
				}
				if(!empty($error_msg16))
				{
					echo $error_msg16;
				}
				if(!empty($error_msgD))
				{
					echo $error_msgD;
				}
			?>
		</div>
	</form>
	
</div>

	
<!-- Output Beekeeper table -->

	<div>
		<h2>Show All Bee Keepers</h2>

		<?php
			echo "<table>";
				echo "<tr>";
					echo "<th>First Name</th>";
					echo "<th>Last Name</th>";
					echo "<th>Street Address</th>";
					echo "<th>City</th>";
					echo "<th>State</th>";
					echo "<th>Zipcode</th>";
					echo "<th>Phone Number</th>";
					echo "<th>Email Address</th>";
					echo "<th>Action</th>";
				echo "</tr>";

				//Output all records from Beekeeper table
			  foreach ($beekeepers as $beekeeper) :
					echo "<tr>";
						echo	"<td>" . $beekeeper['firstName'] . "</td>";
						echo	"<td>" . $beekeeper['lastName'] . "</td>";
						echo	"<td>" . $beekeeper['street'] . "</td>";
						echo	"<td>" . $beekeeper['city'] . "</td>";
						echo	"<td>" . $beekeeper['state'] . "</td>";
						echo	"<td>" . $beekeeper['zipcode'] . "</td>";
						echo	"<td>" . $beekeeper['phone'] . "</td>";
						echo	"<td>" . $beekeeper['email'] . "</td>";
						echo	"<td>"; 
									echo '<form action="beekeeper.php" method="post">';?>
									<input type ="hidden" name="id" value="<?php echo $beekeeper['id']; ?>">
									<?php echo '<input type="submit" name="deleteRecord" value ="Delete">';
									echo "</form>"; 
						echo 	"</td>";
					echo "</tr>";
			endforeach;
		  
			echo "</table>";
		?>
	</div>
			
<?php include('inc/footer.php'); ?>
