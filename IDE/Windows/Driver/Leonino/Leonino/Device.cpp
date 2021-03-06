/*++

Module Name:

Device.cpp

Abstract:

This module contains the implementation of the
device driver.

Environment:

Windows User-Mode Driver Framework (WUDF)

--*/
#include "internal.h"
#include "device.tmh"

HRESULT
	CMyDevice::CreateInstanceAndInitialize(
	__in IWDFDriver *FxDriver,
	__in IWDFDeviceInitialize * FxDeviceInit,
	__out CMyDevice **Device
	)
	/*++

	Routine Description:

	This method creates and initializs an instance of the driver's 
	device callback object.

	Arguments:

	FxDeviceInit - the settings for the device.

	Device - a location to store the referenced pointer to the device object.

	Return Value:

	Status

	--*/
{
	//
	// Create a new instance of the device class
	//
	CComObject<CMyDevice> *pMyDevice = NULL;
	HRESULT hr = S_OK;

	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DEVICE, "%!FUNC! Entry");

	hr = CComObject<CMyDevice>::CreateInstance( &pMyDevice );
	if (FAILED(hr))
	{
		TraceEvents(TRACE_LEVEL_ERROR,
			TRACE_DEVICE,
			"%!FUNC! Failed to create device instance %!hresult!",
			hr);
		goto Exit;
	}

	//
	// Initialize the instance.  This calls the WUDF framework,
	// which keeps a reference to the device interface for the lifespan
	// of the device.
	//
	hr = pMyDevice->Initialize(FxDriver, FxDeviceInit);
	if (FAILED(hr))
	{
		TraceEvents(TRACE_LEVEL_ERROR,
			TRACE_DEVICE,
			"%!FUNC! Failed to initialize device %!hresult!",
			hr);
		goto Exit;
	}

	*Device = pMyDevice;

Exit:

	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DEVICE, "%!FUNC! Exit");

	return hr;
}

HRESULT
	CMyDevice::Initialize(
	__in IWDFDriver           * FxDriver,
	__in IWDFDeviceInitialize * FxDeviceInit
	)
	/*++

	Routine Description:

	This method initializes the device callback object and creates the
	partner device object.

	The method should perform any device-specific configuration that:
	*  could fail (these can't be done in the constructor)
	*  must be done before the partner object is created -or-
	*  can be done after the partner object is created and which aren't 
	influenced by any device-level parameters the parent (the driver
	in this case) might set.

	Arguments:

	FxDeviceInit - the settings for this device.

	Return Value:

	status.

	--*/
{
	IWDFDevice *fxDevice = NULL;
	HRESULT hr = S_OK;
	IUnknown *unknown = NULL;

	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DEVICE, "%!FUNC! Entry");

	//
	// Configure things like the locking model before we go to create our 
	// partner device.
	//

	//
	// Set the locking model.
	//

	FxDeviceInit->SetLockingConstraint(None);

	//
	// Set power policy ownership.
	//
	FxDeviceInit->SetPowerPolicyOwnership(TRUE);

	//
	// Any per-device initialization which must be done before 
	// creating the partner object.
	//

	//
	// Create a new FX device object and assign the new callback object to 
	// handle any device level events that occur.
	//

	//
	// We pass an IUnknown reference to CreateDevice, which takes its own
	// reference if everything works.
	//

	hr = this->QueryInterface(__uuidof(IUnknown), (void **)&unknown);
	if (FAILED(hr))
	{
		TraceEvents(TRACE_LEVEL_ERROR,
			TRACE_DEVICE,
			"%!FUNC! Failed to get IUnknown %!hresult!",
			hr);
		goto Exit;
	}

	hr = FxDriver->CreateDevice(FxDeviceInit, unknown, &fxDevice);
	DriverSafeRelease(unknown);
	if (FAILED(hr))
	{
		TraceEvents(TRACE_LEVEL_ERROR,
			TRACE_DEVICE,
			"%!FUNC! Failed to create a framework device %!hresult!",
			hr);
		goto Exit;
	}

	//
	// Set our FxDevice member variable.
	//
	m_FxDevice = fxDevice;

	//
	// Drop the reference we got from CreateDevice.  Since this object
	// is partnered with the framework object they have the same 
	// lifespan - there is no need for an additional reference.
	//

	DriverSafeRelease(fxDevice);

