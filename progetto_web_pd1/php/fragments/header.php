<header class="card-header text-center main-header" id="header">
    <h2 class="navbar-brand mx-auto text-center main-title" >Air-PoliTO</h2>
    <?php if (userLoggedIn()): ?>
    	<p>Bentornato <?php echo $_SESSION[SESSION_USERNAME] ?></p>
    <?php endif; ?>
    <?php if (isset($_GET['logout'])): ?>
	    <p>Torna presto!</p>
    <?php endif; ?>
</header>
<noscript>
	<div class="container alert-danger text-center">
        <h6>
            <i class="material-icons md-28">warning</i>
            Per poter utilizzare il sito &egrave; necessario JavaScript.
		    Abilita JavaScript nel tuo browser per avere un'esperienza migliore.
        </h6>
	</div>
</noscript>