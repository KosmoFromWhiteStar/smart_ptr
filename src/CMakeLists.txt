cmake_minimum_required (VERSION 3.8)

add_executable (smart_ptr ${CMAKE_SOURCE_DIR}/incl/smartPtr.h smart_ptr.cpp)
target_link_directories(smart_ptr PUBLIC ${CMAKE_SOURCE_DIR}/incl)

