# Agent Guidelines for SFML-Flecs Engine

## Build Commands
```bash
# Build the project
./build.sh Build Release

# Build with custom directories
./build.sh BuildDir InstallDir
```

## Code Style & Formatting
- **Language**: C++20
- **Indentation**: 4 spaces (never tabs)
- **Line limit**: 120 characters
- **Formatting**: Use clang-format with project .clang-format config
- **Private members**: Prefix with underscore (e.g., `_memberName`)
- **Naming**: CamelCase for classes/functions, camelBack for variables/parameters

## Linting & Static Analysis
- **Tool**: clang-tidy with comprehensive checks enabled
- **Config**: .clang-tidy file in project root
- **Warnings as errors**: All warnings treated as errors

## Project Structure
- **Core architecture**: ECS-based using Flecs library
- **Graphics**: SFML 3.0.1 for rendering/window management
- **Build system**: CMake with Ninja generator
- **Dependencies**: Tracy profiler, nlohmann/json, flecs ECS

## Key Conventions
- **Headers**: Use `#pragma once` (not include guards)
- **Includes**: Follow include order in .clang-format (Core headers first, then SFML, then system)
- **Error handling**: Use exceptions appropriately, avoid raw pointers
- **Memory management**: Prefer smart pointers and RAII
- **ECS pattern**: Components are simple data structs, systems handle logic