#include <stdio.h>
#include <stdint.h>
#include "regtable.h"

int main(void) {
    /* Sample hardware registers and variables */
    uint8_t  io_status   = 0xC3;
    uint8_t  fault_code  = 0x1F;
    uint16_t encoder_pos = 0x3F1F;
    uint16_t bus_speed   = 1000;
    uint32_t alarm_mask  = 0xA55A1234;
    uint32_t cycle_count = 148920;

    /* 1. ASCII STYLE (Universal, 7-bit, Serial/UART) */
    TBL_ASCII_HEAD("1. ASCII SERIAL LINK");
    TBL_ASCII_ROW("Protocol", "RS485 / Modbus RTU");
    TBL_STYLE_ROW8(ASCII, "IO Status (8b: HEX+BIN)", io_status, F_HEX | F_BIN);
    TBL_STYLE_ROW32(ASCII, "Cycle Counter (32b: DEC)", cycle_count, F_DEC);
    TBL_ASCII_FOOT();
    putchar('\n');

    /* 2. SINGLE-LINE UTF-8 (Clean, Modern Default) */
    TBL_SINGLE_HEAD("2. SINGLE LINE UTF-8");
    TBL_SINGLE_ROW("Fieldbus", "PROFINET IRT");
    TBL_STYLE_ROW16(SINGLE, "Baudrate (16b: DEC+HEX)", bus_speed, F_DEC | F_HEX);
    TBL_STYLE_ROW16(SINGLE, "Encoder (16b: FULL)", encoder_pos, F_DEC | F_HEX | F_BIN);
    TBL_STYLE_ROW32(SINGLE, "Alarm Register (32b: HEX)", alarm_mask, F_HEX);
    TBL_SINGLE_FOOT();
    putchar('\n');

    /* 3. DOUBLE-LINE UTF-8 (Industrial, DOS/BIOS Style) */
    TBL_DOUBLE_HEAD("3. DOUBLE LINE DRIVE");
    TBL_DOUBLE_ROW("Drive State", "OPERATIONAL");
    TBL_STYLE_ROW8(DOUBLE, "Fault Register (8b: BIN)", fault_code, F_BIN);
    TBL_STYLE_ROW16(DOUBLE, "Raw Position (16b: HEX)", encoder_pos, F_HEX);
    TBL_STYLE_ROW32(DOUBLE, "Alarm Register (32b: BIN)", alarm_mask, F_BIN);
    TBL_DOUBLE_FOOT();
    putchar('\n');

    /* 4. ROUNDED CORNERS UTF-8 (Modern CLI / TUI) */
    TBL_ROUND_HEAD("4. ROUNDED CORNERS");
    TBL_ROUND_ROW("Target MCU", "STM32F4 / ARM Cortex-M4");
    TBL_STYLE_ROW8(ROUND, "Error Code (8b: DEC+HEX)", fault_code, F_DEC | F_HEX);
    TBL_STYLE_ROW16(ROUND, "Encoder (16b: HEX+BIN)", encoder_pos, F_HEX | F_BIN);
    TBL_STYLE_ROW32(ROUND, "Up Time (32b: DEC)", 864200, F_DEC);
    TBL_ROUND_FOOT();
    putchar('\n');

    /* 5. MARKDOWN STYLE (Documentation & Logging) */
    TBL_MD_HEAD("5. MARKDOWN FORMAT");
    TBL_MD_ROW("Frame Validation", "CRC_OK");
    TBL_STYLE_ROW8(MD, "Status Flags (8b: BIN)", io_status, F_BIN);
    TBL_STYLE_ROW16(MD, "Speed (16b: DEC+HEX)", bus_speed, F_DEC | F_HEX);
    TBL_STYLE_ROW32(MD, "Mask Register (32b: HEX)", 0x00FF0F01, F_HEX);
    TBL_MD_FOOT();
    putchar('\n');

    /* 6. WAVE STYLE (Retro TUI Console) */
    TBL_WAVE_HEAD("6. WAVE CONSOLE STYLE");
    TBL_WAVE_ROW("Signal Quality", "98.5 %");
    TBL_STYLE_ROW8(WAVE,  "IO Bits (8b: FULL)", io_status, F_DEC | F_HEX | F_BIN);
    TBL_STYLE_ROW16(WAVE, "Encoder (16b: FULL)", encoder_pos, F_DEC | F_HEX | F_BIN);
    TBL_STYLE_ROW32(WAVE, "Raw Bits (32b: BIN)", alarm_mask, F_BIN);
    TBL_WAVE_FOOT();

    return 0;
}
