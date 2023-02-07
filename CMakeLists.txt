cmake_minimum_required(VERSION 3.1.0)
project(HuffmanTree VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(HuffmanTree huffman.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
