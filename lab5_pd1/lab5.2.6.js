// lab5.2.6 javascript

function maggiore() {
    var max = -Infinity;
    for (var i = 0; i < arguments.length; i++) {
        if (parseInt(arguments[i].value) > max)
            max = arguments[i].value;
    }
    alert(max);
}