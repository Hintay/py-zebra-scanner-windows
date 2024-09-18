from __future__ import annotations
import typing

__all__ = [
    "Attribute",
    "Barcode",
    "CoreScanner",
    "Scanner"
]


class Attribute:
    """
    Attribute Instance of Specified Scanner
    """
    def __repr__(self) -> str: ...
    def set_value(self, arg0: object) -> int: 
        """
        Set the value of attribute of the scanner. Attribute set using this command are lost after the next power down.
        """
    def store_value(self, arg0: object) -> int: 
        """
        Store the value of attribute of the scanner. Attribute store using this command are persistent over power down and power up cycles.
        """
    @property
    def datatype(self) -> str:
        """
        :type: str
        """
    @property
    def id(self) -> int:
        """
        :type: int
        """
    @property
    def permission(self) -> str:
        """
        :type: str
        """
    @property
    def value(self) -> object:
        """
        :type: object
        """
    pass

class Barcode:
    class Type:
        def __eq__(self, other: object) -> bool: ...
        def __getstate__(self) -> int: ...
        def __hash__(self) -> int: ...
        def __index__(self) -> int: ...
        def __init__(self, value: int) -> None: ...
        def __int__(self) -> int: ...
        def __ne__(self, other: object) -> bool: ...
        def __repr__(self) -> str: ...
        def __setstate__(self, state: int) -> None: ...
        @property
        def name(self) -> str:
            """
            :type: str
            """
        @property
        def value(self) -> int:
            """
            :type: int
            """
        ST_AUS_POSTAL: Barcode.Type # value = <Type.ST_AUS_POSTAL: 35>
        ST_AZTEC: Barcode.Type # value = <Type.ST_AZTEC: 45>
        ST_AZTEC_RUNE: Barcode.Type # value = <Type.ST_AZTEC_RUNE: 46>
        ST_BOOKLAND: Barcode.Type # value = <Type.ST_BOOKLAND: 22>
        ST_C39FULL: Barcode.Type # value = <Type.ST_C39FULL: 19>
        ST_CANADIN_POSTAL: Barcode.Type # value = <Type.ST_CANADIN_POSTAL: 38>
        ST_CCA_EAN128: Barcode.Type # value = <Type.ST_CCA_EAN128: 81>
        ST_CCA_EAN13: Barcode.Type # value = <Type.ST_CCA_EAN13: 82>
        ST_CCA_EAN8: Barcode.Type # value = <Type.ST_CCA_EAN8: 83>
        ST_CCA_RSS14: Barcode.Type # value = <Type.ST_CCA_RSS14: 86>
        ST_CCA_RSS_EXPANDED: Barcode.Type # value = <Type.ST_CCA_RSS_EXPANDED: 84>
        ST_CCA_RSS_LIMITED: Barcode.Type # value = <Type.ST_CCA_RSS_LIMITED: 85>
        ST_CCA_UPCA: Barcode.Type # value = <Type.ST_CCA_UPCA: 87>
        ST_CCA_UPCE: Barcode.Type # value = <Type.ST_CCA_UPCE: 88>
        ST_CCB_EAN128: Barcode.Type # value = <Type.ST_CCB_EAN128: 97>
        ST_CCB_EAN13: Barcode.Type # value = <Type.ST_CCB_EAN13: 98>
        ST_CCB_EAN8: Barcode.Type # value = <Type.ST_CCB_EAN8: 99>
        ST_CCB_RSS14: Barcode.Type # value = <Type.ST_CCB_RSS14: 102>
        ST_CCB_RSS_EXPANDED: Barcode.Type # value = <Type.ST_CCB_RSS_EXPANDED: 100>
        ST_CCB_RSS_LIMITED: Barcode.Type # value = <Type.ST_CCB_RSS_LIMITED: 101>
        ST_CCB_UPCA: Barcode.Type # value = <Type.ST_CCB_UPCA: 103>
        ST_CCB_UPCE: Barcode.Type # value = <Type.ST_CCB_UPCE: 104>
        ST_CCC_EAN128: Barcode.Type # value = <Type.ST_CCC_EAN128: 89>
        ST_CHINESE2OF5: Barcode.Type # value = <Type.ST_CHINESE2OF5: 114>
        ST_CODABAR: Barcode.Type # value = <Type.ST_CODABAR: 2>
        ST_CODE11: Barcode.Type # value = <Type.ST_CODE11: 12>
        ST_CODE16K: Barcode.Type # value = <Type.ST_CODE16K: 18>
        ST_CODE49: Barcode.Type # value = <Type.ST_CODE49: 13>
        ST_CODE93: Barcode.Type # value = <Type.ST_CODE93: 7>
        ST_CODE_128: Barcode.Type # value = <Type.ST_CODE_128: 3>
        ST_CODE_32: Barcode.Type # value = <Type.ST_CODE_32: 32>
        ST_CODE_39: Barcode.Type # value = <Type.ST_CODE_39: 1>
        ST_CODE_Z: Barcode.Type # value = <Type.ST_CODE_Z: 117>
        ST_CUECODE: Barcode.Type # value = <Type.ST_CUECODE: 56>
        ST_D2OF5: Barcode.Type # value = <Type.ST_D2OF5: 4>
        ST_DATAMATRIX: Barcode.Type # value = <Type.ST_DATAMATRIX: 27>
        ST_DATAMATRIX_PARAM: Barcode.Type # value = <Type.ST_DATAMATRIX_PARAM: 116>
        ST_DISTANCE: Barcode.Type # value = <Type.ST_DISTANCE: 47>
        ST_DUTCH_POSTAL: Barcode.Type # value = <Type.ST_DUTCH_POSTAL: 36>
        ST_EAN128: Barcode.Type # value = <Type.ST_EAN128: 15>
        ST_EAN13: Barcode.Type # value = <Type.ST_EAN13: 11>
        ST_EAN13_2: Barcode.Type # value = <Type.ST_EAN13_2: 75>
        ST_EAN8: Barcode.Type # value = <Type.ST_EAN8: 10>
        ST_EAN8_2: Barcode.Type # value = <Type.ST_EAN8_2: 74>
        ST_I2OF5: Barcode.Type # value = <Type.ST_I2OF5: 6>
        ST_IATA: Barcode.Type # value = <Type.ST_IATA: 5>
        ST_ISBT128: Barcode.Type # value = <Type.ST_ISBT128: 25>
        ST_ISBT128_CON: Barcode.Type # value = <Type.ST_ISBT128_CON: 33>
        ST_ISSN: Barcode.Type # value = <Type.ST_ISSN: 54>
        ST_JAN13_W_CODE128: Barcode.Type # value = <Type.ST_JAN13_W_CODE128: 120>
        ST_JAPAN_POSTAL: Barcode.Type # value = <Type.ST_JAPAN_POSTAL: 34>
        ST_KOREAN_3_OF_5: Barcode.Type # value = <Type.ST_KOREAN_3_OF_5: 115>
        ST_MACRO_PDF: Barcode.Type # value = <Type.ST_MACRO_PDF: 40>
        ST_MACRO_QR_CODE: Barcode.Type # value = <Type.ST_MACRO_QR_CODE: 41>
        ST_MATRIX2OF5: Barcode.Type # value = <Type.ST_MATRIX2OF5: 57>
        ST_MAXICODE: Barcode.Type # value = <Type.ST_MAXICODE: 37>
        ST_MICRO_PDF: Barcode.Type # value = <Type.ST_MICRO_PDF: 26>
        ST_MICRO_PDF_CCA: Barcode.Type # value = <Type.ST_MICRO_PDF_CCA: 29>
        ST_MICRO_QR_CODE: Barcode.Type # value = <Type.ST_MICRO_QR_CODE: 44>
        ST_MOA: Barcode.Type # value = <Type.ST_MOA: 106>
        ST_MSI: Barcode.Type # value = <Type.ST_MSI: 14>
        ST_NOT_APP: Barcode.Type # value = <Type.ST_NOT_APP: 0>
        ST_NW7: Barcode.Type # value = <Type.ST_NW7: 24>
        ST_PARAMETER: Barcode.Type # value = <Type.ST_PARAMETER: 51>
        ST_PDF417: Barcode.Type # value = <Type.ST_PDF417: 17>
        ST_PDF417_PARAMETER: Barcode.Type # value = <Type.ST_PDF417_PARAMETER: 112>
        ST_PLANET_CODE: Barcode.Type # value = <Type.ST_PLANET_CODE: 31>
        ST_POSTNET_US: Barcode.Type # value = <Type.ST_POSTNET_US: 30>
        ST_QR_CODE: Barcode.Type # value = <Type.ST_QR_CODE: 28>
        ST_RSS14: Barcode.Type # value = <Type.ST_RSS14: 48>
        ST_RSS_EXPANDED: Barcode.Type # value = <Type.ST_RSS_EXPANDED: 50>
        ST_RSS_LIMITED: Barcode.Type # value = <Type.ST_RSS_LIMITED: 49>
        ST_SCANLET: Barcode.Type # value = <Type.ST_SCANLET: 55>
        ST_SIGNATURE_CAPTURE: Barcode.Type # value = <Type.ST_SIGNATURE_CAPTURE: 105>
        ST_TLC39: Barcode.Type # value = <Type.ST_TLC39: 90>
        ST_TRIOPTIC: Barcode.Type # value = <Type.ST_TRIOPTIC: 21>
        ST_UK_POSTAL: Barcode.Type # value = <Type.ST_UK_POSTAL: 39>
        ST_UPCA: Barcode.Type # value = <Type.ST_UPCA: 8>
        ST_UPCA_2: Barcode.Type # value = <Type.ST_UPCA_2: 72>
        ST_UPCA_W_CODE128: Barcode.Type # value = <Type.ST_UPCA_W_CODE128: 23>
        ST_UPCD: Barcode.Type # value = <Type.ST_UPCD: 20>
        ST_UPCE0: Barcode.Type # value = <Type.ST_UPCE0: 9>
        ST_UPCE0_2: Barcode.Type # value = <Type.ST_UPCE0_2: 73>
        ST_UPCE1: Barcode.Type # value = <Type.ST_UPCE1: 16>
        ST_UPCE1_2: Barcode.Type # value = <Type.ST_UPCE1_2: 80>
        ST_UPU_FICS_POSTAL: Barcode.Type # value = <Type.ST_UPU_FICS_POSTAL: 53>
        ST_USPS_4CB: Barcode.Type # value = <Type.ST_USPS_4CB: 52>
        __members__: dict # value = {'ST_NOT_APP': <Type.ST_NOT_APP: 0>, 'ST_CODE_39': <Type.ST_CODE_39: 1>, 'ST_CODABAR': <Type.ST_CODABAR: 2>, 'ST_CODE_128': <Type.ST_CODE_128: 3>, 'ST_D2OF5': <Type.ST_D2OF5: 4>, 'ST_IATA': <Type.ST_IATA: 5>, 'ST_I2OF5': <Type.ST_I2OF5: 6>, 'ST_CODE93': <Type.ST_CODE93: 7>, 'ST_UPCA': <Type.ST_UPCA: 8>, 'ST_UPCE0': <Type.ST_UPCE0: 9>, 'ST_EAN8': <Type.ST_EAN8: 10>, 'ST_EAN13': <Type.ST_EAN13: 11>, 'ST_CODE11': <Type.ST_CODE11: 12>, 'ST_CODE49': <Type.ST_CODE49: 13>, 'ST_MSI': <Type.ST_MSI: 14>, 'ST_EAN128': <Type.ST_EAN128: 15>, 'ST_UPCE1': <Type.ST_UPCE1: 16>, 'ST_PDF417': <Type.ST_PDF417: 17>, 'ST_CODE16K': <Type.ST_CODE16K: 18>, 'ST_C39FULL': <Type.ST_C39FULL: 19>, 'ST_UPCD': <Type.ST_UPCD: 20>, 'ST_TRIOPTIC': <Type.ST_TRIOPTIC: 21>, 'ST_BOOKLAND': <Type.ST_BOOKLAND: 22>, 'ST_UPCA_W_CODE128': <Type.ST_UPCA_W_CODE128: 23>, 'ST_NW7': <Type.ST_NW7: 24>, 'ST_ISBT128': <Type.ST_ISBT128: 25>, 'ST_MICRO_PDF': <Type.ST_MICRO_PDF: 26>, 'ST_DATAMATRIX': <Type.ST_DATAMATRIX: 27>, 'ST_QR_CODE': <Type.ST_QR_CODE: 28>, 'ST_MICRO_PDF_CCA': <Type.ST_MICRO_PDF_CCA: 29>, 'ST_POSTNET_US': <Type.ST_POSTNET_US: 30>, 'ST_PLANET_CODE': <Type.ST_PLANET_CODE: 31>, 'ST_CODE_32': <Type.ST_CODE_32: 32>, 'ST_ISBT128_CON': <Type.ST_ISBT128_CON: 33>, 'ST_JAPAN_POSTAL': <Type.ST_JAPAN_POSTAL: 34>, 'ST_AUS_POSTAL': <Type.ST_AUS_POSTAL: 35>, 'ST_DUTCH_POSTAL': <Type.ST_DUTCH_POSTAL: 36>, 'ST_MAXICODE': <Type.ST_MAXICODE: 37>, 'ST_CANADIN_POSTAL': <Type.ST_CANADIN_POSTAL: 38>, 'ST_UK_POSTAL': <Type.ST_UK_POSTAL: 39>, 'ST_MACRO_PDF': <Type.ST_MACRO_PDF: 40>, 'ST_MACRO_QR_CODE': <Type.ST_MACRO_QR_CODE: 41>, 'ST_MICRO_QR_CODE': <Type.ST_MICRO_QR_CODE: 44>, 'ST_AZTEC': <Type.ST_AZTEC: 45>, 'ST_AZTEC_RUNE': <Type.ST_AZTEC_RUNE: 46>, 'ST_DISTANCE': <Type.ST_DISTANCE: 47>, 'ST_RSS14': <Type.ST_RSS14: 48>, 'ST_RSS_LIMITED': <Type.ST_RSS_LIMITED: 49>, 'ST_RSS_EXPANDED': <Type.ST_RSS_EXPANDED: 50>, 'ST_PARAMETER': <Type.ST_PARAMETER: 51>, 'ST_USPS_4CB': <Type.ST_USPS_4CB: 52>, 'ST_UPU_FICS_POSTAL': <Type.ST_UPU_FICS_POSTAL: 53>, 'ST_ISSN': <Type.ST_ISSN: 54>, 'ST_SCANLET': <Type.ST_SCANLET: 55>, 'ST_CUECODE': <Type.ST_CUECODE: 56>, 'ST_MATRIX2OF5': <Type.ST_MATRIX2OF5: 57>, 'ST_UPCA_2': <Type.ST_UPCA_2: 72>, 'ST_UPCE0_2': <Type.ST_UPCE0_2: 73>, 'ST_EAN8_2': <Type.ST_EAN8_2: 74>, 'ST_EAN13_2': <Type.ST_EAN13_2: 75>, 'ST_UPCE1_2': <Type.ST_UPCE1_2: 80>, 'ST_CCA_EAN128': <Type.ST_CCA_EAN128: 81>, 'ST_CCA_EAN13': <Type.ST_CCA_EAN13: 82>, 'ST_CCA_EAN8': <Type.ST_CCA_EAN8: 83>, 'ST_CCA_RSS_EXPANDED': <Type.ST_CCA_RSS_EXPANDED: 84>, 'ST_CCA_RSS_LIMITED': <Type.ST_CCA_RSS_LIMITED: 85>, 'ST_CCA_RSS14': <Type.ST_CCA_RSS14: 86>, 'ST_CCA_UPCA': <Type.ST_CCA_UPCA: 87>, 'ST_CCA_UPCE': <Type.ST_CCA_UPCE: 88>, 'ST_CCC_EAN128': <Type.ST_CCC_EAN128: 89>, 'ST_TLC39': <Type.ST_TLC39: 90>, 'ST_CCB_EAN128': <Type.ST_CCB_EAN128: 97>, 'ST_CCB_EAN13': <Type.ST_CCB_EAN13: 98>, 'ST_CCB_EAN8': <Type.ST_CCB_EAN8: 99>, 'ST_CCB_RSS_EXPANDED': <Type.ST_CCB_RSS_EXPANDED: 100>, 'ST_CCB_RSS_LIMITED': <Type.ST_CCB_RSS_LIMITED: 101>, 'ST_CCB_RSS14': <Type.ST_CCB_RSS14: 102>, 'ST_CCB_UPCA': <Type.ST_CCB_UPCA: 103>, 'ST_CCB_UPCE': <Type.ST_CCB_UPCE: 104>, 'ST_SIGNATURE_CAPTURE': <Type.ST_SIGNATURE_CAPTURE: 105>, 'ST_MOA': <Type.ST_MOA: 106>, 'ST_PDF417_PARAMETER': <Type.ST_PDF417_PARAMETER: 112>, 'ST_CHINESE2OF5': <Type.ST_CHINESE2OF5: 114>, 'ST_KOREAN_3_OF_5': <Type.ST_KOREAN_3_OF_5: 115>, 'ST_DATAMATRIX_PARAM': <Type.ST_DATAMATRIX_PARAM: 116>, 'ST_CODE_Z': <Type.ST_CODE_Z: 117>, 'ST_JAN13_W_CODE128': <Type.ST_JAN13_W_CODE128: 120>}
        pass
    def __repr__(self) -> str: ...
    def get_symbology(self) -> str: 
        """
        Get symbology type by ID.
        """
    @property
    def code(self) -> str:
        """
        :type: str
        """
    @property
    def symbology(self) -> str:
        """
        :type: str
        """
    @property
    def type(self) -> int:
        """
        :type: int
        """
    ST_AUS_POSTAL: Barcode.Type # value = <Type.ST_AUS_POSTAL: 35>
    ST_AZTEC: Barcode.Type # value = <Type.ST_AZTEC: 45>
    ST_AZTEC_RUNE: Barcode.Type # value = <Type.ST_AZTEC_RUNE: 46>
    ST_BOOKLAND: Barcode.Type # value = <Type.ST_BOOKLAND: 22>
    ST_C39FULL: Barcode.Type # value = <Type.ST_C39FULL: 19>
    ST_CANADIN_POSTAL: Barcode.Type # value = <Type.ST_CANADIN_POSTAL: 38>
    ST_CCA_EAN128: Barcode.Type # value = <Type.ST_CCA_EAN128: 81>
    ST_CCA_EAN13: Barcode.Type # value = <Type.ST_CCA_EAN13: 82>
    ST_CCA_EAN8: Barcode.Type # value = <Type.ST_CCA_EAN8: 83>
    ST_CCA_RSS14: Barcode.Type # value = <Type.ST_CCA_RSS14: 86>
    ST_CCA_RSS_EXPANDED: Barcode.Type # value = <Type.ST_CCA_RSS_EXPANDED: 84>
    ST_CCA_RSS_LIMITED: Barcode.Type # value = <Type.ST_CCA_RSS_LIMITED: 85>
    ST_CCA_UPCA: Barcode.Type # value = <Type.ST_CCA_UPCA: 87>
    ST_CCA_UPCE: Barcode.Type # value = <Type.ST_CCA_UPCE: 88>
    ST_CCB_EAN128: Barcode.Type # value = <Type.ST_CCB_EAN128: 97>
    ST_CCB_EAN13: Barcode.Type # value = <Type.ST_CCB_EAN13: 98>
    ST_CCB_EAN8: Barcode.Type # value = <Type.ST_CCB_EAN8: 99>
    ST_CCB_RSS14: Barcode.Type # value = <Type.ST_CCB_RSS14: 102>
    ST_CCB_RSS_EXPANDED: Barcode.Type # value = <Type.ST_CCB_RSS_EXPANDED: 100>
    ST_CCB_RSS_LIMITED: Barcode.Type # value = <Type.ST_CCB_RSS_LIMITED: 101>
    ST_CCB_UPCA: Barcode.Type # value = <Type.ST_CCB_UPCA: 103>
    ST_CCB_UPCE: Barcode.Type # value = <Type.ST_CCB_UPCE: 104>
    ST_CCC_EAN128: Barcode.Type # value = <Type.ST_CCC_EAN128: 89>
    ST_CHINESE2OF5: Barcode.Type # value = <Type.ST_CHINESE2OF5: 114>
    ST_CODABAR: Barcode.Type # value = <Type.ST_CODABAR: 2>
    ST_CODE11: Barcode.Type # value = <Type.ST_CODE11: 12>
    ST_CODE16K: Barcode.Type # value = <Type.ST_CODE16K: 18>
    ST_CODE49: Barcode.Type # value = <Type.ST_CODE49: 13>
    ST_CODE93: Barcode.Type # value = <Type.ST_CODE93: 7>
    ST_CODE_128: Barcode.Type # value = <Type.ST_CODE_128: 3>
    ST_CODE_32: Barcode.Type # value = <Type.ST_CODE_32: 32>
    ST_CODE_39: Barcode.Type # value = <Type.ST_CODE_39: 1>
    ST_CODE_Z: Barcode.Type # value = <Type.ST_CODE_Z: 117>
    ST_CUECODE: Barcode.Type # value = <Type.ST_CUECODE: 56>
    ST_D2OF5: Barcode.Type # value = <Type.ST_D2OF5: 4>
    ST_DATAMATRIX: Barcode.Type # value = <Type.ST_DATAMATRIX: 27>
    ST_DATAMATRIX_PARAM: Barcode.Type # value = <Type.ST_DATAMATRIX_PARAM: 116>
    ST_DISTANCE: Barcode.Type # value = <Type.ST_DISTANCE: 47>
    ST_DUTCH_POSTAL: Barcode.Type # value = <Type.ST_DUTCH_POSTAL: 36>
    ST_EAN128: Barcode.Type # value = <Type.ST_EAN128: 15>
    ST_EAN13: Barcode.Type # value = <Type.ST_EAN13: 11>
    ST_EAN13_2: Barcode.Type # value = <Type.ST_EAN13_2: 75>
    ST_EAN8: Barcode.Type # value = <Type.ST_EAN8: 10>
    ST_EAN8_2: Barcode.Type # value = <Type.ST_EAN8_2: 74>
    ST_I2OF5: Barcode.Type # value = <Type.ST_I2OF5: 6>
    ST_IATA: Barcode.Type # value = <Type.ST_IATA: 5>
    ST_ISBT128: Barcode.Type # value = <Type.ST_ISBT128: 25>
    ST_ISBT128_CON: Barcode.Type # value = <Type.ST_ISBT128_CON: 33>
    ST_ISSN: Barcode.Type # value = <Type.ST_ISSN: 54>
    ST_JAN13_W_CODE128: Barcode.Type # value = <Type.ST_JAN13_W_CODE128: 120>
    ST_JAPAN_POSTAL: Barcode.Type # value = <Type.ST_JAPAN_POSTAL: 34>
    ST_KOREAN_3_OF_5: Barcode.Type # value = <Type.ST_KOREAN_3_OF_5: 115>
    ST_MACRO_PDF: Barcode.Type # value = <Type.ST_MACRO_PDF: 40>
    ST_MACRO_QR_CODE: Barcode.Type # value = <Type.ST_MACRO_QR_CODE: 41>
    ST_MATRIX2OF5: Barcode.Type # value = <Type.ST_MATRIX2OF5: 57>
    ST_MAXICODE: Barcode.Type # value = <Type.ST_MAXICODE: 37>
    ST_MICRO_PDF: Barcode.Type # value = <Type.ST_MICRO_PDF: 26>
    ST_MICRO_PDF_CCA: Barcode.Type # value = <Type.ST_MICRO_PDF_CCA: 29>
    ST_MICRO_QR_CODE: Barcode.Type # value = <Type.ST_MICRO_QR_CODE: 44>
    ST_MOA: Barcode.Type # value = <Type.ST_MOA: 106>
    ST_MSI: Barcode.Type # value = <Type.ST_MSI: 14>
    ST_NOT_APP: Barcode.Type # value = <Type.ST_NOT_APP: 0>
    ST_NW7: Barcode.Type # value = <Type.ST_NW7: 24>
    ST_PARAMETER: Barcode.Type # value = <Type.ST_PARAMETER: 51>
    ST_PDF417: Barcode.Type # value = <Type.ST_PDF417: 17>
    ST_PDF417_PARAMETER: Barcode.Type # value = <Type.ST_PDF417_PARAMETER: 112>
    ST_PLANET_CODE: Barcode.Type # value = <Type.ST_PLANET_CODE: 31>
    ST_POSTNET_US: Barcode.Type # value = <Type.ST_POSTNET_US: 30>
    ST_QR_CODE: Barcode.Type # value = <Type.ST_QR_CODE: 28>
    ST_RSS14: Barcode.Type # value = <Type.ST_RSS14: 48>
    ST_RSS_EXPANDED: Barcode.Type # value = <Type.ST_RSS_EXPANDED: 50>
    ST_RSS_LIMITED: Barcode.Type # value = <Type.ST_RSS_LIMITED: 49>
    ST_SCANLET: Barcode.Type # value = <Type.ST_SCANLET: 55>
    ST_SIGNATURE_CAPTURE: Barcode.Type # value = <Type.ST_SIGNATURE_CAPTURE: 105>
    ST_TLC39: Barcode.Type # value = <Type.ST_TLC39: 90>
    ST_TRIOPTIC: Barcode.Type # value = <Type.ST_TRIOPTIC: 21>
    ST_UK_POSTAL: Barcode.Type # value = <Type.ST_UK_POSTAL: 39>
    ST_UPCA: Barcode.Type # value = <Type.ST_UPCA: 8>
    ST_UPCA_2: Barcode.Type # value = <Type.ST_UPCA_2: 72>
    ST_UPCA_W_CODE128: Barcode.Type # value = <Type.ST_UPCA_W_CODE128: 23>
    ST_UPCD: Barcode.Type # value = <Type.ST_UPCD: 20>
    ST_UPCE0: Barcode.Type # value = <Type.ST_UPCE0: 9>
    ST_UPCE0_2: Barcode.Type # value = <Type.ST_UPCE0_2: 73>
    ST_UPCE1: Barcode.Type # value = <Type.ST_UPCE1: 16>
    ST_UPCE1_2: Barcode.Type # value = <Type.ST_UPCE1_2: 80>
    ST_UPU_FICS_POSTAL: Barcode.Type # value = <Type.ST_UPU_FICS_POSTAL: 53>
    ST_USPS_4CB: Barcode.Type # value = <Type.ST_USPS_4CB: 52>
    pass

