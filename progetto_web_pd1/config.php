<?php
    /*
     * DIRECTORY NAME COSTANTS
     */
    define('DIR_BASE', __DIR__ . '/');
    define('DIR_PHP', DIR_BASE . 'php/');
    define('DIR_CSS', DIR_BASE . 'css/');
    define('DIR_JS', DIR_BASE . 'js/');
    define('DIR_IMG', DIR_BASE .'img/');
    define('DIR_ICON', DIR_BASE . 'material-icons/');
    define('DIR_PHP_FRAGMENTS', DIR_PHP . 'fragments/');
    define('DIR_PHP_FUNCTIONS', DIR_PHP . 'functions/');
    define('DIR_PHP_OBJECTS', DIR_PHP . 'objects/');
    
    /*
     * DATABASE COSTANTS
     */
    define('DB_NAME', 's267537');
    define('DB_PASSWORD', 'mblierym');
    define('DB_USERNAME', 's267537');
    define('DB_HOST', 'localhost');
    
    define('DB_TABLE_USERS', 'Users');
    define('DB_TABLE_USERS_USER', 'usr');
    define('DB_TABLE_USERS_PASSWORD', 'pwd');
    define('DB_TABLE_USERS_SALE', 'sale');
    define('DB_TABLE_SEATS', 'Seats');
    define('DB_TABLE_SEATS_ID', 'id');
    define('DB_TABLE_SEATS_USER', 'usr');
    define('DB_TABLE_SEATS_STATUS', 'stat');
    
    /*
     * COOKIES NAME COSTANTS
     */
    define('SESSION_USERNAME', 'user');
    define('SESSION_LAST_INTERACTION', 'last_interaction');
    
    define('SESSION_TIMEOUT', 120); // 2 min
    define('MY_SEATS', 'my_seats');
    define('NUM_MY_SEATS', 'num_my_seats');
    
    /*
     * 
     */
    define('AIRPLANE_ROWS', 10);
    define('AIRPLANE_COLUMNS', 6);
?>