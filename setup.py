from setuptools import setup, Extension
import pybind11

cpp_args = ['/std:c++17', '/DPUGIXML_WCHAR_MODE', '/Zc:wchar_t']

sfc_module = Extension(
    'zebra_scanner',
    sources=[
        'zebra-scanner/event_sink.cpp',
        'zebra-scanner/barcode.cpp',
        'zebra-scanner/attribute.cpp',
        'zebra-scanner/scanner.cpp',
        'zebra-scanner/zebra_scanner.cpp',
        'zebra-scanner/lib/fmt/format.cc',
        'zebra-scanner/lib/pugixml/pugixml.cpp'
        ],
    include_dirs=[
        pybind11.get_include(),
        "zebra-scanner/include"
        ],
    language='c++',
    libraries=['ole32'],
    extra_compile_args=cpp_args
    )

setup(
    name='zebra_scanner_windows',
    version='1.0',
    author="Hintay",
    author_email="hintay@me.com",
    description="Scan barcodes in python with Zebra Scanner for Windows ",
    url="https://github.com/Hintay/py-zebra-scanner-windows",
    packages=setuptools.find_packages(),
    classifiers=[
        "Programming Language :: Python",
        "License :: OSI Approved :: Mozilla Public License 2.0 (MPL 2.0)",
        "Operating System :: Microsoft :: Windows",
    ],
    ext_modules=[sfc_module]
)