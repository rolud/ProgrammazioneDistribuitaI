<?php
session_start();
require("includes/connection.php");
?>
<html>
<head>
	<title>lab6.1.6 - home</title>
	<link href="style.css" rel=stylesheet type="text/css">
</head>
<body>
	<h1>MARKET</h1>
	<form action="carrello.php" method="GET">
    	<table>
    		<tr><th>Prodotto</th><th>Quantità</th></tr>
    		<?php
    		  $link = connect_db();
    		  $query = "SELECT id, nome FROM product;";
    		  $result = query_db($link, $query);
    		  if (mysqli_num_rows($result) > 0) {
    		      while ($row = mysqli_fetch_row($result)) {
    		          echo "<tr><td><a href='./product.php?id=$row[1]'>$row[1]</a></td><td><input type='number' name='$row[0]'></td></tr>";
    		      }
    		  }
    		  mysqli_close($link);
    		?>
    	</table>
    	<button type="submit">RIEPILOGO</button>
	</form>
</body>
</html>