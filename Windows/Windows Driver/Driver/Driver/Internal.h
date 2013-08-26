/*++

Module Name:

    Internal.h

Abstract:

    This module contains the local type definitions for the
    driver.

Environment:

    Windows User-Mode Driver Framework (WUDF)

--*/

#pragma once

#include <intsafe.h>
#include <assert.h>

//
// ATL support
//
#include "atlbase.h"
#include "atlcom.h"

//
// Include the WUDF Headers
//

#include "wudfddi.h"
#include "wudfusb.h"

//
// Use specstrings for in/out annotation of function parameters.
//

#include "specstrings.h"

//
// GUID include
//
#include <initguid.h>

//
// Windows IOCTL definitions.
//
#include "winioctl.h"

//
// Device Interface GUID
// 0410b530-9d8f-44b4-be87-5da7780e54fe
//
DEFINE_GUID(GUID_DEVINTERFACE_Driver,
    0x0410b530,0x9d8f,0x44b4,0xbe,0x87,0x5d,0xa7,0x78,0x0e,0x54,0xfe);

//
// Define the tracing flags.
//
// Tracing GUID - c7f6dbe6-ee7b-4f3d-a7f8-3fff98c79ebd
//

#define WPP_CONTROL_GUIDS                                              \
    WPP_DEFINE_CONTROL_GUID(                                           \
        MyDriver1TraceGuid, (c7f6dbe6,ee7b,4f3d,a7f8,3fff98c79ebd), \
                                                                            \
        WPP_DEFINE_BIT(MYDRIVER_ALL_INFO)                              \
        WPP_DEFINE_BIT(TRACE_DRIVER)                                   \
        WPP_DEFINE_BIT(TRACE_DEVICE)                                   \
        WPP_DEFINE_BIT(TRACE_QUEUE)                                    \
        )                             

#define WPP_FLAG_LEVEL_LOGGER(flag, level)                                  \
    WPP_LEVEL_LOGGER(flag)

#define WPP_FLAG_LEVEL_ENABLED(flag, level)                                 \
    (WPP_LEVEL_ENABLED(flag) &&                                             \
     WPP_CONTROL(WPP_BIT_ ## flag).Level >= level)

#define WPP_LEVEL_FLAGS_LOGGER(lvl,flags) \
           WPP_LEVEL_LOGGER(flags)
               
#define WPP_LEVEL_FLAGS_ENABLED(lvl, flags) \
           (WPP_LEVEL_ENABLED(flags) && WPP_CONTROL(WPP_BIT_ ## flags).Level >= lvl)

//
// This comment block is scanned by the trace preprocessor to define our
// Trace function.
//
// begin_wpp config
// FUNC Trace{FLAG=MYDRIVER_ALL_INFO}(LEVEL, MSG, ...);
// FUNC TraceEvents(LEVEL, FLAGS, MSG, ...);
// end_wpp
//

//
// Forward definition of queue.
//
typedef class CMyIoQueue *PCMyIoQueue;

//
// Include the type specific headers.
//
#include "Driver.h"
#include "Device.h"
#include "IoQueue.h"
#include "Logger.h"
//
// Driver specific #defines
//
#define MYDRIVER_TRACING_ID      L"Microsoft\\UMDF\\Driver V1.0"

template <typename T>
inline void DriverSafeRelease(T *&t)
{
      if(t)
            t->Release();
      t = NULL;
}


