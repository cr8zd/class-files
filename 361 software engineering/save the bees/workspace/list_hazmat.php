<?php 
	$pageTitle = "Hazardous Material To Bees";
	include('inc/header.php'); 

	//Add hazmat to hazardousMaterial table
	if(isset($_POST['record_hazmat'])) {
		$name = $_POST['name'];
		$casID = $_POST['casID'];
		$comments = $_POST['comments'];
		$toxicityLevel = $_POST['toxicityLevel'];
		$alternative = $_POST['alternative'];
		
		//Unit testing on form input.
		if(!empty($name)) {
			$error_msg1 = "PASS name not empty.<br>";
		}
		else{
			$error_msg1 = "FAIL name empty.<br>";
		}
	    if(!empty($casID)) {
			$error_msg2 = "PASS casID not empty.<br>";
		}
		else{
			$error_msg2 = "FAIL casID empty.<br>";
		}
		if(!empty($toxicityLevel)) {
			$error_msg4 = "PASS toxicityLevel not empty.<br>";
		}
		else{
			$error_msg4 = "FAIL toxicityLevel empty.<br>";
		}

		
		//Checks if record_hazmat form inputs are empty.
		if(empty($name)) {
			$error_msg = "A name is required.<br>";
			$valid = 0;
		}
		else if(empty($casID)) {
			$error_msg = "A casID is required.<br>";
			$valid = 0;
		}
		else if(empty($toxicityLevel)) {
			$error_msg = "A toxicity level is required.<br>";
			$valid = 0;
		}
		else {
			$valid=1;
		}
		
		//If no errors, add the record_hazmat to database in hazardousMaterial table.
		if($valid != 0 ) {
			$stmt = $mysqli->prepare
				("INSERT INTO HazardousMaterial (name, casID, comments, toxicityLevel, alternative) 
					VALUES (?, ?, ?, ?, ?)");
			$stmt->bind_param('sisss', $name, $casID, $comments, $toxicityLevel, $alternative);
			$stmt->execute();
			if(!$stmt->execute()){
				$error_msgD = "PASS added to row.";
			}
			else{
				$error_msgD = "FAIL could not add.";
			}
			$stmt->close();
		}
	}
	

	//Update hazmat in hazardousMaterial table
	if(isset($_POST['update_hazmat'])) {
		$name = $_POST['name'];
		$casID = $_POST['casID'];
		$comments = $_POST['comments'];
		$toxicityLevel = $_POST['toxicityLevel'];
		$alternative = $_POST['alternative'];
		$hazmat_id = $_POST['id'];

		//Unit testing on form input.
		if(!empty($name)) {
			$error_msg9 = "PASS name not empty.<br>";
		}
		else{
			$error_msg9 = "FAIL name empty.<br>";
		}
	    if(!empty($casID)) {
			$error_msg10 = "PASS casID not empty.<br>";
		}
		else{
			$error_msg10 = "FAIL casID empty.<br>";
		}
		if(!empty($toxicityLevel)) {
			$error_msg11 = "PASS toxicity level not empty.<br>";
		}
		else{
			$error_msg11 = "FAIL toxicity level empty.<br>";
		}

		
		//Checks if update_hazmat form inputs are empty.
		if(empty($name)) {
			$error_msg = "A name is required.<br>";
			$valid = 0;
		}
		else if(empty($casID)) {
			$error_msg = "A casID is required.<br>";
			$valid = 0;
		}
		else if(empty($toxicityLevel)) {
			$error_msg = "A toxicity level is required.<br>";
			$valid = 0;
		}
		else {
			$valid=1;
		}
		//If no errors, Update the beekeeper in Beekeeper table.
		if($valid != 0 ) {
			$stmt = $mysqli->prepare
				("UPDATE HazardousMaterial 
					SET name = ?, casID = ?, comments = ?, toxicityLevel = ?, alternative = ?
					WHERE id = $hazmat_id");
			$stmt->bind_param('sisss', $name, $casID, $comments, $toxicityLevel, $alternative);
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
	
	//Delete a hazmat from database in hazardousMaterial table
	if(isset($_POST['deleteRecord'])){
		$hazmat_id = $_POST['id'];
		if(!($stmt = $mysqli->prepare("DELETE FROM HazardousMaterial WHERE id = '$hazmat_id'"))){
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
	$query = "SELECT id, name, casID, comments, toxicityLevel, alternative
			  FROM HazardousMaterial ORDER BY name ASC";
	$hazardousmaterial = $mysqli->query($query);

?>
<div id="intro">
	<h2>The Hazardous Material to Bees</h2>
	<p>Add a hazardous material here.</p>
</div>

<!-- ADD HazMat to HazMat table-->

<div>
	<h2>Add a new Hazardous Material</h2>
	<form action="list_hazmat.php" method="post">
		<table>
			<tr>
				<th>
					<label for"name">Name</label>
				</th>
				<td>
					<input type="text" name="name">
				</td>
			</tr>
			<tr>
				<th>
					<label for"casID">CAS ID#</label>
				</th>
				<td>
					<input type="text" name="casID">
				</td>
			</tr>
			<tr>
				<th>
					<label for"comments">Comments</label>
				</th>
				<td>
				    <textarea required name="comments" cols="22" rows="5" class="form-control"></textarea>
				</td>
			</tr>
			<tr>
				<th>
					<label for"toxicityLevel">Level of Toxicity</label>
				</th>
				<td>
					<input type="text" name="toxicityLevel">
				</td>
			</tr>
			<tr>
				<th>
					<label for"alternative">Alternative</label>
				</th>
				<td>
					<input type="text" name="alternative">
				</td>
			</tr>
		<div id="record_btn">
			<input type="submit" name="record_hazmat" value="ADD">
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
				if(!empty($error_msg4))
				{
					echo $error_msg4;
				}
			?>
		</div>
	</form>
	
	<!-- UPDATE hazmat in hazmat table-->
	<form action="list_hazmat.php" method="post">
		<table>
			<tr>
				<th>
					<label for"id">What do you want to edit?</label>
				</th>
				<td>
					<select name="id">
						<?php foreach ($hazardousmaterial as $hazmat) :
							echo '<option value="'. $hazmat['id']. '">'.
							$hazmat['name']. ' '. $hazmat['casID']. '</option>';
							endforeach; 
						?>
					</select>
				</td>
			</tr>
			<tr>
				<th>
					<label for"name">Name</label>
				</th>
				<td>
					<input type="text" name="name">
				</td>
			</tr>
			<tr>
				<th>
					<label for"casID">CAS ID</label>
				</th>
				<td>
					<input type="text" name="casID">
				</td>
			</tr>
			<tr>
				<th>
					<label for"comments">Comments</label>
				</th>
				<td>
					<textarea required name="comments" cols="22" rows="5" class="form-control"></textarea>
				</td>
			</tr>
			<tr>
				<th>
					<label for"toxicityLevel">Level of Toxicity</label>
				</th>
				<td>
					<input type="text" name="toxicityLevel">
				</td>
			</tr>
			<tr>
				<th>
					<label for"alternative">Alternative</label>
				</th>
				<td>
					<input type="text" name="alternative">
				</td>
			</tr>
		</table>
		<div id="record_btn">
			<input type="submit" name="update_hazmat" value="UPDATE">
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
				if(!empty($error_msgD))
				{
					echo $error_msgD;
				}
			?>
		</div>
	</form>
	
</div>

	
<!-- Output HazMat table -->

	<div>
		<h2>Show All Hazardous Material</h2>

		<?php
			echo "<table>";
				echo "<tr>";
					echo "<th>Name</th>";
					echo "<th>CAS ID</th>";
					echo "<th>Comments</th>";
					echo "<th>Level of Toxicity</th>";
					echo "<th>Alternative</th>";
				echo "</tr>";

				//Output all records from HazMat table
			  foreach ($hazardousmaterial as $hazmat) :
					echo "<tr>";
						echo	"<td>" . $hazmat['name'] . "</td>";
						echo	"<td>" . $hazmat['casID'] . "</td>";
						echo	"<td>" . $hazmat['comments'] . "</td>";
						echo	"<td>" . $hazmat['toxicityLevel'] . "</td>";
						echo	"<td>" . $hazmat['alternative'] . "</td>";
						echo	"<td>"; 
									echo '<form action="list_hazmat.php" method="post">';?>
									<input type ="hidden" name="id" value="<?php echo $hazmat['id']; ?>">
									<?php echo '<input type="submit" name="deleteRecord" value ="Delete">';
									echo "</form>"; 
						echo 	"</td>";
					echo "</tr>";
			endforeach;
		  
			echo "</table>";
		?>
	</div>
			
<?php include('inc/footer.php'); ?>
