// lab5.1.6 javascript

var n;

function getNumber() {
		n = prompt("Inserisci un numero");
//		if (n) {
//			if (isNaN(n)) {
//				alert("Non hai inserito un numero);
//			}
//		}
}

function showRes() {
	if (n && !isNaN(n)) {
		var div = document.getElementById("mainDiv");
		var table = document.createElement("table");
		table.setAttribute("id", "mainTable");
		div.appendChild(table);	
		
		for (var i = 0; i <= n; i++) {
			var row = document.createElement("tr");
			row.setAttribute("id", "r_"+i);
			table.appendChild(row);
			
			for (var j = 0; j <= n; j++) {
				var item = document.createElement("td");
				item.setAttribute("id", "item_" + i + "_" +j);
				item.innerHTML = i * j;
				row.appendChild(item);
			}
			
			
		}
	}
}