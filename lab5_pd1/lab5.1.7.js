// lab5.1.7 javascript

var nums = new Array();

function init() {
    var div = document.getElementById("numDiv");
    var ul = document.createElement("ul");
    ul.setAttribute("id", "numList");
    div.appendChild(ul);
    var table = document.createElement("table");
    table.setAttribute("id", "table_avg");
    div.appendChild(table);
    var row = document.createElement("tr");
    row.setAttribute("id", "table_avg_row");
    table.appendChild(row);
    var item = document.createElement("td");
    item.setAttribute("id", "avg_text");
    item.innerHTML = "Average";
    row.appendChild(item);
    item = document.createElement("td");
    item.setAttribute("id", "avg_value");
    row.appendChild(item);
    div.style.visibility = "hidden";
}

function newNumber() {
    var n = prompt("Insert a number");
    if (n && !isNaN(n)) {
        nums.push(n);
        var div = document.getElementById("numDiv");
        if (div.style.visibility == "hidden") div.style.visibility = "visible";
        var ul = document.getElementById("numList");
        var li = document.createElement("li");
        li.setAttribute("id", "n_" + nums.length);
        li.innerHTML = n;
        ul.appendChild(li);

        var avg = 0;
        for (var i = 0; i < nums.length; i++) {
            avg += parseInt(nums[i]);
        }
        avg = avg / nums.length;

        document.getElementById("avg_value").innerHTML = avg;
    } else {
        alert("You insert something that is not a number or you have canceled");
    }
}