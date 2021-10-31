#pragma once
#include <wtypes.h>

class EventBridge {
public:
	virtual void OnImageEvent(LPBYTE media_buffer, LONG buffer_size) = 0;
	virtual void OnVideoEvent(LPBYTE media_buffer, LONG buffer_size) = 0;
	virtual void OnBarcodeEvent(SHORT event_type, BSTR scan_data) = 0;
	virtual void OnPNPEvent(SHORT event_type, BSTR pnp_xml) = 0;
	virtual void OnCommandResponseEvent(SHORT status, BSTR scan_cmd_response) = 0;
	virtual void OnScanRMDEvent(SHORT event_type, BSTR event_data) = 0;
	virtual void OnIOEvent(SHORT type, UCHAR data) = 0;
	virtual void OnScannerNotificationEvent(SHORT notification_type, BSTR p_scanner_data) = 0;
	virtual void OnBinaryDataEvent(LPBYTE binary_buffer, LONG buffer_size, SHORT data_format, BSTR* scanner_data) = 0;
	virtual void OnParameterBarcodeEvent(LPBYTE barcode_buffer, LONG buffer_size) = 0;
};