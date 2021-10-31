/*******************************************************************************************
* @file common_defs.h
* @brief CoreScanner common definitions
* @version 1.0.0.1
* @date 2020-05-21
* @copyright  ©2020 Zebra Technologies Corporation and/or its affiliates. All rights reserved.
********************************************************************************************/
#pragma once

//---- Scanner Types ------//
#define SCANNER_TYPES_ALL       0x01
#define SCANNER_TYPES_SNAPI     0x02
#define SCANNER_TYPES_SSI       0x03
#define SCANNER_TYPES_IBMHID    0x06
#define SCANNER_TYPES_NIXMODB   0x07
#define SCANNER_TYPES_HIDKB     0x08
#define SCANNER_TYPES_IBMTT     0x09
#define SCANNER_TYPES_SSI_BT    0x0B
#define SCANNER_TYPES_OPOS      0x0D

//---- Event Types ------//
#define EVENT_TYPE_BARCODE  0x01
#define EVENT_TYPE_IMAGE    0x02
#define EVENT_TYPE_VIDEO    0x04
#define EVENT_TYPE_RMD      0x08
#define EVENT_TYPE_PNP      0x10
#define EVENT_TYPE_OTHER    0x20

//---- Command return status ------//
#define   STATUS_SUCCESS 0
#define   STATUS_LOCKED 10


/// Maximum number of scanners to be connected
#define MAX_NUM_DEVICES 255

//--------- Command Opcodes    --------//
enum class OPCODE
{
    // Gets the version of CoreScanner
    GET_VERSION = 0x3E8,    //1000

    // Register for API events
    REGISTER_FOR_EVENTS = 0x3E9,    //1001

    // Unregister for API events
    UNREGISTER_FOR_EVENTS = 0x3EA,    //1002

    // Get Bluetooth scanner pairing bar code
    GET_PAIRING_BARCODE = 0x3ED,    //1005

    // Claim a specific device
    CLAIM_DEVICE = 0x5DC,    //1500

    // Release a specific device
    RELEASE_DEVICE = 0x5DD,    //1501

    // Abort MacroPDF of a specified scanner
    DEVICE_ABORT_MACROPDF = 0x7D0,    //2000

    // Abort firmware update process of a specified scanner, while in progress
    DEVICE_ABORT_UPDATE_FIRMWARE = 0x7D1,    //2001

    // Turn Aim off
    DEVICE_AIM_OFF = 0x7D2,    //2002

    // Turn Aim on
    DEVICE_AIM_ON = 0x7D3,    //2003

    // Flush MacroPDF of a specified scanner
    DEVICE_FLUSH_MACROPDF = 0x7D5,    //2005

    // Pull the trigger of a specified scanner
    DEVICE_PULL_TRIGGER = 0x7DB,    //2011

    // Release the trigger of a specified scanner
    DEVICE_RELEASE_TRIGGER = 0x7DC,    //2012

    // Disable scanning on a specified scanner
    DEVICE_SCAN_DISABLE = 0x7DD,    //2013

    // Enable scanning on a specified scanner
    DEVICE_SCAN_ENABLE = 0x7DE,    //2014

    // Set parameters to default values of a specified scanner
    DEVICE_SET_PARAMETER_DEFAULTS = 0x7DF,    //2015

    // Set parameters of a specified scanner
    DEVICE_SET_PARAMETERS = 0x7E0,    //2016

    // Set and persist parameters of a specified scanner
    DEVICE_SET_PARAMETER_PERSISTANCE = 0x7E1,    //2017

    // Reboot a specified scanner
    REBOOT_SCANNER = 0x7E3,    //2019

    // Disconnect the specified Bluetooth scanner
    DISCONNECT_BT_SCANNER = 0x7E7,    //2023

    // Change a specified scanner to snapshot mode 
    DEVICE_CAPTURE_IMAGE = 0xBB8,    //3000

    // Change a specified scanner to decode mode 
    DEVICE_CAPTURE_BARCODE = 0xDAC,    //3500

    // Change a specified scanner to video mode 
    DEVICE_CAPTURE_VIDEO = 0xFA0,    //4000


    // Get all the attributes of a specified scanner
    RSM_ATTR_GETALL = 0x1388,    //5000

    // Get the attribute values(s) of specified scanner
    RSM_ATTR_GET = 0x1389,    //5001

    // Get the next attribute to a given attribute of specified scanner
    RSM_ATTR_GETNEXT = 0x138A,    //5002

    // Set the attribute values(s) of specified scanner
    RSM_ATTR_SET = 0x138C,    //5004

    // Store and persist the attribute values(s) of specified scanner
    RSM_ATTR_STORE = 0x138D,    //5005


    // Get the topology of the connected devices
    GET_DEVICE_TOPOLOGY = 0x138E,    //5006

    // Remove all Symbol device entries from registry
    UNINSTALL_SYMBOL_DEVICES = 0x1392,    //5010

    // Start (flashing) the updated firmware
    START_NEW_FIRMWARE = 0x1396,    //5014

    // Update the firmware to a specified scanner
    DEVICE_UPDATE_FIRMWARE = 0x1398,    //5016

