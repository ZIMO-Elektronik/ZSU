#include <gtest/gtest.h>
#include <zsu/zsu.hpp>

TEST(firmware, default_initialized_members) {
  static constexpr zsu::Firmware firmware;
}