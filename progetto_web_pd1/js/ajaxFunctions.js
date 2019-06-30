
/**
 * create AJAX request for the browser used
 * 
 * @returns the AJAX request
 */
function ajaxRequest() {
	try { // Non IE Browser? 
    	var request = new XMLHttpRequest()
	} catch(e1){ // No
    	try { // IE 6+?
        	request = new ActiveXObject("Msxml2.XMLHTTP")
    	} catch(e2){ // No
	   		try { // IE 5?
	       		request = new ActiveXObject("Microsoft.XMLHTTP")
	   		} catch(e3){ // No AJAX Support
				request = false
	   		}
  		}
	}
	return request
}

/**
 * queries the db to update or insert the booking
 * 
 * @param seatid: the id of the seat the user wants to book
 * 
 * @returns updates seat status
 */
function bookSeat(seatid) {
	var id = seatid.split("_");
	$.post(
		"php/ajax/update_seat.php", 
		{"id" : id[1]},
		function (data) {
			seat = jQuery.parseJSON(data);
			$('#' + seatid).removeClass();
			$('#' + seatid).addClass(seat.classname);
			//$('#action_response').addClass("alert alert-info text-center");
			$('#action_response').html('<strong>' + seat.msg + '</strong>');
			$('#action_response').css('visibility', 'visible');
		}
	)
	
}

/**
 * ajax check if username is available or not
 * 
 * @param user
 * @returns
 */
function checkUser(user) {
	if (user.value == "") {
		$('#user_stat').html('&nbsp;');
		return;
	}
	$.post(
		'php/ajax/check_user.php', 
		{user : user.value}, 
		function (data) {
			$('#user_stat').html(data);
		}
	)
}
