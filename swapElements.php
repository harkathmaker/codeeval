<?php
# https://www.codeeval.com/open_challenges/112/

    $input = split("\n", file_get_contents($argv[1]));
    
    foreach($input as $key => $line) {
        if(strlen($line) <= 1) {
            continue;
        }
        $elements = array();

        # Iterating through with strpos is faster than exploding
        $start = 0;
        $distPos = strpos($line,' ');
        while($distPos !== FALSE && substr($line,$start,1) != ':') {
            $elements[] = intval(substr($line,$start,$distPos-$start));
            $start = $distPos+1;
            $distPos = strpos($line,' ',$start);
        }
        $start = strpos($line,' ',$start);
        $distPos = strpos($line,'-',$start);
        # Parse swap commands
        while($distPos !== FALSE) {
            $swap1 = intval(substr($line,$start,$distPos-$start));
            $secondEnd = strpos($line,',',$distPos);
            if($secondEnd === FALSE) {
                # Reached end of the line so just read to the newline
                $swap2 = intval(substr($line,$distPos+1));
            } else {
                $swap2 = intval(substr($line,$distPos+1,$secondEnd-$distPos+1));
            }

            # Swap elements
            $temp = $elements[$swap1];
            $elements[$swap1] = $elements[$swap2];
            $elements[$swap2] = $temp;

            if($secondEnd === FALSE) {
                break;
            }
            $start = $secondEnd+1;
            $distPos = strpos($line,'-',$start);
        }

        foreach($elements as $e) {
            echo $e,' ';
        }
        echo "\n";
    }
    
?>

