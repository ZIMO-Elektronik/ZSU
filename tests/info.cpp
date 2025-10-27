#include <gtest/gtest.h>
#include <zsu/zsu.hpp>

TEST(info, default_initialized_members) { static constexpr zsu::Info info; }
