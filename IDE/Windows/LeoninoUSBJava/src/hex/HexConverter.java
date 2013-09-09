/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package hex;

/**
 *
 * @author rudarobson
 */
public class HexConverter {

    public static byte HexToByte(char hex) {
        if (hex >= 0x30 && hex <= 0x39) {
            return (byte) (hex - 0x30);
        }
        if (hex >= 0x41 && hex <= 0x46) {
            return (byte) (hex - 0x41 + 0xA);
        }
        if (hex >= 0x61 && hex <= 0x66) {
            return (byte) (hex - 0x61 + 0xA);
        }

        throw new RuntimeException("Unknown Hex Char: " + hex);
    }

    public static int HexToMax4Bytes(String hex) {
        if (hex == null) {
            return 0;
        }

        int len = hex.length();

        if (len < 0) {
            return 0;
        }

        int i = 0;
        int word = 0;
        for (i = 0; i < len; i++) {
            word |= (((int) HexToByte(hex.charAt(i))) << 4 * (len - i - 1));
        }

        return word;
    }

    public static long HexToMax8Bytes(String hex) {
        if (hex == null) {
            return 0;
        }

        int len = hex.length();

        if (len < 0) {
            return 0;
        }

        int i = 0;
        long word = 0;

        for (i = 0; i < len; i++) {
            word |= (((long) HexToByte(hex.charAt(i))) << (4 * (len - i - 1)));
        }

        return word;
    }
}
