set(EXAMPLE_CONFIG_FILES
    "../../config/vsomeip.json"
    "../../config/vsomeip-local.json"
)

find_package(vsomeip3 3.5.5 REQUIRED)
find_package(Boost)

include_directories(
    ${Boost_INCLUDE_DIR}
    ${VSOMEIP_INCLUDE_DIRS}
)

add_executable(server server.cpp )
target_link_libraries(server vsomeip3 ${Boost_LIBRARIES} )

add_executable(client client.cpp )
target_link_libraries(client vsomeip3 ${Boost_LIBRARIES})

