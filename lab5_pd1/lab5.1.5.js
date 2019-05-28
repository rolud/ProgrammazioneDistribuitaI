// lab5.1.5 javascript

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
		
		for (var i = 1; i <= n; i++) {
			var square = Math.pow(i, 2);
			var cube = Math.pow(i, 3);
			
			var row = document.createElement("tr");
			row.setAttribute("id", "r_"+i);
			table.appendChild(row);
			
			var item = document.createElement("td");
			item.setAttribute("id", "item_"+i);
			item.innerHTML = i;
			row.appendChild(item);
			
			item = document.createElement("td");
			item.setAttribute("id", "item_"+i+"_square");
			item.innerHTML = square;
			row.appendChild(item);
			
			item = document.createElement("td");
			item.setAttribute("id", "item_"+i+"_cube");
			item.innerHTML = cube;
			row.appendChild(item);
		}
	}
}