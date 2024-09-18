#pragma once
#include "targetver.h"
#include <atlbase.h>
#include <atlcom.h>

#include "event_bridge.h"

#import <_CoreScanner.tlb> no_namespace named_guids

constexpr auto IDC_CORESCANNER = 1;


extern _ATL_FUNC_INFO OnImageEventInfo;
extern _ATL_FUNC_INFO OnVideoEventInfo;
extern _ATL_FUNC_INFO OnBarcodeEventInfo;
extern _ATL_FUNC_INFO OnPNPEventInfo;
extern _ATL_FUNC_INFO OnCommandResponseEventInfo;
extern _ATL_FUNC_INFO OnScanRMDEventInfo;
extern _ATL_FUNC_INFO OnIOEventInfo;
extern _ATL_FUNC_INFO OnScannerNotificationEventInfo;
extern _ATL_FUNC_INFO OnBinaryDataEventInfo;
extern _ATL_FUNC_INFO OnParameterBarcodeEventInfo;


class EventSink final :
	public IDispEventSimpleImpl<IDC_CORESCANNER, EventSink, &DIID__ICoreScannerEvents>
{
public:

    BEGIN_SINK_MAP(EventSink)
        // Make sure the Event Handlers have __stdcall calling convention
        SINK_ENTRY_INFO(IDC_CORESCANNER, DIID__ICoreScannerEvents, 
            1, OnImageEvent, &OnImageEventInfo)
        SINK_ENTRY_INFO(IDC_CORESCANNER, DIID__ICoreScannerEvents, 
            2, OnVideoEvent, &OnVideoEventInfo)
        SINK_ENTRY_INFO(IDC_CORESCANNER, DIID__ICoreScannerEvents, 
            3, OnBarcodeEvent, &OnBarcodeEventInfo)
        SINK_ENTRY_INFO(IDC_CORESCANNER, DIID__ICoreScannerEvents, 
            4, OnPNPEvent, &OnPNPEventInfo)
        SINK_ENTRY_INFO(IDC_CORESCANNER, DIID__ICoreScannerEvents, 
            5, OnCommandResponseEvent, &OnCommandResponseEventInfo)
        SINK_ENTRY_INFO(IDC_CORESCANNER, DIID__ICoreScannerEvents, 
            6, OnScanRMDEvent, &OnScanRMDEventInfo)
        SINK_ENTRY_INFO(IDC_CORESCANNER, DIID__ICoreScannerEvents, 
            7, OnIOEvent, &OnIOEventInfo)
        SINK_ENTRY_INFO(IDC_CORESCANNER, DIID__ICoreScannerEvents, 
            8, OnScannerNotificationEvent, &OnScannerNotificationEventInfo)
        SINK_ENTRY_INFO(IDC_CORESCANNER, DIID__ICoreScannerEvents, 
            9, OnBinaryDataEvent, &OnBinaryDataEventInfo)
        SINK_ENTRY_INFO(IDC_CORESCANNER, DIID__ICoreScannerEvents, 
            10, OnParameterBarcodeEvent, &OnParameterBarcodeEventInfo)
    END_SINK_MAP()

    /**
	* Event sink class constructor
	*/
    explicit EventSink() = default;
    explicit EventSink(EventBridge* p_event_bridge): bridge_(p_event_bridge) {}

    EventSink(const EventSink&) = delete;
    EventSink& operator=(const EventSink&) = delete;
    EventSink(EventSink&&) = default;
    EventSink& operator=(EventSink&&) = default;

    virtual ~EventSink() = default;

    /**
	* Image event handler function
	* @param eventType - Type of image event received
	* @param size - Size of image data buffer
	* @param imageFormat - Format of image (jpeg/bmp/tiff)
	* @param sfImageData - Image data buffer
	* @param pScannerData - Information in xml about the scanner that triggered the image event
	*/
    void __stdcall OnImageEvent(short eventType, long size, short imageFormat, VARIANT* sfImageData, BSTR* pScannerData);

    /**
    * Video event handler function
    * @param eventType - Type of video event received
    * @param size - Size of video data buffer
    * @param sfvideoData - Video data buffer
    * @param pScannerData - Reserved param (empty string)
    */
    void __stdcall OnVideoEvent(short eventType, long size, VARIANT* sfvideoData, BSTR* pScannerData);

    /**
    * Scan decode data event handler function
    * @param eventType - Barcode event type ( 1 - good decode )
    * @param pscanData - Scan data output xml with decode data
    */
    void __stdcall OnBarcodeEvent(short eventType, BSTR* pscanData);

    /**
    * PNP event handler function
    * @param eventType - PNP event type (0 - attach/1 - detach)
    * @param ppnpData - Information string containing details of attached/detached scanner
    */
    void __stdcall OnPNPEvent(short eventType, BSTR* ppnpData);

    /**
    * Command response event handler function - received after asynchronous command execution
    * @param status - Command execution status
    * @param prspData - Command response information string
    */
    void __stdcall OnCommandResponseEvent(short status, BSTR* prspData);

    /**
    * Scanner RMD event handler function
    * @param eventType - Type of RMD event received
    * @param prmdData - Information string containing data of event
    */
    void __stdcall OnScanRMDEvent(short eventType, BSTR* prmdData);

    /**
    * IO notification event handler function
    * @param type - Reserved
    * @param data - Reserved
    */
    void __stdcall OnIOEvent(short type, unsigned char data);

    /**
    * Scanner notification event handler function
    * @param notificationType - Type of notification event received
    * @param pScannerData - Information string containing details of scanner
    */
    void __stdcall OnScannerNotificationEvent(short notificationType, BSTR* pScannerData);

    /**
    * Binary data event handler function
    * @param eventType - Reserved
    * @param size - Size of binary data buffer
    * @param sDataFormat - Format of binary data
    * @param sfBinaryData - Binary data buffer
    * @param pScannerData - Information in xml about the scanner that triggered the binary data event
    */
    void __stdcall OnBinaryDataEvent(short eventType, long size, short sDataFormat, VARIANT* sfBinaryData, BSTR* pScannerData);

    void __stdcall OnParameterBarcodeEvent(short eventType, long size, short imageFormat, VARIANT* sfImageData, BSTR* pData);

private:
	EventBridge* bridge_ = nullptr;
};
