# --- Sources Files ---
file(GLOB_RECURSE SOURCE_FILES Private/*.cpp)
file(GLOB_RECURSE HEADER_FILES Private/*.h)

add_library(SFMLFlecsEngineCore)
target_sources(SFMLFlecsEngineCore PRIVATE ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(SFMLFlecsEngineCore PUBLIC Public)
target_include_directories(SFMLFlecsEngineCore PRIVATE Private)
target_link_libraries(SFMLFlecsEngineCore PUBLIC Vendor)

# Enable debug mode if we are in the debug build
target_compile_definitions(SFMLFlecsEngineCore PRIVATE $<$<CONFIG:Debug>:DEBUG>)

# Create alias target for modern CMake usage
add_library(SFMLFlecsEngine::Core ALIAS SFMLFlecsEngineCore)
