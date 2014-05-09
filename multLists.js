// https://www.codeeval.com/open_challenges/113/

var fs  = require("fs");
fs.readFileSync(process.argv[2]).toString().split('\n').forEach(function (line) {
    if (line !== "") {
        //do something here
        //console.log(answer_line);
        var list1pos = 0;
        var list1end = line.indexOf(" ",list1pos)+1;
        var list2pos = line.indexOf("|")+2;
        var list2end = line.indexOf(" ",list2pos)+1;
        var answer_line = "";

        while(line.charAt(list1pos) != "|") {
            var v1 = parseInt(line.substring(list1pos,list1end),10);
            var v2;
            if(list2end === 0) {
                v2 = parseInt(line.substring(list2pos),10);
            } else {
                v2 = parseInt(line.substring(list2pos,list2end),10);
            }
            answer_line += (v1*v2) + " ";
            list1pos = list1end;
            list1end = line.indexOf(" ",list1pos)+1;
            list2pos = list2end;
            list2end = line.indexOf(" ",list2pos)+1;
        }
        console.log(answer_line);
    }
});
