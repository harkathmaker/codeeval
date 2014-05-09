// https://www.codeeval.com/open_challenges/67/

var fs  = require("fs");
fs.readFileSync(process.argv[2]).toString().split('\n').forEach(function (line) {
    if (line != "") {
        console.log(parseInt("0x"+line));
    }
});
