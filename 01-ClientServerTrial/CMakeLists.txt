cmake_minimum_required(VERSION 3.5)
project(vsomeip_example)

find_package(vsomeip3 REQUIRED)
find_package(Boost REQUIRED)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${VSOMEIP_INCLUDE_DIRS}
)

configure_file(
    "${CMAKE_SOURCE_DIR}/vsomeip-local.json"
    "${CMAKE_BINARY_DIR}/vsomeip-local.json"
    COPYONLY
)

add_executable(server server.cpp)
target_link_libraries(server vsomeip3 ${Boost_LIBRARIES})

add_executable(client client.cpp)
target_link_libraries(client vsomeip3 ${Boost_LIBRARIES})