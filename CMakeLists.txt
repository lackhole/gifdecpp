cmake_minimum_required(VERSION 3.19)
project(untitled4)

find_package(OpenCV)
add_subdirectory(gifdec)

set(CMAKE_CXX_STANDARD 17)
add_executable(untitled4 example.cc)

target_link_libraries(untitled4 PUBLIC ${OpenCV_LIBS} gifdec)
target_include_directories(untitled4 PUBLIC
        ${OpenCV_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR})
