// https://www.codeeval.com/open_challenges/111/
// Secondary implementation to compare split speed with manual traversal.
import java.io.File;
import java.io.BufferedReader;
import java.io.FileReader;

public class Main {
    public static void main (String[] args) throws Exception {
        File file = new File(args[0]);
        BufferedReader in = new BufferedReader(new FileReader(file));
        String line;
        while ((line = in.readLine()) != null) {
            int longestWordLength = 0;
            int longestWordIndex = 0;
            String lineWords[] = line.split(" ");
            for(int i=0;i<lineWords.length;i++) {
                if(lineWords[i].length() > longestWordLength) {
                    longestWordLength = lineWords[i].length();
                    longestWordIndex = i;
                }
            }
            
            System.out.println(lineWords[longestWordIndex]);
        }
    }
}