class CoreScanner:
    """
    Zebra CoreScanner Driver Instance
    """
    def __init__(self) -> None: ...
    def __repr__(self) -> str: ...
    def close(self) -> None: 
        """
        Closes the application instance through the CoreScanner service.
        """
    def fetch_scanners(self) -> None: 
        """
        Fetch all scanners that are connected. This command should be invoked after the Open command.
        """
    def on_scanner_added(self, arg0: object) -> None: 
        """
        Triggered when a new scanner is added. The parameter is the new scanner.
        """
    def on_scanner_removed(self, arg0: object) -> None: 
        """
        Triggered when a scanner is removed. The parameter is the removed scanner.
        """
    def open(self) -> None: 
        """
        Opens a CoreScanner instance. This must be the first command called before invoking any other command.
        """
    @property
    def scanners(self) -> typing.Dict[int, Scanner]:
        """
        Scanners list

        :type: typing.Dict[int, Scanner]
        """
    pass

class Scanner:
    """
    Zebra Scanner Instance
    """
    def __repr__(self) -> str: ...
    @typing.overload
    def fetch_attributes(self) -> typing.List[Attribute]: 
        """
        Fetch all the attributes of the scanner.

        Fetch the value of attribute of the scanner.

        Fetch the values of attribute(s) of the scanner.

        Fetch the values of attribute(s) of the scanner.
        """
    @typing.overload
    def fetch_attributes(self, arg0: int) -> typing.List[Attribute]: ...
    @typing.overload
    def fetch_attributes(self, arg0: str) -> typing.List[Attribute]: ...
    @typing.overload
    def fetch_attributes(self, arg0: typing.List[int]) -> typing.List[Attribute]: ...
    def on_barcode(self, arg0: object) -> None: 
        """
        Triggered when there is a barcode scanned. The parameter is the barcode.
        """
    def pull_trigger(self) -> None: 
        """
        Pull the trigger of the scanner.
        """
    def release_trigger(self) -> None: 
        """
        Release the trigger of the scanner.
        """
    @property
    def DoM(self) -> str:
        """
        :type: str
        """
    @property
    def GUID(self) -> str:
        """
        :type: str
        """
    @property
    def PID(self) -> str:
        """
        :type: str
        """
    @property
    def VID(self) -> str:
        """
        :type: str
        """
    @property
    def attributes(self) -> typing.Dict[int, Attribute]:
        """
        :type: typing.Dict[int, Attribute]
        """
    @property
    def firmware(self) -> str:
        """
        :type: str
        """
    @property
    def modelnumber(self) -> str:
        """
        :type: str
        """
    @property
    def scannerID(self) -> int:
        """
        :type: int
        """
    @property
    def serialnumber(self) -> str:
        """
        :type: str
        """
    @property
    def type(self) -> str:
        """
        :type: str
        """
    pass
