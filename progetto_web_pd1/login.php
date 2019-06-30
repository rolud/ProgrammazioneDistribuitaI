<?php
    /**
     * pagina di login
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
    
    if(isset($_POST['submit_login'])) {
        try {
            if( $_POST['username_login'] == "" || $_POST['password_login'] == "") {
                throw new Exception("All field are required.");
            }
            
            
            $user = secure($conn, $_POST['username_login']);
//             $password = md5($_POST['password_login']);
                       
            $sql = "SELECT * FROM " . DB_TABLE_USERS . " WHERE ". DB_TABLE_SEATS_USER . " = '$user';";
            $res = dbQuery($conn, $sql);
            if (mysqli_num_rows($res) != 1) {
                throw new Exception("Wrong username or password.");
            }
            $row = mysqli_fetch_row($res);
            $password = md5($_POST['password_login'] . $row[2]);
            if ($password != $row[1]) {
                throw new Exception("Wrong username or password.");
            }
            
            $_SESSION[SESSION_USERNAME] = $user;
            $_SESSION[SESSION_LAST_INTERACTION] = time();
            
            redirect('index.php');
            
        } catch (Exception $e) {
            $login_error = $e->getMessage();
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
	<script>
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
            		<h5 class="card-header text-center page-content-title">Log In</h5>
            		<?php if (isset($_GET['msg'])): ?>
            			<div class="container alert-danger text-center">
            				<p><?php echo sanitizeInput($_GET['msg']); ?></p>
            			</div>
            		<?php endif; ?>
            		<?php if ($login_error != ""):?>
            			<div class="container alert-danger text-center" role="alert">
            				<strong><?php echo $login_error; ?></strong>
            			</div>
            		<?php endif; ?>
                    <form id='login' action='login.php' method='POST' onmouseenter="viewDescription('Inserisci una email  e una password valide per poter accedere alla tua pagina personale.')" onmouseleave="hideDescription()">
                    	<div class="form-group">
                    		<label for='email'>Email</label>
                    		<input type='email' class='form-control' name='username_login' placeholder='esempio@email.com' required>
                    	</div>
                    	<div class="form-group">
                    		<label for='pwd'>Password</label>
                    		<input type='password' class='form-control' name='password_login' placeholder='password' required>
                    	</div>
                    	<button type='submit' class='btn btn-primary' name='submit_login'>Login</button>
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
