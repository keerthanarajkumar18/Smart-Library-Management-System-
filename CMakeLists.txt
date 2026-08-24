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
    src/ReservationQueue.cpp
    src/StandardFineStrategy.cpp
    src/RoleBasedFineStrategy.cpp
    src/AccessControl.cpp   
    src/Logger.cpp
    src/StatisticsService.cpp
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

add_executable(ReservationQueueTest
    tests/ReservationQueueTest.cpp
)

target_link_libraries(ReservationQueueTest PRIVATE
    SmartLibrary
    gtest_main
)

add_executable(LibraryReservationTest
    tests/LibraryReservationTest.cpp
)

target_link_libraries(LibraryReservationTest PRIVATE
    SmartLibrary
    gtest_main
)

add_executable(FineStrategyTest
    tests/FineStrategyTest.cpp
)

target_link_libraries(FineStrategyTest PRIVATE
    SmartLibrary
    gtest_main
)

add_executable(LibraryFineTest
    tests/LibraryFineTest.cpp
)

target_link_libraries(LibraryFineTest PRIVATE
    SmartLibrary
    gtest_main
)

add_executable(AccessControlTest
    tests/AccessControlTest.cpp
)

target_link_libraries(AccessControlTest PRIVATE
    SmartLibrary
    gtest_main
)

add_executable(LibraryAccessControlTest
    tests/LibraryAccessControlTest.cpp
)

target_link_libraries(LibraryAccessControlTest PRIVATE
    SmartLibrary
    gtest_main
)

add_executable(LibraryExceptionTest
    tests/LibraryExceptionTest.cpp
)

target_link_libraries(LibraryExceptionTest PRIVATE
    SmartLibrary
    gtest_main
)

add_executable(LibraryExceptionIntegrationTest
    tests/LibraryExceptionIntegrationTest.cpp
)

target_link_libraries(LibraryExceptionIntegrationTest PRIVATE
    SmartLibrary
    gtest_main
)

add_executable(LoggerTest
    tests/LoggerTest.cpp
)

target_link_libraries(LoggerTest PRIVATE
    SmartLibrary
    gtest_main
)


add_executable(LibraryLoggerTest
    tests/LibraryLoggerTest.cpp
)

target_link_libraries(LibraryLoggerTest PRIVATE
    SmartLibrary
    gtest_main
)

add_executable(StatisticsTest
    tests/StatisticsTest.cpp
)

target_link_libraries(StatisticsTest PRIVATE
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

add_test(
    NAME ReservationQueueTest
    COMMAND ReservationQueueTest
)

add_test(
    NAME LibraryReservationTest
    COMMAND LibraryReservationTest
)

add_test(
    NAME FineStrategyTest
    COMMAND FineStrategyTest
)

add_test(
    NAME LibraryFineTest
    COMMAND LibraryFineTest
)

add_test(
    NAME AccessControlTest
    COMMAND AccessControlTest
)

add_test(
    NAME LibraryAccessControlTest
    COMMAND LibraryAccessControlTest
)

add_test(
    NAME LibraryExceptionTest
    COMMAND LibraryExceptionTest
)

add_test(
    NAME LibraryExceptionIntegrationTest
    COMMAND LibraryExceptionIntegrationTest
)

add_test(
    NAME LoggerTest
    COMMAND LoggerTest
)

add_test(
    NAME LibraryLoggerTest
    COMMAND LibraryLoggerTest
)

add_test(
    NAME StatisticsTest
    COMMAND StatisticsTest
)