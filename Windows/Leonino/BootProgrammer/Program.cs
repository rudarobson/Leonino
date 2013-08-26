using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Hex;
using System.IO;
using Leonino.USB;

namespace BootProgrammer
{
    class Program
    {
        public const int dataOffset = 4;
        public const int pageSize = 32;
        public const int MAXDATASIZE = pageSize;
        public const int MAXPACKETSIZE = MAXDATASIZE + dataOffset;


        public static byte[] dataToWrite = new byte[200];
        public static int dataToWriteCount = 0;
        public static int addressToWrite = -1;

        public const byte write_flash = 1;
        public const byte erase_fkash = 2;
        public const byte boot_end = 3;

        public static void FlushToWriteData(FileStream usb)
        {
            byte[] dataRead = new byte[MAXPACKETSIZE];
            int bytesRead = 0;
            int count = dataToWriteCount > MAXDATASIZE ? MAXDATASIZE : dataToWriteCount;

            dataToWrite[0] = write_flash;
            dataToWrite[1] = (byte)((addressToWrite >> 8) & 0xFF);
            dataToWrite[2] = (byte)(addressToWrite & 0xFF);
            dataToWrite[3] = (byte)(count & 0xff);

            usb.Write(dataToWrite, 0, dataOffset + count);
            usb.Flush();
            bytesRead = usb.Read(dataRead, 0, dataOffset + count);
            for (int i = 0; i < bytesRead; i++)
            {
                if (dataRead[i] != dataToWrite[i])
                    throw new Exception("Data Not Writtern");
            }

            for (int i = 0; i < dataToWriteCount - count; i++)
                dataToWrite[dataOffset + i] = dataToWrite[dataOffset + i + count];

            dataToWriteCount -= count;

        }
        public static void SimulateWrite(byte[] data, int address, int count, FileStream usb)
        {
            if (address < 0x300000)//not config WORD
            {
                if (address < 0x2000)
                    throw new Exception("Trying to Overwrite Bootloader!");

                if (addressToWrite == -1)//just to set first address
                    addressToWrite = address;

                if (dataToWriteCount >= MAXDATASIZE || ((addressToWrite / pageSize) != (address / pageSize)))//Full buffer or different pages
                {
                    FlushToWriteData(usb);
                    addressToWrite = address;
                }

                data.CopyTo(dataToWrite, dataOffset + dataToWriteCount);
                dataToWriteCount += count;


            }
        }

        public static void End(FileStream usb)
        {
            FlushToWriteData(usb);

            byte[] dataRec = new byte[2];
            dataRec[0] = boot_end;
            usb.Write(dataRec, 0, 1);//write [0] = 0x00 packet to signal end
            usb.Flush();
            dataRec[0] = 1;
            usb.Read(dataRec, 0, 2);
            if (dataRec[0] != 'O' && dataRec[1] != 'K')
                throw new Exception("Couldn't start User APP");
        }

        public static void Erase(int address, FileStream usb)
        {
            if (address < 0x300000)//not config WORD
            {
                if (address < 0x2000)
                    throw new Exception("Trying to Overwrite Bootloader!");
                byte[] dataRec = new byte[4];
                dataRec[0] = erase_fkash;
                dataRec[1] = (byte)((address >> 8) & 0xFF);
                dataRec[2] = (byte)(address & 0xFF);
                usb.Write(dataRec, 0, 3);
                usb.Flush();
                int readBytes = usb.Read(dataRec, 0, 2);
                if (dataRec[0] != 'O' && dataRec[1] != 'K')
                    throw new Exception("Couldn't Erase");
            }
        }

        static void Write(string hexFileName, int type)
        {
            HexParser hexParser = new HexParser(hexFileName);
            hexParser.StartReading();

            HexRecord record = hexParser.ReadLine();

            LowLevelWrite usbHelper = new LowLevelWrite();
            FileStream usb = usbHelper.GetStream();
            try
            {
                while (record.Type != HexRecord.EOF)
                {
                    switch (record.Type)
                    {
                        case HexRecord.DataType:
                            switch (type)
                            {
                                case write_flash:
                                    SimulateWrite(record.Data, record.Address, record.Length, usb);
                                    break;
                                case erase_fkash:
                                    Erase(record.Address, usb);
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
                if (type == write_flash)
                {
                    FlushToWriteData(usb);
                    End(usb);
                }
            }
            finally
            {
                usbHelper.Dispose();//usb.Close() is called
                hexParser.Dispose();
            }
        }

        static void Main(string[] args)
        {
            string hexFileName = @"C:\Users\rudarobson\Desktop\app.hex";
            Write(hexFileName, erase_fkash);
            Write(hexFileName, write_flash);
        }
    }
}
