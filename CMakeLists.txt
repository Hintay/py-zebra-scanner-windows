cmake_minimum_required(VERSION 3.15...3.29)

project(
        zebra-scanner
        VERSION ${SKBUILD_PROJECT_VERSION}
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17 CACHE STRING "C++ version selection")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 CONFIG REQUIRED)

# ==============================================================================
# Dependencies
# ==============================================================================

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt
        GIT_TAG        0c9fce2ffefecfdce794e1859584e25877b7b592)  # 11.0.2

FetchContent_Declare(
        pugixml
        GIT_REPOSITORY https://github.com/zeux/pugixml
        GIT_TAG        db78afc2b7d8f043b4bc6b185635d949ea2ed2a8)  # 1.14

FetchContent_Declare(
        magic_enum
        GIT_REPOSITORY https://github.com/Neargye/magic_enum
        GIT_TAG        dd6a39d0ba1852cf06907e0f0573a2a10d23c2ad)  # 0.9.6

FetchContent_MakeAvailable(fmt pugixml magic_enum)

# ==============================================================================
# Includes
# ==============================================================================
include_directories (
        zebra-scanner/include
)

pybind11_add_module(zebra-scanner
        zebra-scanner/event_sink.cpp
        zebra-scanner/barcode.cpp
        zebra-scanner/attribute.cpp
        zebra-scanner/scanner.cpp
        zebra-scanner/zebra_scanner.cpp
)

target_link_libraries(zebra-scanner PRIVATE fmt::fmt pugixml::pugixml magic_enum::magic_enum)

install(TARGETS zebra-scanner LIBRARY DESTINATION .)