<?php
$cookie_name = "Country";
$cookie_value = "IT";
setcookie($cookie_name, $cookie_value, time() + (3600 * 24), "/");
?>

<html>
<head>
	<title>A</title>
</head>
<body>
	<h1>Italia!</h1>
</body>
</html>