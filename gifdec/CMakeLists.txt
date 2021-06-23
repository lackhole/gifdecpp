cmake_minimum_required(VERSION 3.19)
project(gifdec C CXX)

set(CMAKE_CXX_STANDARD 11)
set(GIFDEC_CC_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_library(gifdec STATIC
        ${GIFDEC_CC_INCLUDE_DIR}/gifdec/c/gifdec_c.c
        ${GIFDEC_CC_INCLUDE_DIR}/gifdec/gifdec.cc)

target_include_directories(gifdec PUBLIC ${GIFDEC_CC_INCLUDE_DIR})
