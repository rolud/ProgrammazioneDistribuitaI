<html>
<head>
<title>B</title>
</head>
<body>
	<p>
        <?php
        if(isset($_COOKIE["Country"])) {
            echo "Cookie Country value is " . $_COOKIE["Country"]; 
        }
        ?>
	</p>
</body>
</html>