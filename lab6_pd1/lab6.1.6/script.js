function calctot() {
    var table = document.getElementById("main");
    var nrows = document.getElementById("main").getElementsByTagName("tr").length - 2;
    var tot = 0;
    for (var i = 0; i < nrows; i++) {
        tot += parseFloat(document.getElementById("prezzo_" + i).innerHTML) * parseInt(document.getElementById("qnt_" + i).value);
    }
    document.getElementById("totale").innerHTML = "€ " + tot;
}