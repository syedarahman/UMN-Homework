<!-- Syeda Rahman. Hw 9. 4131.  -->

<?php
  error_reporting('E_All');
  ini_set ('display_errors', '1');
  session_start ();
  include_once 'databaseHW8S16.php';

  $error='';
  $username='';
  $login='';
  $password='';
  $delete_id='';

  if(!empty($_POST['submit'])) {
  $username = trim($_POST['username']);
    if($username == ''){
      $error.= "Please enter a valid value for the Name field. </ br>";
  }
  $login = trim($_POST['login']);
    if($login == ''){
      $error .= "Please enter a valid value for the Login field. </ br>";
  }
    $password = trim($_POST['password']);
    if($password == ''){
      $error.= "Please enter a valid value for the Password field. </ br>";
    }
    
    
  }

  // add new user
  if(($error == '') and isset($_POST['submit'])) {
    $conn = new mysqli($db_servername, $db_username, $db_password, $db_name, $db_port);
    // check connection
    if ($conn->connect_error)  {
      $error.= 'Connection failed: '.$conn->connect_error.'<br>';
    }
    else {
      $sql = "SELECT acc_name, acc_login, acc_password FROM tbl_accounts WHERE acc_login = '$login';";
      $result = $conn->query($sql);
      if($result->num_rows > 0) {
        $error.= "This login already exists. <br>";
      }
      else {
        $sql = "INSERT INTO tbl_accounts (acc_name, acc_login, acc_password) VALUES ('$username', '$login', '". sha1($password)."');";
        if ($conn->query($sql) === TRUE) {
          $error.= "Account added successfully";
        } 
      }
    }
    $conn->close();
  }
  if (isset($_POST['update']) and is_numeric($_POST['update'])) {
    $update_id = $_POST['update'];
    $error_temp = '';
    $new_name = trim($_POST['new_name']);
    if($new_name == ''){
      $error.= "Please enter a valid value for the Name field. <br>";
      $error_temp.= "error found.";
    }
    $new_login = trim($_POST['new_login']);
    if($new_login == ''){
      $error .= "Please enter a valid value for the Login field. <br>";
      $error_temp.= "error found.";
    }
    $new_password = trim($_POST['new_password']);
    if($new_password == ''){
      $error.= "Please enter a valid value for the Password field. <br>";
      $error_temp.= "error found.";
    }
    
    if ($error_temp == '') {
      // connect to the database
      $conn = new mysqli($db_servername, $db_username, $db_password, $db_name, $db_port);
      // check the connection
      if ($conn->connect_error) {
        $error.= 'Connection failed: '.$conn->connect_error.'<br>';
      }
      else {
        $sql1 = "SELECT * FROM tbl_accounts WHERE acc_login = '$new_login';";
        $result = $conn->query($sql1);
        if ($result->num_rows == 0) { // no user
          $sql = "UPDATE tbl_accounts SET acc_name = '$new_name', acc_login = '$new_login', acc_password = '".sha1($new_password)."' WHERE acc_id = '$update_id';";
          $conn->query($sql);
          $error .= "Account updated successfully. <br>";
        }
        else {
          $error .= "This login already exists. <br>";
        }
      }
      $conn->close();
    }
  }
  if (isset($_POST['delete']) and is_numeric($_POST['delete'])) {
    // connect to database
    $conn = new mysqli($db_servername, $db_username, $db_password, $db_name, $db_port);
    // check connection
    if ($conn->connect_error)  {
      $error.= 'Connection failed: '.$conn->connect_error.'<br>';
    }
    $delete_id = $_POST['delete'];
    $sql = "DELETE FROM tbl_accounts WHERE acc_id = '$delete_id'";
    if ($conn->query($sql) === TRUE) {
      $error.= "Account deleted successfully";
    } 
    $conn->close();
  }
?>

<html>
<head>
  <title>Admin Page</title><br>
  <style type="text/css">
    * {
      margin: auto;
    }
    body { 
      padding:10px;
      font-family: calibri;
    }
    div.main {
      background: lightgrey;
      padding: 20px;
      border: 1px solid black;
      width: 800px;
      margin: auto;
      border-radius: 5px;
    }
/*    table.grid {
      width: 75%;
      margin-left: auto;
      margin-right: auto;
      background-color: white;
      border-spacing: 10px;
      border-collapse: separate;
      margin: auto;
    }*/
