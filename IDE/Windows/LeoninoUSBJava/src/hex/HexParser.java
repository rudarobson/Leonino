/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package hex;

import java.io.*;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author rudarobson
 */
public class HexParser {

    private static int DATALENOFFSET = 1;
    private static int DATAOFFSET = 9;
    private static int ADDRESSOFFSET = 3;
    private static int TYPEOFFSET = 7;
    private String FilePath;
    private BufferedReader File;
    private int Endianess;
    public int LastAddressOffset = 0;

    public HexParser(String filePath) {
        this(filePath, 0);
    }

    public HexParser(String filePath, int endianness) {
        FilePath = filePath;
        Endianess = endianness;
    }

    public void StartReading() throws FileNotFoundException {
        LastAddressOffset = 0;
        if (File == null) {
            File = new BufferedReader(new FileReader(FilePath));
        }
    }

    public HexRecord ReadLine() {
        HexRecord record = new HexRecord();
//        if (File.EndOfStream) {
//            record.Type = HexRecord.EOF;
//            return record;
//        }
        try {
            String line = File.readLine();

            record.setType(RecordType(line));
            String data = null;
            switch (record.getType()) {
                case HexRecord.DataType:
                    data = RecordData(line);

                    record.setAddress(LastAddressOffset);
                    record.setAddress(HexToWord(RecordDataAddress(line)));
                    record.setLength(RecordDataLength(line));
                    record.setCheckSum(0);
                    record.setData(new byte[record.getLength()]);

                    for (int i = 0; i < data.length(); i += 2)//two because it's in Hex characters, 2 character = 1 byte
                    {
                        record.getData()[i / 2] = (byte) ((HexToByte(data.charAt(i)) << 4) | HexToByte(data.charAt(i + 1)));
                    }

                    break;
                case HexRecord.EOF:
                    break;
                case HexRecord.ExtendedSegmentAddress:
                    break;
                case HexRecord.ExtendedLinearAddressRecord:
                    data = RecordData(line);
                    record.setLength(RecordDataLength(line));
                    record.setData(new byte[record.getLength()]);
                    for (int i = 0; i < data.length(); i += 2)//two because it's in Hex characters, 2 character = 1 byte
                    {
                        record.getData()[i / 2] = (byte) ((HexToByte(data.charAt(i)) << 4) | HexToByte(data.charAt(i + 1)));
                    }


                    record.setExtendedAddress((record.getData()[0] << 8) | record.getData()[1]);
                    LastAddressOffset = record.getExtendedAddress() << 16;
                    break;

            }
        } catch (Exception ex) {
        }
        return record;
    }

    private String RecordDataAddress(String block) {
        return block.substring(ADDRESSOFFSET, ADDRESSOFFSET + 4);
    }

    private byte HexToByte(char hex) {
        return HexConverter.HexToByte(hex);
    }

    private int HexToWord(String hex) {
        return (int) HexConverter.HexToMax4Bytes(hex);
    }

    private int RecordType(String block) {
        int type = HexToByte(block.charAt(TYPEOFFSET)) * 16 + HexToByte(block.charAt(TYPEOFFSET + 1));
        switch (type) {

            case HexRecord.DataType:
                return HexRecord.DataType;
            case HexRecord.EOF:
                return HexRecord.EOF;
            case HexRecord.ExtendedSegmentAddress:
                return HexRecord.ExtendedSegmentAddress;
            case HexRecord.ExtendedLinearAddressRecord:
                return HexRecord.ExtendedLinearAddressRecord;
            default:
                throw new RuntimeException("Record Type Unknown!");
        }
    }

    private int RecordDataLength(String block) {
        return HexToByte(block.charAt(DATALENOFFSET)) * 16 + HexToByte(block.charAt(DATALENOFFSET + 1));
    }

    private String RecordData(String block) {
        int type = RecordType(block);

        if (type == HexRecord.EOF) {
            return null;
        }

        int len = RecordDataLength(block);
        String ret = block.substring(DATAOFFSET, DATAOFFSET + 2 * len);

        return ret;
    }

    public void Dispose() {
        try {
            File.close();
        } catch (IOException ex) {
            throw new RuntimeException();
        }
    }
}
