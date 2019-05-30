<?php
session_start();
setcookie("Place", "Polito");
setcookie("lab", "php");
?>
<html>
<head>
<title>COOKIES</title>
<style type="text/css"> table,tr,td,th {border-style:solid}</style>
</head>
<body>
<table>
	<tr>
		<th>COOKIE NAME</th>
		<th>COOKIE VALUE</th>
	</tr>
	<?php
    	foreach ($_COOKIE as $name => $value) {
    	    echo "<tr><td>$name</td><td>$value</td></tr>";
    	}
        //print_r($_COOKIE);
    ?>
</table>

</body>
</html>