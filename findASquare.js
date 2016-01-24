// https://www.codeeval.com/open_challenges/101/

EPSILON = .01;

function Point(x,y) {
    this.x = x;
    this.y = y;
}

// Properly takes into account rotated squares.
function isSquare3(pts) {
    // Check whether there are two points an equal distance from the first
    var diag = Math.pow(pts[0].x-pts[1].x,2)+Math.pow(pts[0].y-pts[1].y,2);
    var diagIdx = 1;

    for(var i=2;i<4;i++) {
        var newDiag = Math.pow(pts[0].x-pts[i].x,2)+Math.pow(pts[0].y-pts[i].y,2);
        if(newDiag > diag) {
            diagIdx = i;
            diag = newDiag;
        }
    }

    // Apparently degenerate square of all the same point does not count.
    if(diag < EPSILON) {
        return false;
    }

    var sidePts = [];
    for(var i=1;i<4;i++) {
        if(i != diagIdx) {
            sidePts.push(pts[i]);
        }
    }
    var sideLength = Math.pow(pts[0].x-sidePts[0].x,2)+Math.pow(pts[0].y-sidePts[0].y,2);
    if(Math.abs(Math.pow(pts[0].x-sidePts[1].x,2)+Math.pow(pts[0].y-sidePts[1].y,2)-sideLength) > EPSILON) {
        return false;
    }

    // Verify the diagonal is twice the side length
    if(Math.abs(diag-2*sideLength) > EPSILON) {
        return false;
    }

    // Verify the last point is the same distance to the "middle two"
    if(Math.abs(Math.pow(pts[diagIdx].x-sidePts[0].x,2)+Math.pow(pts[diagIdx].y-sidePts[0].y,2)-sideLength) > EPSILON || 
       Math.abs(Math.pow(pts[diagIdx].x-sidePts[1].x,2)+Math.pow(pts[diagIdx].y-sidePts[1].y,2)-sideLength) > EPSILON) {
        return false;
    }

    // Make sure the middle two are the same distance apart as the other
    // diagonal
    return Math.abs(Math.pow(sidePts[0].x-sidePts[1].x,2)+Math.pow(sidePts[0].y-sidePts[1].y,2)-diag) < EPSILON;
}

var fs  = require("fs");
fs.readFileSync(process.argv[2]).toString().split('\n').forEach(function (line) {
    if (line != "") {
        var pts = [];
        rawPairs = line.split("(");
        for(var i=1;i<5;i++) {
            var coords = rawPairs[i].split(",");
            pts.push(new Point(parseInt(coords[0]),parseInt(coords[1])));
        }
        if(isSquare3(pts)) {
            console.log("true");
        } else {
            console.log("false");
        }
    }
});
