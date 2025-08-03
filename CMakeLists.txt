cmake_minimum_required(VERSION 3.16)
project(Kalem)

set(CMAKE_CXX_STANDARD 17)

# Set output directories for Windows/MinGW
if(WIN32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
endif()

# Add glad library
add_library(glad STATIC libs/glad/src/glad.c)
target_include_directories(glad PUBLIC libs/glad/include)

# For Windows, define necessary macros for GLAD
if(WIN32)
    target_compile_definitions(glad PRIVATE WIN32_LEAN_AND_MEAN)
endif()

# Configure GLFW build options for MinGW compatibility
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_USE_HYBRID_HPG ON CACHE BOOL "" FORCE)  # Use hybrid GPU selection

# Add GLFW as subdirectory
add_subdirectory(libs/glfw)

# Main application
add_executable(Kalem 
    src/main.cpp
    src/engine/AnimationEngine.cpp
    src/engine/Scene.cpp
    src/engine/Timeline.cpp
    src/engine/PhysicsEngine.cpp
    src/objects/AnimationObject.cpp
    src/objects/Particle.cpp
    src/objects/Shape.cpp
    src/objects/Text.cpp
    src/rendering/Renderer.cpp
    src/api/EasyAPI.cpp
    src/utils/Math.cpp
    src/utils/Colors.cpp
    src/utils/Time.cpp
)

# Include directories
target_include_directories(Kalem PRIVATE 
    libs/glad/include 
    libs/glfw/include
    libs/glm
    src
    src/engine
    src/objects
    src/rendering
    src/api
    src/utils
)

# For Windows, define necessary macros for GLAD
if(WIN32)
    target_compile_definitions(Kalem PRIVATE WIN32_LEAN_AND_MEAN)
endif()

# Link libraries
target_link_libraries(Kalem PRIVATE glad glfw)

# For Windows, we need to link against the Windows libraries
if(WIN32)
    target_link_libraries(Kalem PRIVATE kernel32 user32 gdi32 winspool shell32 ole32 oleaut32 uuid comdlg32 advapi32)
endif()

# Examples
add_executable(example_basic_motion examples/basic_motion.cpp)
target_include_directories(example_basic_motion PRIVATE src)
target_link_libraries(example_basic_motion PRIVATE glad glfw)

# Documentation
configure_file(README.md ${CMAKE_BINARY_DIR}/README.md COPYONLY)
