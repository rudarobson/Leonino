/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package hex;

/**
 *
 * @author rudarobson
 */
public class HexRecord {

    public final static int DataType = 0;
    public final static int EOF = 1;
    public final static int ExtendedSegmentAddress = 2;
    public final static int ExtendedLinearAddressRecord = 4;
    
    private int type;
    private int extendedAddress;
    private int address;
    private int length;
    private byte[] data = null;
    private int checkSum;

    public int getFullAddress() {
        return extendedAddress + address;
    }
    
    public int getAddress() {
        return address;
    }

    public void setAddress(int Address) {
        this.address = Address;
    }

    public int getCheckSum() {
        return checkSum;
    }

    public void setCheckSum(int CheckSum) {
        this.checkSum = CheckSum;
    }

    public byte[] getData() {
        return data;
    }

    public void setData(byte[] Data) {
        this.data = Data;
    }

    public int getExtendedAddress() {
        return extendedAddress;
    }

    public void setExtendedAddress(int ExtendedAddress) {
        this.extendedAddress = ExtendedAddress;
    }

    public int getLength() {
        return length;
    }

    public void setLength(int Length) {
        this.length = Length;
    }

    public int getType() {
        return type;
    }

    public void setType(int Type) {
        this.type = Type;
    }
}
