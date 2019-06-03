<?php
require("includes/connection.php");
$link = connect_db();
if (!empty($_GET)) {
    foreach ($_GET as $key => $value) {
        if ($_GET[$key]) {
			$query = "INSERT INTO carrello (id,qnt) 
						VALUES ($key, $value)
						ON DUPLICATE KEY UPDATE qnt = $value;";
		} else {
			$query = "DELETE FROM carrello WHERE id = $key;";
		}
		query_db($link, $query);
	}
}
?>
<html>
<head>
	<title>lab6.1.6 - carrello</title>
	<meta charset="utf-8">
	<link href="style.css" rel=stylesheet type="text/css">
	<script type="text/javascript" src="script.js">
	</script>
	<style type="text/CSS">input {width:100px}</style>
</head>
<body>
	<h1>CARRELLO</h1>
	<form action="carrello.php" method="GET">
		<table id="main">
			<tr><th>Prodotto</th><th>Prezzo (€)</th><th>Quantità</th></tr>
			<?php 
				$query = "SELECT product.id, nome, prezzo, qnt 
						FROM product, carrello
						WHERE product.id = carrello.id;";
				$result = query_db($link, $query);
				if (mysqli_num_rows($result) > 0) {
					$n = 0;
					while ($row = mysqli_fetch_row($result)) {
					
					echo "<tr><td id='nome_$n'>$row[1]</td><td id='prezzo_$n'>$row[2]</td><td><input type='number' id='qnt_$n' name='$row[0]' value='$row[3]'></td></tr>";
					$n = $n + 1;
					
					}
				}
				mysqli_close($link);
			?>
			<tr>
				<td>TOTALE</td>
				<td colspan="2" id="totale"></td>		
			</tr>
		</table>
		<div>
			<button type="button"><a href="acquista.php">COMPRA</a></button>
			<button type="submit">AGGIORNA</button>
			<button type="button"><a href="home.php">INDIETRO</a></button>
		</div>
	<form>
	<script type="text/javascript">
		calctot();
	</script>
</body>
</html>