Exit:

	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DEVICE, "%!FUNC! Exit");

	return hr;
}

HRESULT
	CMyDevice::Configure(
	VOID
	)
	/*++

	Routine Description:

	This method is called after the device callback object has been initialized 
	and returned to the driver.  It would setup the device's queues and their 
	corresponding callback objects.

	Arguments:

	FxDevice - the framework device object for which we're handling events.

	Return Value:

	status

	--*/
{

	HRESULT hr = S_OK;

	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DEVICE, "%!FUNC! Entry");

	//
	// Create and configure the I/O queue 
	//
	hr = CMyIoQueue::CreateInstanceAndInitialize(m_FxDevice, this, &m_IoQueue);
	if (FAILED(hr))
	{
		TraceEvents(TRACE_LEVEL_ERROR,
			TRACE_DEVICE,
			"%!FUNC! Failed to create and initialize queue %!hresult!",
			hr);
		goto Exit;
	}

	hr = m_IoQueue->Configure();
	if (FAILED(hr))
	{
		TraceEvents(TRACE_LEVEL_ERROR,
			TRACE_DEVICE,
			"%!FUNC! Failed to configure queue %!hresult!",
			hr);
		goto Exit;
	} 

	//
	// Create Device Interface
	//
	hr = m_FxDevice->CreateDeviceInterface(&GUID_DEVINTERFACE_Leonino,NULL);
	if (FAILED(hr))
	{
		TraceEvents(TRACE_LEVEL_ERROR,
			TRACE_DEVICE,
			"%!FUNC! Failed to create device interface %!hresult!",
			hr);
		goto Exit;
	}

Exit:

	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DEVICE, "%!FUNC! Exit");

	return hr;
}

HRESULT
	CMyDevice::OnPrepareHardware(
	__in IWDFDevice * /* FxDevice */
	)
	/*++

	Routine Description:

	This routine is invoked to ready the driver
	to talk to hardware.

	Arguments:

	FxDevice  : Pointer to the WDF device interface

	Return Value:

	HRESULT 

	--*/
{
	HRESULT hr;
	IWDFUsbTargetFactory *usbFactory = NULL;
	IWDFUsbTargetDevice *usbDevice = NULL;

	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DEVICE, "%!FUNC! Entry");

	hr = m_FxDevice->QueryInterface(IID_PPV_ARGS(&usbFactory));

	if (FAILED(hr))
	{
		TraceEvents(TRACE_LEVEL_ERROR,
			TRACE_DEVICE,
			"%!FUNC! Failed to get USB target factory %!hresult!",
			hr);
		goto Exit;
	}

	hr = usbFactory->CreateUsbTargetDevice(&usbDevice);

	if (FAILED(hr))
	{
		TraceEvents(TRACE_LEVEL_ERROR,
			TRACE_DEVICE,
			"%!FUNC! Failed to create USB target device %!hresult!",
			hr);

		goto Exit;
	}

	//
	// Store a weak reference in a private data member. Because it is an object
	// in the WDF object tree, the object will be alive until we delete it
	// explicitly in ReleaseHardware.
	//
	m_FxUsbDevice = usbDevice;

	this->CreateUsbIoTargets();

Exit:

	DriverSafeRelease(usbDevice);

	DriverSafeRelease(usbFactory);

	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DEVICE, "%!FUNC! Exit");

	return hr;
}


