<?php
//redirects the user to the appropriate page
				if($_POST['choice']=="1"){
					header('Location: modplayer.php'); 
				}else if($_POST['choice']=="2"){
					header('Location: viewplayer.php'); 
				}else if($_POST['choice']=="3"){
					header('Location: modjob.php'); 
				}else if($_POST['choice']=="4"){
					header('Location: viewjob.php'); 
				}else if($_POST['choice']=="5"){
					header('Location: modworld.php'); 
				}else if($_POST['choice']=="6"){
					header('Location: viewworld.php'); 
				}else if($_POST['choice']=="7"){
					header('Location: moditem.php'); 
				}else if($_POST['choice']=="8"){
					header('Location: viewitem.php'); 
				}
?>
