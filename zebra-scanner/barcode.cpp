#include "barcode.h"
#include "common_defs.h"

const wchar_t* Barcode::GetSymbology(const int type)
{
	const auto enum_type(static_cast<BarcodeType>(type));
	switch (enum_type)
	{
	case BarcodeType::ST_NOT_APP:
		return L"NOT APPLICABLE";
	case BarcodeType::ST_CODE_39:
		return L"CODE 39";
	case BarcodeType::ST_CODABAR:
		return L"CODABAR";
	case BarcodeType::ST_CODE_128:
		return L"CODE 128";
	case BarcodeType::ST_D2OF5:
		return L"DISCRETE 2 OF 5";
	case BarcodeType::ST_IATA:
		return L"IATA";
	case BarcodeType::ST_I2OF5:
		return L"INTERLEAVED 2 OF 5";
	case BarcodeType::ST_CODE93:
		return L"CODE 93";
	case BarcodeType::ST_UPCA:
		return L"UPC-A";
	case BarcodeType::ST_UPCE0:
		return L"UPC-E0";
	case BarcodeType::ST_EAN8:
		return L"EAN-8";
	case BarcodeType::ST_EAN13:
		return L"EAN-13";
	case BarcodeType::ST_CODE11:
		return L"CODE 11";
	case BarcodeType::ST_CODE49:
		return L"CODE 49";
	case BarcodeType::ST_MSI:
		return L"MSI";
	case BarcodeType::ST_EAN128:
		return L"EAN-128";
	case BarcodeType::ST_UPCE1:
		return L"UPC-E1";
	case BarcodeType::ST_PDF417:
		return L"PDF-417";
	case BarcodeType::ST_CODE16K:
		return L"CODE 16K";
	case BarcodeType::ST_C39FULL:
		return L"CODE 39 FULL ASCII";
	case BarcodeType::ST_UPCD:
		return L"UPC-D";
	case BarcodeType::ST_TRIOPTIC:
		return L"CODE 39 TRIOPTIC";
	case BarcodeType::ST_BOOKLAND:
		return L"BOOKLAND";
	case BarcodeType::ST_UPCA_W_CODE128:
		return L"UPC-A w/Code 128 Supplemental";
	case BarcodeType::ST_JAN13_W_CODE128:
		return L"EAN/JAN-13 w/Code 128 Supplemental";
	case BarcodeType::ST_NW7:
		return L"NW-7";
	case BarcodeType::ST_ISBT128:
		return L"ISBT-128";
	case BarcodeType::ST_MICRO_PDF:
		return L"MICRO PDF";
	case BarcodeType::ST_DATAMATRIX:
		return L"DATAMATRIX";
	case BarcodeType::ST_QR_CODE:
		return L"QR CODE";
	case BarcodeType::ST_MICRO_PDF_CCA:
		return L"MICRO PDF CCA";
	case BarcodeType::ST_POSTNET_US:
		return L"POSTNET US";
	case BarcodeType::ST_PLANET_CODE:
		return L"PLANET CODE";
	case BarcodeType::ST_CODE_32:
		return L"CODE 32";
	case BarcodeType::ST_ISBT128_CON:
		return L"ISBT-128 CON";
	case BarcodeType::ST_JAPAN_POSTAL:
		return L"JAPAN POSTAL";
	case BarcodeType::ST_AUS_POSTAL:
		return L"AUS POSTAL";
	case BarcodeType::ST_DUTCH_POSTAL:
		return L"DUTCH POSTAL";
	case BarcodeType::ST_MAXICODE:
		return L"MAXICODE";
	case BarcodeType::ST_CANADIN_POSTAL:
		return L"CANADIAN POSTAL";
	case BarcodeType::ST_UK_POSTAL:
		return L"UK POSTAL";
	case BarcodeType::ST_MACRO_PDF:
		return L"MACRO PDF";
	case BarcodeType::ST_MACRO_QR_CODE:
		return L"MACRO QR CODE";
	case BarcodeType::ST_MICRO_QR_CODE:
		return L"MICRO QR CODE";
	case BarcodeType::ST_AZTEC:
		return L"AZTEC";
	case BarcodeType::ST_AZTEC_RUNE:
		return L"AZTEC RUNE";
	case BarcodeType::ST_DISTANCE:
		return L"DISTANCE";
	case BarcodeType::ST_RSS14:
		return L"GS1 DATABAR";
	case BarcodeType::ST_RSS_LIMITED:
		return L"GS1 DATABAR LIMITED";
	case BarcodeType::ST_RSS_EXPANDED:
		return L"GS1 DATABAR EXPANDED";
	case BarcodeType::ST_PARAMETER:
		return L"PARAMETER";
	case BarcodeType::ST_USPS_4CB:
		return L"USPS 4CB";
	case BarcodeType::ST_UPU_FICS_POSTAL:
		return L"UPU FICS POSTAL";
	case BarcodeType::ST_ISSN:
		return L"ISSN";
	case BarcodeType::ST_SCANLET:
		return L"SCANLET";
	case BarcodeType::ST_CUECODE:
		return L"CUECODE";
	case BarcodeType::ST_MATRIX2OF5:
		return L"MATRIX 2 OF 5";
	case BarcodeType::ST_UPCA_2:
		return L"UPC-A + 2 SUPPLEMENTAL";
	case BarcodeType::ST_UPCE0_2:
		return L"UPC-E0 + 2 SUPPLEMENTAL";
	case BarcodeType::ST_EAN8_2:
		return L"EAN-8 + 2 SUPPLEMENTAL";
	case BarcodeType::ST_EAN13_2:
		return L"EAN-13 + 2 SUPPLEMENTAL";
	case BarcodeType::ST_UPCE1_2:
		return L"UPC-E1 + 2 SUPPLEMENTAL";
	case BarcodeType::ST_CCA_EAN128:
		return L"CCA EAN-128";
	case BarcodeType::ST_CCA_EAN13:
		return L"CCA EAN-13";
	case BarcodeType::ST_CCA_EAN8:
		return L"CCA EAN-8";
	case BarcodeType::ST_CCA_RSS_EXPANDED:
		return L"GS1 DATABAR EXPANDED COMPOSITE (CCA)";
	case BarcodeType::ST_CCA_RSS_LIMITED:
		return L"GS1 DATABAR LIMITED COMPOSITE (CCA)";
	case BarcodeType::ST_CCA_RSS14:
		return L"GS1 DATABAR COMPOSITE (CCA)";
	case BarcodeType::ST_CCA_UPCA:
		return L"CCA UPC-A";
	case BarcodeType::ST_CCA_UPCE:
		return L"CCA UPC-E";
	case BarcodeType::ST_CCC_EAN128:
		return L"CCA EAN-128";
	case BarcodeType::ST_TLC39:
		return L"TLC-39";
	case BarcodeType::ST_CCB_EAN128:
		return L"CCB EAN-128";
	case BarcodeType::ST_CCB_EAN13:
		return L"CCB EAN-13";
	case BarcodeType::ST_CCB_EAN8:
		return L"CCB EAN-8";
	case BarcodeType::ST_CCB_RSS_EXPANDED:
		return L"GS1 DATABAR EXPANDED COMPOSITE (CCB)";
	case BarcodeType::ST_CCB_RSS_LIMITED:
		return L"GS1 DATABAR LIMITED COMPOSITE (CCB)";
	case BarcodeType::ST_CCB_RSS14:
		return L"GS1 DATABAR COMPOSITE (CCB)";
	case BarcodeType::ST_CCB_UPCA:
		return L"CCB UPC-A";
	case BarcodeType::ST_CCB_UPCE:
		return L"CCB UPC-E";
	case BarcodeType::ST_SIGNATURE_CAPTURE:
		return L"SIGNATURE CAPTUREE";
	case BarcodeType::ST_MOA:
		return L"MOA";
	case BarcodeType::ST_PDF417_PARAMETER:
		return L"PDF417 PARAMETER";
	case BarcodeType::ST_CHINESE2OF5:
		return L"CHINESE 2 OF 5";
	case BarcodeType::ST_KOREAN_3_OF_5:
		return L"KOREAN 3 OF 5";
	case BarcodeType::ST_DATAMATRIX_PARAM:
		return L"DATAMATRIX PARAM";
	case BarcodeType::ST_CODE_Z:
		return L"CODE Z";
	case BarcodeType::ST_UPCA_5:
		return L"UPC-A + 5 SUPPLEMENTAL";
	case BarcodeType::ST_UPCE0_5:
		return L"UPC-E0 + 5 SUPPLEMENTAL";
	case BarcodeType::ST_EAN8_5:
		return L"EAN-8 + 5 SUPPLEMENTAL";
	case BarcodeType::ST_EAN13_5:
		return L"EAN-13 + 5 SUPPLEMENTAL";
	case BarcodeType::ST_UPCE1_5:
		return L"UPC-E1 + 5 SUPPLEMENTAL";
	case BarcodeType::ST_MACRO_MICRO_PDF:
		return L"MACRO MICRO PDF";
	case BarcodeType::ST_OCRB:
		return L"OCRB";
	case BarcodeType::ST_OCRA:
		return L"OCRA";
	case BarcodeType::ST_PARSED_DRIVER_LICENSE:
		return L"PARSED DRIVER LICENSE";
	case BarcodeType::ST_PARSED_UID:
		return L"PARSED UID";
	case BarcodeType::ST_PARSED_NDC:
		return L"PARSED NDC";
	case BarcodeType::ST_DATABAR_COUPON:
		return L"DATABAR COUPON";
	case BarcodeType::ST_PARSED_XML:
		return L"PARSED XML";
	case BarcodeType::ST_HAN_XIN_CODE:
		return L"HAN XIN CODE";
	case BarcodeType::ST_CALIBRATION:
		return L"CALIBRATION";
	case BarcodeType::ST_GS1_DATAMATRIX:
		return L"GS1 DATA MATRIX";
	case BarcodeType::ST_GS1_QR:
		return L"GS1 QR";
	case BarcodeType::BT_MAINMARK:
		return L"MAINMARK";
	case BarcodeType::BT_DOTCODE:
		return L"DOTCODE";
	case BarcodeType::BT_GRID_MATRIX:
		return L"GRID MATRIX";
	case BarcodeType::BT_UDI_CODE:
		return L"UDI CODE";
	}
	return L"";
}
