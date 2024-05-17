file(GLOB_RECURSE SRC *.cpp)
add_executable(ZSUExamples ${SRC})

sanitize("address,undefined")

target_common_warnings(ZSUExamples PRIVATE)

target_link_libraries(ZSUExamples PRIVATE ZSU::ZSU)
