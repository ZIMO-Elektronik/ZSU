#include <algorithm>
#include <iostream>
#include <zsu/zsu.hpp>

int main() {
  auto zsu_file{zsu::read("./data/MS-5.3.1.zsu")};

  // Print file format version
  std::cout << "ZSU file version " << zsu_file.info.version << "\n";

  // Print number of found device firmwares
  std::cout << "Number of firmwares " << size(zsu_file.firmwares) << "\n";

  // Print found device IDs
  std::cout << "Found device IDs: ";
  std::ranges::for_each(zsu_file.firmwares, [](auto&& fw) {
    std::cout << std::hex << fw.id << " ";
  });
}
