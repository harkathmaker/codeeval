// https://www.codeeval.com/open_challenges/29/

var fs  = require("fs");
fs.readFileSync(process.argv[2]).toString().split('\n').forEach(function (line) {
    if (line != "") {
        var list = line.split(",").map(function(item) {
            return parseInt(item,10);
        });
        function sortNumber(a,b) {
            return a - b;
        }
        list = list.filter(function(elem, pos) {
            return list.indexOf(elem) == pos;
        });
        list.sort(sortNumber);
        var answer_line = list.join();
        console.log(answer_line);
    }
});