    // Update the firmware to a specified scanner using a scanner plug-in
    DEVICE_UPDATE_FIRMWARE_FROM_PLUGIN = 0x1399,    //5017

    // Update good scan tone of the scanner with specified wav file
    UPDATE_DECODE_TONE = 0x13BA,    //5050

    // Erase good scan tone of the scanner
    ERASE_DECODE_TONE = 0x13BB,    //5051

    // Perform an action involving scanner beeper/LEDs
    SET_ACTION = 0x1770,    //6000

    // Set the serial port settings of a NIXDORF Mode-B scanner
    DEVICE_SET_SERIAL_PORT_SETTINGS = 0x17D5,    //6101

    // Switch the USB host mode of a specified scanner
    DEVICE_SWITCH_HOST_MODE = 0x1838,    //6200

    // Switch CDC devices
    SWITCH_CDC_DEVICES = 0x1839,    //6201



    // HID keyboard emulator opcodes ----------------------

    // Enable/Disable keyboard emulation mode
    KEYBOARD_EMULATOR_ENABLE = 0x189C,    //6300

    // Set the locale for keyboard emulation mode
    KEYBOARD_EMULATOR_SET_LOCALE = 0x189D,    //6301

    // Get current configuration of the HID keyboard emulator
    KEYBOARD_EMULATOR_GET_CONFIG = 0x189E,    //6302



    // Driver ADF commands --------------------------------

    //  Configure Driver ADF
    CONFIGURE_DADF = 0x1900,    //6400

    // Reset Driver ADF
    RESET_DADF = 0x1901,    //6401



    // Scale opcodes --------------------------------------

    // Measure the weight on the scanner's platter and get the value
    SCALE_READ_WEIGHT = 0x1b58,    //7000

    //  Zero the scale
    SCALE_ZERO_SCALE = 0X1B5A,    //7002

    // Reset the scale
    SCALE_SYSTEM_RESET = 0X1B67,    //7015
};

//---------- Beep Codes for SoundBeeper() function -----------//
#define ONESHORTHIGH       0x00
#define TWOSHORTHIGH       0x01
#define THREESHORTHIGH     0x02
#define FOURSHORTHIGH      0x03
#define FIVESHORTHIGH      0x04

#define ONESHORTLOW        0x05
#define TWOSHORTLOW        0x06
#define THREESHORTLOW      0x07
#define FOURSHORTLOW       0x08
#define FIVESHORTLOW       0x09

#define ONELONGHIGH        0x0A
#define TWOLONGHIGH        0x0B
#define THREELONGHIGH      0x0C
#define FOURLONGHIGH       0x0D
#define FIVELONGHIGH       0x0E

#define ONELONGLOW         0x0F
#define TWOLONGLOW         0x10
#define THREELONGLOW       0x11
#define FOURLONGLOW        0x12
#define FIVELONGLOW        0x13

#define FASTHIGHLOWHIGHLOW 0x14
#define SLOWHIGHLOWHIGHLOW 0x15
#define HIGHLOW            0x16
#define LOWHIGH            0x17
#define HIGHLOWHIGH        0x18
#define LOWHIGHLOW         0x19

#define LED1ON   0x2B /* Green  Led On */
#define LED2ON   0x2D /* Yellow  Led On */
#define LED3ON   0x2F /* Red  Led On */
#define LED1OFF  0x2A /* Green  Led Off  */
#define LED2OFF  0x2E /* Yellow  Led Off */
#define LED3OFF  0x30 /* Red  Led Off */

//----- Firmware Download Events ------//
#define SCANNER_UF_SESS_START        0x0B // Triggered when flash download session starts 
#define SCANNER_UF_DL_START          0x0C // Triggered when component download starts 
#define SCANNER_UF_DL_PROGRESS       0x0D // Triggered when block(s) of flash completed 
#define SCANNER_UF_DL_END            0x0E // Triggered when component download ends 
#define SCANNER_UF_SESS_END          0x0F // Triggered when flash download session ends 
#define SCANNER_UF_STATUS            0x10 // Triggered when update error or status

//------- Scanner Notification Event Types ----//
#define BARCODE_MODE    0x01
#define IMAGE_MODE      0x02
#define VIDEO_MODE      0x03
#define DEVICE_ENABLED  0x0D
#define DEVICE_DISABLED 0x0E

