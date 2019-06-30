<?php
    /**
     * homepage
     */
    require_once 'config.php';
    require_once DIR_PHP_FUNCTIONS . 'session.php';
    require_once DIR_PHP_FUNCTIONS . 'database.php';
    require_once DIR_PHP_FUNCTIONS . 'lib.php';
    require_once DIR_PHP_FUNCTIONS . 'use_https.php';
        
    sessionStart();
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
  
    <div id="mainContent" style="padding-top: 20px; margin-bottom: 70px" class="container" role="main">
        <div class="row">


            <div class="col-sm-3">
                <?php require_once('./php/fragments/sidebar.php'); ?>                
            </div>


            <div class="col-sm-6">
            	<div>
    	            <h5 class="card-header text-center page-content-title">Volo 0B 4105</h5>
            		<?php require_once('./php/fragments/seats_map.php'); ?>
        		</div>    
            </div>


            <div class="col-sm-3">
            	<div id="seats_occupation">
            		<table class="page-sum">
            			<tr><td class=" text-white">Posti</td><td id="s_tot" class="text-center text-white"></td></tr>
            			<tr><td class=" text-white">Posti acquistati</td><td id="s_purchased" class="text-center text-white"></td></tr>
            			<tr><td class="text-white">Posti prenotati</td><td id="s_booked" class="text-center text-white"></td></tr>
            		</table>
            	</div>
            	<?php if (isset($_GET['msg']) && $_GET['msg'] != ""): ?>  <!-- TODO sanitize GET and POST --> 
                	<div id="info_alert" style='margin: 20px 0' class="alert alert-info text-center" role="alert">
                		<strong><?php echo sanitizeInput($_GET['msg']); ?></strong>
                	</div>
            	<?php endif;?>
            	<div id="action_response" style="margin: 20px 0; visibility: hidden" class="alert alert-info text-center"></div>

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
