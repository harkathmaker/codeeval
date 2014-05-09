// https://www.codeeval.com/open_challenges/87/

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;

public class Main {
    public static final int GridSize = 256;
    public static final int ROW = 0;
    public static final int COLUMN = 1;

    ArrayList<BoardChange> changeList = new ArrayList<BoardChange>();

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
            BoardChange b = new BoardChange(COLUMN, Integer.parseInt(queryArgs[1]), Short.parseShort(queryArgs[2]));
            changeList.add(b);
        } else if(queryArgs[0].equals("SetRow")) {
            changeList.add(new BoardChange(ROW, Integer.parseInt(queryArgs[1]), Short.parseShort(queryArgs[2])));
        } else if(queryArgs[0].equals("QueryRow")) {
            System.out.println(getSum(changeList, ROW, Integer.parseInt(queryArgs[1])));
        } else if(queryArgs[0].equals("QueryCol")) {
            System.out.println(getSum(changeList, COLUMN, Integer.parseInt(queryArgs[1])));
        }
    }

    public int getSum(ArrayList<BoardChange> changeList, int axis, int index) {
        int sum = 0;
        HashMap<Integer,Short> cellChanges = new HashMap<Integer,Short>(8);

        for(int i=changeList.size()-1;i>=0;i--) {
            BoardChange c = changeList.get(i);
            if(c.axis == axis && c.index == index) {
                // The row/column was updated to this so any earlier changes are irrelevant
                return sum + c.value * (GridSize-cellChanges.size());
            } else if(c.axis != axis) {
                if(!cellChanges.containsKey(c.index)) {
                    cellChanges.put(c.index,c.value);
                    sum += c.value;
                }
            }
        }
        return sum;
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
