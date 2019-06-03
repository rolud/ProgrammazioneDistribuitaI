<?php
    session_id('1754');
    session_start();
    if (isset($_SESSION['count'])) {
        $count = $_SESSION['count'];
        if ($count >= 2) {
            header('Location: UNO.php');
            exit();
        } 
    } else {
        $count = 0;
    }
?>
<html>
<head>
<title>LAB6.1.5 - DUE</title>
</head>
<body>
	<?php 
	   $_SESSION['count'] = $count + 1;
	   session_write_close();
	?>
	<p>Un alunno chiede alla maestra: “Maestra, posso essere punito 
	per qualcosa che non ho fatto?”. E la maestra: “Certo che no! 
	Perché me lo chiedi?”. Allora l'alunno risponde: “Perché non ho 
	fatto i compiti!”.</p>
	<form action="./UNO.php" method="GET">
		<button type="submit" name="submit_due">ESCI</button>
	</form>
</body>
</html>