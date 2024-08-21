#include <gtest/gtest.h>
#include <numeric>
#include <zsu/zsu.hpp>
#include "utility.hpp"

TEST(read, read_throws_on_invalid_path) {
  EXPECT_THROW(zsu::read("invalid path"), std::filesystem::filesystem_error);
}

TEST(read, read_zsu_file_containing_ms_firmwares) {
  auto zsu_file{
    zsu::read(source_location_parent_path() / "../data/MS_4.235.0.zsu")};

  EXPECT_EQ(zsu_file.info.id, "DF");
  EXPECT_EQ(zsu_file.info.version, 1);
  EXPECT_EQ(size(zsu_file.firmwares), 44uz);

  // Find MS450 (ID 0x06043200)
  auto ms450_firmware{*std::ranges::find_if(
    zsu_file.firmwares, [](auto&& fw) { return fw.id == 0x06043200u; })};
  EXPECT_EQ(ms450_firmware.id, 0x06043200u);
  EXPECT_EQ(ms450_firmware.type, 3);
  EXPECT_EQ(ms450_firmware.bl_type, 2);
  EXPECT_EQ(ms450_firmware.iv,
            (zsu::IV{148u, 157u, 18u, 87u, 129u, 92u, 108u, 100u}));
  EXPECT_GT(
    std::accumulate(cbegin(ms450_firmware.bin), cend(ms450_firmware.bin), 0u),
    0u);
}

TEST(read, read_zsu_file_containing_mx_firmwares) {
  auto zsu_file{
    zsu::read(source_location_parent_path() / "../data/DS230503.zsu")};

  EXPECT_EQ(zsu_file.info.id, "DF");
  EXPECT_EQ(zsu_file.info.version, 1);
  EXPECT_EQ(size(zsu_file.firmwares), 92uz);

  // Find MX645 (ID 0xDD)
  auto mx645_firmware{*std::ranges::find_if(
    zsu_file.firmwares, [](auto&& fw) { return fw.id == 0xDDu; })};
  EXPECT_EQ(mx645_firmware.id, 0xDDu);
  EXPECT_EQ(mx645_firmware.type, 2);
  EXPECT_FALSE(mx645_firmware.bl_type);
  EXPECT_FALSE(mx645_firmware.iv);
  EXPECT_GT(
    std::accumulate(cbegin(mx645_firmware.bin), cend(mx645_firmware.bin), 0u),
    0u);
}