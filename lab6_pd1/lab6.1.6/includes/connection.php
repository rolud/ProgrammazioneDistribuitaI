<?php
function connect_db() {
    $server = "localhost";
    $user = "root";
    $password = "";
    $db = "market";
    
    $link = mysqli_connect($server, $user, $password, $db);
    if (mysqli_connect_errno()) {
        die ("Error: " . mysqli_connect_error());
    }
    
    return $link;
}

function query_db($link, $query) {
    $result = mysqli_query($link, $query);
    if (!$result) {
        die("Error: " . mysqli_error($link));
    }
    return $result;
}
?>