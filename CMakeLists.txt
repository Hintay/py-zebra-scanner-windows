cmake_minimum_required(VERSION 3.16...3.29)

project(
        zebra-scanner
        VERSION ${SKBUILD_PROJECT_VERSION}
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17 CACHE STRING "C++ version selection")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-DUNICODE -D_UNICODE)

set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(PUGIXML_WCHAR_MODE ON CACHE INTERNAL "Enable wchar_t mode")
set(PUGIXML_INSTALL OFF CACHE INTERNAL "Disable pugixml installation rules")
set(FMT_INSTALL OFF CACHE INTERNAL "Disable {fmt} installation rules")

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
        GIT_TAG        3b17184379fcaaeb7f1fbe08018b7fedf2640b3b)  # 1.14+ with installation rules

FetchContent_Declare(
        magic_enum
        GIT_REPOSITORY https://github.com/Neargye/magic_enum
        GIT_TAG        dd6a39d0ba1852cf06907e0f0573a2a10d23c2ad)  # 0.9.6

FetchContent_MakeAvailable(fmt pugixml magic_enum)

if(NOT EXISTS "${CMAKE_CURRENT_BINARY_DIR}/cmake/FindIDL.cmake")
  message(STATUS "Downloading FindIDL.cmake from https://github.com/apriorit/FindIDL")
  file(DOWNLOAD "https://raw.githubusercontent.com/apriorit/FindIDL/1.0.2/cmake/FindIDL.cmake"
                "${CMAKE_CURRENT_BINARY_DIR}/cmake/FindIDL.cmake"
                EXPECTED_HASH SHA256=d88db93c485227b287371bd1848d82110fa5ef32e5febe6865aa3ec27c7558b3
                TLS_VERIFY ON)
endif()

include(${CMAKE_CURRENT_BINARY_DIR}/cmake/FindIDL.cmake)

# ==============================================================================
# Includes
# ==============================================================================
include_directories (
        zebra-scanner/include
)

add_idl(CoreScanner zebra-scanner/_CoreScanner.idl)

python_add_library(zebra_scanner MODULE
        zebra-scanner/event_sink.cpp
        zebra-scanner/barcode.cpp
        zebra-scanner/attribute.cpp
        zebra-scanner/scanner.cpp
        zebra-scanner/zebra_scanner.cpp
)
target_link_libraries(zebra_scanner PRIVATE pybind11::headers)
target_link_libraries(zebra_scanner PRIVATE pybind11::module)
set_target_properties(zebra_scanner PROPERTIES CXX_VISIBILITY_PRESET "hidden")
set_target_properties(zebra_scanner PROPERTIES CUDA_VISIBILITY_PRESET "hidden")
pybind11_extension(zebra_scanner)

if(NOT DEFINED CMAKE_INTERPROCEDURAL_OPTIMIZATION)
    target_link_libraries(zebra_scanner PRIVATE pybind11::lto)
endif()

target_compile_definitions(zebra_scanner PUBLIC $<$<BOOL:${PUGIXML_WCHAR_MODE}>:PUGIXML_WCHAR_MODE>)

target_link_libraries(zebra_scanner PRIVATE CoreScanner fmt::fmt pugixml::pugixml magic_enum::magic_enum)

install(TARGETS zebra_scanner LIBRARY DESTINATION .)
install(FILES "${PROJECT_SOURCE_DIR}/zebra_scanner.pyi" DESTINATION .)
