#include "event_sink.h"

#include "_CoreScanner_i.c"
#include <iostream>
#include <string>
#include "afxdisp.h"  // MFC Automation classes

using namespace std;
EventSink * ScannerEventSink;
IMPLEMENT_DYNAMIC(EventSink, CCmdTarget)

/**
* Event sink constructor
**/
EventSink::EventSink(): bridge_(nullptr)
{
    EnableAutomation();
}

EventSink::EventSink(EventBridge* p_event_bridge)
{
    bridge_ = p_event_bridge;
    EnableAutomation();
}

/**
* virtual function called when last OLE reference is released
*/
void EventSink::OnFinalRelease()
{
    CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(EventSink, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(EventSink, CCmdTarget)
    DISP_FUNCTION_ID(EventSink, "ImageEvent", 1, OnImageEvent, VT_EMPTY, VTS_I2 VTS_I4 VTS_I2 VTS_PVARIANT VTS_BSTR)
    DISP_FUNCTION_ID(EventSink, "VideoEvent", 2, OnVideoEvent, VT_EMPTY, VTS_I2 VTS_I4 VTS_PVARIANT VTS_BSTR)
    DISP_FUNCTION_ID(EventSink, "BarcodeEvent", 3, OnBarcodeEvent, VT_EMPTY, VTS_I2 VTS_BSTR)
    DISP_FUNCTION_ID(EventSink, "PNPEvent", 4, OnPNPEvent, VT_EMPTY, VTS_I2 VTS_BSTR)
    DISP_FUNCTION_ID(EventSink, "CommandResponseEvent", 5, OnCommandResponseEvent, VT_EMPTY, VTS_I2 VTS_BSTR)
    DISP_FUNCTION_ID(EventSink, "ScanRMDEvent", 6, OnScanRMDEvent, VT_EMPTY, VTS_I2 VTS_BSTR)
    DISP_FUNCTION_ID(EventSink, "IOEvent", 7, OnIOEvent, VT_EMPTY, VTS_I2 VTS_UI1)
    DISP_FUNCTION_ID(EventSink, "ScannerNotificationEvent", 8, OnScannerNotificationEvent, VT_EMPTY, VTS_I2 VTS_BSTR)
    DISP_FUNCTION_ID(EventSink, "BinaryDataEvent", 9, OnBinaryDataEvent, VT_EMPTY, VTS_I2 VTS_I4 VTS_I2 VTS_PVARIANT VTS_BSTR)
    DISP_FUNCTION_ID(EventSink, "ParameterBarcodeEvent", 10, OnParameterBarcodeEvent, VT_EMPTY, VTS_I2 VTS_I4 VTS_I2 VTS_PVARIANT VTS_BSTR)
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(EventSink, CCmdTarget)
    INTERFACE_PART(EventSink, DIID__ICoreScannerEvents, Dispatch)
END_INTERFACE_MAP()

/**
* Image event handler
**/
void EventSink::OnImageEvent(short eventType, long size, short imageFormat, VARIANT* sfImageData, BSTR* pScannerData)
{
    LPBYTE MediaBuffer;
    SAFEARRAY* psa = sfImageData->parray;
    HRESULT hr = SafeArrayAccessData(psa, reinterpret_cast<void**>(&MediaBuffer));
    hr = SafeArrayUnaccessData(psa);
    bridge_->OnImageEvent(MediaBuffer, size);
}

/**
* Video event handler
**/
void EventSink::OnVideoEvent(short eventType, long size, VARIANT* sfvideoData, BSTR* pScannerData)
{
    LPBYTE MediaBuffer;
    SAFEARRAY* psa = sfvideoData->parray;
    HRESULT hr = SafeArrayAccessData(psa, reinterpret_cast<void**>(&MediaBuffer));
    hr = SafeArrayUnaccessData(psa);
    bridge_->OnVideoEvent(MediaBuffer, size);
}

/**
* Barcode data event handler
**/
void EventSink::OnBarcodeEvent(short eventType, BSTR pscanData)
{
    bridge_->OnBarcodeEvent(eventType, pscanData);
}

/**
* PNP event handler
**/
void EventSink::OnPNPEvent(short eventType, BSTR ppnpData)
{
    bridge_->OnPNPEvent(eventType, ppnpData);
}

/**
* Response event handler
**/
void EventSink::OnCommandResponseEvent(short status, BSTR prspData)
{
    bridge_->OnCommandResponseEvent(status, prspData);
}

/**
* RMD event handler
**/
void EventSink::OnScanRMDEvent(short eventType, BSTR prmdData)
{
    bridge_->OnScanRMDEvent(eventType, prmdData);
}

/**
* Notification event handler
**/
void EventSink::OnIOEvent(short type, unsigned char data)
{
    bridge_->OnIOEvent(type, data);
}

/**
* Scanner notification event handler
**/
void EventSink::OnScannerNotificationEvent(short notificationType, BSTR pScannerData)
{
    bridge_->OnScannerNotificationEvent(notificationType, pScannerData);
}

/**
* Binary data event handler
**/
void EventSink::OnBinaryDataEvent(short eventType, long size, short sDataFormat, VARIANT* sfBinaryData, BSTR* pScannerData)
{
    LPBYTE BinaryBuffer;
    SAFEARRAY* psa = sfBinaryData->parray;
    HRESULT hr = SafeArrayAccessData(psa, reinterpret_cast<void**>(&BinaryBuffer));
    hr = SafeArrayUnaccessData(psa);
    bridge_->OnBinaryDataEvent(BinaryBuffer, size, sDataFormat, pScannerData);
}

void EventSink::OnParameterBarcodeEvent(short eventType, long size, short imageFormat, VARIANT* sfImageData, BSTR* pData)
{
    LPBYTE BarcodeBuffer;
    SAFEARRAY* psa = sfImageData->parray;
    HRESULT hr = SafeArrayAccessData(psa, reinterpret_cast<void**>(&BarcodeBuffer));
    hr = SafeArrayUnaccessData(psa);
    bridge_->OnParameterBarcodeEvent(BarcodeBuffer, size);
}