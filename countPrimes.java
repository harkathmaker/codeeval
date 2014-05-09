// https://www.codeeval.com/open_challenges/63/

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;

public class Main {
    public static int[] findPrimes(int limit) {
        boolean[] marked = new boolean[limit/2];
        // Mark with sieve of Eratosthenes
        int p = 3;
        int root = (int)Math.sqrt(limit)+1;
        while(p < root) {
            int k = p + (p-1)/2;
            while(k < limit/2) {
                marked[k] = true;
                k += p;
            }
            do {
                p += 2;
            } while(p < limit/2 && marked[(p-1)/2]);
        }
        
        // Start at 0 instead of 1, since marked[0] representing 1 is
        // unmarked.
        int returnSize = 0;
        for(int i=0;i<marked.length;i++) {
            if(!marked[i]) {
                returnSize++;
            }
        }
        int[] retArray = new int[returnSize];
        retArray[0] = 2;
        int i = 1;
        int k = 1;
        while(i < marked.length) {
            if(!marked[i]) {
                retArray[k] = i*2+1;
                k++;
            }
            i++;
        }
        return retArray;
    }

    // Counts the number of primes in an inclusive range via binary search.
    public static int primesInRange(int lower,int upper,int[] primes) {
        int start = Arrays.binarySearch(primes,0,primes.length,lower);
        int end = Arrays.binarySearch(primes,0,primes.length,upper);
        if(start < 0) {
            start = -(start+1);
        }
        if(end < 0) {
            end = -(end+1);
        } else {
            end++;
        }
        return end-start;
    }

    public static void main (String[] args) throws Exception {
        File file = new File(args[0]);
        BufferedReader in = new BufferedReader(new FileReader(file));
        String line;
        // Highest we have to search for primes
        int limit = 0;
        ArrayList<Integer> starts = new ArrayList<Integer>();
        ArrayList<Integer> ends = new ArrayList<Integer>();
        while((line = in.readLine()) != null) {
            if(line.length() < 1) {
                continue;
            }
            String[] parts = line.split(",");
            starts.add(Integer.parseInt(parts[0]));
            ends.add(Integer.parseInt(parts[1]));
        }
        int[] primes = findPrimes(Collections.max(ends)+1);
        for(int i=0;i<starts.size();i++) {
            System.out.println(primesInRange(starts.get(i),ends.get(i),primes));
        }
    }
}
