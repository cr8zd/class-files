<?php
    $pageTitle = "Honeybee Friendly Plants";
    include('inc/header.php');
    
    if(isset($_POST['record_plant'])) {
        $commonName = $_POST['commonName'];
        $sciName = $_POST['sciName'];
        $zone = $_POST['zone'];
        $light = $_POST['light'];
        $information = $_POST['information'];
    
    
    //Unit testing on form input.
		if(!empty($commonName)) {
			$error_msg1 = "PASS common name not empty.<br>";
		}
		else{
			$error_msg1 = "FAIL common name empty.<br>";
		}
		if(!empty($sciName)) {
			$error_msg2 = "PASS scientific name not empty.<br>";
		}
		else{
			$error_msg2 = "FAIL scientific name empty.<br>";
		}
		if(!empty($zone)) {
			$error_msg3 = "PASS zone not empty.<br>";
		}
		else{
			$error_msg3 = "FAIL zone empty.<br>";
		}
		if(!empty($light)) {
			$error_msg4 = "PASS light not empty.<br>";
		}
		else{
			$error_msg4 = "FAIL light empty.<br>";
		}
		if(!empty($information)) {
			$error_msg5 = "PASS information not empty.<br>";
		}
		else{
			$error_msg5 = "FAIL information empty.<br>";
		}
		
		//check if form inputs are empty
			if(empty($commonName)) {
			$error_msg = "A common name is required.<br>";
			$valid = 0;
		}
		else if(empty($sciName)) {
			$error_msg = "A scientific name is required.<br>";
			$valid = 0;
		}
		else if(empty($zone)) {
			$error_msg = "A zone is required.<br>";
			$valid = 0;
		}
		else if(empty($light)) {
			$error_msg = "Light is required.<br>";
			$valid = 0;
		}
		else if(empty($information)) {
			$error_msg = "Information is required.<br>";
			$valid = 0;
		}
		else{
		    $valid=1;
		}
    
		if($valid != 0 ) {
        	$stmt = $mysqli->prepare
            	("INSERT INTO Plants (commonName, sciName, zone, light, information)
             	VALUES (?, ?, ?, ?, ?)");
         	$stmt->bind_param('sssss', $commonName, $sciName, $zone, $light, $information);
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
    
    
    //update plant to Plants table
    if(isset($_POST['update_plant'])) {
        $commonName = $_POST['commonName'];
        $sciName = $_POST['sciName'];
        $zone = $_POST['zone'];
        $light = $_POST['light'];
        $information = $_POST['information'];
        $plant_id = $_POST['id'];
    
    
    
    //unit testing
    	if(!empty($commonName)) {
			$error_msg6 = "PASS common name not empty.<br>";
		}
		else{
			$error_msg6 = "FAIL common name empty.<br>";
		}
		 if(!empty($sciName)) {
			$error_msg7 = "PASS scientific name not empty.<br>";
		}
		else{
			$error_msg7 = "FAIL scientific name empty.<br>";
		}
		 if(!empty($zone)) {
			$error_msg8 = "PASS zone not empty.<br>";
		}
		else{
			$error_msg8 = "FAIL zone empty.<br>";
		}
		 if(!empty($light)) {
			$error_msg9 = "PASS light not empty.<br>";
		}
		else{
			$error_msg9 = "FAIL light empty.<br>";
		}
		 if(!empty($information)) {
			$error_msg10 = "PASS information not empty.<br>";
		}
		else{
			$error_msg10 = "FAIL information empty.<br>";
		}
    
    //check if form inputs are empty
			if(empty($commonName)) {
			$error_msg = "A common name is required.<br>";
			$valid = 0;
		}
		else if(empty($sciName)) {
			$error_msg = "A scientific name is required.<br>";
			$valid = 0;
		}
		else if(empty($zone)) {
			$error_msg = "A zone is required.<br>";
			$valid = 0;
		}
		else if(empty($light)) {
			$error_msg = "Light is required.<br>";
			$valid = 0;
		}
		else if(empty($information)) {
			$error_msg = "Information is required.<br>";
			$valid = 0;
		}
		else{
		    $valid=1;
		}
    
    
    
    	if($valid != 0 ) {
        	$stmt = $mysqli->prepare
            	("UPDATE Plants SET commonName = ?, sciName = ?, zone = ?, light = ?, information = ?
  				WHERE id = $plant_id");
             
         	$stmt->bind_param('sssss', $commonName, $sciName, $zone, $light, $information);
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


        //delete from Plants table
    if(isset($_POST['deleteRecord'])){
		$plant_id = $_POST['id'];
		if(!($stmt = $mysqli->prepare("DELETE FROM Plants WHERE id = '$plant_id'"))){
			echo "Prepare failed: (" . $mysqli->errno . ") " . $mysqli->error;
		}
		if(!$stmt->execute()){
			$error_msgD = "FAIL could not delete.";
		}
		else{
			$error_msgD = "PASS deleted row.";
		}
	}
    
    
    
    $query = "SELECT id, commonName, sciName, zone, light, information
			  FROM Plants ORDER BY commonName ASC";
	$plants = $mysqli->query($query);
	
?>

<div id="intro">
	<h2>Honeybee Friendly plants</h2>
	<p>Add a Honeybee Friendly Plant Here.</p>
</div>

<div>
    <h2>Add a New Plant</h2>
    <form action="plants.php" method="post">
        <table>
            <tr>
                <th>
                    <label for "commonName"> Common Name</label>
                </th>
                <td>
                    <input type="text" name="commonName">
                </td>
            </tr>
            <tr>
                <th>
                    <label for "sciName">Scientific Name</label>
                </th>
                <td>
                    <input type ="text" name="sciName">
                    
                </td>
            </tr>
            <tr>
                <th>
                    <label for "zone">Zone</label>
                </th>
                <td>
                    <input type="text" name="zone">
                </td>
            </tr>
            <tr>
                <th>
                    <label for "light">Light</label>
                </th>
                <td>
                    <input type="text" name="light">
                </td>
            </tr>
            <tr>
                <th>
                    <label for "information">Information</label>
                </th>
                <td>
                     <textarea required name="information" cols="22" rows="5" class="form-control"></textarea>
                </td>
            </tr>
        </table>
        	<div id="record_btn">
			<input type="submit" name="record_plant" value="ADD">
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
		?>
		</div>
    </form>
    
   <form action="plants.php" method="post">
       <table>
           <tr>
               <th>
                   <label for "id">Which plant do you want to edit?</label>
               </th>
               <td>
                   <select name="id">
                       <?php foreach ($plants as $plant) :
                           echo '<option value="' . $plant['id'] . '">' .
                           $plant['commonName']. ' ' . $plant['sciName'] . '</option>';
                        endforeach;
                        ?>
                   </select>
               </td>
           </tr>
           <tr>
               <th>
                   <label for"commonName">Common Name</label>
               </th>
               <td>
                   <input type="text" name="commonName">
               </td>
           </tr>
           <tr>
               <th>
                   <label for"sciName">Scientific Name</label>
               </th>
               <td>
                   <input type="text" name="sciName">
               </td>
           </tr>
           <tr>
               <th>
                   <label for"zone">Zone</label>
               </th>
               <td>
                   <input type="text" name="zone">
               </td>
           </tr>
           <tr>
               <th>
               <label for"light">Light</label>
               </th>
               <td>
                   <input type="text" name="light">
               </td>
           </tr>
             <tr>
               <th>
               <label for"information">Information</label>
               </th>
               <td>
                  
                   <textarea required name="information" cols="22" rows="5" class="form-control"></textarea>
               </td>
           </tr>
       </table>
       	<div id="record_btn">
			<input type="submit" name="update_plant" value="UPDATE">
		</div>
		<div id="err">
			<?php
				if(!empty($error_msg))
				{
					echo $error_msg;
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
				if(!empty($error_msg9))
				{
					echo $error_msg9;
				}
				if(!empty($error_msg10))
				{
					echo $error_msg10;
				}
			?>
		</div>
   </form>
</div>


    <div>
        <h2>Show All Plants</h2>
        
        <?php
            echo "<table>";
                echo "<tr>";
                    echo "<th>Common Name</th>";
					echo "<th>Scientific Name</th>";
					echo "<th>Zone</th>";
					echo "<th>Light</th>";
					echo "<th>Information</th>";
				    echo "<th>Action</th>";
				echo "</tr>";
				
	        foreach ($plants as $plant) :
	            echo "<tr>";
	                echo	"<td>" . $plant['commonName'] . "</td>";
					echo	"<td>" . $plant['sciName'] . "</td>";
					echo	"<td>" . $plant['zone'] . "</td>";
					echo	"<td>" . $plant['light'] . "</td>";
					echo	"<td>" . $plant['information'] . "</td>";
					echo	"<td>"; 
		          		echo '<form action="calendar.php" method="post">';?>
								<input type ="hidden" name="pname" value="<?php echo $plant['commonName']; ?>">
								<input type ="hidden" name="pdate" value="<?php echo date('Y-m-d'); ?>">
								<?php echo '<input type="submit" name="addtocalendar" value ="Add to Calendar">';
						echo "</form>";
					echo 	"</td>";
					echo	"<td>"; 
	                        echo '<form action="plants.php" method="post">';?>
										<input type ="hidden" name="id" value="<?php echo $plant['id']; ?>">
										<?php echo '<input type="submit" name="deleteRecord" value ="Delete">';
										echo "</form>"; 
							echo 	"</td>";
						echo "</tr>";
			endforeach;
		  
			echo "</table>";
		?>
    </div>
    
<?php include('inc/footer.php'); ?>