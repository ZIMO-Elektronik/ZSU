#include <gtest/gtest.h>
#include <zsu/zsu.hpp>

TEST(file, default_initialized_members) { static constexpr zsu::File file; }