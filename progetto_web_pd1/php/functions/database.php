<?php
    
    function dbConnect() {
        $link = mysqli_connect(DB_HOST, DB_USERNAME, DB_PASSWORD, DB_NAME);
        if (mysqli_connect_errno()) {
            redirect("./error.php", "error", mysqli_connect_error());        
        }
        return $link;
    }

    function dbQuery($link, $query) {
        $result = mysqli_query($link, $query);
        if (!$result) {
            throw new Exception(mysqli_error($link));
        }
        return $result;
    }

    function dbClose($link) {
        mysqli_close($link);
    }

    function dbStartTransaction($link) {
        mysqli_autocommit($link, false);
    }

    function dbEndTransaction($link) {
        if (!mysqli_commit($link)) throw new Exception('Commit fallito');
        mysqli_autocommit($link, true);
    }

    function dbRollback($link) {
        mysqli_rollback($link);
        mysqli_autocommit($link, true);
    }
    
    function secure($link, $str) {
        $str = strip_tags($str);
        $str = htmlentities($str);
        $str = stripcslashes($str);
        return mysqli_real_escape_string($link, $str);
    }
?>