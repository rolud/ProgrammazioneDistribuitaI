<?php 
    /**
     * controllo sulla disponibilità dello username
     */
    require_once '../../config.php';
    require_once DIR_PHP_FUNCTIONS . 'session.php';
    require_once DIR_PHP_FUNCTIONS . 'database.php';
    require_once DIR_PHP_FUNCTIONS . 'lib.php';
    
    
    if (isset($_POST['user'])) {
        $userstat = '';
        if (checkUser($_POST['user'])) {
            $conn = dbConnect();
            $user   = secure($conn, $_POST['user']);
            $sql = "SELECT * FROM " . DB_TABLE_USERS . " WHERE " . DB_TABLE_USERS_USER . " = '$user';";
            $res = null;
            try {
            $res = dbQuery($conn, $sql);
            } catch (Exception $e) {
                dbClose($conn);
                return;
            }
            
            if (mysqli_num_rows($res) != 0)
                $userstat =  "<span class='taken'>&nbsp;&#x2718; Lo username '$user' non &egrave; disponibile</span>";
            else
                $userstat = "<span class='available'>&nbsp;&#x2714; Lo username '$user' &egrave; disponibile</span>";
            
            if (isset($res) && $res != null)
                mysqli_free_result($res);
            dbClose($conn);
        } else {
            $userstat = "<span class='taken'>&nbsp;&#x2718; Inserisci una email valida</span>";
        }
        echo $userstat;
    }
?>