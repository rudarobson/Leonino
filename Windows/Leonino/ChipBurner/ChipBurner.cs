using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Hex;


namespace Hex
{
    class HexParser
    {
        static void Write(string hexFileName)
        {
            HexParser hexParser = new HexParser(hexFileName);
            hexParser.StartReading();
            int pageSize = 32;

            HexRecord record = hexParser.ReadLine();
            byte[] data = new byte[pageSize];


            int totalWritten = 0;

            Commander cmd = new Commander();
            try
            {
                FileStream usb = cmd.GetUSB();
                byte[] nill = new byte[100];
                //    usb.Read(nill, 0, 100);
            }
            catch
            {
            }

            if (cmd.BeginProgramming())
            {
                cmd.ChipErase();

                while (record.Type != HexRecord.EOF)
                {
                    switch (record.Type)
                    {
                        case HexRecord.DataType:
                            for (int i = 0; i < record.Length; i++)
                            {
                                if (totalWritten == pageSize || (((record.FullAddress + i) / (2 * pageSize)) != (cmd.Address / pageSize)))
                                {
                                    cmd.Write(data, totalWritten);
                                    cmd.Address = (int)(cmd.Address) + (totalWritten / 2);

                                    totalWritten = 0;
                                }

                                data[totalWritten++] = record.Data[i];
                            }

                            break;
                        case HexRecord.ExtendedLinearAddressRecord:
                        case HexRecord.ExtendedSegmentAddress:
                            throw new Exception("Not Supporte Yet");
                    }
                    record = hexParser.ReadLine();
                }

                if (totalWritten != 0)
                    cmd.Write(data, totalWritten);
            }
            cmd.Dispose();

            hexParser.Dispose();
        }

        static bool Verify(string hexFileName)
        {
            HexParser hexParser = new HexParser(hexFileName);
            hexParser.StartReading();
            int pageSize = 32;

            HexRecord record = hexParser.ReadLine();
            byte[] data = new byte[pageSize];

            Commander cmd = new Commander();
            try
            {
                FileStream usb = cmd.GetUSB();
                byte[] nill = new byte[100];
                //    usb.Read(nill, 0, 100);
            }
            catch
            {
            }
            bool success = true;
            if (cmd.BeginProgramming())
            {
                while (record.Type != HexRecord.EOF && success)
                {
                    switch (record.Type)
                    {
                        case HexRecord.DataType:
                            cmd.Address = record.Address / 2;
                            cmd.Read(data, record.Length);
                            for (int i = 0; i < record.Length; i++)
                            {
                                if (data[i] != record.Data[i])
                                {
                                    success = false;
                                    break;
                                }
                            }

                            break;
                        case HexRecord.ExtendedLinearAddressRecord:
                        case HexRecord.ExtendedSegmentAddress:
                            throw new Exception("Not Supporte Yet");
                    }
                    record = hexParser.ReadLine();
                }

            }
            cmd.Dispose();

            hexParser.Dispose();

            return success;
        }

        static void Run(bool run)
        {
            Commander cmd = new Commander();
            cmd.Start(run);
        }
        static void Main(string[] args)
        {
            //Write(@"C:\Users\rudarobson\Desktop\led.hex");
            //if (!Verify(@"C:\Users\rudarobson\Desktop\led.hex"))
            //{
            //    throw new Exception("Error!");
            //}
            //Run(false);
            Commander cmd = new Commander();
            FileStream usbStream = cmd.GetUSB();
            byte[] writeb = new byte[40];
            byte[] readb = new byte[40];
            writeb[0] = 1;
            writeb[1] = 0x20;
            writeb[2] = 0;
            writeb[3] = 2;
            writeb[4] = 0xD7;
            writeb[5] = 0xFF;
            usbStream.Write(writeb, 0, 6);
            usbStream.Flush();
            usbStream.Read(readb, 0, 2);

            for (int i = 0; i < 2; i++)
            {
                if (readb[i] != writeb[i + 4])
                {
                    int x = 1;
                    x++;
                }
            }
            
        }
    }
}
