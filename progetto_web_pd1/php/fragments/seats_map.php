<?php
    require_once DIR_PHP_OBJECTS . 'seat.php';

//     define('ROWS', 10);
//     define('COLUMNS', 6);
    
    $nmyseats = 0;
    
    $_SESSION[MY_SEATS] = array();

    $conn = dbConnect();
    $sql = "SELECT * FROM " . DB_TABLE_SEATS . ";";
    $res = null;
    try {
        $res = dbQuery($conn, $sql);
    } catch (Exception $e) {
        dbClose($conn);
        redirect("./error.php", "error", $e->getMessage());
    }
    $seats = array();
    $nseats = mysqli_num_rows($res);
    if ($nseats > 0) {
        while ($row = mysqli_fetch_array($res)) {
            array_push($seats, new Seat($row[0], $row[1], $row[2]));
        }
    }
    mysqli_free_result($res);
    dbClose($conn);

?>
<div class="row">
	<div class="col-sm-3"></div>
    <div class="col-sm-6"> 
    	<div class="plane-body">
            <table id="plane_seats_map" class="mx-auto" onmouseenter="viewDescription('Clicca su un posto per prenotarlo o liberarlo.&lt;br&gt;Per farlo devi essere autenticato!')" onmouseleave="hideDescription()">
                <tr>
                	<?php 
                	   for ($j = 0; $j < AIRPLANE_COLUMNS/2; $j++) echo "<td class='text-center seatid'>" . chr($j + 65) . "</td>";
                	   echo "<td></td>";
                	   for ($j = ceil(AIRPLANE_COLUMNS/2); $j < AIRPLANE_COLUMNS; $j++) echo "<td class='text-center seatid'>" . chr($j + 65) . "</td>";
        	        ?>
                </tr>
                <?php 
                for ($i = 0; $i < AIRPLANE_ROWS; $i++) {
                        $row = $i + 1;         
                        echo "<tr>";
        
                        for ($j = 0; $j < AIRPLANE_COLUMNS/2; $j++) {
                            $col = chr($j + 65); // 65 is ASCII code for A
                            $id = "" . $col . $row;
                            $class = getSeatClass($id, $seats, $nmyseats);
                            echo "<td><button id='seat_" . $id . "' name='" . $id . "' class='" . $class . "' type='button'"; 
                            if (userLoggedIn()) {
                                echo " onclick='bookSeat(this.id)'";
                            }
                            echo "><i class='material-icons md-18'>event_seat</i></button></td>";
                        }
                        echo "<td class='text-center seatid'><span>$row</span></td>";
                        for ($j = ceil(AIRPLANE_COLUMNS/2); $j < AIRPLANE_COLUMNS; $j++) {
                            $col = chr($j + 65); // 65 is ASCII code for A
                            $id = "" . $col . $row;
                            $class = getSeatClass($id, $seats, $nmyseats);
                            echo "<td><button id='seat_" . $id . "' name='" . $id . "' class='" . $class . "' type='button'"; 
                            if (userLoggedIn()) {
                                echo " onclick='bookSeat(this.id)'";
                            }
                            echo "><i class='material-icons md-18'>event_seat</i></button></td>";
                        }
                        
                        
                        echo "</tr>";
                    }
                    
                    $_SESSION[NUM_MY_SEATS] = $nmyseats;
                ?>
                <tr>
                	<?php 
                	   for ($j = 0; $j < AIRPLANE_COLUMNS/2; $j++) echo "<td class='text-center seatid'>" . chr($j + 65) . "</td>";
                	   echo "<td></td>";
                	   for ($j = ceil(AIRPLANE_COLUMNS/2); $j < AIRPLANE_COLUMNS; $j++) echo "<td class='text-center seatid'>" . chr($j + 65) . "</td>";
        	        ?>
                </tr>
            </table>
		</div>
 
    </div>
    <div class="col-sm-3"></div>
</div>


