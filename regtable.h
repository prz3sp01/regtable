/**
 * @file regtable.h
 * @brief Zero-heap, single-header C library for hardware register inspection and formatted CLI tables.
 * @author Karol prz3sp01 Przespolewski
 * @version 1.1
 * @date 2026-09-30
 * @license MIT
 */

#ifndef REGTABLE_H
#define REGTABLE_H

/* --- Version Information --- */
#define REGTABLE_VERSION_MAJOR 1
#define REGTABLE_VERSION_MINOR 1
#define REGTABLE_VERSION_STR "1.1"

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

/* --- Display Format Flags --- */
#define F_BIN (1U << 0) /* Binary representation with byte separation */
#define F_HEX (1U << 1) /* Hexadecimal format (0x...) */
#define F_DEC (1U << 2) /* Unsigned decimal format */

/* =============================================================================
 * STYLE 1: Pure ASCII (7-bit clean, UART, serial consoles, headless setups)
 * ============================================================================= */
#define TBL_ASCII_HEAD(title)                                                                                          \
    printf("+---------------------------+----------------------------------------------+\n"                            \
           "| %-25.25s | VALUE / REGISTER                             |\n"                                             \
           "+---------------------------+----------------------------------------------+\n",                           \
           (title))
#define TBL_ASCII_ROW(k, v) printf("| %-25.25s | %44s |\n", (k), (v))
#define TBL_ASCII_FOOT() printf("+---------------------------+----------------------------------------------+\n")

/* =============================================================================
 * STYLE 2: Single-line UTF-8 (Clean, thin modern border)
 * ============================================================================= */
#define TBL_SINGLE_HEAD(title)                                                                                         \
    printf("┌───────────────────────────┬──────────────────────────────────────────────┐\n"                            \
           "│ %-25.25s │ VALUE / REGISTER                             │\n"                                             \
           "├───────────────────────────┼──────────────────────────────────────────────┤\n",                           \
           (title))
#define TBL_SINGLE_ROW(k, v) printf("│ %-25.25s │ %44s │\n", (k), (v))
#define TBL_SINGLE_FOOT() printf("└───────────────────────────┴──────────────────────────────────────────────┘\n")

/* =============================================================================
 * STYLE 3: Double-line UTF-8 (Industrial, retro DOS/BIOS aesthetic)
 * ============================================================================= */
#define TBL_DOUBLE_HEAD(title)                                                                                         \
    printf("╔═══════════════════════════╦══════════════════════════════════════════════╗\n"                            \
           "║ %-25.25s ║ VALUE / REGISTER                             ║\n"                                             \
           "╠═══════════════════════════╬══════════════════════════════════════════════╣\n",                           \
           (title))
#define TBL_DOUBLE_ROW(k, v) printf("║ %-25.25s ║ %44s ║\n", (k), (v))
#define TBL_DOUBLE_FOOT() printf("╚═══════════════════════════╩══════════════════════════════════════════════╝\n")

/* =============================================================================
 * STYLE 4: Rounded Corners UTF-8 (Modern CLI / TUI interface)
 * ============================================================================= */
#define TBL_ROUND_HEAD(title)                                                                                          \
    printf("╭───────────────────────────┬──────────────────────────────────────────────╮\n"                            \
           "│ %-25.25s │ VALUE / REGISTER                             │\n"                                             \
           "├───────────────────────────┼──────────────────────────────────────────────┤\n",                           \
           (title))
#define TBL_ROUND_ROW(k, v) printf("│ %-25.25s │ %44s │\n", (k), (v))
#define TBL_ROUND_FOOT() printf("╰───────────────────────────┴──────────────────────────────────────────────╯\n")

/* =============================================================================
 * STYLE 5: Markdown Table (Direct copy-paste into technical reports and logs)
 * ============================================================================= */
#define TBL_MD_HEAD(title)                                                                                             \
    printf("| %-25.25s | VALUE / REGISTER                             |\n"                                             \
           "|:--------------------------|---------------------------------------------:|\n",                           \
           (title))
#define TBL_MD_ROW(k, v) printf("| %-25.25s | %44s |\n", (k), (v))
#define TBL_MD_FOOT() printf("|---------------------------+----------------------------------------------|\n")

/* =============================================================================
 * STYLE 6: Wavy / Wave ASCII (Retro console style with ~ and :)
 * ============================================================================= */
#define TBL_WAVE_HEAD(title)                                                                                           \
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"                           \
           ": %-25.25s : VALUE / REGISTER                             :\n"                                             \
           "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n",                          \
           (title))
#define TBL_WAVE_ROW(k, v) printf(": %-25.25s : %44s :\n", (k), (v))
#define TBL_WAVE_FOOT() printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n")

