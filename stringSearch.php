<?php
# https://www.codeeval.com/open_challenges/28/

    function mySubstring($haystack,$needle) {
        $current = 0;
        while($current < strlen($haystack)) {
            //echo "Starting search at index $current\n";
            $r = mySubstring_h($current,0,$haystack,$needle);
            if($r[1] == strlen($needle)) {
                return true;
            }
            $current++;
        }
        return false;
    }
    function mySubstring_h($currentHay,$currentNeedle,$haystack,$needle) {
        $followingWildcard = false;
        while($currentHay < strlen($haystack) && $currentNeedle < strlen($needle)) {
            if($followingWildcard) {
                // if last character was wildcard, call recursive and set pointer
                // to result.
                //echo "Entering wildcard loop\n";
                do {
                    $r = mySubstring_h($currentHay,$currentNeedle,$haystack,$needle);
                    $currentHay++;
                } while($r[1] == -1);
                //echo "Returning $r[0],$r[1] following wildcard\n";
                return $r;
            } else {
                // if character is not wildcard, proceed
                if($needle[$currentNeedle] == '*') {
                    // if character is wildcard, skip
                    $followingWildcard = true;
                    $currentNeedle++;
                    continue;
                } else if($needle[$currentNeedle] == '\\' && $currentNeedle < strlen($needle)-1 && $needle[$currentNeedle+1] == '*') {
                    $char = '*';
                    // Need to skip an extra character
                    $currentNeedle++;
                } else {
                    $char = $needle[$currentNeedle];
                }
                //echo "char:$char\n";
                //echo "currentHay:$haystack[$currentHay]\n";
                $currentNeedle++;
                if($char == $haystack[$currentHay]) {
                    //echo "Char $char passes.\n";
                    $currentHay++;
                } else {
                    //echo "Returned (-1,-1) after character mismatch\n";
                    return array( -1, -1 );
                }
            }
        }
        if($currentNeedle == strlen($needle)) {
            // if reached end of input, report success
            //echo "Returning $r[0],$r[1] at end of needle\n";
            return array( $currentHay, $currentNeedle );
        } else {
            // if pointer is -1, cannot find a substring
            //echo "Returned (-1,-1) at end of needle\n";
            return array( -1, $currentNeedle);
        }
    }

    $input = split("\n", file_get_contents($argv[1]));
    
    foreach($input as $key => $line) {
        if(strlen($line) <= 1) {
            continue;
        }
        $splitLine = split(",",$line);

        if(mySubstring($splitLine[0],$splitLine[1])) {
            echo 'true';
        } else {
            echo 'false';
        }
        echo "\n";
    }
    
?>
