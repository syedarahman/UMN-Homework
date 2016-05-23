<?php
session_start ();
if (isset($_SESSION['user']['id'])) {
   unset($_SESSION['user']);
}
 header('Location: login.php');
 exit ();
?>