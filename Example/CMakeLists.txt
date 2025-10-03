cmake_minimum_required(VERSION 3.31)
project(SFEExample)

set(CMAKE_CXX_STANDARD 23)

# Create the example executable
add_executable(SFEExample Main.cpp)
target_link_libraries(SFEExample PRIVATE SFE::Core)
