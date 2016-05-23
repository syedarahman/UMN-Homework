<?php
    error_reporting('E_All');
    ini_set ('display_errors', '1');
    session_start ();
    if (isset($_SESSION['user']['id'])) {
        header('Location: calendar.php');
        exit ();
    }

    $login = '';
    $username = '';
    $error = '';

    if (!empty($_POST)) 
    {
        if(!empty ($_POST['login']))
        {
            $login = trim($_POST['login']);
            if($login == '') 
            {
                $error .= 'Please enter a valid username for User Login field. </br >';
            }
        }
        if (!empty ($_POST)) 
        {
            $username = trim($_POST['username']);
            if($username == '') 
            {
                $error .= 'Please enter a valid username for the Username field. </br >';
            }
        }
        if (!empty ($_POST)) 
        {
            $password = trim($_POST['password']);
            if($password == '') 
            {
                $error .= 'Please enter a valid password for the Password field. </br >';
            }
        }
    }   

    include_once 'databaseHW8S16.php';
    $conn = new mysqli($db_servername, $db_username, $db_password, $db_name, $db_port);
    if($conn -> connect_error) 
    {
        $error .= 'mySQLerror' . $conn -> connect_error. '<br>';
    }
    else 
    {
        $sql_query = 'SELECT * FROM tbl_accounts WHERE acc_login = \''.$login. '\' LIMIT 1;';
        $result = $conn -> query ($sql_query);

        if($result -> num_rows == 1) 
        {
            if($row = $result -> fetch_assoc())
            {
                $hashed_password = $row['acc_password'];
                if (sha1($password) == $hashed_password)
                {
                    $_SESSION['user']['id'] = $row['acc_id'];
                    $_SESSION['user']['name'] = $row['acc_name'];

                    $conn -> close ();
                    header ('Location: calendar.php');
                    exit();  
                }
                else 
                {
                    $error .= 'Password is incorrect. Please check the password and try again! </br >';
                }
            }
        }
        else 
        {
            $error .= 'Username is incorrect. Please check the username and try again! </br >';
        }
    }
?>

<!DOCTYPE html>
<html>
<head>
    <style type="text/css">
          .main {
            border: 1px solid black;
            margin: auto;
            text-align: center;
            width: 400px;
          }
          #form {
            padding: 10px 10px 10px 10px;
          }
        </style>
    </style>
</head>
<body>
    <div class = "main">
        <h1>Login Page </h1>
        <div style = "color: red">
            <?php echo $error; ?>
        </div>
        <p>Please enter your user's login name and password. Both values are case sensitive.</p>
        <form method ="post" action="login.php">
            <label for = "user"> <strong>Login:</strong> </label>
            <input type = "text" name = "login" value = "<?php echo htmlentities ($login); ?>" >
            <br/><br/>
            <label for="user"> <strong>Password:</strong> </label>
            <input type= "text" name="password" value="" />
            <br /><br />
            <input type = "submit" value="Submit" />
        </form>
   </div>
</body>
</html>

