/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package leoninousb;

import com.sun.jna.*;
import com.sun.jna.platform.win32.Guid.*;
import com.sun.jna.platform.win32.*;
import com.sun.jna.ptr.*;
import com.sun.jna.win32.*;
import java.nio.*;
import java.util.*;

/**
 *
 * @author rudarobson
 */
public class USBLowLevel {

    protected interface UsbLibrary extends StdCallLibrary {
        boolean GetDeviceHandle(GUID guid, PointerByReference handle);
    }

    protected interface FlushLibrary extends StdCallLibrary {
        boolean FlushFileBuffers(WinNT.HANDLE hFile);//wat Pointer instead of WinNt.HANDLE
    }
    
    private Kernel32 kernel32 = null;
    private FlushLibrary kernel32flush = null;
    private UsbLibrary usbHandler = null;
    private WinNT.HANDLE usbStream = null;

    public USBLowLevel() {
        kernel32 = (Kernel32) Native.loadLibrary(Kernel32.class, W32APIOptions.UNICODE_OPTIONS);
        kernel32flush = (FlushLibrary) Native.loadLibrary("kernel32.dll", FlushLibrary.class);
        System.setProperty("jna.library.path","C:/Users/rudarobson/Documents/GitHub/Leonino/IDE/Windows/LeoninoUSBJava/Dlls");

        usbHandler = (UsbLibrary) Native.loadLibrary(
                "LeoninoUSB.dll",
                UsbLibrary.class,
                new HashMap() {

                    {
                        put(Library.OPTION_FUNCTION_MAPPER, new StdCallFunctionMapper());
                    }
                });
    }

    public void open() {
        PointerByReference handle = new PointerByReference();
        usbHandler.GetDeviceHandle(Guids.LionOne, handle);
        usbStream = new WinNT.HANDLE(handle.getValue());
    }

    public void close() {
        if (usbStream != null) {
            kernel32.CloseHandle(usbStream);
        }

    }

    public int read(byte[] data, int maxCount) {
        IntByReference numRead = new IntByReference();
        ByteBuffer dataBuf = ByteBuffer.allocate(maxCount);
        kernel32.ReadFile(usbStream, dataBuf, maxCount, numRead, null);
        dataBuf.get(data, 0, numRead.getValue());
        return numRead.getValue();//numRead.getValue();
    }

    public int write(byte[] data, int count) {
        IntByReference numWriten = new IntByReference();
        kernel32.WriteFile(usbStream, data, count, numWriten, null);
        return numWriten.getValue();
    }

    public void flush() {
        kernel32flush.FlushFileBuffers(usbStream);
    }
}
