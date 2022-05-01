#include <stdio.h>
#include <stdlib.h>

#include "mem.h"

/* Ref : https://gbdev.io/pandocs/The_Cartridge_Header.html#0147---cartridge-type */
static const cart_type_t cart_type[] = {
    [0] = {"ROM ONLY"},
    [1] = {"MBC1"},
    [2] = {"MBC1+RAM"},
    [3] = {"MBC1+RAM+BATTERY"},
    [5] = {"MBC2"},
    [6] = {"MBC2+BATTERY"},
    [8] = {"ROM+RAM 1"},
    [9] = {"ROM+RAM+BATTERY 1"},
    [0x0B] = {"MMM01"},
    [0x0C] = {"MMM01+RAM"},
    [0x0D] = {"MMM01+RAM+BATTERY"},
    [0x0F] = {"MBC3+TIMER+BATTERY"},
    [0x10] = {"MBC3+TIMER+RAM+BATTERY 2"},
    [0x11] = {"MBC3"},
    [0x12] = {"MBC3+RAM 2"},
    [0x13] = {"MBC3+RAM+BATTERY 2"},
    [0x19] = {"MBC5"},
    [0x1A] = {"MBC5+RAM"},
    [0x1B] = {"MBC5+RAM+BATTERY"},
    [0x1C] = {"MBC5+RUMBLE"},
    [0x1D] = {"MBC5+RUMBLE+RAM"},
    [0x1E] = {"MBC5+RUMBLE+RAM+BATTERY"},
    [0x20] = {"MBC6"},
    [0x22] = {"MBC7+SENSOR+RUMBLE+RAM+BATTERY"},
    [0xFC] = {"POCKET CAMERA"},
    [0xFD] = {"BANDAI TAMA5"},
    [0xFE] = {"HuC3"},
    [0xFF] = {"HuC1+RAM+BATTERY"},
};

s8 cart_load(u8 *rom, char *filename)
{
    FILE *f = fopen(filename, "rb");
    if (!f) {
        printf("Usage: ./gb_emu <rom>\n");
        return -1;
    }

    fseek(f, 0, SEEK_END);
    u32 file_size = ftell(f);
    fseek(f, 0, SEEK_SET);

    if (!file_size) {
        fclose(f);
        return -1;
    }

    printf("Cartridge's memory size : %d\n", file_size);

    rom = (u8 *)malloc(file_size);
    u32 r = fread(rom, 1, file_size, f);
    fclose(f);
    if (r != file_size)
        return -1;

    /* An internal information area is located
     * at $0100-014F in each cartridge.
     */
    cart_header_t *cart_hdr = (cart_header_t *)(rom + 0x100);

    /* Checksum */
    u16 x = 0;
    for (u16 i = 0x134; i <= 0x14C; i++)
        x = x - rom[i] - 1;

    printf("Cartridge loaded\n");
    printf("\tEntryPoint : 0x%x\n", *(u32 *)&cart_hdr->entry_point);
    printf("\tTitle      : %s\n", cart_hdr->title);
    printf("\tCart Type  : 0x%x(%s)\n", cart_hdr->cartridge_type,
                                        cart_type[cart_hdr->cartridge_type].type);
    printf("\tROM size   : 0x%x\n", cart_hdr->rom_size);
    printf("\tRAM size   : 0x%x\n", cart_hdr->ram_size);
    printf("\tChecksum   : 0x%x(%s)\n", cart_hdr->header_checksum,
                                        ((x & 0xff) == cart_hdr->header_checksum) 
                                        ? "PASSED" : "FAILED");
    return 0;
}
