<?php
    /**
     * pagina di registrazione
     */
    require_once 'config.php';
    require_once DIR_PHP_FUNCTIONS . 'session.php';
    require_once DIR_PHP_FUNCTIONS . 'database.php';
    require_once DIR_PHP_FUNCTIONS . 'lib.php';
    require_once DIR_PHP_FUNCTIONS . 'use_https.php';
    
    sessionStart();
    if (userLoggedIn()) {
        redirect('index.php');
    }
    
    $login_error = "";
    
    $conn = dbConnect();
    
    if(isset($_POST['submit_signup'])) {
        try {
            if( $_POST['username_signup'] == "" || $_POST['password_signup'] == "") {
                throw new Exception("All field are required.");
            }
            
            if (!checkUser($_POST['username_signup'])) {
                throw new Exception("Forbidden characters in username.");
            }
            if (!checkPassword($_POST['password_signup'])) {
                throw new Exception("La password deve contenere un carattere alfabetico minuscolo e un altro carattere alfabetico minuscolo o un numero.");
            }
            
            $user = secure($conn, $_POST['username_signup']);
            $sale = generaSale();
            $password = md5($_POST['password_signup'] . $sale);
            

            dbStartTransaction($conn);
            $sql = "SELECT * FROM " . DB_TABLE_USERS . " FOR UPDATE;";
            $res = dbQuery($conn, $sql);
            $sql = "SELECT * FROM " . DB_TABLE_USERS . " WHERE " . DB_TABLE_USERS_USER . " = '$user';";
            $res = dbQuery($conn, $sql);
            if (mysqli_num_rows($res) != 0) {
                throw new Exception("Utente gi&agrave; esistente.");
            }
            
            $sql = "INSERT INTO " . DB_TABLE_USERS . " (" . DB_TABLE_USERS_USER . ", " . DB_TABLE_USERS_PASSWORD . "," . DB_TABLE_USERS_SALE . ") VALUE ('$user','$password','$sale');";
            if (!dbQuery($conn, $sql)) {
                throw new Exception("Insert error");
            }
            dbEndTransaction($conn);
            
            
            $_SESSION[SESSION_USERNAME] = $user;
            $_SESSION[SESSION_LAST_INTERACTION] = time();
            
            redirect('index.php');
            
        } catch (Exception $e) {
            $login_error = $e->getMessage();
            dbRollback($conn);
        }
    }
    
    dbClose($conn);

?>
<!DOCTYPE html>
<html lang="it">
<head>  
    <?php require_once './php/fragments/head_tags.php'; ?>
</head>
<body class="bg">
    <script type="text/javascript">
    	if (!checkCookie()) {
    		$('body').append('<div id="over"><div id="info_alert" class="cookie-alert text-center" role="alert">Per poter utilizzare il sito devi attivare i cookie</div></div>');
    	}
    </script>
    <?php require_once('./php/fragments/header.php'); ?>
  
    <div style="padding-top: 20px" class="container" role="main">
        <div class="row">
            <div class="col-sm-3">
                <?php require_once('./php/fragments/sidebar.php'); ?>                
            </div>
            <div class="col-sm-6">
            	<div id='login_block'>
            		<h5 class="card-header text-center page-content-title">Registrati</h5>
            		<?php if ($login_error != ""):?>
            			<div class="alert alert-danger text-center" role="alert">
            				<strong><?php echo $login_error; ?></strong>
            			</div>
            		<?php endif; ?>
                    <form id='signup' action='registrazione.php' method='POST'>
                    	<div class="form-group">
                    		<label for='email'>Email</label>
                    		<input type='email' class='form-control' name='username_signup' placeholder='esempio@email.com' onkeyup='checkUser(this)' onmouseenter="viewDescription('Lo username deve essere una email valida.')" onmouseleave="hideDescription()" required>
                    		<div id="user_stat"></div>
                    	</div>
                    	<div class="form-group">
                    		<label for='pwd'>Password</label>
                    		<input type='password' class='form-control' name='password_signup' placeholder='password' onkeyup='checkPwd(this)' onmouseenter="viewDescription('La password deve contenere almeno un carattere alfabetico minuscolo e almeno un altro carattere alfabetico minuscolo o un numero.')" onmouseleave="hideDescription()" required>
                    		<div id="pwd_stat" style="visibility:hidden"><span class='taken'>&nbsp;&#x2718; La password non soddisfa i requisiti</span></div>
                    	</div>
                    	<button type='submit' class='btn btn-primary' name='submit_signup'>Registrati</button>
                    </form>   
            	</div>                 
            </div>


            <div class="col-sm-3">
                
            </div>


        </div>
    </div>
    <footer class="page-footer pt-4  fixed-bottom ">
    	<div class="footer-copyright text-center py-3 footer"> 
    	Rocco Luigi Scarcella S267537<br>Progetto Programmazione Distribuita I
      	</div>
    </footer>
</body>
</html>
