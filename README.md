# ZSU

[![build](https://github.com/ZIMO-Elektronik/ZSU/actions/workflows/build.yml/badge.svg)](https://github.com/ZIMO-Elektronik/ZSU/actions/workflows/build.yml) [![tests](https://github.com/ZIMO-Elektronik/ZSU/actions/workflows/tests.yml/badge.svg)](https://github.com/ZIMO-Elektronik/ZSU/actions/workflows/tests.yml)

<img src="data/images/logo.png" width="15%" align="right">

ZSU is a German acronym for ZIMO-Sammel-Update (ZIMO-Collective-Update), a file format for firmware updates. The format supports multiple, optionally [Salsa20](https://github.com/ZIMO-Elektronik/Salsa20) encrypted, firmwares for a variety of target devices. ZSU files are currently used by the following products:
- Command stations
  - [ZIMO MXULF](http://www.zimo.at/web2010/products/InfMXULF_EN.htm)
  - [Z21](https://www.z21.eu/en)
- Decoders
  - [ZIMO MN decoders](http://www.zimo.at/web2010/products/mn-nicht-sound-decoder_EN.htm)
  - [ZIMO Small-](http://www.zimo.at/web2010/products/ms-sound-decoder_EN.htm) and [large-scale MS decoders](http://www.zimo.at/web2010/products/ms-sound-decoder-grossbahn_EN.htm)
  - [ZIMO MX function decoders](http://www.zimo.at/web2010/products/funktionsdecoder_EN.htm)
  - [ZIMO Small-](http://www.zimo.at/web2010/products/lokdecoder_EN.htm) and [large-scale MX decoders](http://www.zimo.at/web2010/products/lokdecodergrosse_EN.htm)
  - [ZIMO accessory decoders](http://www.zimo.at/web2010/products/zubehoerdecoder_EN.htm)

<details>
  <summary>Table of contents</summary>
  <ol>
    <li><a href="#file-format-specification">File format specification</a></li>
      <ul>
        <li><a href="#header">Header</a></li>
        <li><a href="#firmware-data">Firmware data</a></li>
      </ul>
    <li><a href="#getting-started">Getting started</a></li>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
        <li><a href="#build">Build</a></li>
      </ul>
    <li><a href="#usage">Usage</a></li>
  </ol>
</details>

## File format specification
A ZSU file consists of a header and a binary blob of firmware data. The header format is essentially [CSV](https://en.wikipedia.org/wiki/Comma-separated_values) text with a tab `\t` as a delimiter and a semicolon `;` as an EOL character. The first line contains file information, the following lines contain firmware entries. A colon `:` indicates the end of the header.

### Header
| Tab seperated values | Encoding | Description                                                                                                        |
| -------------------- | -------- | ------------------------------------------------------------------------------------------------------------------ |
| DF                   | ASCII    | ZSU file identifier                                                                                                |
| 1                    | ASCII    | Header version                                                                                                     |
| ;                    | ASCII    | Firmware info start identifier                                                                                     |
| 100938240            | ASCII    | 4 byte device ID as decimal ASCII<br/>(example: 0x06043200 for MS450-0)                                            |
| 159                  | ASCII    | Offset to firmware data in file<br/>(-1 due to "legacy bug", the actual start address would be A0 in this example) |
| 145792               | ASCII    | Length of firmware data in file                                                                                    |
| MS-450               | ASCII    | Device name                                                                                                        |
| 1                    | ASCII    | Version                                                                                                            |
| 17                   | ASCII    | Subversion                                                                                                         |
| 3                    | ASCII    | Microcontroller<br/>1 = PIC16<br/>2 = PIC18<br/>3 = STM32                                                          |
| 2                    | ASCII    | Bootloader type **(optional)**<br/>1 = MX82x family<br/>2 =  STM                                                   |
| 9465695272716466818  | ASCII    | 8 byte encryption IV as decimal ASCII **(optional)**                                                               |
| :                    | ASCII    | Header end identifier                                                                                              |

### Firmware data
Binary, optionally encrypted, firmware data.

| Value or example | Encoding | Description   |
| ---------------- | -------- | ------------- |
| 0x00             | Binary   | Firmware data |
| ...              | Binary   | ...           |

### Examples
Example of latest [MX decoder ZSU file](./data/DS230503.zsu)
```sh
DF	1;
198	4330	52226	Flm_E69	40	20	2;
142	56560	34818	MDS_442	40	20	2;
152	91382	51458	M152	40	20	2;
# ...
165	3172876	52226	DU65	40	20	2:
```

Example of latest [MS decoder ZSU file](./data/MS_4.235.0.zsu)
```sh
DF	1;
2081506816	3135	117696	MN170-0_4	4	235	3	2	10367926798890783065;
2131841024	120831	117888	MN180-0_4	4	235	3	2	14087017121960536323;
2098397184	238719	117888	MN300-0_4	4	235	3	2	2968593227443176535;
# ...
184549633	6489791	147648	MS001-1_4	4	235	3	2	1389861890318814935:
```

## Getting started
### Prerequisites
- C++23 compatible compiler
- [CMake](https://cmake.org/) ( >= 3.25 )

### Installation
This library is meant to be consumed with CMake.

```cmake
# Either by including it with CPM
cpmaddpackage("gh:ZIMO-Elektronik/ZSU@0.0.1")

# or the FetchContent module
FetchContent_Declare(
  ZSU
  GIT_REPOSITORY https://github.com/ZIMO-Elektronik/ZSU
  GIT_TAG v0.0.1)

target_link_libraries(YourTarget PRIVATE ZSU::ZSU)
```

### Build
If the build is running as a top-level CMake project then tests and a small example will be generated.
```sh
cmake -Bbuild
cmake --build build --target ZSUExamples
```

## Usage
```cpp
// Read .zsu file
auto zsu_file{zsu::read("./data/MS_4.235.0.zsu")};

// Print file format version
std::cout << "ZSU file version " << zsu_file.info.version << "\n";

// Print number of found device firmwares
std::cout << "Number of firmwares " << size(zsu_file.firmwares) << "\n";

// Print found device IDs
std::cout << "Found device IDs: ";
std::ranges::for_each(zsu_file.firmwares, [](auto&& fw) {
  std::cout << std::hex << fw.id << " ";
});
```