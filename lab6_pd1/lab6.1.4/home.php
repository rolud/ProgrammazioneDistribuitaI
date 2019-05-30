<?php
    session_start();
    $name = $_GET["name"];
    $lastname = $_GET["lastname"];
    if (isset($_SESSION[$name . $lastname])) {
        $count = $_SESSION[$name . $lastname];
    } else {
        $count = 0;
    }
?>
<html>
<head>
	<title>lab6.1.4 - login</title>
</head>
<body>
	<h1>MySite</h1>
	<?php 
	   $_SESSION[$name . $lastname] = $count + 1;
	   if ($_SESSION[$name . $lastname] > 1) {
	       echo "<p>Bentornato, caro " . $name . " " . $lastname . ", nel mio umile sito.</p>";
	       echo "<p>(Accesso numero " . $_SESSION[$name . $lastname] . ")</p>";
	   }
	?>
	<p>Claremont è una città universitaria nella parte orientale della contea 
	   di Los Angeles, California, Stati Uniti, a circa 30 miglia (48 km) a est 
	   del centro di Los Angeles ai piedi delle montagne di San Gabriel. Secondo 
	   il censimento del 2010, la popolazione è di 34.926 abitanti. Claremont è 
	   nota per i suoi sette istituti di istruzione superiore, le sue strade alberate 
	   ed i suoi edifici storici. Nel luglio 2007, è stata valutata dalla CNN come il 
	   quinto posto migliore dove vivere negli Stati Uniti, ed era il luogo con il 
	   rating più alto della California. Grazie al suo grande numero di alberi e 
	   residenti con dottorati, è conosciuta come "la città degli alberi e dei 
	   dottorati di ricerca".</p>
</body>
</html>