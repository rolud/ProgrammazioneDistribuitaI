<?php
    session_id('1754');
    session_start();
    if (!empty($_GET)) {
        if (isset($_GET['submit_due'])) {
            $_SESSION['count'] = $_SESSION['count'] - 1;
            session_write_close();
        }
    }
?>
<html>
<head>
<title>LAB6.1.5 - UNO</title>
</head>
<body>
    <form action="./DUE.php" method="GET">
		<button type="submit">ENTRA</button>
	</form>
</body>
</html>