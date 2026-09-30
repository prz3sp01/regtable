# regtable.h

### A lightweight, zero-heap, single-header C library for hardware register inspection and formatted CLI tables. Designed specifically for embedded firmware developers, industrial automation engineers (PLC/fieldbus), and CLI diagnostic tooling where dynamic memory allocation (`malloc`/`free`) is forbidden.

---

Designed specifically for embedded firmware developers, and CLI tooling where dynamic memory allocation (`malloc`/`free`) is forbidden or undesirable.

## 🚀 Key Features

- **Header-Only**: Single drop-in file (`regtable.h`), zero external dependencies beyond standard C99 `libc`.
- **Zero-Heap**: Pure stack buffer operations with no dynamic memory allocation (`malloc`/`free`), eliminating heap fragmentation risks in embedded systems.
- **Hardware Register Formatting**: Native inspection for 8-bit, 16-bit, and 32-bit registers with adaptive binary formatting (`b10100101 01011010`) that balances byte spacing based on active format flags.
- **Pointer & Memory Inspection**: Architecture-aware pointer formatting (32-bit and 64-bit systems), safe `(NULL)` handling without faults, and optional inline memory dereferencing for 8-bit, 16-bit, and 32-bit values (`DEREF8`, `DEREF16`, `DEREF32`).
- **Flexible Format Flags**: Freely selectable individual or combined value representations (`F_DEC`, `F_HEX`, `F_BIN`).
- **8 Visual Framing Styles**: ASCII (UART/serial consoles), Single-line UTF-8, Double-line UTF-8 (DOS/BIOS aesthetic), Rounded UTF-8, Markdown, Wavy ASCII, plus new industrial variants: Slash (`///`) and Hashes (`###`).
- **Strict Fixed-Width Alignment**: A guaranteed 44-character value column prevents border drift across both 32-bit targets and 64-bit host systems.
- **C and C++ Compatible**: Safe `extern "C"` wrappers for straightforward integration into both C and C++ toolchains.

---

## 🎨 Visual Table Styles

### 1. ASCII (7-bit clean, UART & Serial Terminals)

```text
+---------------------------+--------------------------------------------+
| 1. ASCII SERIAL LINK      | VALUE / REGISTER                           |
+---------------------------+--------------------------------------------+
| Protocol                  |                         RS485 / Modbus RTU |
| IO Status (8b: HEX+BIN)   |                             0xC3 b11000011 |
| Cycle Counter (32b: DEC)  |                                     148920 |
+---------------------------+--------------------------------------------+
```
### 2. Single-Line UTF-8 (Modern & Clean)

```text
┌───────────────────────────┬────────────────────────────────────────────┐
│ 2. SINGLE LINE UTF-8      │ VALUE / REGISTER                           │
├───────────────────────────┼────────────────────────────────────────────┤
│ Fieldbus                  │                               PROFINET IRT │
│ Baudrate (16b: DEC+HEX)   │                                1000 0x03E8 |
│ Encoder (16b: FULL)       │            16159 0x3F1F b00111111 00011111 │
│ Alarm Register (32b: HEX) │                                 0xA55A1234 |
└───────────────────────────┴────────────────────────────────────────────┘
```

### 3. Double-Line UTF-8 (Industrial Retro / BIOS)

```text
╔═══════════════════════════╦════════════════════════════════════════════╗
║ 3. DOUBLE LINE DRIVE      ║ VALUE / REGISTER                           ║
╠═══════════════════════════╬════════════════════════════════════════════╣
║ Drive State               ║                                OPERATIONAL ║
║ Fault Register (8b: BIN)  ║                                  b00011111 ║
║ Raw Position (16b: HEX)   ║                                     0x3F1F ║
║ Alarm Register (32b: BIN) ║       b10100101 01011010 00010010 00110100 ║
╚═══════════════════════════╩════════════════════════════════════════════╝
```

### 4. Rounded Corners UTF-8 (Modern CLI)

