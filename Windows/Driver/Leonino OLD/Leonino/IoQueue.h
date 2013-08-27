/*++

Module Name:

    IoQueue.h

Abstract:

    This file defines the queue callback interface.

Environment:

    Windows User-Mode Driver Framework (WUDF)

--*/

#pragma once

//
// Queue Callback Object.
//

class CMyIoQueue :
    public CComObjectRootEx<CComMultiThreadModel>,
    public IQueueCallbackDeviceIoControl,
	public IQueueCallbackRead,
	public IQueueCallbackWrite
	//public IRequestCallbackRequestCompletion
	
{

public:

    DECLARE_NOT_AGGREGATABLE(CMyIoQueue)

    BEGIN_COM_MAP(CMyIoQueue)
        COM_INTERFACE_ENTRY(IQueueCallbackDeviceIoControl)
		COM_INTERFACE_ENTRY(IQueueCallbackRead)
		COM_INTERFACE_ENTRY(IQueueCallbackWrite)
		//COM_INTERFACE_ENTRY(IRequestCallbackRequestCompletion)
    END_COM_MAP()

    CMyIoQueue() : 
        m_FxQueue(NULL),
        m_Device(NULL)
    {
    }

    ~CMyIoQueue()
    {
        // empty
    }

    HRESULT
    Initialize(
        __in IWDFDevice *FxDevice,
        __in CMyDevice *MyDevice
        );

    static 
    HRESULT 
    CreateInstanceAndInitialize( 
        __in IWDFDevice *FxDevice,
        __in CMyDevice *MyDevice,
        __out CMyIoQueue**    Queue
        );

    HRESULT
    Configure(
        VOID
        )
    {
        return S_OK;
    }

    //
    // Wdf Callbacks
    //

    //    
    // IQueueCallbackDeviceIoControl
    //
    virtual
    VOID
    STDMETHODCALLTYPE
    OnDeviceIoControl( 
        __in IWDFIoQueue *pWdfQueue,
        __in IWDFIoRequest *pWdfRequest,
        __in ULONG ControlCode,
        __in SIZE_T InputBufferSizeInBytes,
        __in SIZE_T OutputBufferSizeInBytes
        );

	////
	//// IQueueCallbackWrite
	////
	virtual
		VOID
		STDMETHODCALLTYPE
		OnWrite(
		_In_ IWDFIoQueue *pWdfQueue,
		_In_ IWDFIoRequest *pWdfRequest,
		_In_ SIZE_T NumOfBytesToWrite
		);

	//
	// IQueueCallbackRead
	//
	virtual
		VOID
		STDMETHODCALLTYPE
		OnRead(
		_In_ IWDFIoQueue *pWdfQueue,
		_In_ IWDFIoRequest *pWdfRequest,
		_In_ SIZE_T NumOfBytesToRead
		);

	//
	//IRequestCallbackRequestCompletion
	//

	/*virtual
		VOID
		STDMETHODCALLTYPE
		OnCompletion (
		_In_ IWDFIoRequest*                 pWdfRequest,
		_In_ IWDFIoTarget*                  pIoTarget,
		_In_ IWDFRequestCompletionParams*   pParams,
		_In_ PVOID                          pContext
		);*/


	//
	//IQueueCallbackIoStop
	//

	//virtual
	//	VOID
	//	STDMETHODCALLTYPE
	//	OnStop(
	//	_In_ IWDFIoQueue *   pWdfQueue,
	//	_In_ IWDFIoRequest * pWdfRequest,
	//	_In_ ULONG           ActionFlags
	//	);


	//
	// Private member variables.
	//
//
// Private member variables.
//
private:

    //
    // Weak reference to framework queue object.
    //
    IWDFIoQueue *               m_FxQueue;

    //
    // Pointer to device class.
    //
    CMyDevice *                  m_Device;

};
