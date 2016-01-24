<?php
# https://www.codeeval.com/open_challenges/76/

    function areRotations($str1,$str2) {
        if(strlen($str1) != strlen($str2)) {
            return false;
        }
        for($i=0;$i<strlen($str2);$i++) {
            if($str2[$i] == $str1[0]) {
                // Start the search
                for($k=0;$k<strlen($str2);$k++) {
                    $idx = ($k+$i) % strlen($str2);
                    if($str2[($k+$i) % strlen($str2)] != $str1[$k]) {
                        break;
                    }
                }
                if($k == strlen($str2)) {
                    // We found a rotation
                    return true;
                }
            }
        }
        return false;
    }

    $input = split("\n", file_get_contents($argv[1]));
    
    foreach($input as $key => $line) {
        if(strlen($line) < 1) {
            continue;
        }
        $strings = split(",", $line);
        
        if(areRotations($strings[0],$strings[1])) {
            echo "True\n";
        } else {
            echo "False\n";
        }
    }
    
?>
