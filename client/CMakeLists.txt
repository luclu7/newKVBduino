cmake_minimum_required(VERSION 2.8.12)
project(serialClient)

add_definitions("-std=c++20")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# add libserial
#find_library(LIBSERIAL serial)


# add file messages/messages.cpp


add_executable(client main.cpp messages/messages.cpp tests/tests.cpp)
target_link_libraries(client ${CONAN_LIBS})