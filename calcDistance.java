// https://www.codeeval.com/open_challenges/99/

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.File;

public class Main {
    public static void main (String[] args) throws Exception {

    File file = new File(args[0]);
    BufferedReader in = new BufferedReader(new FileReader(file));
    String line;
    while ((line = in.readLine()) != null) {
        if (line.length() > 0) {
            int x1Start = line.indexOf('(')+1;
            int y1Start = line.indexOf(',')+1;
            while(line.charAt(y1Start) == ' ')
                y1Start++;
            int y1End = line.indexOf(')');
            int x2Start = line.indexOf('(',y1End)+1;
            int y2Start = line.indexOf(',',x2Start)+1;
            while(line.charAt(y2Start) == ' ')
                y2Start++;
            int y2End = line.indexOf(')',y2Start);
            int x1 = Integer.parseInt(line.substring(x1Start,y1Start-2));
            int y1 = Integer.parseInt(line.substring(y1Start,y1End));
            int x2 = Integer.parseInt(line.substring(x2Start,y2Start-2));
            int y2 = Integer.parseInt(line.substring(y2Start,y2End));
            System.out.println((int)Math.sqrt(Math.pow(x2-x1,2)+Math.pow(y2-y1,2)));
        }
    }
  }
}