/* =============================================================================
 * STYLE 7: Slash (Hatched aesthetic using / and |)
 * ============================================================================= */
#define TBL_SLASH_HEAD(title)                                                                                          \
    printf("/////////////////////////////////////////////////////////////////////////////\n"                           \
           "| %-25.25s | VALUE / REGISTER                             |\n"                                             \
           "/////////////////////////////////////////////////////////////////////////////\n",                          \
           (title))
#define TBL_SLASH_ROW(k, v) printf("| %-25.25s | %44s |\n", (k), (v))
#define TBL_SLASH_FOOT() printf("/////////////////////////////////////////////////////////////////////////////\n")

/* =============================================================================
 * STYLE 8: Hashes (Heavy industrial console look using #)
 * ============================================================================= */
#define TBL_HASH_HEAD(title)                                                                                           \
    printf("#############################################################################\n"                           \
           "# %-25.25s # VALUE / REGISTER                             #\n"                                             \
           "#############################################################################\n",                          \
           (title))
#define TBL_HASH_ROW(k, v) printf("# %-25.25s # %44s #\n", (k), (v))
#define TBL_HASH_FOOT() printf("#############################################################################\n")

/* Default Aliases (pointing to Single-line UTF-8) */
#define TBL_HEAD(title) TBL_SINGLE_HEAD(title)
#define TBL_ROW_STR(k, v) TBL_SINGLE_ROW(k, v)
#define TBL_FOOT() TBL_SINGLE_FOOT()

    /* Internal Value Formatter */
    static inline void _tbl_format_val(char *buf, size_t buf_sz, uint32_t val, uint8_t bits, uint8_t flags)
    {
        int len = 0;
        if (flags & F_DEC)
        {
            len += snprintf(buf + len, buf_sz - len, "%u ", (unsigned int)val);
        }
        if (flags & F_HEX)
        {
            if (bits <= 8)
                len += snprintf(buf + len, buf_sz - len, "0x%02X ", (uint8_t)val);
            else if (bits <= 16)
                len += snprintf(buf + len, buf_sz - len, "0x%04X ", (uint16_t)val);
            else
                len += snprintf(buf + len, buf_sz - len, "0x%08X ", val);
        }
        if (flags & F_BIN)
        {
            len += snprintf(buf + len, buf_sz - len, "b");
            /* Jeśli jest też HEX lub DEC, nie dodajemy spacji między bajtami dla 32-bit */
            int add_spaces = !(bits == 32 && (flags & (F_HEX | F_DEC)));
            for (int8_t b = bits - 1; b >= 0; b--)
            {
                if (len < (int)buf_sz - 2)
                {
                    buf[len++] = (val & (1UL << b)) ? '1' : '0';
                    if (add_spaces && b % 8 == 0 && b != 0)
                        buf[len++] = ' ';
                }
            }
            buf[len] = '\0';
        }
    }

    /* Internal Pointer Formatter */
    static inline void _tbl_format_ptr(char *buf, size_t buf_sz, const void *ptr, uint8_t deref_bytes)
    {
        if (ptr == NULL)
        {
            snprintf(buf, buf_sz, "(NULL)");
            return;
        }

        int len = 0;
#if UINTPTR_MAX == 0xFFFFFFFF
        len = snprintf(buf, buf_sz, "0x%08tX", (uintptr_t)ptr);
#else
    len = snprintf(buf, buf_sz, "0x%016tX", (uintptr_t)ptr);
#endif

        if (deref_bytes == 8 && len < (int)buf_sz - 1)
        {
            snprintf(buf + len, buf_sz - len, " -> 0x%02X", *(const uint8_t *)ptr);
        }
        else if (deref_bytes == 16 && len < (int)buf_sz - 1)
        {
            snprintf(buf + len, buf_sz - len, " -> 0x%04X", *(const uint16_t *)ptr);
        }
        else if (deref_bytes == 32 && len < (int)buf_sz - 1)
        {
            snprintf(buf + len, buf_sz - len, " -> 0x%08X", *(const uint32_t *)ptr);
        }
    }

/* Default Style Row Macros */
#define TBL_ROW8(k, val, flg)                                                                                          \
    do                                                                                                                 \
    {                                                                                                                  \
        char _b[64];                                                                                                   \
        _tbl_format_val(_b, sizeof(_b), (uint8_t)(val), 8, (flg));                                                     \
        TBL_SINGLE_ROW(k, _b);                                                                                         \
    } while (0)
#define TBL_ROW16(k, val, flg)                                                                                         \
    do                                                                                                                 \
    {                                                                                                                  \
        char _b[64];                                                                                                   \
        _tbl_format_val(_b, sizeof(_b), (uint16_t)(val), 16, (flg));                                                   \
        TBL_SINGLE_ROW(k, _b);                                                                                         \
    } while (0)
