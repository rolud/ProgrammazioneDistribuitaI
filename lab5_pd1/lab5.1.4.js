// lab5.1.4 javascript

var n1;
var n2;

function getNumber() {
		n1 = prompt("Inserisci un numero");
		n2 = prompt("Inserisci un altro numero");	
}

function showRes() {
	if (!isNaN(n1) && !isNaN(n2)) {
		var sum = parseInt(n1) + parseInt(n2);
		var dif = parseInt(n1) - parseInt(n2);
		
		var div = document.getElementById("mainDiv");
		var ul = document.createElement('ul');
		ul.setAttribute("id", "mainUl");
		div.appendChild(ul);
		
		var item = document.createElement("li");
		item.setAttribute("id", "li_sum");
		ul.appendChild(item);
		item.innerHTML = sum;
		
		item = document.createElement("li");
		item.setAttribute("id", "li_dif");
		ul.appendChild(item);
		item.innerHTML = dif;
	}
}