// https://www.codeeval.com/open_challenges/75/

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.File;
import java.util.LinkedList;
import java.util.Iterator;

public class Main {
    public static void main (String[] args) throws Exception {
        File file = new File(args[0]);
        BufferedReader in = new BufferedReader(new FileReader(file));
        String line;
        while ((line = in.readLine()) != null) {
            if (line.length() == 0) {
                continue;
            }
            String[] components = line.split(",");
            int soldiers = Integer.parseInt(components[0]);
            int j = Integer.parseInt(components[1]);
            LinkedList<Integer> list = new LinkedList<Integer>();
            for(int i=0;i<soldiers;i++) {
                list.add(i);
            }
            Iterator it = list.listIterator(0);
            Integer current = 0;
            while(!list.isEmpty()) {
                for(int i=0;i<j;i++) {
                    if(!it.hasNext()) {
                        it = list.listIterator(0);
                    }
                    current = (Integer)it.next();
                }
                it.remove();
                
                System.out.printf("%d ",current);
            }
            System.out.println();
        }
    }
}
