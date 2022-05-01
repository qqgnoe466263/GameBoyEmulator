#ifndef _MEM_H_
#define _MEM_H_

#include "common.h"

#define ROM_BANK00  0x3fff
#define ROM_BANKNN  0x7fff

typedef struct cartridge_type {
	u8 type[0x20];
} cart_type_t;

/* 0x0100-0x014F */
typedef struct cartridge_header {
    u8 entry_point[0x4];        // 0100-0103
    u8 nintendo_logo[0x30];     // 0104-0133
    u8 title[0x10];             // 0134-0143
    u8 new_licensee_code[0x2];  // 0144-0145
    u8 sgb_flag;                // 0146
    u8 cartridge_type;          // 0147
    u8 rom_size;                // 0148
    u8 ram_size;                // 0149
    u8 destination_code;        // 014a
    u8 old_licensee_code;       // 014b
    u8 mask_rom_version_number; // 014c
    u8 header_checksum;         // 014d
} cart_header_t; 

s8 cart_load(u8 *rom, char *filename);

#endif
