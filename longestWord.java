// https://www.codeeval.com/open_challenges/111/
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
            String longestWord = "";
            int wordStart = 0;
            int wordEnd = line.indexOf(' ');
            while(wordStart < line.length()) {
                if(wordEnd == -1) {
                    wordEnd = line.length();
                }
                if(wordEnd-wordStart > longestWordLength) {
                    longestWordLength = wordEnd-wordStart;
                    longestWord = line.substring(wordStart,wordEnd);
                }
                wordStart = wordEnd+1;
                wordEnd = line.indexOf(' ',wordStart);
            }
            System.out.println(longestWord);
        }
    }
}
