cmake_minimum_required(VERSION 3.5)
project(vsomeip_client)

set(CMAKE_CXX_STANDARD 11)

find_package(vsomeip3 REQUIRED)

add_executable(client client.cpp)
target_link_libraries(client ${VSOMEIP_LIBRARIES})
