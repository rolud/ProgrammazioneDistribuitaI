<?php
    require_once 'config.php';
    require_once DIR_PHP_FUNCTIONS . 'session.php';
    require_once DIR_PHP_FUNCTIONS . 'database.php';
    require_once DIR_PHP_FUNCTIONS . 'lib.php';
    require_once DIR_PHP_FUNCTIONS . 'use_https.php';    
    
    sessionStart();
    
    if (!userLoggedIn()) {
        redirect('login.php');
    }
    
    $user = $_SESSION[SESSION_USERNAME];
    $msg = "";
    //var_dump($_SESSION[MY_SEATS]);
    
    $conn = dbConnect();

    try {
        
        dbStartTransaction($conn);
        $sql = "SELECT * FROM " . DB_TABLE_SEATS . " FOR UPDATE;";
        $res = dbQuery($conn, $sql);
        $db_seats = array();
        if (mysqli_num_rows($res) != 0) {
            while ($row = mysqli_fetch_array($res)) {
                $db_seats[$row[0]] =  new Seat($row[0], $row[1], $row[2]);
                echo $row[0] . " >> " .$row[1] . " >> " . $row[2] . "<br>";
            }
        }
        
        if (isset($_SESSION[MY_SEATS]) && !empty($_SESSION[MY_SEATS])) {
            $compro = true;
            foreach ($_SESSION[MY_SEATS] as $key => $value) {
                echo $key . " => " . $value . "<br>";
                if ($value == 1) {
                    if (isset($db_seats[$key]) && $db_seats[$key]->getUser() != $_SESSION[SESSION_USERNAME]) {
                        $compro = false;
                    } 
                }
            }
            if ($compro) {
                foreach ($_SESSION[MY_SEATS] as $key => $value) {
                    if ($value == 1) {
                        $sql = "INSERT INTO " . DB_TABLE_SEATS . "(" . DB_TABLE_SEATS_ID . "," . DB_TABLE_SEATS_USER . "," . DB_TABLE_SEATS_STATUS . ")
                                VALUE ('$key', '$user', 2)
                                ON DUPLICATE KEY UPDATE " . DB_TABLE_SEATS_STATUS . " = 2;";
                        dbQuery($conn, $sql);
                    }
                }
                $msg = "Hai completato l'acquisto dei tuoi posti.";
            } else {
                $sql  = "DELETE FROM " . DB_TABLE_SEATS . " WHERE " . DB_TABLE_SEATS_USER . " = '$user' AND " . DB_TABLE_SEATS_STATUS .  " != 2;";
                $res = dbQuery($conn, $sql);
                $msg = "Alcuni dei tuoi posti non sono più disponibili. Tutti i posti che avevi prenotato sono stati liberati";
            }
        }
        
        unset($_SESSION[MY_SEATS]);
        

        
//         if (mysqli_num_rows($res) == $_SESSION[NUM_MY_SEATS] ) { /* acquisto i posti */
//             $sql  = "UPDATE " . DB_TABLE_SEATS . " SET " . DB_TABLE_SEATS_STATUS . " = 2 WHERE " . DB_TABLE_SEATS_USER . " = '$user' AND " . DB_TABLE_SEATS_STATUS .  " != 2;";
//             $res = dbQuery($conn, $sql);
//             $msg = "Hai completato l'acquisto dei tuoi posti.";
//         } else {
//             $sql  = "DELETE FROM " . DB_TABLE_SEATS . " WHERE " . DB_TABLE_SEATS_USER . " = '$user' AND " . DB_TABLE_SEATS_STATUS .  " != 2;";
//             $res = dbQuery($conn, $sql);
//             $msg = "Alcuni dei tuoi posti non sono pi&ugrave; disponibili. Tutti i posti che avevi prenotato sono stati liberati";
//         }
        
        
        
        dbEndTransaction($conn);
    } catch (Exception $e) {
        dbRollback($conn);
    }
    
    dbClose($conn);
    
    redirect('index.php', 'msg', $msg);
?>