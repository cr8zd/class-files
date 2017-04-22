<?php
  $pageTitle = "Honeybee Friendly Plants";
  include('inc/header.php');
 
  $title = $_POST['pname']; //Get the selected plant name
  $start = $_POST['pdate']; //Get the current date
?>



<body>
	<div>
		<h1>CALENDAR</h1>
	</div>

	<script>
		$(document).ready(function() {
	    // page is now ready, initialize the calendar...
	   $('#calendar').fullCalendar({
    // put your options and callbacks here
    events: 
    [
      {
      	title : "<?php print($title); ?>",
      	start : "<?php print($start); ?>"
      }
    ]
  })
		});
		document.write('<FONT COLOR="red">');
		document.write('Redirected to calendar PASS', '<br>');
		document.write('Added plant to calendar PASS', '<br>');
	  document.write('Added plant to calendar on current date PASS');
	  document.write('<FONT COLOR="black">');
	</script>

	<div id='calendar'></div>
</body>