#pragma once
#include "event_sink.h"

#include <map>
#include <pugixml.hpp>

#include <pybind11/pybind11.h>
#include <pybind11/pytypes.h>
#include <pybind11/stl.h>

#import "libid:DB07B9FC-18B0-4B55-9A44-31D2C2F87875" no_namespace named_guids


class Scanner;
namespace py = pybind11;

class CoreScanner final : public EventBridge
{
public:
	explicit CoreScanner();
	virtual ~CoreScanner();
	CoreScanner(const CoreScanner&) = delete;
	CoreScanner& operator=(const CoreScanner&) = delete;
	CoreScanner(CoreScanner&&) = default;
	CoreScanner& operator=(CoreScanner&&) = default;

	void Open();
	void Close();
	void RegisterEvents() const;

	void OnScannerAddedDecorator(py::object& obj);
	void OnScannerRemovedDecorator(py::object& obj);
	void OnScannerAdded(std::shared_ptr<Scanner>& scanner);
	void OnScannerRemoved(std::shared_ptr<Scanner>& scanner);

	void FetchScanners();
	void ParseScannerFromXml(const pugi::xml_node& scanner);

	void OnImageEvent(LPBYTE media_buffer, LONG buffer_size) override;
	void OnVideoEvent(LPBYTE media_buffer, LONG buffer_size) override;
	void OnBarcodeEvent(SHORT event_type, BSTR scan_data) override;
	void OnPNPEvent(SHORT event_type, BSTR pnp_xml) override;
	void OnCommandResponseEvent(SHORT status, BSTR scan_cmd_response) override;
	void OnScanRMDEvent(SHORT event_type, BSTR event_data) override;
	void OnIOEvent(SHORT type, UCHAR data) override;
	void OnScannerNotificationEvent(SHORT notification_type, BSTR p_scanner_data) override;
	void OnBinaryDataEvent(LPBYTE binary_buffer, LONG buffer_size, SHORT data_format, BSTR* scanner_data) override;
	void OnParameterBarcodeEvent(LPBYTE barcode_buffer, LONG buffer_size) override;

	std::map<int, std::shared_ptr<Scanner>> scanners_;

	typedef py::object ScannerCallback;
	std::vector<ScannerCallback> on_scanner_added_;
	std::vector<ScannerCallback> on_scanner_removed_;

	bool is_open_ = false;

protected:
	CComQIPtr<ICoreScanner> scanner_interface_;
	std::unique_ptr<EventSink> scanner_event_sink_;
};