```text
╭───────────────────────────┬────────────────────────────────────────────╮
│ 4. ROUNDED CORNERS        │ VALUE / REGISTER                           │
├───────────────────────────┼────────────────────────────────────────────┤
│ Target MCU                │                    STM32F4 / ARM Cortex-M4 │
│ Error Code (8b: DEC+HEX)  │                                    31 0x1F │
│ Encoder (16b: HEX+BIN)    │                  0x3F1F b00111111 00011111 │
│ Up Time (32b: DEC)        │                                     864200 │
╰───────────────────────────┴────────────────────────────────────────────╯
```

### 5. Markdown Style (Documentation & Log Files)

```text
| 5. MARKDOWN FORMAT        | VALUE / REGISTER                           |
|:--------------------------|-------------------------------------------:|
| Frame Validation          |                                     CRC_OK |
| Status Flags (8b: BIN)    |                                  b11000011 |
| Speed (16b: DEC+HEX)      |                                1000 0x03E8 |
| Mask Register (32b: HEX)  |                                 0x00FF0F01 |
|---------------------------+--------------------------------------------|
```

### 6. Wave Style (Retro Terminal)

```text
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
: 6. WAVE CONSOLE STYLE     : VALUE / REGISTER                           :
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
: Signal Quality            :                                     98.5 % :
: IO Bits (8b: FULL)        :                         195 0xC3 b11000011 :
: Encoder (16b: FULL)       :                  0x3F1F b00111111 00011111 :
: Raw Bits (32b: BIN)       :       b10100101 01011010 00010010 00110100 :
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
```
### 7. Styl SLASH (/// oraz |)
```text
//////////////////////////////////////////////////////////////////////////
| 7. SLASH INDUSTRIAL       | VALUE / REGISTER                           |
//////////////////////////////////////////////////////////////////////////
| Protocol                  |                         RS485 / Modbus RTU |
| IO Status (8b: HEX+BIN)   |                             0xC3 b11000011 |
| Cycle Counter (32b: DEC)  |                                     148920 |
| Buffer Pointer (raw)      |                         0x00007FFFE0C12EBC |
| Target Register (*p)      |           0x00007FFFE0C12EBC -> 0x000021AC |
//////////////////////////////////////////////////////////////////////////
```
### 8. Styl HASHES (### oraz #)

```text
##########################################################################
# 8. HASHES AUDIT LOG       # VALUE / REGISTER                           #
##########################################################################
# Protocol                  #                         RS485 / Modbus RTU #
# IO Status (8b: HEX+BIN)   #                             0xC3 b11000011 #
# Cycle Counter (32b: DEC)  #                                     148920 #
# Buffer Pointer (raw)      #                         0x00007FFFE0C12EBC #
# Target Register (*p)      #           0x00007FFFE0C12EBC -> 0x000021AC #
##########################################################################
```

## ⚡ Quick Start

1. Copy `regtable.h` into your project's include path.

2. Include the header in your C or C++ file:

```C
#include "regtable.h"

int main(void) {
    uint8_t  inputs  = 0xC3;
    uint16_t encoder = 0x3F1F;
    uint32_t alarms  = 0xA55A1234;

    TBL_HEAD("SYSTEM DIAGNOSTICS");
    TBL_ROW_STR("Link State", "ONLINE");
    TBL_ROW8("Digital Inputs (8b)", inputs, F_HEX | F_BIN);
    TBL_ROW16("Angle Encoder (16b)", encoder, F_DEC | F_HEX | F_BIN);
    TBL_ROW32("Alarm Mask (32b)", alarms, F_HEX);
    TBL_FOOT();

    return 0;
}
```

## 🛠️ Building and Running the Demo

```bash
make run
```

## 📄 License

- **License:** [MIT License](LICENSE)
- **Copyright:** (c) 2026 Karol "prz3sp01" Przespolewski
- **Contact:** karol@przespol.eu
