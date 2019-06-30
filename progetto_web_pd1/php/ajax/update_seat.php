<?php
    require_once '../../config.php';
    require_once DIR_PHP_FUNCTIONS . 'session.php';
    require_once DIR_PHP_FUNCTIONS . 'database.php';
    require_once DIR_PHP_FUNCTIONS . 'lib.php';
    
    sessionStart();
    if (!userLoggedIn()) {
        redirect('../../login.php');
    }
    
    
    $user = $_SESSION['user'];
    if ($_SESSION[NUM_MY_SEATS]) {
        $nseat = $_SESSION[NUM_MY_SEATS];
    } else {
        $nseat = 0;
    }
    
    if (!isset($_SESSION[MY_SEATS]))
        $_SESSION[MY_SEATS] = array();

    if (isset($_POST['id']) && $_POST['id'] != "") {
         
    
        $conn = dbConnect();
        
        $id = secure($conn, $_POST['id']);
        
        $class = "";
        $msg = "";
        
        try {
            
            dbStartTransaction($conn);
            $sql = "SELECT * FROM " . DB_TABLE_USERS . " FOR UPDATE;";
            $res = dbQuery($conn, $sql);
            
            $sql = "SELECT * FROM " . DB_TABLE_SEATS . " WHERE " . DB_TABLE_SEATS_ID . " = '$id';";
            
            $res = dbQuery($conn, $sql);
            
            if (mysqli_num_rows($res) == 0) { /* posto non presente in db, posso prenotarlo */
                $sql = "INSERT INTO " . DB_TABLE_SEATS . "(" . DB_TABLE_SEATS_ID . "," . DB_TABLE_SEATS_USER . "," . DB_TABLE_SEATS_STATUS . ")" . 
                       "VALUE ('$id', '$user', 1);";
                if (!dbQuery($conn, $sql)) throw new Exception("Update query error");
                $class = "seat seat-booked-by-me seat-active";
                $msg = "Hai prenotato il posto $id.";
                $nseat++;
                $_SESSION[MY_SEATS][$id] = 1;
            } else {
                $row = mysqli_fetch_row($res);
                if ($row[2] == 1) {   /* posto già prenotato */
                    if ($row[1] == $user) { /* se già prenotato da me lo libero */
                        $sql  = "DELETE FROM " . DB_TABLE_SEATS . " WHERE " . DB_TABLE_SEATS_ID . " = '$id';";
                        if (!dbQuery($conn, $sql)) throw new Exception("Delete query error");   
                        $class = "seat seat-free seat-active";
                        $msg = "Hai annullato la prenotazione del posto $id.";
                        $nseat--;
                        $_SESSION[MY_SEATS][$id] = 0;
                    } else{  /* se prenotato da un altro*/  
                        $sql  = "UPDATE " . DB_TABLE_SEATS . " SET " . DB_TABLE_SEATS_USER . " = '$user' WHERE " . DB_TABLE_SEATS_ID . " = '$id';";
                        if (!dbQuery($conn, $sql)) throw new Exception("Update query error");
                        $class = "seat seat-booked-by-me seat-active";
                        $msg = "Hai prenotato il posto $id.";
                        $nseat++;
                        $_SESSION[MY_SEATS][$id] = 1;
                    } // TODO gestire se voglio liberare un mio posto ma non è più prenotato da me
                } else if ($row[2] == 2) {
                    $class = "seat seat-purchased";
                    $msg = "Qualcun altro ha acquistato il posto $id.";
                }
            }
            
            dbEndTransaction($conn);
            
            mysqli_free_result($res);
            
        } catch (Exception $e) {
            dbRollback($conn);
        }
        
//         mysqli_free_result($res);
        
        dbClose($conn);
        
        $_SESSION[NUM_MY_SEATS] = $nseat;
        echo '{"classname":"' . $class . '","msg":"' . $msg . '"}';
    }
?>