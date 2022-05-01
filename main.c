#include <stdio.h>
#include <stdlib.h>

#include "gb_emu.h"

int main(int argc, char **argv)
{
    gb_emu_t *gb_emu = malloc(sizeof(gb_emu_t));

    if (cart_load(gb_emu->rom, argv[1]) < 0) {
        return -1;
    }

    return 0;
}
