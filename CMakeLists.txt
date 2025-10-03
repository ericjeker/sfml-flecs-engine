cmake_minimum_required(VERSION 3.31...4.1)
project(SFE)

# --- CMake Specifications ---
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# --- Platform-specific configurations ---
if(UNIX AND NOT APPLE)
    # Linux-specific settings
    find_package(PkgConfig REQUIRED)
    find_package(X11 REQUIRED)

    # Additional Linux libraries that might be needed
    find_package(Threads REQUIRED)
elseif(WIN32)
    # Windows-specific settings
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

# --- Add the Vendor and Core subdirectories ---
add_subdirectory(Vendor)
add_subdirectory(Core)

# --- Optional: Build example ---
option(SFE_BUILD_EXAMPLE "Build the example project" ON)
if(SFE_BUILD_EXAMPLE)
    add_subdirectory(Example)
endif()
