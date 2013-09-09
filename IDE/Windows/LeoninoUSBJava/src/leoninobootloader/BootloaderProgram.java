/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package leoninobootloader;

import hex.HexParser;
import hex.HexRecord;
import leoninousb.USBLowLevel;

/**
 *
 * @author rudarobson
 */
public class BootloaderProgram {

    public final static int dataOffset = 4;
    public final static int pageSize = 32;
    public final static int MAXDATASIZE = pageSize;
    public final static int MAXPACKETSIZE = MAXDATASIZE + dataOffset;
    public final static byte write_flash = 1;
    public final static byte erase_flash = 2;
    public final static byte boot_end = 3;
    public static byte[] dataToWrite = new byte[200];
    public static int dataToWriteCount = 0;
    public static int addressToWrite = -1;

    private static void resetVariables() {
        dataToWriteCount = 0;
        addressToWrite = -1;
    }

    private static void FlushToWriteData(USBLowLevel usb) {
        byte[] dataRead = new byte[MAXPACKETSIZE];
        int bytesRead = 0;
        int count = dataToWriteCount > MAXDATASIZE ? MAXDATASIZE : dataToWriteCount;

        dataToWrite[0] = write_flash;
        dataToWrite[1] = (byte) (addressToWrite & 0xFF);//little endian
        dataToWrite[2] = (byte) ((addressToWrite >> 8) & 0xFF);
        dataToWrite[3] = (byte) (count & 0xff);

        usb.write(dataToWrite, dataOffset + count);
        usb.flush();
        bytesRead = usb.read(dataRead, dataOffset + count);
//        for (int i = 0; i < bytesRead; i++) {
//            if (dataRead[i] != dataToWrite[i]) {
//                streamWriter.WriteLine("{0:x0000} \t {3:x} \t\t {1:x00}:{2:x00}", addressToWrite, dataRead[i], dataToWrite[i], i - dataOffset);
//            }
//            //                    throw new Exception("Data Not Writtern");
//        }

        for (int i = 0; i < dataToWriteCount - count; i++) {
            dataToWrite[dataOffset + i] = dataToWrite[dataOffset + i + count];
        }

        dataToWriteCount -= count;
    }

    private static void SimulateWrite(byte[] data, int address, int count, USBLowLevel usb) {
        if (address < 0x300000)//not config WORD
        {
            if (address < 0x2000) {
                throw new RuntimeException("Trying to Overwrite Bootloader!");
            }

            if (addressToWrite == -1)//just to set first address
            {
                addressToWrite = address;
            }

            if (dataToWriteCount >= MAXDATASIZE || ((addressToWrite / pageSize) != (address / pageSize)))//Full buffer or different pages
            {
                FlushToWriteData(usb);
                addressToWrite = address;
            }

            for (int i = 0; i < count; i++) {
                dataToWrite[dataOffset + dataToWriteCount + i] = data[i];
            }

            dataToWriteCount += count;


        }
    }

    private static void End(USBLowLevel usb) {
        byte[] dataRec = new byte[2];
        dataRec[0] = boot_end;
        usb.write(dataRec, 1);//write [0] = 0x00 packet to signal end
        usb.flush();
        dataRec[0] = 1;
        usb.read(dataRec, 2);
        if (dataRec[0] != 'O' && dataRec[1] != 'K') {
            throw new RuntimeException("Couldn't start User APP");
        }
    }

    public static void Erase(int address, USBLowLevel usb) {
        resetVariables();
        if (address < 0x300000)//not config WORD
        {
            if (address < 0x2000) {
                throw new RuntimeException("Trying to Overwrite Bootloader!");
            }
            byte[] dataRec = new byte[4];
            dataRec[0] = erase_flash;
            dataRec[1] = (byte) (address & 0xFF);//little endian
            dataRec[2] = (byte) ((address >> 8) & 0xFF);
            usb.write(dataRec, 3);
            usb.flush();
            int readBytes = usb.read(dataRec, 2);
            if (dataRec[0] != 'O' && dataRec[1] != 'K') {
                throw new RuntimeException("Couldn't Erase");
            }
        }
    }

    public static void Write(String hexFileName, int type) {
        resetVariables();
        HexParser hexParser = new HexParser(hexFileName);

        USBLowLevel usb = null;
        HexRecord record = null;
        try {
            hexParser.StartReading();

            record = hexParser.ReadLine();

            usb = new USBLowLevel();
            usb.open();
            while (record.getType() != HexRecord.EOF) {
                switch (record.getType()) {
                    case HexRecord.DataType:
                        switch (type) {
                            case write_flash:
                                SimulateWrite(record.getData(), record.getAddress(), record.getLength(), usb);
                                break;
                            case erase_flash:
                                Erase(record.getAddress(), usb);
                                break;
                        }


                        break;
                    case HexRecord.ExtendedLinearAddressRecord:
                    case HexRecord.ExtendedSegmentAddress:
                        throw new Exception("Not Supporte Yet");
                    case HexRecord.EOF:

                        break;
                }
                record = hexParser.ReadLine();
            }
            if (type == write_flash) {
                FlushToWriteData(usb);
                End(usb);
            }

        } catch (Exception ex) {
        } finally {
            if (usb != null) {
                usb.close();//usb.Close() is called
            }
            if (hexParser != null) {
                hexParser.Dispose();
            }
        }
    }
}
