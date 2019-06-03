<?php
require("includes/connection.php");
if(!empty($_GET)) {
    if (isset($_GET['id'])) {
        $p = $_GET['id'];
    }
}
?>
<html>
<head>
	<title>lab6.1.6 - product</title>
	<meta charset="utf-8">
	<link href="style.css" rel=stylesheet type="text/css">
</head>
<body>
	<h1>PRODOTTO</h1>
	<table id="main">
		<tr><th>Prodotto</th><th>Prezzo</th><th>Descrizione</th></tr>
		<?php 
		  $link = connect_db();
		  $query = "SELECT nome, prezzo, descrizione FROM product WHERE NOME='$p';";
		  $result = query_db($link, $query);
		  if (mysqli_num_rows($result) > 0) {
		      while ($row = mysqli_fetch_row($result)) {
		          echo "<tr><td>$row[0]</td><td>$row[1]</td><td>$row[2]</td></tr>";
		      }
		  }
		  mysqli_close($link);
		?>
		<tr>
			
		</tr>
	</table>
</body>
</html>