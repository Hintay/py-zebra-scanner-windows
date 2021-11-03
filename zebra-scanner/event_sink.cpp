#include "event_sink.h"

#include <atlsafe.h>
#include <iostream>

#import "libid:DB07B9FC-18B0-4B55-9A44-31D2C2F87875" no_namespace named_guids

using namespace std;

_ATL_FUNC_INFO OnImageEventInfo = { CC_STDCALL, VT_EMPTY, 5,
    {VT_I2, VT_I4, VT_I2, VT_VARIANT | VT_BYREF, VT_BSTR | VT_BYREF} };
_ATL_FUNC_INFO OnVideoEventInfo = { CC_STDCALL, VT_EMPTY, 4,
    {VT_I2, VT_I4, VT_VARIANT | VT_BYREF, VT_BSTR | VT_BYREF} };
_ATL_FUNC_INFO OnBarcodeEventInfo = { CC_STDCALL, VT_EMPTY, 2,
    {VT_I2, VT_BSTR | VT_BYREF} };
_ATL_FUNC_INFO OnPNPEventInfo = { CC_STDCALL, VT_EMPTY, 2,
    {VT_I2, VT_BSTR | VT_BYREF} };
_ATL_FUNC_INFO OnCommandResponseEventInfo = { CC_STDCALL, VT_EMPTY, 2,
    {VT_I2, VT_BSTR | VT_BYREF} };
_ATL_FUNC_INFO OnScanRMDEventInfo = { CC_STDCALL, VT_EMPTY, 2,
    {VT_I2, VT_BSTR | VT_BYREF} };
_ATL_FUNC_INFO OnIOEventInfo = { CC_STDCALL, VT_EMPTY, 2,
    {VT_I2, VT_UI1} };
_ATL_FUNC_INFO OnScannerNotificationEventInfo = { CC_STDCALL, VT_EMPTY, 2,
    {VT_I2, VT_BSTR | VT_BYREF} };
_ATL_FUNC_INFO OnBinaryDataEventInfo = { CC_STDCALL, VT_EMPTY, 5,
    {VT_I2, VT_I4, VT_I2, VT_VARIANT | VT_BYREF, VT_BSTR | VT_BYREF} };
_ATL_FUNC_INFO OnParameterBarcodeEventInfo = { CC_STDCALL, VT_EMPTY, 5,
    {VT_I2, VT_I4, VT_I2, VT_VARIANT | VT_BYREF, VT_BSTR | VT_BYREF} };


/**
* Image event handler
**/
void EventSink::OnImageEvent(short eventType, long size, short imageFormat, VARIANT* sfImageData, BSTR* pScannerData)
{
    LPBYTE media_buffer;
    SAFEARRAY* psa = sfImageData->parray;
    HRESULT hr = SafeArrayAccessData(psa, reinterpret_cast<void**>(&media_buffer));
    hr = SafeArrayUnaccessData(psa);
    bridge_->OnImageEvent(media_buffer, size);
}

/**
* Video event handler
**/
void EventSink::OnVideoEvent(short eventType, long size, VARIANT* sfvideoData, BSTR* pScannerData)
{
    LPBYTE media_buffer;
    SAFEARRAY* psa = sfvideoData->parray;
    HRESULT hr = SafeArrayAccessData(psa, reinterpret_cast<void**>(&media_buffer));
    hr = SafeArrayUnaccessData(psa);
    bridge_->OnVideoEvent(media_buffer, size);
}

/**
* Barcode data event handler
**/
void EventSink::OnBarcodeEvent(short eventType, BSTR* pscanData)
{
    bridge_->OnBarcodeEvent(eventType, *pscanData);
}

/**
* PNP event handler
**/
void EventSink::OnPNPEvent(short eventType, BSTR* ppnpData)
{
    bridge_->OnPNPEvent(eventType, *ppnpData);
}

/**
* Response event handler
**/
void EventSink::OnCommandResponseEvent(short status, BSTR* prspData)
{
    bridge_->OnCommandResponseEvent(status, *prspData);
}

/**
* RMD event handler
**/
void EventSink::OnScanRMDEvent(short eventType, BSTR* prmdData)
{
    bridge_->OnScanRMDEvent(eventType, *prmdData);
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
void EventSink::OnScannerNotificationEvent(short notificationType, BSTR* pScannerData)
{
    bridge_->OnScannerNotificationEvent(notificationType, *pScannerData);
}

/**
* Binary data event handler
**/
void EventSink::OnBinaryDataEvent(short eventType, long size, short sDataFormat, VARIANT* sfBinaryData, BSTR* pScannerData)
{
    LPBYTE binary_buffer;
    SAFEARRAY* psa = sfBinaryData->parray;
    HRESULT hr = SafeArrayAccessData(psa, reinterpret_cast<void**>(&binary_buffer));
    hr = SafeArrayUnaccessData(psa);
    bridge_->OnBinaryDataEvent(binary_buffer, size, sDataFormat, pScannerData);
}

void EventSink::OnParameterBarcodeEvent(short eventType, long size, short imageFormat, VARIANT* sfImageData, BSTR* pData)
{
    LPBYTE barcode_buffer;
    SAFEARRAY* psa = sfImageData->parray;
    HRESULT hr = SafeArrayAccessData(psa, reinterpret_cast<void**>(&barcode_buffer));
    hr = SafeArrayUnaccessData(psa);
    bridge_->OnParameterBarcodeEvent(barcode_buffer, size);
}