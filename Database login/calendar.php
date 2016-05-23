<?php
	session_start ();
	if (!isset($_SESSION['user']['id'])) 
	{
		header('Location: login.php');
		exit ();
	}
?>

<!DOCTYPE html>
<html>
  	<head>
    <meta charset='charset=utf-8'>
    <title>Logout html test</title>
    <style type="text/css">
        tr {
            height: 80px;
            text-align: center;
        }
        th {
            font-size: 18px;
            color: black;
        }
        td {
            color: black;
            border: 1px ;
            width: 130px;
            border-radius: 5px;
            background-color: #aaf0d1;
            border-color: #3abda0;
        }
        table {
            background-color: white;
            margin: 0px auto;
            border: 1px solid black;
            padding: 10px 10px 10px 10px;
        }
        p {
            margin: 0px auto;
            text-align: center;
        }
        #notes {
            font-family: italics;
            text-align: center;
        }
        html, body {
            height: 75%;
            margin: 0;
            padding: 0;  
        }
    </style>
  	</head>

	<body>
		<!-- Title -->
		<h1 style="text-align:center">HW 9 Calendar</h1>
	    <div>
		  <p><strong> Welcome <?php echo $_SESSION['user']['name']; ?></strong> </p>
		  <p><a href="logout.php">Logout</a></p>
		  <p><a href="admin.php">Admin</a></p>
		 </div><br>
		<!-- Calendar table -->
		<table>
	        <tr> 
	            <td><span style="font-weight:bold">Monday</span></td>
	            <td><p><em>10-12</em></p>
	                <p>Research meeting</p>
	                <p><a id="one" class="popper" popbox="pop">Nicholson Hall</a></p>
	            </td>		
	            <td><p><em>1:00-4:00pm</em></p>
	                <p>Work</p>
	                <p><a id="two" class="popper" popbox="pop">Keller</a></p>
	            </td>
	            <td></td>
	        </tr>
	        <tr>
	            <td><span style="font-weight:bold">Tuesday</span></td>
	            <td></td>
	            <td></td>
	            <td></td>
	        </tr> 
	        <tr>
	            <td><span style="font-weight:bold">Wednesday</span></td>
	            <td><p><em>1-2pm</em></p>
	                <p>Lunch date with the Jonas Brothers</p>
	                <p><a id="two" class="popper" popbox="pop">Keller</a></td>	</p>	
	            <td><p><em>3-4pm</em></p>
	                <p>OS lec</p>
	                <p><a id="two" class="popper" popbox="pop">Keller</a></td></td></p>
	            <td><p><em>8-9pm</em></p>
	                <p>Study group</p>
	                <p><a id="three" class="popper" popbox="pop">Pillsbury</a></p>
	            </td>
	        </tr>
	        <tr>
	            <td><span style="font-weight:bold">Thursday</span></td>
	            <td><p><em>10-12</em></p>
	                <p>Research meeting</p>
	                <p><a id="one" class="popper" popbox="pop">Nicholson Hall</a></p></td>
	            <td><p><em>8-9pm</em></p>
	                <p>Study group</p>
	                <p><a id="three" class="popper" popbox="pop">Pillsbury</a></p>
	            </td>
	            <td></td>
	        </tr>
	        
	        <tr>
	            <td><span style="font-weight:bold">Friday</span></td>
	            <td></td>
	            <td></td>
	            <td></td>
	        </tr>
		</table> <br/>
	    <div id="notes"> * Used Chrome to test.</div> <br><br>
	</body>

</html>