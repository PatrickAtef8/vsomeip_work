cmake_minimum_required(VERSION 3.5)
project(vsomeip_helloworld)

find_package(vsomeip3 REQUIRED)
find_package(Boost REQUIRED)

include_directories(
    ${Boost_INCLUDE_DIRS}
    ${VSOMEIP_INCLUDE_DIRS}
)

# Copy the correct JSON config file into the build directory
configure_file(
    "${CMAKE_SOURCE_DIR}/server.json"
    "${CMAKE_BINARY_DIR}/server.json"
    COPYONLY
)

# Server setup
add_executable(server server.cpp)
target_link_libraries(server vsomeip3 ${Boost_LIBRARIES})
