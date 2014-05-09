<?php
# https://www.codeeval.com/open_challenges/124/

    $input = split("\n", file_get_contents($argv[1]));
    
    foreach($input as $key => $line) {
        if(strlen($line) <= 1) {
            continue;
        }
        $distances = array();

        $cities = explode("; ",$line);

        # Parse the distance to each city;
        foreach($cities as $ckey => $c) {
            $distPos = strpos($c,',');
            $distances[] = intval(substr($c,$distPos+1));
        }

        # Sort them, which will allow us to traverse the list and compute
        # each intermediate distance
        sort($distances);

        $lastDist = 0;
        foreach($distances as $d) {
            echo ($d-$lastDist);
            $lastDist = $d;
            if($d !== end($distances)) {
                echo ",";
            } else {
                echo "\n";
            }
        }
    }
    
?>
