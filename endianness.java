// https://www.codeeval.com/open_challenges/15/

import java.nio.ByteOrder;


public class Main {
    public static void main (String[] args) throws Exception {
        if (ByteOrder.nativeOrder().equals(ByteOrder.BIG_ENDIAN)) {
          System.out.println("BigEndian");
        } else {
          System.out.println("LittleEndian");
        }
    }
}