/*    table.grid td {
      background-color: lightblue;
      padding: 5px;
      border-radius: 5px;
      margin: auto;
    }*/
    table, tr, td, th {
      text-align: center;
      border: 1px solid black;
      color: #336699; 
      background-color: white;
      margin: auto;
    }
    input[type=text], input[type=password]{
      border: 1px solid black;
    }
    #error {
      color: red ;
    }
    div.table {
      position: center;
      margin: auto;
      color: #336699; 
      background-color: white;
    }
  </style>
</head>
<body><br><br>
    <h1 style="text-align:center">HW 9 Admin Page</h1>
      <div>
      <p style="text-align:center"><strong> Welcome <?php echo $_SESSION['user']['name']; ?></strong> </p>
      <p style="text-align:center"><a href="logout.php">Logout</a></p>
      <p style="text-align:center"><a href="admin.php">Admin</a></p>
      <p style="text-align:center"><a href="calendar.php">Calendar</a></p>
     </div><br><br>

    <div class="main" style="text-align:center">
      <h1 style="text-align:center">List of Users</h1>
      <div id = "error" style="text-align:center">
        <?php 
          if ($error != '') {
            echo $error; 
          }
        ?>
      </div><br>

      <?php 
        $conn = new mysqli($db_servername, $db_username, $db_password, $db_name, $db_port);
        // check the connection
        if ($conn->connect_error)  {
          $error.= 'Connection failed: '.$conn->connect_error.'<br>';
        }
        $sql = "SELECT * FROM tbl_accounts;";
        $result = $conn->query($sql);
        echo "<form action='' method='post'>";
        echo "<table cellpadding='2'>"; 
        echo  "<tr>
                <th>ID</th>
                <th>Name</th>   
                <th>Login</th>
                <th>Password</th>
                <th>Action</th>
              </tr>";
        while ($row = $result->fetch_assoc()) {
          echo  "<tr id='".$row['acc_id']."'>";
            echo "<th>".$row['acc_id']."</th>";  
            echo "<th>";
              echo "<div class = 'table'>";
              echo $row['acc_name']; 
              echo "</div>";
              echo "<form action='' method='post'>";
              echo "<div style='display:none;'>";
              echo "  <input type='text' name='new_name'/>";
              echo "</div>";
            echo "</th>";
            echo "<th>";
              echo "<div class = 'table'>";
              echo $row['acc_login'];
              echo "</div>"; 
              echo "<div style='display:none;'>";
              echo "  <input type='text' name='new_login'/>";
              echo "</div>";
            echo "</th>"; 
            echo "<th>"; 
              echo "<div style='display:none;'>";
              echo "<input type='password' name='new_password'/>";
              echo "</div>";  
              echo "</form>"; 
              echo "</th>"; 
            echo "<th><button type='submit' onclick='edit(".$row['acc_id'].")' value='".$row['acc_id']."' />Edit</button>";     
            echo "<button type='submit' name='delete' value='".$row['acc_id']."' />Delete</button>
                 </th>";
          echo  "</tr>";
        }
        $conn->close(); // close connection
        echo "</table>";
        echo "</form>";
  ?>

<!--       <table class="grid">
        <tr>  <th>ID</th>  <th>Name</th>  <th>Login</th>  <th>New Password</th>  <th>Action</th></tr> 
        
        <tr>  <td>1</td>  <td>Jim Smith</td>  <td>Smitty</td>  <td></td>  
          <td><button name="edit" value="1">Edit</button>  
          <button name="delete" value="1">Delete</button></td>
        </tr>

        <tr>
          <td>2</td>  <td>Jane Jones</td>  <td>JJones</td>  <td></td>  
          <td><button name="edit" value="2">Edit</button>  
          <button name="delete" value="2">Delete</button></td>
        </tr> 
      </table> 
    </div>
    <p></p> -->

      <br><br><h1 style="text-align:center">Add New User</h1>
      <form action = "admin.php" method = "post" style="margin: auto">
      Name: <input type="text" name="username" style="text-align:center"> <br><br>
      Login: <input type="text" name="login"style="text-align:center"><br><br>
      Password: <input type="password" name="password" style="text-align:center"><br><br>
     <input name="submit" type="submit" value="Add User"> 
  </form> <br><br>
    
</div> <!-- close main -->

<script type = "text/javascript">
  function edit(num) {
    var str1 = "<th>"+num+"</th> <form action='' method='post'><th><input type='text' name='new_name'></th><th><input type='text' name='new_login'></th><th><input type='password' name='new_password'></th>  <th><button name = 'update' type='submit' value="+num+">Update</button></form>  <form action = 'admin.php'> <button type='submit'>Cancel</button></form></th>";
    document.getElementById(num).innerHTML = (str1);
  }
</script>

</body>
</html>