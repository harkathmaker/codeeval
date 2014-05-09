// https://www.codeeval.com/open_challenges/41/

var fs  = require("fs");
fs.readFileSync(process.argv[2]).toString().split('\n').forEach(function (line) {
    if (line != "") {
        var res = line.split(";");
        var vals = res[1].split(",");
        var elRange = parseInt(res[0])-2;
        var sum = 0;
        for(var i=0;i<vals.length;i++) {
            sum += parseInt(vals[i]);
        }
        // Sum of numbers 0 to n = n(n+1) / 2, so subtract this out to find our duplicate
        var duplicatedVal = sum - elRange * (elRange+1) / 2;
        console.log(duplicatedVal);
    }
});