HRESULT
	CMyDevice::OnReleaseHardware(
	__in IWDFDevice * /* FxDevice */
	)
	/*++

	Routine Description:

	This routine is invoked when the device is being removed or stopped
	It releases all resources allocated for this device.

	Arguments:

	FxDevice - Pointer to the Device object.

	Return Value:

	HRESULT - Always succeeds.

	--*/
{
	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DEVICE, "%!FUNC! Entry");

	if (m_FxUsbDevice != NULL) {

		m_FxUsbDevice->DeleteWdfObject();
		m_FxUsbDevice = NULL;

		m_In_Pipe->DeleteWdfObject();
		m_In_Pipe = NULL;

		m_Out_Pipe->DeleteWdfObject();
		m_Out_Pipe = NULL;

		DriverSafeRelease(m_pUsbInterface);
	}

	TraceEvents(TRACE_LEVEL_INFORMATION, TRACE_DEVICE, "%!FUNC! Exit");

	return S_OK;
}



//
//Helpers
//
IWDFUsbTargetPipe *CMyDevice::GetInPipe(){
	return m_In_Pipe;
}

IWDFUsbTargetPipe *CMyDevice::GetOutPipe(){
	return m_Out_Pipe;
}

HRESULT CMyDevice::CreateUsbIoTargets(){
	HRESULT hr;
	IWDFUsbInterface *pUsbInterface = NULL;
	UCHAR num_int = m_FxUsbDevice->GetNumInterfaces();
	IWDFUsbTargetPipe *endp1_in = NULL;
	IWDFUsbTargetPipe *endp2_out = NULL;

	UNREFERENCED_PARAMETER(num_int);
	hr = m_FxUsbDevice->RetrieveUsbInterface(0,&pUsbInterface);
	m_pUsbInterface = pUsbInterface;

	if(FAILED(hr)){
		TraceEvents(TRACE_LEVEL_ERROR,
			TRACE_DEVICE,
			"%!FUNC! Unable to retrieve interface descriptor");

		goto Exit;
	}else
	{
		UCHAR numEndpoints = pUsbInterface->GetNumEndPoints();

		for(UCHAR i = 0;i < numEndpoints;i++){

			IWDFUsbTargetPipe *pipe = NULL;
			hr = pUsbInterface->RetrieveUsbPipeObject(i,&pipe);

			if(SUCCEEDED(hr)){
				
				if(pipe->IsInEndPoint() && UsbdPipeTypeBulk == pipe->GetType()){
					endp1_in = pipe;
				}else if(pipe->IsOutEndPoint() && UsbdPipeTypeBulk == pipe->GetType()){
					endp2_out = pipe;
				}else{
					TraceEvents(TRACE_LEVEL_ERROR,
						TRACE_DEVICE,
						"%!FUNC! Transfer type doesn't match");

					hr = E_UNEXPECTED;

					DriverSafeRelease(endp1_in);
					DriverSafeRelease(endp2_out);
				}

			}else{
				TraceEvents(TRACE_LEVEL_ERROR,
					TRACE_DEVICE,
					"%!FUNC! Cant get USBPIPE");

				Logger::Log("Cant get USBPIPE\n");

				DriverSafeRelease(endp1_in);
				DriverSafeRelease(endp2_out);
			}
		}

		if(SUCCEEDED(hr)){
			this->m_In_Pipe = endp1_in;
			this->m_Out_Pipe = endp2_out;
			LONG timeout;

			timeout = 5000;//5.000 milliseconds = 5 seconds
			hr = m_In_Pipe->SetPipePolicy( PIPE_TRANSFER_TIMEOUT,sizeof(timeout),&timeout);

			hr = m_Out_Pipe->SetPipePolicy( PIPE_TRANSFER_TIMEOUT,sizeof(timeout),&timeout);

		}
	}

Exit:
	//DriverSafeRelease(pUsbInterface);

	return hr;
}

IWDFUsbInterface *CMyDevice::GetUsbInterface(){
	return m_pUsbInterface;
}