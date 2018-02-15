<?php

	$host = 'host';
	$user = 'user';
	$password = 'password';
	$name_db = 'name_db';
    
	mysql_connect($host, $user, $password) or die ('Nie można połączyć się z Mysql');
	mysql_select_db ($name_db) or die ('Nie można wybrać bazy');
	mysql_query("SET NAMES 'utf8'");
	mysql_query("SET CHARACTER_SET 'utf8_general_ci'");
	
?>