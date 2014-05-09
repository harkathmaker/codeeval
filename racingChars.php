<?php
# https://www.codeeval.com/open_challenges/136/

    function getTrackChar($lastPos, $newPos) {
        if($lastPos == -1 || $lastPos == $newPos) {
            return '|';
        } else if($lastPos < $newPos) {
            return '\\';
        } else {
            return '/';
        }
    }

    $input = split("\n", file_get_contents($argv[1]));
    
    $lastPos = -1;

    foreach($input as $key => $line) {
        if(strlen($line) == 0) {
            continue;
        }
        if($lastPos != -1) {
            echo "\n";
        }
        $newPos = strpos($line,'C');
        if($newPos === FALSE || ($lastPos != -1 && abs($newPos-$lastPos) > 1)) {
            $newPos = strpos($line,'_');
        }
        $line[$newPos] = getTrackChar($lastPos,$newPos);
        $lastPos = $newPos;
            echo $line;
    }
    
?>
