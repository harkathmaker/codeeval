// https://www.codeeval.com/open_challenges/17/

function sign(x) { return x > 0 ? 1 : (x < 0 ? -1 : 0); }

var fs  = require("fs");
fs.readFileSync(process.argv[2]).toString().split('\n').forEach(function (line) {
    if (line != "") {
        rawNums = line.split(",");
        var nums = new Array(rawNums.length);
        var k = 0;
        nums[0] = parseInt(rawNums[0]);
        // Form a shortened array, with all consecutive positives/zeros merged.
        for(var i=1;i<rawNums.length;i++) {
            if(sign(parseInt(rawNums[i])) >= 0 && sign(nums[k]) >= 0) {
                nums[k] += parseInt(rawNums[i]);
            } else {
                k++;
                nums[k] = parseInt(rawNums[i]);
            }
        }
        var highestSum = -Infinity;
        for(var start=0;nums[start]!==undefined;start++) {
            var sum = nums[start];
            highestSum = Math.max(highestSum,sum);
            for(var end=start+1;nums[end]!==undefined;end++) {
                sum += nums[end];
                if(sum > highestSum) {
                    highestSum = sum;
                }
            }
        }
        console.log(highestSum);
    }
});
