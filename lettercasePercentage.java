// https://www.codeeval.com/open_challenges/147/
import java.io.File;
import java.io.BufferedReader;
import java.io.FileReader;

public class Main {
    public static void main (String[] args) throws Exception {
        File file = new File(args[0]);
        BufferedReader in = new BufferedReader(new FileReader(file));
        String line;
        while ((line = in.readLine()) != null) {
            int lowers = 0;
            int uppers = 0;
            for(int i=0;i<line.length();i++) {
                char c = line.charAt(i);
                if(c >= 'a' && c <= 'z') {
                    lowers += 1;
                } else if(c >= 'A' && c <= 'Z') {
                    uppers += 1;
                }
            }
            float lRatio;
            float uRatio;
            if(lowers+uppers == 0) {
                lRatio = uRatio = 0;
            } else {
                lRatio = (float)lowers/(float)(lowers+uppers)*100;
                uRatio = (float)uppers/(float)(lowers+uppers)*100;
            }
            System.out.printf("lowercase: %.2f uppercase: %.2f\n",lRatio,uRatio);
        }
    }
}
