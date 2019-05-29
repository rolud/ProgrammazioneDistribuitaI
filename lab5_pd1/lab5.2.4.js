// lab5.2.4 javascript

function updateSum(num) {
    var n1 = num.value;
    var n2;
    if (num.id == "num1") {
        n2 = document.getElementById("num2").value;
    } else if (num.id == "num2") {
        n2 = document.getElementById("num1").value;
    }

    document.getElementById("sum").value = parseInt(n1) + parseInt(n2);
}