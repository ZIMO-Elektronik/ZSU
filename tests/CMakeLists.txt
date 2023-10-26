include(GoogleTest)

file(GLOB_RECURSE SRC *.cpp)
add_executable(ZSUTests ${SRC})

sanitize("address,undefined")

target_common_warnings(ZSUTests PRIVATE)

cpmaddpackage("gh:google/googletest#main")

target_link_libraries(ZSUTests PRIVATE ZSU::ZSU GTest::gtest_main GTest::gmock)

gtest_discover_tests(ZSUTests)
