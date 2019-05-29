// lab5.2.7 javascript

var floppy = {
    prezzo: 0.2,
    qnt: 0 
};

var cd = {
    prezzo: 1.0,
    qnt: 0
};

var dvd = {
    prezzo: 2.0,
    qnt: 0
};

function calc() {
    floppy.qnt = parseInt(document.getElementById("floppy").value);
    cd.qnt = parseInt(document.getElementById("cd").value);
    dvd.qnt = parseInt(document.getElementById("dvd").value);
    document.getElementById("res").value = floppy.prezzo * floppy.qnt + cd.prezzo * cd.qnt + dvd.prezzo * dvd.qnt;
}