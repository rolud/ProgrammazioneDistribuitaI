<?php
    require_once DIR_PHP_OBJECTS . 'seat.php';

    /**
     * effettua un reindirizzamento
     * @param string $url la pagina a cui reindirizzare
     * @param string $name nome del parametro GET da passare
     * @param string $value valore del parametro GET da passare
     */
    function redirect($url, $name="", $value="") {
        header('HTTP/1.1 307 temporary redirect');
        header('Location: ' . $url . '?' . urlencode($name) . '=' . urlencode($value));
        exit();
    }
    
    /**
     * controlla che l'email sia un'email valida
     * @param string $user email dell'utente
     * @return mixed
     */
    function checkUser($user) {
        return filter_var($user, FILTER_VALIDATE_EMAIL);    
    }
    
    /**
     * controlla che la password soddisfi i requisiti
     * @param string $password
     * @return number 0 se la password non soddisfa i requisiti
     */
    function checkPassword($password) {
        $pattern = '/(?=.{2})(?=.*[a-z])(?=.*[A-Z0-9])/'; 
        return preg_match($pattern, $password);
    }
    
    /**
     * controlla se un posto sia presente in un array di posti
     * @param array $seats_array
     * @param string $id
     * @return Seat|NULL ritorna l'oggetto Seat se trovato, altrimenti null
     */
    function searchSeat($seats_array, $id) {
        foreach ($seats_array as $s) {
            if ($s->getId() == $id) {
                return $s;
            }
        }
        return null;
    }
    
    /**
     * ritorna la classe da assegnare al posto nella mappa in base allo stato del posto
     * (0 libero, 1 prenotato, 2 acquistato)
     * @param string $seatid
     * @param array $seatsarray
     * @param int $nmyseats
     * @return string
     */
    function getSeatClass($seatid, $seatsarray, &$nmyseats) {
        $class = "";
        $logged = false;
        if (userLoggedIn()) $logged = true;
        if (($s = searchSeat($seatsarray, $seatid)) != null) {
            if ($s->getStatus() == 1) {
                if ($logged) {
                    if ($s->getUser() == $_SESSION[SESSION_USERNAME]) {
                        $class = "seat seat-booked-by-me seat-active";
                        $nmyseats++;
                        if (!isset($_SESSION[MY_SEATS])) 
                            $_SESSION[MY_SEATS] = array();
                        $_SESSION[MY_SEATS][$seatid] = 1;
                    } else {
                        $class = "seat seat-booked seat-active";
                        
                    }
                } else {
                    $class = "seat seat-booked";
                }
            } else if ($s->getStatus() == 2) {
                $class = "seat seat-purchased";
            }
        } else {
            if ($logged)
                $class = "seat seat-free seat-active";
            else 
                $class = "seat seat-free";
        }
        return $class;
    }
    
    /**
     * genera stringa casuale di 10 caratteri da aggiungere alla password prima di effettuare l'hash
     * @return string
     */
    function generaSale() {
        $caratteri = '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';
        $sale = '';
        for ($i = 0; $i < 10; $i++)
            $sale .= $caratteri[rand(0, strlen($caratteri) -1)];
        return $sale;
    }
    
    /**
     * sanifica una stringa in input da una richiesta GET/POST che deve essere stampata nella pagina
     * @param string $str
     * @return string
     */
    function sanitizeInput($str) {
        $str = strip_tags($str);
        $str = htmlentities($str);
        return $str;        
    }

?>