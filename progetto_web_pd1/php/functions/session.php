<?php
    
    /**
     * start session if isn't started yet
     */
    function sessionStart() {
        if (!isset($_SESSION)) {
            session_start();
        }
    }

    /**
     * deletes cookies and destroy actual session
     */
    function logout() {
        $_SESSION = array();
        if (ini_get('session.use_cookies')) {
            $params = session_get_cookie_params();
            setcookie(session_name(), '', time() - 3600*24, 
                      $params['path'], $params['domain'], 
                      $params['secure'], $params['httponly']);
        }
        session_destroy();
    }

    /**
     * check if the user is logged
     * 
     * @return boolean
     */
    function userLoggedIn() { 
        //echo $_SESSION['user'];
        // TODO implement expiration time
        if (isset($_SESSION[SESSION_USERNAME])) {
            if (!isSessionExpired()) {
                return true;
            } else {
                redirect("login.php", "msg", "Session expired");
            }
        } else {
            return false;
        }
    }
    
    function isSessionExpired() {
        $t = time();
        $diff = 0;
        $new = false;
        $expired = false;
        
        if (isset($_SESSION)/*isset($_COOKIE[SESSION_LAST_INTERACTION])*/) {
            $t0 = $_SESSION[SESSION_LAST_INTERACTION];
            //$t0 = $_COOKIE[SESSION_LAST_INTERACTION];
            $diff = $t - $t0;
        } else {
            $new = true;
        }
        
        if ($new || ($diff > SESSION_TIMEOUT)) {
            logout();
            $expired = true;    
        } else {
            $_SESSION[SESSION_LAST_INTERACTION] = time();
            //$_COOKIE[SESSION_LAST_INTERACTION] = time();
        }
        
        return $expired;
    }
?>