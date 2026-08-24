# CMake generated Testfile for 
# Source directory: C:/Users/KEERTHANA/OneDrive/Desktop/MCW Training/Library_Management_System
# Build directory: C:/Users/KEERTHANA/OneDrive/Desktop/MCW Training/Library_Management_System/uild
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(BookTest "C:/Users/KEERTHANA/OneDrive/Desktop/MCW Training/Library_Management_System/uild/BookTest.exe")
set_tests_properties(BookTest PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/KEERTHANA/OneDrive/Desktop/MCW Training/Library_Management_System/CMakeLists.txt;115;add_test;C:/Users/KEERTHANA/OneDrive/Desktop/MCW Training/Library_Management_System/CMakeLists.txt;0;")
add_test(MemberTest "C:/Users/KEERTHANA/OneDrive/Desktop/MCW Training/Library_Management_System/uild/MemberTest.exe")
set_tests_properties(MemberTest PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/KEERTHANA/OneDrive/Desktop/MCW Training/Library_Management_System/CMakeLists.txt;120;add_test;C:/Users/KEERTHANA/OneDrive/Desktop/MCW Training/Library_Management_System/CMakeLists.txt;0;")
add_test(BorrowRecordTest "C:/Users/KEERTHANA/OneDrive/Desktop/MCW Training/Library_Management_System/uild/BorrowRecordTest.exe")
set_tests_properties(BorrowRecordTest PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/KEERTHANA/OneDrive/Desktop/MCW Training/Library_Management_System/CMakeLists.txt;125;add_test;C:/Users/KEERTHANA/OneDrive/Desktop/MCW Training/Library_Management_System/CMakeLists.txt;0;")
add_test(LibraryTest "C:/Users/KEERTHANA/OneDrive/Desktop/MCW Training/Library_Management_System/uild/LibraryTest.exe")
set_tests_properties(LibraryTest PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/KEERTHANA/OneDrive/Desktop/MCW Training/Library_Management_System/CMakeLists.txt;130;add_test;C:/Users/KEERTHANA/OneDrive/Desktop/MCW Training/Library_Management_System/CMakeLists.txt;0;")
add_test(LibraryBorrowReturnTest "C:/Users/KEERTHANA/OneDrive/Desktop/MCW Training/Library_Management_System/uild/LibraryBorrowReturnTest.exe")
set_tests_properties(LibraryBorrowReturnTest PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/KEERTHANA/OneDrive/Desktop/MCW Training/Library_Management_System/CMakeLists.txt;135;add_test;C:/Users/KEERTHANA/OneDrive/Desktop/MCW Training/Library_Management_System/CMakeLists.txt;0;")
add_test(ReservationQueueTest "C:/Users/KEERTHANA/OneDrive/Desktop/MCW Training/Library_Management_System/uild/ReservationQueueTest.exe")
set_tests_properties(ReservationQueueTest PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/KEERTHANA/OneDrive/Desktop/MCW Training/Library_Management_System/CMakeLists.txt;140;add_test;C:/Users/KEERTHANA/OneDrive/Desktop/MCW Training/Library_Management_System/CMakeLists.txt;0;")
add_test(LibraryReservationTest "C:/Users/KEERTHANA/OneDrive/Desktop/MCW Training/Library_Management_System/uild/LibraryReservationTest.exe")
set_tests_properties(LibraryReservationTest PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/KEERTHANA/OneDrive/Desktop/MCW Training/Library_Management_System/CMakeLists.txt;145;add_test;C:/Users/KEERTHANA/OneDrive/Desktop/MCW Training/Library_Management_System/CMakeLists.txt;0;")
subdirs("googletest-build")
