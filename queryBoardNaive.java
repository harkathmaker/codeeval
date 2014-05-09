// https://www.codeeval.com/open_challenges/87/
// Test to compare performance of naive matrix with previous list implementation

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;

public class Main {
    public static final int GridSize = 256;
    public static final int ROW = 0;
    public static final int COLUMN = 1;

    public short[][] board = new short[GridSize][GridSize];

    public class BoardChange {
        public BoardChange(int axis, int index, short value) {
            this.axis = axis;
            this.index = index;
            this.value = value;
        }
        int axis;
        int index;
        short value;
    }

    public void processLine(String line) {
        String[] queryArgs = line.split(" ");
        if(queryArgs[0].equals("SetCol")) {
            int col = Integer.parseInt(queryArgs[1]);
            short value = Short.parseShort(queryArgs[2]);
            for(int i=0;i<GridSize;i++) {
                board[i][col] = value;
            }
        } else if(queryArgs[0].equals("SetRow")) {
            int row = Integer.parseInt(queryArgs[1]);
            short value = Short.parseShort(queryArgs[2]);
            for(int i=0;i<GridSize;i++) {
                board[row][i] = value;
            }
        } else if(queryArgs[0].equals("QueryRow")) {
            int row = Integer.parseInt(queryArgs[1]);
            int sum = 0;
            for(int i=0;i<GridSize;i++) {
                sum += board[row][i];
            }
            System.out.println(sum);
        } else if(queryArgs[0].equals("QueryCol")) {
            int col = Integer.parseInt(queryArgs[1]);
            int sum = 0;
            for(int i=0;i<GridSize;i++) {
                sum += board[i][col];
            }
            System.out.println(sum);
        }
    }

    public static void main (String[] args) throws Exception {

        File file = new File(args[0]);
        BufferedReader in = new BufferedReader(new FileReader(file));
        String line;

        Main m = new Main();

        while ((line = in.readLine()) != null) {
            if(line.length() > 0) {
                m.processLine(line);
            }
        }
    }
}
