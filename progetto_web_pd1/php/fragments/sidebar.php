<div id="sidebar">
    <nav class="list-group border-0 text-center text-md-left sidecard">
        <?php if (userLoggedIn()): ?>
            <a class='mx-auto text-center sidelink' href='index.php' onmouseenter="viewDescription('Clicca qui per aggiornare la mappa dei posti.')" onmouseleave="hideDescription()">
            	<i class="material-icons md-18">refresh</i> Aggiorna
        	</a>
            <a class='mx-auto text-center sidelink' href='acquista.php' onmouseenter="viewDescription('Clicca qui per acquistare i posti che hai prenotato.')" onmouseleave="hideDescription()">
            	<i class="material-icons md-18">local_airport</i> Acquista
        	</a>
            <a class='mx-auto text-center sidelink' href='logout.php' onmouseenter="viewDescription('Clicca qui per disconnetterti.')" onmouseleave="hideDescription()">
            	<i class="material-icons md-18">exit_to_app</i> Log Out
        	</a>
        <?php else: ?> 
        	<a class='mx-auto text-center sidelink' href='index.php' onmouseenter="viewDescription('Homepage.')" onmouseleave="hideDescription()">
        		<i class="material-icons md-18">home</i> Home
			</a>
        	<a class='mx-auto text-center sidelink' href='login.php' onmouseenter="viewDescription('Clicca qui per poterti autenticare.')" onmouseleave="hideDescription()">
        		<i class="material-icons md-18">lock_open</i> Log In
    		</a>
            <a class='mx-auto text-center sidelink' href='registrazione.php' onmouseenter="viewDescription('Clicca qui per registrarti.')" onmouseleave="hideDescription()">
            	<i class="material-icons md-18">person_add</i> Registrati
        	</a>   
        <?php endif;?>
    </nav>
</div>