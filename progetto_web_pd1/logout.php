<?php
    include 'config.php';
    include DIR_PHP_FUNCTIONS . 'session.php';
    include DIR_PHP_FUNCTIONS . 'lib.php';
    
    sessionStart();
    logout();
    redirect("index.php", "logout");
?>
    