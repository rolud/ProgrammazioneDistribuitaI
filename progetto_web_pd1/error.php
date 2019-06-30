<?php
    require_once 'config.php';
    require_once DIR_PHP_FUNCTIONS . 'session.php';
    require_once DIR_PHP_FUNCTIONS . 'database.php';
    require_once DIR_PHP_FUNCTIONS . 'lib.php';
    require_once DIR_PHP_FUNCTIONS . 'use_https.php';
    
?>
<!DOCTYPE html>
<html lang="it">
<head>  
    <?php require_once './php/fragments/head_tags.php'; ?>
    
</head>
<body class="bg">
    <script type="text/javascript">
    	if (!checkCookie()) {
			$('body').append('<div id="over"><div id="info_alert" class="cookie-alert text-center" role="alert">Per poter utilizzare il sito attivare i cookie</div></div>');
    	}

    </script>
    <?php require_once('./php/fragments/header.php'); ?>
  
    <div id="mainContent" style="padding-top: 20px; margin-bottom: 70px" class="container" role="main">
        <div class="row">


            <div class="col-sm-3">
                            
            </div>


            <div class="col-sm-6">
            	<div style="margin-top: 200px; color: rgb(13,52,139)" class="text-center">
                   	<h2>OPS!</h2>
                   	<h5>C'&egrave; stato un errore.</h5>
                   	<p>Il sito torner&agrave; presto funzionante.</p>
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
    <script type="text/javascript">
		countSeats();
    </script>
</body>
</html>