/**
 * 
 */

/**
 * controllo se i cookie sono abilitati
 * @returns
 */
function checkCookie() {
	if (document.cookieEnabled)
		return true;
	document.cookie = "cookietest=1";
	var cookie_enabled = document.cookie.indexOf("cookietest=") != -1;
	document.cookie = "cookietest=1; expires=Thu, 01-Jan-1970 00:00:01 GMT";
	return cookie_enabled;
}

/**
 * conta e stampa nella pagine html lo stato dei posti dell'aereo
 * @returns
 */
function countSeats() {
	var table = document.getElementById("plane_seats_map");
	document.getElementById("s_tot").innerHTML = table.getElementsByClassName("seat").length;
	document.getElementById("s_purchased").innerHTML = table.getElementsByClassName("seat-purchased").length;
	document.getElementById("s_booked").innerHTML = table.getElementsByClassName("seat-booked").length + table.getElementsByClassName("seat-booked-by-me").length;
}

/**
 * mostra una descrizione del form su cui si trova il cursore
 * @param description
 * @returns
 */
function viewDescription(description) {
	$('#sidebar').append("<div style='margin: 20px 0' class='alert alert-info' id='descr'><strong>" + description + "</strong></div>");
	
//	document.getElementById(id).innerHTML = description;
//	document.getElementById(id).style.visibility = 'visible';
}

/**
 * nasconde la descrizione del form
 * @returns
 */
function hideDescription() {
	$('#descr').remove();
}

/**
 * controlla che la password soddisfi i requisiti
 * @param pwd
 * @returns
 */
function checkPwd(pwd) {
	pattern = /(?=.{2})(?=.*[a-z])(?=.*[A-Z0-9])/;
	if (pwd.value.match(pattern) != null) {
		document.getElementById('pwd_stat').style.visibility = 'hidden';
	} else {
		
		document.getElementById('pwd_stat').style.visibility = 'visible';
	}
}

