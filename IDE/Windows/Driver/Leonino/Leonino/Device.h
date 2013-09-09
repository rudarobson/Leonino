/*++

Module Name:

    Device.h

Abstract:

    This module contains the type definitions of the
    device driver.

Environment:

    Windows User-Mode Driver Framework (WUDF)

--*/

#pragma once

//
// Class for the device.
//

class CMyDevice :
    public CComObjectRootEx<CComMultiThreadModel>,
    public IPnpCallbackHardware
{

public:

    DECLARE_NOT_AGGREGATABLE(CMyDevice)

    BEGIN_COM_MAP(CMyDevice)
        COM_INTERFACE_ENTRY(IPnpCallbackHardware)
    END_COM_MAP()

    CMyDevice() :
        m_FxDevice(NULL),
        m_IoQueue(NULL),
        m_FxUsbDevice(NULL)
    {
    }

    ~CMyDevice()
    {
    }

//
// Private data members.
//
private:

    //
    // Weak reference to framework device object.
    //
    IWDFDevice *            m_FxDevice;

    //
    // Weak reference to I/O queue
    //
    CMyIoQueue *            m_IoQueue;

    //
    // Weak reference to framework USB device
    //
    IWDFUsbTargetDevice *   m_FxUsbDevice;

	//
	// Weak reference to a winUsbPipe
	//
	IWDFUsbInterface *m_pUsbInterface;
	//
	// Endpoint pipes
	//
	IWDFUsbTargetPipe *m_In_Pipe;//endp 1
	IWDFUsbTargetPipe *m_Out_Pipe;//endp 2
//
// Private methods.
//
private:

    HRESULT
    Initialize(
        __in IWDFDriver *FxDriver,
        __in IWDFDeviceInitialize *FxDeviceInit
        );

//
// Public methods
//
public:
	//
	//Helpers
	//
	IWDFDevice *GetFxDevice(){
		return m_FxDevice;
	}
	IWDFUsbTargetDevice *GetFxUsbDevice(){
		return m_FxUsbDevice;
	}
	HRESULT CreateUsbIoTargets();
	IWDFUsbTargetPipe* GetInPipe();
	IWDFUsbTargetPipe* GetOutPipe();

    //
    // The factory method used to create an instance of this driver.
    //
    
    static
    HRESULT
    CreateInstanceAndInitialize(
        __in IWDFDriver *FxDriver,
        __in IWDFDeviceInitialize *FxDeviceInit,
        __out CMyDevice **Device
        );

    HRESULT
    Configure(
        VOID
        );

//
// COM methods
//
public:

    //
    // IPnpCallbackHardware
    //

    virtual
    HRESULT
    STDMETHODCALLTYPE
    OnPrepareHardware(
            __in IWDFDevice *FxDevice
            );

    virtual
    HRESULT
    STDMETHODCALLTYPE
    OnReleaseHardware(
        __in IWDFDevice *FxDevice
        );

	IWDFUsbInterface *GetUsbInterface();

};


