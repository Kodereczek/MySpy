<?php
	
	include('config.php');
	include('connect.php');
	
	if(MD5($_POST['random'].MYSPY_KEY) == $_POST['code'])
	{
		$device = $_POST['device'];
		$result = mysql_fetch_array(mysql_query("SELECT `delete`, `update`, `reset` FROM `Devices` WHERE `nameCrc32` = '$device'"));
		if($result['delete'] > 0 || $result['update'] > 0 || $result['reset'] > 0) mysql_query("UPDATE `Devices` SET `delete` = '0', `update` = '0', `reset` = '0' WHERE `nameCrc32` = '$device'");
		
		echo $result['delete'].':'.$result['update'].':'.$result['reset'];
	}
	else echo '0';
	
?>