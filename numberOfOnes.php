<?php
# https://www.codeeval.com/open_challenges/16/

    $input = split("\n", file_get_contents($argv[1]));
    
    foreach($input as $key => $line) {
        if(strlen($line) < 1) {
            continue;
        }
        $n = intval($line);
        $ones = 0;
        while($n > 0) {
            if($n % 2 == 1) {
                $ones++;
                $n--;
            }
            $n >>= 1;
        }
        echo "$ones\n";
    }
    
?>