#define TBL_ROW32(k, val, flg)                                                                                         \
    do                                                                                                                 \
    {                                                                                                                  \
        char _b[64];                                                                                                   \
        _tbl_format_val(_b, sizeof(_b), (uint32_t)(val), 32, (flg));                                                   \
        TBL_SINGLE_ROW(k, _b);                                                                                         \
    } while (0)
#define TBL_ROW_PTR(k, p)                                                                                              \
    do                                                                                                                 \
    {                                                                                                                  \
        char _b[64];                                                                                                   \
        _tbl_format_ptr(_b, sizeof(_b), (const void *)(p), 0);                                                         \
        TBL_SINGLE_ROW(k, _b);                                                                                         \
    } while (0)
#define TBL_ROW_PTR_DEREF8(k, p)                                                                                       \
    do                                                                                                                 \
    {                                                                                                                  \
        char _b[64];                                                                                                   \
        _tbl_format_ptr(_b, sizeof(_b), (const void *)(p), 8);                                                         \
        TBL_SINGLE_ROW(k, _b);                                                                                         \
    } while (0)
#define TBL_ROW_PTR_DEREF16(k, p)                                                                                      \
    do                                                                                                                 \
    {                                                                                                                  \
        char _b[64];                                                                                                   \
        _tbl_format_ptr(_b, sizeof(_b), (const void *)(p), 16);                                                        \
        TBL_SINGLE_ROW(k, _b);                                                                                         \
    } while (0)
#define TBL_ROW_PTR_DEREF32(k, p)                                                                                      \
    do                                                                                                                 \
    {                                                                                                                  \
        char _b[64];                                                                                                   \
        _tbl_format_ptr(_b, sizeof(_b), (const void *)(p), 32);                                                        \
        TBL_SINGLE_ROW(k, _b);                                                                                         \
    } while (0)

/* Explicit Style Selection Macros */
#define TBL_STYLE_ROW8(style, k, val, flg)                                                                             \
    do                                                                                                                 \
    {                                                                                                                  \
        char _b[64];                                                                                                   \
        _tbl_format_val(_b, sizeof(_b), (uint8_t)(val), 8, (flg));                                                     \
        TBL_##style##_ROW(k, _b);                                                                                      \
    } while (0)
#define TBL_STYLE_ROW16(style, k, val, flg)                                                                            \
    do                                                                                                                 \
    {                                                                                                                  \
        char _b[64];                                                                                                   \
        _tbl_format_val(_b, sizeof(_b), (uint16_t)(val), 16, (flg));                                                   \
        TBL_##style##_ROW(k, _b);                                                                                      \
    } while (0)
#define TBL_STYLE_ROW32(style, k, val, flg)                                                                            \
    do                                                                                                                 \
    {                                                                                                                  \
        char _b[64];                                                                                                   \
        _tbl_format_val(_b, sizeof(_b), (uint32_t)(val), 32, (flg));                                                   \
        TBL_##style##_ROW(k, _b);                                                                                      \
    } while (0)
#define TBL_STYLE_ROW_PTR(style, k, p)                                                                                 \
    do                                                                                                                 \
    {                                                                                                                  \
        char _b[64];                                                                                                   \
        _tbl_format_ptr(_b, sizeof(_b), (const void *)(p), 0);                                                         \
        TBL_##style##_ROW(k, _b);                                                                                      \
    } while (0)
#define TBL_STYLE_ROW_PTR_DEREF8(style, k, p)                                                                          \
    do                                                                                                                 \
    {                                                                                                                  \
        char _b[64];                                                                                                   \
        _tbl_format_ptr(_b, sizeof(_b), (const void *)(p), 8);                                                         \
        TBL_##style##_ROW(k, _b);                                                                                      \
    } while (0)
#define TBL_STYLE_ROW_PTR_DEREF16(style, k, p)                                                                         \
    do                                                                                                                 \
    {                                                                                                                  \
        char _b[64];                                                                                                   \
        _tbl_format_ptr(_b, sizeof(_b), (const void *)(p), 16);                                                        \
        TBL_##style##_ROW(k, _b);                                                                                      \
    } while (0)
#define TBL_STYLE_ROW_PTR_DEREF32(style, k, p)                                                                         \
    do                                                                                                                 \
    {                                                                                                                  \
        char _b[64];                                                                                                   \
        _tbl_format_ptr(_b, sizeof(_b), (const void *)(p), 32);                                                        \
        TBL_##style##_ROW(k, _b);                                                                                      \
    } while (0)

#ifdef __cplusplus
}
#endif

#endif /* REGTABLE_H */