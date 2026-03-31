cmake_minimum_required(VERSION 3.14.0 FATAL_ERROR)

project(cpp-backend-template LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")

find_package(Crow CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)

add_subdirectory(src)


# --- TESTING CONFIGURATION ---

# Turn on testing in CMake
enable_testing()

# Ask vcpkg to find Google Test
find_package(GTest CONFIG REQUIRED)

# Create a brand new executable just for running tests.
# Notice we MUST include Utils.cpp so the test knows how to do the math!
add_executable(backend_tests 
    tests/algorithm_test.cpp 
    src/utils/Utils.cpp 
)

# Link GTest to your test executable
target_link_libraries(backend_tests PRIVATE GTest::gtest GTest::gtest_main)

# Register the test executable with CMake's test runner
add_test(NAME BackendTests COMMAND backend_tests)