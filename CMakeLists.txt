cmake_minimum_required(VERSION 3.15)
project(tcp_udp_server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fsanitize=address,undefined")

include_directories(include)

add_executable(test_threadpool tests/test_threadpool.cpp)
target_link_libraries(test_threadpool pthread)

add_executable(test_tcpserver tests/test_tcpserver.cpp)
target_link_libraries(test_tcpserver pthread)