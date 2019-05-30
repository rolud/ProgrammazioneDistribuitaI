<html>
<head>
<title>B</title>
</head>
<body>
	<p>
        <?php
        if(isset($_COOKIE["Country_lab6.1.3"])) {
            echo "Cookie Country value is " . $_COOKIE["Country"]; 
        } else {
            echo "Cookie Country of lab6.1.3 is not set!";
        }
        ?>
	</p>
</body>
</html>