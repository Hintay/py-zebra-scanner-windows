from setuptools import setup, Extension, find_packages
from pathlib import Path
import pybind11

cpp_args = ['/std:c++17', '/Zc:wchar_t']

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
    define_macros=[('PUGIXML_WCHAR_MODE', None)],
    extra_compile_args=cpp_args
    )

this_directory = Path(__file__).parent
long_description = (this_directory / "README.md").read_text()

setup(
    name='zebra_scanner_windows',
    version='1.0',
    author="Hintay",
    author_email="hintay@me.com",
    description="Scan barcodes in python with Zebra Scanner for Windows ",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/Hintay/py-zebra-scanner-windows",
    packages=find_packages(),
    classifiers=[
        "Programming Language :: Python",
        "License :: OSI Approved :: Mozilla Public License 2.0 (MPL 2.0)",
        "Operating System :: Microsoft :: Windows",
    ],
    ext_modules=[sfc_module]
)