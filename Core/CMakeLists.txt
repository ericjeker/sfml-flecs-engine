# --- Sources Files ---
file(GLOB_RECURSE SOURCE_FILES Private/*.cpp)
file(GLOB_RECURSE HEADER_FILES Private/*.h)

add_library(SFECore)
target_sources(SFECore PRIVATE ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(SFECore PUBLIC Public)
target_include_directories(SFECore PRIVATE Private)
target_link_libraries(SFECore PUBLIC SFEVendor)

# Enable debug mode if we are in the debug build
target_compile_definitions(SFECore PRIVATE $<$<CONFIG:Debug>:DEBUG>)

# Create alias target for modern CMake usage
add_library(SFE::Core ALIAS SFECore)
