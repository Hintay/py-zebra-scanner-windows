#pragma once
#include <string>

class Barcode
{
public:
	explicit Barcode(std::wstring code, const int type) :
		code_(std::move(code)), type_(type) {}

	static const wchar_t* GetSymbology(int type);

	std::wstring code_;
	int type_;
};
