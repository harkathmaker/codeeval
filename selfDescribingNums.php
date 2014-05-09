<?php
# https://www.codeeval.com/open_challenges/112/

    $input = split("\n", file_get_contents($argv[1]));
    
    foreach($input as $key => $line) {
        if(strlen($line) <= 1) {
            continue;
        }
        $isSelfDescribing = 1;
        $freqs = count_chars($line,0);
        for($i=0;$i<10;$i++) {
            if($freqs[ord('0')+$i] != $line[$i]) {
                $isSelfDescribing = 0;
                break;
            }
        }
        echo $isSelfDescribing;

        echo "\n";
    }
    
?>
