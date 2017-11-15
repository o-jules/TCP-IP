/**
 * 
 * ```bash
 * javac ./Endian.java
 * java Endian #attention: not `./Endian`
 * ```
 */

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.Arrays;

public class Endian {
  public static void main(String[] args) {

    // `ByteOrder.nativeOrder()` invoked `Bits.byteOrder()` (a non-`public` method)
    // returns a `static` member which could be accessed through source code inspection.
    if (ByteOrder.nativeOrder() == ByteOrder.LITTLE_ENDIAN) {
      System.out.println("Default: <Little> endian.");
    } else if (ByteOrder.nativeOrder() == ByteOrder.BIG_ENDIAN) {
      System.out.printf("Default: <Big> endian.");
    } else {
      System.out.printf("Default: <Unkown> endian.");
    }

    ByteBuffer bb = ByteBuffer.wrap(new byte[12]);
    bb.asCharBuffer().put("abcdef");
    System.out.println(Arrays.toString(bb.array()));

    bb.rewind(); // put the reading cursor at the begining of the buffer zone
    bb.order(ByteOrder.BIG_ENDIAN);
    bb.asCharBuffer().put("abcdef");
    System.out.println(Arrays.toString(bb.array()));


    bb.rewind(); // put the reading cursor at the begining of the buffer zone
    bb.order(ByteOrder.LITTLE_ENDIAN);
    bb.asCharBuffer().put("abcdef");
    System.out.println(Arrays.toString(bb.array()));
  }
}