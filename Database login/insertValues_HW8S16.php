
<?php
	error_reporting(E_ALL); 
	ini_set( 'display_errors','1'); 
	$con= mysqli_connect('egon.cs.umn.edu','S16CS4131U87','10902','S16CS4131U87','3307');
	// Check connection
	if (mysqli_connect_errno())
	{
		echo 'Failed to connect to MySQL:' . mysqli_connect_error();
	}
	echo sha1('JJ123'); //sha1 encrypts pass for user Smitty
	echo sha1('JJ456');

	$str1 = "JJ123";
	$str2 = "JJ456";

	mysqli_query($con,"INSERT INTO tbl_accounts (acc_name, acc_login, acc_password) VALUES ('John Smith', 'Smitty', '". sha1($str1)."');");
	mysqli_query($con,"INSERT INTO tbl_accounts (acc_name, acc_login, acc_password) VALUES ('Jane Jones', 'JJones', '". sha1($str2)."');");

	mysqli_close($con);

	echo '<h1> Successfully Inserted Values into the Table </h1>'
?> 
