# Zebra Scanner Python Extension for Windows
This is Windows version of Zebra Scanner python extension. 

For the original Linux version, see https://github.com/dayjaby/zebra-scanner

### Built With

- [{fmt}](https://github.com/fmtlib/fmt)
- [pugixml](https://github.com/zeux/pugixml)
- [Magic Enum C++](https://github.com/Neargye/magic_enum) (Optional, for barcode types)

## Supported boards

Developed based on DS8108 model.

More boards please check https://www.zebra.cn/us/en/support-downloads/software/developer-tools/scanner-sdk-for-windows.html

## Features

- Scanner added and removed decorator
- Get, set and store attributes for scanners
- Barcode scanned decorator
- Barcode type ID to symbology type supported
- Barcode symbology types enumeration (Optional, with C++ 17)
- Full `__repr__` supported

**Note:** Scanners added after the `open()` command will have no PID and VID information.

## Building

Requirements:

- [Zebra CoreScanner Driver for Windows](https://www.zebra.cn/us/en/support-downloads/software/developer-tools/scanner-sdk-for-windows.html)
- Visual Studio 2017 or above
- pybind11 (`pip install pybind11`)

## A minimal example

```python
import time
from zebra_scanner import CoreScanner

cs = CoreScanner()


@cs.on_scanner_added
def on_scanner_added(scanner):
    print("New scanner found:", scanner)
    scanner.pull_trigger()
    
    print(scanner.fetch_attributes([20004, 535]))
    
    @scanner.on_barcode
    def on_barcode(barcode):
        print("Scanned:", barcode)


@cs.on_scanner_removed
def on_scanner_removed(scanner):
    print("Scanner removed:", scanner)
    scanner.release_trigger()

cs.open()
while True:
    time.sleep(0.1)
    # do nothing while the scanner is reading in continous mode
```

## Running the example

The run result masks the serial number and GUID.

```
> python zebra_test.py
New scanner found: Scanner(type='SNAPI', scannerID=1, serialnumber='21064010xxxxxx', GUID='358929B1EDF24E0180A0C181xxxxxxxx', PID='6400', modelnumber='1504', DoM='DS8108-SR00007ZZCN', firmware='05MAR21')

[Attribute(id=20004, permission='R', datatype='S', value='PAACZS00-006-R02  '), Attribute(id=535, permission='R', datatype='S', value='05MAR21')]

Scanned: Barcode(code='4974365862466', type='11', symbology='EAN-13')

Scanner removed: Scanner(type='SNAPI', scannerID=1, serialnumber='21064010xxxxxx', GUID='358929B1EDF24E0180A0C181xxxxxxxx', PID='6400', modelnumber='1504', DoM='DS8108-SR00007ZZCN', firmware='05MAR21')
```

## About

This project was created by [Hintay](http://kugeek.com) based on the [Linux version](https://github.com/dayjaby/zebra-scanner) by [dayjaby](https://github.com/dayjaby).

### License

This project is provided under a MPL 2.0 license that can be found in the LICENSE file. By using, distributing, or contributing to this project, you agree to the terms and conditions of this license.

