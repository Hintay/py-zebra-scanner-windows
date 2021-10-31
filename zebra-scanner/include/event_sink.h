#pragma once
#define _AFXDLL

#include "targetver.h"
#include "afxctl.h"
#include "afxwin.h"
#include "afxcmn.h"

#include "event_bridge.h"

/**
* Class to handle CoreScanner events
**/
class EventSink final : public CCmdTarget
{
    DECLARE_DYNAMIC(EventSink)

public:
    /**
    * Event sink class constructor
    */
    explicit EventSink();
    explicit EventSink(EventBridge* p_event_bridge);


    /**
    * Event sink class  destructor
    */
    ~EventSink() override = default;

    /**
    * virtual function called when last OLE reference is released
    */
    void OnFinalRelease() override;


    /**
    * Image event handler function
    * @param eventType - Type of image event received
    * @param size - Size of image data buffer
    * @param imageFormat - Format of image (jpeg/bmp/tiff)
    * @param sfImageData - Image data buffer
    * @param pScannerData - Information in xml about the scanner that triggered the image event
    */
    void OnImageEvent(short eventType, long size, short imageFormat, VARIANT* sfImageData, BSTR* pScannerData);

    /**
    * Video event handler function
    * @param eventType - Type of video event received
    * @param size - Size of video data buffer
    * @param sfvideoData - Video data buffer
    * @param pScannerData - Reserved param (empty string)
    */
    void OnVideoEvent(short eventType, long size, VARIANT* sfvideoData, BSTR* pScannerData);

    /**
    * Scan decode data event handler function
    * @param eventType - Barcode event type ( 1 - good decode )
    * @param pscanData - Scan data output xml with decode data
    */
    void OnBarcodeEvent(short eventType, BSTR pscanData);

    /**
    * PNP event handler function
    * @param eventType - PNP event type (0 - attach/1 - detach)
    * @param ppnpData - Information string containing details of attached/detached scanner
    */
    void OnPNPEvent(short eventType, BSTR ppnpData);

    /**
    * Command response event handler function - received after asynchronous command execution
    * @param status - Command execution status
    * @param prspData - Command response information string
    */
    void OnCommandResponseEvent(short status, BSTR prspData);

    /**
    * Scanner RMD event handler function
    * @param eventType - Type of RMD event received
    * @param prmdData - Information string containing data of event
    */
    void OnScanRMDEvent(short eventType, BSTR prmdData);

    /**
    * IO notification event handler function
    * @param type - Reserved
    * @param data - Reserved
    */
    void OnIOEvent(short type, unsigned char data);

    /**
    * Scanner notification event handler function
    * @param notificationType - Type of notification event received
    * @param pScannerData - Information string containing details of scanner
    */
    void OnScannerNotificationEvent(short notificationType, BSTR pScannerData);

    /**
    * Binary data event handler function
    * @param eventType - Reserved
    * @param size - Size of binary data buffer
    * @param sDataFormat - Format of binary data
    * @param sfBinaryData - Binary data buffer
    * @param pScannerData - Information in xml about the scanner that triggered the binary data event
    */
    void OnBinaryDataEvent(short eventType, long size, short sDataFormat, VARIANT* sfBinaryData, BSTR* pScannerData);

    void OnParameterBarcodeEvent(short eventType, long size, short imageFormat, VARIANT* sfImageData, BSTR* pData);

private:
    EventBridge* bridge_;

protected:
    DECLARE_MESSAGE_MAP()
    DECLARE_DISPATCH_MAP()
    DECLARE_INTERFACE_MAP()
};


