# regtable.h

A lightweight, zero-heap, single-header C library for hardware register inspection and formatted CLI tables.

Designed specifically for embedded firmware developers, industrial automation engineers (PLC/fieldbus), and CLI tooling where dynamic memory allocation (`malloc`/`free`) is forbidden or undesirable.

## Key Features

- **Header-Only:** Single file (`regtable.h`), zero external dependencies beyond standard C99 libc.

- **Zero-Heap:** Pure stack buffer operations. No dynamic memory allocation, preventing heap fragmentation.

- **Hardware Register Formatting:** Native inspection for 8-bit, 16-bit, and 32-bit registers with automatic byte-aligned binary separation (`b10100101 01011010`).

- **Flexible Flags:** Select individual or combined formats (`F_DEC`, `F_HEX`, `F_BIN`).

- **6 Visual Styles:** ASCII (UART/serial), Single-line UTF-8, Double-line UTF-8 (DOS/BIOS), Rounded UTF-8, Markdown, and Wave.

- **C and C++ Compatible:** Safe `extern "C"` wrappers.

## Table Styles

### 1. ASCII (7-bit clean, UART serial consoles)

Plaintext

```
+---------------------------+--------------------------------------------+
| 1. ASCII SERIAL LINK      | VALUE / REGISTER                           |
+---------------------------+--------------------------------------------+
| Protocol                  |                         RS485 / Modbus RTU |
| IO Status (8b: HEX+BIN)   |                             0xC3 b11000011 |
| Cycle Counter (32b: DEC)  |                                     148920 |
+---------------------------+--------------------------------------------+
```

### 2. Single-Line UTF-8 (Modern & Clean)

Plaintext

```
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

Plaintext

```
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

Plaintext

```
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

Plaintext

```
| 5. MARKDOWN FORMAT        | VALUE / REGISTER                           |
|:--------------------------|-------------------------------------------:|
| Frame Validation          |                                     CRC_OK |
| Status Flags (8b: BIN)    |                                  b11000011 |
| Speed (16b: DEC+HEX)      |                                1000 0x03E8 |
| Mask Register (32b: HEX)  |                                 0x00FF0F01 |
|---------------------------+--------------------------------------------|
```

### 6. Wave Style (Retro Terminal)

Plaintext

```
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
: 6. WAVE CONSOLE STYLE     : VALUE / REGISTER                           :
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
: Signal Quality            :                                     98.5 % :
: IO Bits (8b: FULL)        :                         195 0xC3 b11000011 :
: Encoder (16b: FULL)       :                  0x3F1F b00111111 00011111 :
: Raw Bits (32b: BIN)       :       b10100101 01011010 00010010 00110100 :
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
```

## Quick Start

1. Copy `regtable.h` into your project's include path.

2. Include the header in your C or C++ file:

C

```
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

## Building and Running the Demo

Bash

```
make run
```

## License

This project is licensed under the MIT License - see the LICENSE file for details.
