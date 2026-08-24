cmake_minimum_required(VERSION 3.15)

project(SmartLibrary)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Use existing GoogleTest
add_subdirectory(
    "C:/Users/KEERTHANA/Downloads/googletest-main/googletest-main"
    "${CMAKE_BINARY_DIR}/googletest-build"
)

# Set C++ standard for GoogleTest targets
set_target_properties(gtest gtest_main PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Create SmartLibrary library
add_library(SmartLibrary
    src/Book.cpp
    src/Member.cpp
    src/BorrowRecord.cpp
    src/Library.cpp
)

# Tell SmartLibrary where header files are
target_include_directories(SmartLibrary PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Main application
add_executable(SmartLibraryApp
    src/main.cpp
)

target_link_libraries(SmartLibraryApp PRIVATE
    SmartLibrary
)

# -------------------------
# Tests
# -------------------------

add_executable(BookTest
    tests/BookTest.cpp
)

target_link_libraries(BookTest PRIVATE
    SmartLibrary
    gtest_main
)

add_executable(MemberTest
    tests/MemberTest.cpp
)

target_link_libraries(MemberTest PRIVATE
    SmartLibrary
    gtest_main
)

add_executable(BorrowRecordTest
    tests/BorrowRecordTest.cpp
)

target_link_libraries(BorrowRecordTest PRIVATE
    SmartLibrary
    gtest_main
)

add_executable(LibraryTest
    tests/LibraryTest.cpp
)

target_link_libraries(LibraryTest PRIVATE
    SmartLibrary
    gtest_main
)

add_executable(LibraryBorrowReturnTest
    tests/LibraryBorrowReturnTest.cpp
)

target_link_libraries(LibraryBorrowReturnTest PRIVATE
    SmartLibrary
    gtest_main
)


# Enable CTest
enable_testing()

# Register tests
add_test(
    NAME BookTest
    COMMAND BookTest
)

add_test(
    NAME MemberTest
    COMMAND MemberTest
)

add_test(
    NAME BorrowRecordTest
    COMMAND BorrowRecordTest
)

add_test(
    NAME LibraryTest
    COMMAND LibraryTest
)

add_test(
    NAME LibraryBorrowReturnTest
    COMMAND LibraryBorrowReturnTest
)