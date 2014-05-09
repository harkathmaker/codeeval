// https://www.codeeval.com/open_challenges/27/

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.File;

public class Main {
    public static void main(String[] args) throws Exception {
        File file = new File(args[0]);
        BufferedReader in = new BufferedReader(new FileReader(file));
        String line;
        while((line = in.readLine()) != null) {
            if(line.length() < 1) {
                continue;
            }
            int n = Integer.parseInt(line);
            // Special case for 0
            if(n == 0) {
                System.out.println("0");
                continue;
            }
            int mask = 1;
            while(n >= mask) {
                mask *= 2;
            }
            mask /= 2;
            while(mask > 0) {
                System.out.print( ((mask & n) != 0) ? 1 : 0 );
                mask /= 2;
            }
            System.out.println();
        }
    }
}
