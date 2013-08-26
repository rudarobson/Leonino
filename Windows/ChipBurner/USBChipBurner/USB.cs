using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace USBChipBurner
{
    public class USB
    {
        [DllImport("GetDevPath.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
        public static extern Boolean GetDeviceHandle([In] ref Guid guid, ref IntPtr handle);

        static void Main(string[] args)
        {
            Guid guid = new Guid(0x0410b530, 0x9d8f, 0x44b4, 0xbe, 0x87, 0x5d, 0xa7, 0x78, 0x0e, 0x54, 0xfe);
            IntPtr handle = IntPtr.Zero;
            GetDeviceHandle(ref guid, ref handle);

            FileStream usb = new FileStream(handle, FileAccess.ReadWrite);
            byte[] buf = new byte[200];
            int totalRead = 0;
            try
            {
                totalRead = usb.Read(buf, 0, 9);
            }
            catch
            {
            }
            buf[0] = 0;
            usb.Write(buf, 0, 1);
            usb.Flush();
            totalRead = usb.Read(buf, 0, 4);
            usb.Close();


        }
    }
}
