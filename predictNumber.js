// https://www.codeeval.com/open_challenges/125/

var fs  = require("fs");

function _predictNum(n,len) {
    if(n < len/2) {
        return _predictNum(n,len/2);
    }
    if(n == 0) {
        return 0;
    }
    return (_predictNum(n-len/2,len/2) + 1) % 3;
}

function predictNum(n) {
    var len = 2;
    while(len < n) {
        len *= 2;
    }
    return _predictNum(n,len);
}

fs.readFileSync(process.argv[2]).toString().split('\n').forEach(function (line) {
    if (line != "") {
        
        console.log(predictNum(parseInt(line)));
    }
});