//----- Symbology Types ---------------//
enum class BarcodeType
{
    ST_NOT_APP = 0x00,
    ST_CODE_39 = 0x01,
    ST_CODABAR = 0x02,
    ST_CODE_128 = 0x03,
    ST_D2OF5 = 0x04,
    ST_IATA = 0x05,
    ST_I2OF5 = 0x06,
    ST_CODE93 = 0x07,
    ST_UPCA = 0x08,
    ST_UPCE0 = 0x09,
    ST_EAN8 = 0x0A,
    ST_EAN13 = 0x0B,
    ST_CODE11 = 0x0C,
    ST_CODE49 = 0x0D,
    ST_MSI = 0x0E,
    ST_EAN128 = 0x0F,
    ST_UPCE1 = 0x10,
    ST_PDF417 = 0x11,
    ST_CODE16K = 0x12,
    ST_C39FULL = 0x13,
    ST_UPCD = 0x14,
    ST_TRIOPTIC = 0x15,
    ST_BOOKLAND = 0x16,
    ST_UPCA_W_CODE128 = 0x17, // For UPC-A w/Code 128 Supplemental
    ST_JAN13_W_CODE128 = 0x78, // For EAN/JAN-13 w/Code 128 Supplemental
    ST_NW7 = 0x18,
    ST_ISBT128 = 0x19,
    ST_MICRO_PDF = 0x1A,
    ST_DATAMATRIX = 0x1B,
    ST_QR_CODE = 0x1C,
    ST_MICRO_PDF_CCA = 0x1D,
    ST_POSTNET_US = 0x1E,
    ST_PLANET_CODE = 0x1F,
    ST_CODE_32 = 0x20,
    ST_ISBT128_CON = 0x21,
    ST_JAPAN_POSTAL = 0x22,
    ST_AUS_POSTAL = 0x23,
    ST_DUTCH_POSTAL = 0x24,
    ST_MAXICODE = 0x25,
    ST_CANADIN_POSTAL = 0x26,
    ST_UK_POSTAL = 0x27,
    ST_MACRO_PDF = 0x28,
    ST_MACRO_QR_CODE = 0x29,
    ST_MICRO_QR_CODE = 0x2C,
    ST_AZTEC = 0x2D,
    ST_AZTEC_RUNE = 0x2E,
    ST_DISTANCE = 0x2F,
    ST_RSS14 = 0x30,
    ST_RSS_LIMITED = 0x31,
    ST_RSS_EXPANDED = 0x32,
    ST_PARAMETER = 0x33,
    ST_USPS_4CB = 0x34,
    ST_UPU_FICS_POSTAL = 0x35,
    ST_ISSN = 0x36,
    ST_SCANLET = 0x37,
    ST_CUECODE = 0x38,
    ST_MATRIX2OF5 = 0x39,
    ST_UPCA_2 = 0x48,
    ST_UPCE0_2 = 0x49,
    ST_EAN8_2 = 0x4A,
    ST_EAN13_2 = 0x4B,
    ST_UPCE1_2 = 0x50,
    ST_CCA_EAN128 = 0x51,
    ST_CCA_EAN13 = 0x52,
    ST_CCA_EAN8 = 0x53,
    ST_CCA_RSS_EXPANDED = 0x54,
    ST_CCA_RSS_LIMITED = 0x55,
    ST_CCA_RSS14 = 0x56,
    ST_CCA_UPCA = 0x57,
    ST_CCA_UPCE = 0x58,
    ST_CCC_EAN128 = 0x59,
    ST_TLC39 = 0x5A,
    ST_CCB_EAN128 = 0x61,
    ST_CCB_EAN13 = 0x62,
    ST_CCB_EAN8 = 0x63,
    ST_CCB_RSS_EXPANDED = 0x64,
    ST_CCB_RSS_LIMITED = 0x65,
    ST_CCB_RSS14 = 0x66,
    ST_CCB_UPCA = 0x67,
    ST_CCB_UPCE = 0x68,
    ST_SIGNATURE_CAPTURE = 0x69,
    ST_MOA = 0x6A,
    ST_PDF417_PARAMETER = 0x70,
    ST_CHINESE2OF5 = 0x72,
    ST_KOREAN_3_OF_5 = 0x73,
    ST_DATAMATRIX_PARAM = 0x74,
    ST_CODE_Z = 0x75,
    ST_UPCA_5 = 0x88,
    ST_UPCE0_5 = 0x89,
    ST_EAN8_5 = 0x8a,
    ST_EAN13_5 = 0x8b,
    ST_UPCE1_5 = 0x90,
    ST_MACRO_MICRO_PDF = 0x9A,
    ST_OCRB = 0xA0,
    ST_OCRA = 0xA1,
    ST_PARSED_DRIVER_LICENSE = 0xB1,
    ST_PARSED_UID = 0xB2,
    ST_PARSED_NDC = 0xB3,
    ST_DATABAR_COUPON = 0xB4,
    ST_PARSED_XML = 0xB6,
    ST_HAN_XIN_CODE = 0xB7,
    ST_CALIBRATION = 0xC0,
    ST_GS1_DATAMATRIX = 0xC1,
    ST_GS1_QR = 0xC2,
    BT_MAINMARK = 0xC3,
    BT_DOTCODE = 0xC4,
    BT_GRID_MATRIX = 0xC8,
	BT_UDI_CODE = 0xCC
};

#define BARCODE_EVENT_TYPE_GOOD_DECODE 1

#define SCANNER_ATTACHED 0
#define SCANNER_DETACHED 1

//Language definition enum 
#ifndef HID_PUMP_LANGUAGE_CODES
#define HID_PUMP_LANGUAGE_CODES
enum LANGUAGE_CODES
{
    STARTCODE = -1,
    DEFAULT = 0,
    FRENCH = 1,
    ENGLISH = 2,
    ENDCODE = ENGLISH + 1 //Allways one more than the last lang entry
};
#endif